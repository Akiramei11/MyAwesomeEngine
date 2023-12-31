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

	void CameraForward( int amount);
	void CameraRight( int amount);
	void CameraUp( int amount);
	void RotateCameraX( int amount);
	void RotateCameraY( int amount);
	void CameraOrbitArround(float3 target, int deltaX, int deltaY);
	void Zoom(int value);

	void UpdateProjectionMatrix(int screen_width, int screen_height);
	void UpdateViewMatrix();
	void UpdateCameraMatrix();
	void LookAt(float3 target, float3 up);

	void CameraControls();
	const float GetSpeed() const { return m_speed; }
	const float GetSpeedRot() const { return m_speedRot; }

	void SetSpeed(const float speed) { m_speed = speed; }
	void SetSpeedRot(const float speed) { m_speedRot = speed; }

private:
	float3 m_position;
	float3 m_forward;
	float3 m_right;
	float3 m_up;
	float m_speed = 0;
	float m_speedRot = 0;

	float4x4 m_proj;
	float4x4 m_view;
	float4x4 m_camera;

	float m_verticalFov = 0;

	Frustum m_frustum;
};
