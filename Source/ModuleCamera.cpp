#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "debugdraw.h"

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
	return true;
}

update_status ModuleCamera::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleCamera::Update()
{
	float4x4 proj = GetProjectionMatrix();
	float3 eye = float3(10, 10, 10);
	float3 target = float3(0, 0, 0);
	float3 up = float3(0, 1, 0);
	float4x4 view = LookAt(eye, target, up);

	glUseProgram(App->GetProgram()->GetProgramId());
	glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(2, 1, GL_TRUE, &proj[0][0]);

	dd::axisTriad(float4x4::identity, 0.1f, 1.0f);
	dd::xzSquareGrid(-20, 20, 0.0f, 1.0f, dd::colors::Gray);
	App->GetDebugDraw()->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);

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

void ModuleCamera::SetFOV() {

}
void ModuleCamera::SetAspectRatio() {

}
void ModuleCamera::SetPlaneDistances() {

}
void ModuleCamera::Position() {

}
void ModuleCamera::Orientation() {

}
float4x4 ModuleCamera::LookAt(const float3 eye, const float3 target, const float3 up)
{
	float3 forward = (eye - target).Normalized();
	float3 right = Cross(forward, up).Normalized();
	float3 viewup = Cross(right, forward).Normalized();

	float4x4 firstMat = float4x4(float3x4(right, viewup, forward, float3(0.0f, 0.0f, 0.0f)));
	firstMat.Transpose();
	float4x4 secondMat = float4x4(float4::unitX, float4::unitY, float4::unitZ, float4(-eye, 1.0f));
	return firstMat * secondMat;

}
float4x4 ModuleCamera::GetProjectionMatrix() {
	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f)) * (float)SCREEN_HEIGHT/ (float)SCREEN_WIDTH;

	return frustum.ProjectionMatrix();
}
float4x4 ModuleCamera::GetViewMatrix() {
	return float4x4::identity;
}