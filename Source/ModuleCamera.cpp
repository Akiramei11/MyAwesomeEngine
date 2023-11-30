#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "ModuleWindow.h"
/*
IMPORTANTE
TODO: hacer las funciones const 
TODO: hacer los parametros const reference
TODO: quitar includes de los .h
TODO: logica de la camara en la classe camera, no en input

*/
ModuleCamera::ModuleCamera()
{
	
}

// Destructor
ModuleCamera::~ModuleCamera()
{
}

// Called before render is available
bool ModuleCamera::Init()
{
	m_position = float3(4,2,4);	
	m_up = float3(0, 1, 0);
	m_speed = 0.003f;
	m_speedRot = 0.001f;

	m_frustum.type = FrustumType::PerspectiveFrustum;
	m_frustum.pos = float3::zero;
	m_frustum.front = -float3::unitZ;
	m_frustum.up = float3::unitY;
	m_frustum.nearPlaneDistance = 0.1f;
	m_frustum.farPlaneDistance = 100.0f;
	m_frustum.verticalFov = math::pi / 4.0f;


	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->GetWindow()->GetWindow(), &windowWidth, &windowHeight);
	float3 target = float3(0, 0, 0);
	float3 up = float3(0, 1, 0);

	LookAt(target, up);
	UpdateCameraMatrix();
	UpdateProjectionMatrix(windowWidth, windowHeight);
	UpdateViewMatrix();

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->GetWindow()->GetWindow(), &windowWidth, &windowHeight);

	UpdateProjectionMatrix(windowWidth, windowHeight);
	UpdateCameraMatrix();
	UpdateViewMatrix();

	glUseProgram(App->GetProgram()->GetProgramId());
	glUniformMatrix4fv(1, 1, GL_TRUE, &m_view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &m_proj[0][0]);

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-20, 20, 0.0f, 1.0f, dd::colors::Gray);
	App->GetDebugDraw()->Draw(m_view, m_proj, windowWidth, windowHeight);

	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{


	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp()
{
	
	return true;
}

void ModuleCamera::CameraForward( int amount) 
{
	m_position = m_position + m_forward * m_speed * amount;
}

void ModuleCamera::CameraRight( int amount) 
{
	m_position = m_position + m_right * m_speed * amount * 0.5;
}

void ModuleCamera::CameraUp( int amount) {
	m_position = m_position + m_up * m_speed * amount * 0.5;
}

void ModuleCamera::RotateCameraX( int amount) 
{
	m_forward = m_forward * float3x3::RotateAxisAngle(m_right, amount * m_speedRot);
	m_up = m_up * float3x3::RotateAxisAngle(m_right, amount * m_speedRot);
}
void ModuleCamera::RotateCameraY(int amount) 
{
	m_forward = m_forward * float3x3::RotateY(amount * m_speedRot);
	m_right = m_right * float3x3::RotateY(amount * m_speedRot);
	m_up = m_up * float3x3::RotateY(amount * m_speedRot);
}

void ModuleCamera::CameraOrbitArround(float3 target, int deltaX, int deltaY) 
{

}

void ModuleCamera::Zoom(int value) 
{
	//float sensitivity = m_frustum.verticalFov * 0.01;
	//m_frustum.verticalFov = m_frustum.verticalFov + value * sensitivity;
	CameraForward( value);

}

void ModuleCamera::UpdateProjectionMatrix(int screen_width, int screen_height) 
{
	m_frustum.horizontalFov = 2.f * atanf(tanf(m_frustum.verticalFov * 0.5f)) * (float)screen_width / (float)screen_height;
	m_proj = m_frustum.ProjectionMatrix();
}

void ModuleCamera::UpdateViewMatrix() 
{
	// Uses a lookAt calculation
	m_view = m_camera;
	m_view.Inverse();
}

void ModuleCamera::UpdateCameraMatrix() 
{
	m_camera = float4x4(float3x4(m_right, m_up, -m_forward, m_position));
}

void ModuleCamera::LookAt(float3 target, float3 up) 
{
	m_forward = (target - m_position).Normalized();
	m_right = Cross(m_forward, up).Normalized();
	m_up = Cross(m_right, m_forward).Normalized();
	UpdateCameraMatrix();
}
