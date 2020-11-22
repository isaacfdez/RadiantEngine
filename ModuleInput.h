#pragma once

#include "Module.h"
#include "Math/float2.h"
#include "SDL_scancode.h"
#include "SDL_mouse.h"

#define NUM_KEYS 300
#define NUM_MOUSE_BUTTONS 5

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

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	KeyState GetKey(int scancode) const
	{
		return keyboard[scancode];
	}

	KeyState GetMouseButtonDown(int button) const
	{
		return mouseButtons[button - 1];
	}

	const float GetMouseWheelMotion() const
	{
		return mouseWheelMotion;
	}

	const float2& GetMouseMotion() const
	{
		return mouseMotion;
	}

	const float2& GetMousePosition() const
	{
		return mouse;
	}

private:
	KeyState keyboard[NUM_KEYS];
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	float mouseWheelMotion = 0;
	float2 mouseMotion = { 0, 0 };
	float2 mouse = { 0, 0 };
};