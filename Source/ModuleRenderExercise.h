#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"
#include "Mesh.h"

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

private:
	unsigned triangle;
	unsigned texture_object;
	Model m_bakerHouse;
};
