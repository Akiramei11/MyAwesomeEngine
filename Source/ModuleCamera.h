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

	void CameraForward(bool positive, int amount);
	void CameraRight(bool positive, int amount);
	void CameraUp(bool positive, int amount);
	void RotateCameraX(bool positive, int amount);
	void RotateCameraY(bool positive, int amount);
	void CameraOrbitArround(float3 target, int deltaX, int deltaY);
	void Zoom(int value);

	void UpdateProjectionMatrix(int screen_width, int screen_height);
	void UpdateViewMatrix();
	void UpdateCameraMatrix();
	void LookAt(float3 target, float3 up);


private:
	float3 m_position;
	float3 m_forward;
	float3 m_right;
	float3 m_up;
	float m_speed;
	float m_speedRot;

	float4x4 m_proj;
	float4x4 m_view;
	float4x4 m_camera;

	float m_verticalFov;

	Frustum m_frustum;
};
