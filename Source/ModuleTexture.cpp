#include "ModuleTexture.h"
#include "DirectXTex.h"


ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

// Called before render is available
bool ModuleTexture::Init()
{
	return true;
}

update_status ModuleTexture::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleTexture::Update()
{


	return UPDATE_CONTINUE;
}

update_status ModuleTexture::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTexture::CleanUp()
{

	//Destroy window
	return true;
}

DirectX::ScratchImage ModuleTexture::LoadTexture(const char* file)
{
	const size_t cSize = strlen(file) + 1;
	wchar_t* fileName = new wchar_t[cSize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, fileName, cSize, file, _TRUNCATE);

	DirectX::ScratchImage texture;
	// Try loading DDS
	HRESULT hr = DirectX::LoadFromDDSFile(fileName, DirectX::DDS_FLAGS_NONE, nullptr, texture);

	// If DDS loading fails, try loading TGA
	if (!SUCCEEDED(hr)) {
		hr = DirectX::LoadFromTGAFile(fileName, DirectX::TGA_FLAGS_NONE, nullptr, texture);
	}
	// If both DDS and TGA loading fails, try loading using WIC
	if (!SUCCEEDED(hr)) {
		hr = DirectX::LoadFromWICFile(fileName, DirectX::WIC_FLAGS_NONE, nullptr, texture);
	}

	delete[] fileName; // Remember to free the allocated memory

	return texture;
}

unsigned ModuleTexture::CreateTexture(DirectX::ScratchImage* texture)
{
	unsigned texid;
	DirectX::TexMetadata texMeta = texture->GetMetadata();
	GLint internalFormat;
	GLenum format;
	GLenum type;
	switch (texMeta.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
	glGenTextures(0, &texid);
	glBindTexture(GL_TEXTURE_2D_ARRAY, texid);
	//glTexImage2D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, 
	//	texMeta.width, texMeta.height, 0, format, type, texture.GetPixels());
	for (size_t i = 0; i < texMeta.mipLevels; ++i)
	{
		const DirectX::Image* mip = texture->GetImage(i, 0, 0);
		glTexImage2D(GL_TEXTURE_2D, i, internalFormat, mip->width, mip->height, 0, format, type, mip->pixels);
	}
	if (texMeta.mipLevels > 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, texMeta.mipLevels - 1);
	}
	return texid;
}

