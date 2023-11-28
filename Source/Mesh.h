#pragma once
#include "Globals.h"

#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#include "tiny_gltf.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void LoadVBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void LoadEBO(const tinygltf::Model& model, const tinygltf::Mesh& mesh, const tinygltf::Primitive& primitive);
	void CreateVAO();

	void SetMaterial(int material) { m_material = material; }
	unsigned GetMaterial() const { return m_material; }

	void Render(const std::vector<unsigned>& textures);

private:
	unsigned m_vbo;
	unsigned m_ebo;
	unsigned m_vao;
	unsigned m_material;

	int m_numVertices;
	int m_numIndices;
};

class Model
{
public:
	Model();
	~Model();
	void Load(const char* assetFileName);
	void LoadMaterials(const tinygltf::Model& srcModel);

	void Render();


private:
	std::vector<Mesh> m_mesh;
	std::vector<unsigned> m_textures;
};
