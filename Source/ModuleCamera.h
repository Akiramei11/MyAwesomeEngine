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

	void CameraForward(bool positive);
	void CameraRight(bool positive);
	void CameraUp(bool positive);
	void RotateCameraX(bool positive);
	void RotateCameraY(bool positive);
	void CameraOrbitArround(float3 target, int deltaX, int deltaY);
	void Zoom(int value);

	void UpdateProjectionMatrix(int screen_width, int screen_height);
	void UpdateViewMatrix();

private:
	float3 m_position;
	float3 m_target;
	float m_speed;
	float4x4 m_proj;
	float4x4 m_view;

	float3 m_up;
	float4 m_rotation;
	float m_verticalFov;

	Frustum m_frustum;
};
