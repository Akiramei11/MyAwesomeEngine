#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercise.h"
#include "ModuleTexture.h"
#include "GL/glew.h"
#include "MathGeoLib.h"
#include "ModuleTexture.h"
#include "FrameBuffer.h"
#include "ModuleEditor.h"


ModuleRenderExercise::ModuleRenderExercise()
{

}
ModuleRenderExercise::~ModuleRenderExercise()
{

}

bool ModuleRenderExercise::Init()
{
	m_model.Load("BakerHouse.gltf");
	return true;
}
update_status ModuleRenderExercise::Update()
{
	//RenderVBO(App->GetProgram()->GetProgramId());
	unsigned program = App->GetProgram()->GetProgramId();
	float4x4 model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
		float4x4::RotateZ(0.0f),
		float3(40.0f, 40.0f, 40.0f));

	glUseProgram(program);
	glUniformMatrix4fv(0, 1, GL_TRUE, &model[0][0]);
	m_model.Render();

	return UPDATE_CONTINUE;
}
bool ModuleRenderExercise::CleanUp()
{
	return true;
}

void ModuleRenderExercise::ClearModel()
{
	m_model.ClearModel();
}
void ModuleRenderExercise::LoadModel(std::string path)
{
	m_model.Load(path.c_str());
}
