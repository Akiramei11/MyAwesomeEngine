#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"
#include "ModuleWindow.h"

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
	m_target = float3(0, 0, 0);
	m_up = float3(0, 1, 0);
	m_rotation = float4(0,0,0,1);
	m_speed = 0.01f;
	m_verticalFov = math::pi / 4.0f;

	m_frustum.type = FrustumType::PerspectiveFrustum;
	m_frustum.pos = float3::zero;
	m_frustum.front = -float3::unitZ;
	m_frustum.up = float3::unitY;
	m_frustum.nearPlaneDistance = 0.1f;
	m_frustum.farPlaneDistance = 100.0f;
	m_frustum.verticalFov = m_verticalFov;


	int windowWidth, windowHeight;
	SDL_GetWindowSize(App->GetWindow()->GetWindow(), &windowWidth, &windowHeight);
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
	float3 up = float3(0, 1, 0);
	UpdateViewMatrix();
	//view = view * float4x4::Translate(2,0,0);


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

void ModuleCamera::CameraForward(bool positive) {
	int dir = 0;
	if (positive) dir = -1;
	else dir = 1;
	float3 forward = (m_position - m_target).Normalized();
	m_position = m_position + forward * m_speed * dir;
	m_target = m_target + forward * m_speed * dir;
}

void ModuleCamera::CameraRight(bool positive) {
	//float3 right = Cross(GetCameraForward(), up).Normalized();
	int dir = 0;
	if (positive) dir = -1;
	else dir = 1;
	float3 forward = (m_position - m_target).Normalized();
	float3 right = Cross(forward, m_up).Normalized();
	m_position = m_position + right * m_speed * dir * 0.5;
	m_target = m_target + right * m_speed * dir * 0.5;
}

void ModuleCamera::CameraUp(bool positive) {
	int dir = 0;
	if (positive) dir = -1;
	else dir = 1;
	float3 forward = (m_position - m_target).Normalized();
	float3 right = Cross(forward, m_up).Normalized();
	float3 viewup = Cross(right, forward).Normalized();
	m_position = m_position + viewup * m_speed * dir * 0.5;
	m_target = m_target + viewup * m_speed * dir * 0.5;
}

void ModuleCamera::RotateCameraX(bool positive) {
	float3 diff = m_target - m_position;
	float3 forward = (m_position - m_target).Normalized();
	float3 right = Cross(forward, m_up).Normalized();
	float3 res;
	if (positive)  res = float3x3::RotateAxisAngle(right, 0.001) * diff;
	else  res = float3x3::RotateAxisAngle(right, -0.001) * diff;
	m_target = res + m_position;
	 
}
void ModuleCamera::RotateCameraY(bool positive) {
	float3 diff = m_target - m_position;
	float3 res;
	if (positive)  res = float3x3::RotateY(0.001) * diff;
	else  res = float3x3::RotateY(-0.001) * diff;
	m_target = res + m_position;

}

void ModuleCamera::CameraOrbitArround(float3 target, int deltaX, int deltaY) {

}

void ModuleCamera::Zoom(int value) {
	float sensitivity = 0.1f;
	m_verticalFov = m_verticalFov + value * sensitivity;
}

void ModuleCamera::UpdateProjectionMatrix(int screen_width, int screen_height) 
{
	m_frustum.horizontalFov = 2.f * atanf(tanf(m_frustum.verticalFov * 0.5f)) * (float)screen_width / (float)screen_height;
	m_proj = m_frustum.ProjectionMatrix();
}

void ModuleCamera::UpdateViewMatrix() 
{
	// Uses a lookAt calculation
	float3 forward = (m_target - m_position).Normalized();
	float3 right = Cross(forward, m_up).Normalized();
	float3 viewup = Cross(right, forward).Normalized();

	float4x4 firstMat = float4x4(float3x4(right, viewup, -forward, float3(0.0f, 0.0f, 0.0f)));
	firstMat.Transpose();
	float4x4 secondMat = float4x4(float4::unitX, float4::unitY, float4::unitZ, float4(-m_position, 1.0f));
	m_view = firstMat * secondMat;
}