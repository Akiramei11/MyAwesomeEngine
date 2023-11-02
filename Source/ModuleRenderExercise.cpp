#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercise.h"
#include "GL/glew.h"
#include "MathGeoLib.h"

ModuleRenderExercise::ModuleRenderExercise()
{

}
ModuleRenderExercise::~ModuleRenderExercise()
{

}

bool ModuleRenderExercise::Init()
{
	triangle = CreateTriangleVBO();

	
	return true;
}
update_status ModuleRenderExercise::Update()
{
	RenderVBO(triangle, App->GetProgram()->GetProgramId());
	auto info = glGetError();
	return UPDATE_CONTINUE;

}
bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO(triangle);
	return true;
}

// This function must be called one time at creation of vertex buffer
unsigned ModuleRenderExercise::CreateTriangleVBO()
{
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	return vbo;
}
// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
	glDeleteBuffers(1, &vbo);
}

// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);
	// TODO: retrieve model view and projection

	Frustum frustum;
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);
	float4x4 proj = frustum.ProjectionMatrix();

	float4x4 model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 1.0f));

	float3 eye = float3(0.0f, 4.0f, 8.0f);
	float3 target = float3(0.0f, 0.0f, 0.0f);
	float3 forward = float3::unitZ;
	float3 up = float3::unitY;


	float4x4 view = float4x4::LookAt(eye, target, forward, up, up);


	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &proj[0][0]);
		// TODO: bind buffer and vertex attributes
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
