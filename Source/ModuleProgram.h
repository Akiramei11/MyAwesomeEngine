#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include <chrono>
class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	unsigned GetProgramId() { return m_program_id; }

	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);


private:
	unsigned m_program_id;
};

