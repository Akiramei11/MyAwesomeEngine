#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleEditor;
class ModuleTexture;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    ModuleOpenGL* GetOpenGL() { return render; }
    ModuleWindow* GetWindow() { return window; }
    ModuleInput*  GetInput() { return input; }
    ModuleProgram* GetProgram() { return program; }
    ModuleCamera* GetCamera() { return camera; }
    ModuleEditor* GetEditor() { return editor; }
    ModuleDebugDraw* GetDebugDraw() { return debug_draw; }
    ModuleTexture* GetTextures() { return texture; }
    ModuleRenderExercise* GetExercise() { return exercice; }


private:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleProgram* program = nullptr;
    ModuleRenderExercise* exercice = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleDebugDraw* debug_draw = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleTexture* texture = nullptr;

    std::list<Module*> modules;

};

extern Application* App;
