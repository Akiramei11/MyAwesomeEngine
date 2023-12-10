#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

#define NUM_MOUSE_BUTTONS 5

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init() override;
	update_status PreUpdate() override;
	bool CleanUp() override;
	
	KeyState GetKey(int id) const { return keyboard[id]; }

	KeyState GetMouseButtonDown(int id) const { return mouse_buttons[id - 1]; }

	// Check for window events last frame
	bool GetWindowEvent(EventWindow code) const;

	// Get mouse / axis position
	const std::pair<int, int>& GetMouseMotion() const;
	const std::pair<int, int>& GetMousePosition() const;

private:
	bool		windowEvents[WE_COUNT];
	KeyState* keyboard = nullptr;
	KeyState	mouse_buttons[NUM_MOUSE_BUTTONS];
	std::pair<int, int> mouse_motion = { 0,0 };
	std::pair<int, int> mouse = {0,0};
};