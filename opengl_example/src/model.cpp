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
	m_meshes.push_back(std::move(glMesh));
}

void Model::Draw() const
{
	for (auto& mesh: m_meshes)
		mesh->Draw();
}