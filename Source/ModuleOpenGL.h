#pragma once
#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleOpenGL : public Module
{
public:
	ModuleOpenGL();
	~ModuleOpenGL();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void WindowResized(unsigned width, unsigned height);
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);



private:
	void* context;
};
