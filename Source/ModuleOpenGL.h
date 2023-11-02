#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
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

//	void APIENTRY OurOpenGLErrorFunction(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	void WindowResized(unsigned width, unsigned height);
	void* GetContext() const { return context; }
	
private:
	void* context;
};
