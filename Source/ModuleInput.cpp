#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "ModuleCamera.h"
#include "SDL/include/SDL.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

    keyboard = SDL_GetKeyboardState(NULL);

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return UPDATE_STOP;
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                App->GetOpenGL()->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
            break;
        }
    }

    if (keyboard[SDL_SCANCODE_W] == 1) {
        App->GetCamera()->CameraForward(true);
    }
    if (keyboard[SDL_SCANCODE_S] == 1) {
        App->GetCamera()->CameraForward(false);
    }
    if (keyboard[SDL_SCANCODE_A] == 1) {
        App->GetCamera()->CameraRight(false);
    }
    if (keyboard[SDL_SCANCODE_D] == 1) {
        App->GetCamera()->CameraRight(true);
    }
    if (keyboard[SDL_SCANCODE_Q] == 1) {
        App->GetCamera()->CameraUp(false);
    }
    if (keyboard[SDL_SCANCODE_E] == 1) {
        App->GetCamera()->CameraUp(true);
    }
    if (keyboard[SDL_SCANCODE_UP] == 1) {
        App->GetCamera()->RotateCameraX(true);
    }
    if (keyboard[SDL_SCANCODE_DOWN] == 1) {
        App->GetCamera()->RotateCameraX(false);
    }
    if (keyboard[SDL_SCANCODE_LEFT] == 1) {
        App->GetCamera()->RotateCameraY(true);
    }
    if (keyboard[SDL_SCANCODE_RIGHT] == 1) {
        App->GetCamera()->RotateCameraY(false);
    }
    
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
