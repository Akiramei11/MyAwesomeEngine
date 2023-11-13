#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void SetFOV();
	void SetAspectRatio();
	void SetPlaneDistances();
	void Position();
	void Orientation();
	float4x4 LookAt(const float3 eye, const float3 target, const float3 up);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:

};
