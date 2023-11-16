#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercise.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "ModuleTexture.h"


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
	float buffer_data[] = {
		-1.0f, -1.0f, 0.0f, //  v0 pos
		1.0f, -1.0f, 0.0f, //  v1 pos
		0.0f, 1.0f, 0.0f, //  v2 pos
		0.0f, 1.0f, //  v0 texcoord
		1.0f, 1.0f, //  v1 texcoord
		0.5f, 0.0f //  v2 texcoord
	};
	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
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
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 3));
	DirectX::ScratchImage tex = App->GetTextures()->LoadTexture("Test-image-Baboon.png");
	unsigned texture_object = App->GetTextures()->CreateTexture(&tex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_object);


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);
	// TODO: retrieve model view and projection
	float4x4 model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateZ(0.0f),
		float3(1.0f, 1.0f, 1.0f));

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);

		// TODO: bind buffer and vertex attributes
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

