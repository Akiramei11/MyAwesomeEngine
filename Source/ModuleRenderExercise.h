#pragma once
#include "Module.h"
#include "Globals.h"
class ModuleRenderExercise : public Module
{
public:

	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	void RenderVBO(unsigned vbo, unsigned program);
	unsigned CreateTriangleVBO();
	void DestroyVBO(unsigned vbo);

private:
	unsigned triangle;
};
