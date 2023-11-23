#include "texture.h"

TextureUPtr Texture::Create(int width, int height, uint32_t format)
{
	auto texture = TextureUPtr(new Texture());
	texture->CreateTexture();
	texture->SetTextureFormat(width, height, format);
	texture->SetFilter(GL_LINEAR, GL_LINEAR);
	return std::move(texture);
}

TextureUPtr Texture::CreateFromImage(const Image *image)
{
	auto texture = TextureUPtr(new Texture());
	texture->CreateTexture();
	texture->SetTextureFromImage(image);
	return std::move(texture);
}

Texture::~Texture()
{
	if (m_texture)
		glDeleteTextures(1, &m_texture);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}

void Texture::SetTextureFormat(int width, int height, uint32_t format)
{
	m_width = width;
	m_height = height;
	m_format = format;

	glTexImage2D(GL_TEXTURE_2D, 0, m_format,
		m_width, m_height, 0,
		m_format, GL_UNSIGNED_BYTE, nullptr);
	// 마지막 인자에 nullptr을 넣으면 복사가 일어나지 않고 메모리 할당만 한다
}

void Texture::CreateTexture()
{
	glGenTextures(1, &m_texture);

	Bind();
	SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image *image)
{
	GLenum format = GL_RGBA;
	switch (image->GetChannelCount())
	{
		default: break;
		case 1: format = GL_RED; break;
		case 2: format = GL_RG; break;
		case 3: format = GL_RGB; break;
	}

	m_width = image->GetWidth();
	m_height = image->GetHeight();
	m_format = format;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		m_width, m_height, 0,
		format, GL_UNSIGNED_BYTE, image->GetData());

	//MipMap생성
	glGenerateMipmap(GL_TEXTURE_2D);
}

CubeTextureUPtr CubeTexture::CreateFromImages(const std::vector<Image*>& images)
{
	auto texture = CubeTextureUPtr(new CubeTexture());
	if (!texture->InitFromImages(images))
		return nullptr;
	return std::move(texture);
}

CubeTexture::~CubeTexture()
{
	if (m_texture)
		glDeleteTextures(1, &m_texture);
}

void CubeTexture::Bind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}

bool CubeTexture::InitFromImages(const std::vector<Image*>& images)
{
	glGenTextures(1, &m_texture);
	Bind();

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (uint32_t i = 0; i < (uint32_t)images.size(); i++)
	{
		auto image = images[i];
		GLenum format = GL_RGBA;
		switch (image->GetChannelCount())
		{
			default: break;
			case 1: format = GL_RED; break;
			case 2: format = GL_RG; break;
			case 3: format = GL_RGB; break;
		}

		// 6방향의 image를 GPU에 복사
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB,
			image->GetWidth(), image->GetHeight(), 0,
			format, GL_UNSIGNED_BYTE,
			image->GetData());
	}
	return true;
}