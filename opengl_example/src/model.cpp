#include "model.h"

ModelUPtr Model::Load(const std::string& filename)
{
	auto model = ModelUPtr(new Model());
	if (!model->LoadByAssimp(filename))
		return nullptr;
	return std::move(model);
}

bool Model::LoadByAssimp(const std::string& filename)
{
	Assimp::Importer importer;
	// scene 생성
	auto scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	// scene 오류 처리
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		SPDLOG_ERROR("failed to load model: {}", filename);
		return false;
	}

// material 처리 start
	// .obj가 있는 directory의 위치 찾기
	// ./model/backpack.obj에서 substr로 ./model을 추출 
	auto dirname = filename.substr(0, filename.find_last_of("/"));
	// lamda closer 형식의 함수 정의 (TexturePtr 반환)
	// [&]는 함수 밖에서 정의된 변수에 접근을 가능하게 해준다
	// (아래의 경우에서는 dirname에 접근이 가능)
	auto LoadTexture = [&](aiMaterial * material, aiTextureType type) -> TexturePtr 
	{
		// 해당 type의 image file이 존재하는지 확인
		if (material->GetTextureCount(type) <= 0)
			return nullptr;
		// 해당 type의 image 파일 이름을 filepath에 받아옴
		aiString filepath;
		material->GetTexture(type, 0, &filepath);
		// filepath를 directory 경로와 합체해서 load
		auto image = Image::Load(fmt::format("{}/{}", dirname, filepath.C_Str()));
		if (!image)
			return nullptr;
		// texture 번호 반환
		return Texture::CreateFromImage(image.get());
	};

	// scene 안에있는 material 개수만큼 반복
	for (uint32_t i = 0; i < scene->mNumMaterials; i++)
	{
		// scene의 i번째 material 정보 get
		auto material = scene->mMaterials[i];
		// 새로운 material pointer 생성
		auto glMaterial = Material::Create();
		// scene의 material diffuse, specular texture를 생성 
		glMaterial->diffuse = LoadTexture(material, aiTextureType_DIFFUSE);
		glMaterial->specular = LoadTexture(material, aiTextureType_SPECULAR);
		// 생성한 texture들을 m_materials에 저장
		m_materials.push_back(std::move(glMaterial));
	}
// material 처리 end

	// scene->mRootNode 부터 재귀적으로 처리
	ProcessNode(scene->mRootNode, scene);
	return true;
}

void Model::ProcessNode(aiNode *node, const aiScene *scene)
{
	// aiNode 구조체가 가진 aiMesh 처리
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		// node에서 scene에 있는 mMeshes의 index를 얻음
		auto meshIndex = node->mMeshes[i];
		// 얻은 index를 통해 mesh 찾기
		auto mesh = scene->mMeshes[meshIndex];
		// mesh 값을 우리의 구조체에 넣어서 보관
		ProcessMesh(mesh, scene);
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
		ProcessNode(node->mChildren[i], scene);
}

void Model::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	SPDLOG_INFO("process mesh: {}, #vert: {}, #face: {}",
		mesh->mName.C_Str(), mesh->mNumVertices, mesh->mNumFaces);

	std::vector<Vertex> vertices;
	vertices.resize(mesh->mNumVertices);
	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		auto& v = vertices[i];
		v.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		v.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		v.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}

	std::vector<uint32_t> indices;
	indices.resize(mesh->mNumFaces * 3);
	// face의 개수 = triangle 개수
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		indices[3 * i] = mesh->mFaces[i].mIndices[0];
		indices[3 * i + 1] = mesh->mFaces[i].mIndices[1];
		indices[3 * i + 2] = mesh->mFaces[i].mIndices[2];
	}

	auto glMesh = Mesh::Create(vertices, indices, GL_TRIANGLES);
	// mesh의 mMaterialINdex가 0이상이면 이 mesh는 material을 갖고 있으므로
	// 해당 material값을 setting 해준다. 
	if (mesh->mMaterialIndex >= 0)
		glMesh->SetMaterial(m_materials[mesh->mMaterialIndex]);
	m_meshes.push_back(std::move(glMesh));
}

void Model::Draw(const Program *program) const
{
	for (auto& mesh: m_meshes)
		mesh->Draw(program);
}