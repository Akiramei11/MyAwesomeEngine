#pragma once
#include "Module.h"
#include "Globals.h"
#include "MathGeoLib.h"

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

	float4x4 MyLookAt(const float3 eye, const float3 target, const float3 up);


private:
	unsigned triangle;
};
