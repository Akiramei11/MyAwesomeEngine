#include "ModelObject.h"
#include "ModuleTexture.h"
#include "Application.h"


ModelObject::ModelObject()
{

}
ModelObject::~ModelObject()
{

}
void ModelObject::Load(const char* assetFileName)
{
	tinygltf::TinyGLTF gltfContext;
	tinygltf::Model srcModel;
	std::string error, warning;
	bool loadOk = gltfContext.LoadASCIIFromFile(&srcModel, &error, &warning, assetFileName);
	if (!loadOk)
	{
		LOG("Error loading %s: %s", assetFileName, error.c_str());
	}
	LoadMaterials(srcModel);
	for (const auto& srcMesh : srcModel.meshes)
	{
		for (const auto& primitive : srcMesh.primitives)
		{
			Mesh mesh = Mesh();
			mesh.LoadVBO(srcModel, srcMesh, primitive);
			mesh.LoadEBO(srcModel, srcMesh, primitive);
			mesh.CreateVAO();
			mesh.SetMaterial(primitive.material);
			m_mesh.push_back(mesh);
		}
	}
}

void ModelObject::LoadMaterials(const tinygltf::Model& srcModel)
{
	for (const auto& srcMaterial : srcModel.materials)
	{
		unsigned int textureId = 0;
		if (srcMaterial.pbrMetallicRoughness.baseColorTexture.index >= 0)
		{
			const tinygltf::Texture& texture = srcModel.textures[srcMaterial.pbrMetallicRoughness.baseColorTexture.index];
			const tinygltf::Image& image = srcModel.images[texture.source];
			textureId = (App->GetTextures()->LoadTexture(image.uri));
		}
		m_textures.push_back(textureId);
	}
}

void ModelObject::Render()
{
	for (Mesh mesh : m_mesh)
	{
		mesh.Render(m_textures);
	}
}

int ModelObject::CountTriangles() 
{
	int triangles = 0;
	for (auto& mesh : m_mesh) {
		triangles += mesh.GetNumIndices();
	}
	return triangles;
}

void ModelObject::ClearModel()
{
	m_mesh.clear();
	m_textures.clear();
}
