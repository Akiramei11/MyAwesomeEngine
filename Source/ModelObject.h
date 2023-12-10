#pragma once
#include "Globals.h"
#include "Mesh.h"

class ModelObject
{
public:
	ModelObject();
	~ModelObject();
	void Load(const char* assetFileName);
	void LoadMaterials(const tinygltf::Model& srcModel);

	void Render();

	int CountTriangles();
	void ClearModel();


private:
	std::vector<Mesh> m_mesh;
	std::vector<unsigned> m_textures;
};

