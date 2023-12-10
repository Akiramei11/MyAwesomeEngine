#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include "ModelObject.h"

class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void RenderVBO(unsigned program);
	unsigned CreateTriangleVBO();
	void DestroyVBO();
	ModelObject* GetModel() { return &m_model; }

	void ClearModel();
	void LoadModel(std::string path);

private:
	ModelObject m_model;
};
