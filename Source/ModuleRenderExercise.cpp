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

	DirectX::ScratchImage tex = App->GetTextures()->LoadTexture("Test-image-Baboon.png");
	texture_object = App->GetTextures()->CreateTexture(&tex);
	
	return true;
}
update_status ModuleRenderExercise::Update()
{
	RenderVBO(App->GetProgram()->GetProgramId());
	return UPDATE_CONTINUE;

}
bool ModuleRenderExercise::CleanUp()
{
	DestroyVBO();
	return true;
}

// This function must be called one time at creation of vertex buffer
unsigned ModuleRenderExercise::CreateTriangleVBO()
{
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

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * 3));
	return vbo;
}
// This function must be called one time at destruction of vertex buffer
void ModuleRenderExercise::DestroyVBO()
{
	glDeleteBuffers(1, &triangle);
}



// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO(unsigned program)
{	
	////Enables the texture
	glActiveTexture(GL_TEXTURE5); // The 5 needs to match with the sampler in fragment shader
	glBindTexture(GL_TEXTURE_2D, texture_object);

	float4x4 model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateZ(0.0f),
		float3(1.0f, 1.0f, 1.0f));

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);

		// TODO: bind buffer and vertex attributes
	// 1 triangle to draw = 3 vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

}

