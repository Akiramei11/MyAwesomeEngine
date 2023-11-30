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
    mouse = SDL_GetMouseState(&m_x, &m_y);
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
    int x, y;
    Uint32 Buttons{ SDL_GetMouseState(&x, &y) };


    if ((Buttons & SDL_BUTTON_LMASK)) {
        App->GetCamera()->CameraRight(false, x - m_x);
        App->GetCamera()->CameraUp(false, y - m_y);

    }
    if (keyboard[SDL_SCANCODE_LALT] && (Buttons & SDL_BUTTON_RMASK)) {
        App->GetCamera()->Zoom(y - m_y);
    }
    else if ((Buttons & SDL_BUTTON_RMASK)) {
        App->GetCamera()->RotateCameraY(true, x - m_x);
        App->GetCamera()->RotateCameraX(true, y - m_y);
    }
    int rotation = 1;
    
    if (keyboard[SDL_SCANCODE_LEFT] == 1) {
        App->GetCamera()->RotateCameraY(true, rotation);
    }
    if (keyboard[SDL_SCANCODE_RIGHT] == 1) {
        App->GetCamera()->RotateCameraY(false, rotation);
    }
    if (keyboard[SDL_SCANCODE_UP] == 1) {
        App->GetCamera()->RotateCameraX(true, rotation);
    }
    if (keyboard[SDL_SCANCODE_DOWN] == 1) {
        App->GetCamera()->RotateCameraX(false, rotation);
    }

    int move = 1;
    if (keyboard[SDL_SCANCODE_W] == 1) {
        App->GetCamera()->CameraForward(true, move);
    }
    if (keyboard[SDL_SCANCODE_S] == 1) {
        App->GetCamera()->CameraForward(false, move);
    }
    if (keyboard[SDL_SCANCODE_A] == 1) {
        App->GetCamera()->CameraRight(false, move);
    }
    if (keyboard[SDL_SCANCODE_D] == 1) {
        App->GetCamera()->CameraRight(true, move);
    }
    if (keyboard[SDL_SCANCODE_Q] == 1) {
        App->GetCamera()->CameraUp(false, move);
    }
    if (keyboard[SDL_SCANCODE_E] == 1) {
        App->GetCamera()->CameraUp(true, move);
    }
    
    m_x = x;
    m_y = y;

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
