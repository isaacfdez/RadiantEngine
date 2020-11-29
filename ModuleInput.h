#pragma once

#include "Module.h"
#include "Globals.h"
#include "Math/float2.h"

#define MAX_KEYS 300
#define NUM_MOUSE_BUTTONS 5

typedef unsigned __int8 Uint8;

class ModuleInput : public Module {
public:

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	inline KeyState GetKey(int id) const { return keyboard[id]; }
	inline KeyState GetMouseButtonDown(int id) const { return mouseButtons[id - 1]; }
	inline bool GetWindowEvent(WindowEvent ev) const { return windowEvents[static_cast<unsigned int>(ev)]; }
	const float GetMouseWheelMotion() const	{ return mouseWheelMotion; }
	const float2& GetMouseMotion() const { return mouseMotion; }

private:
	bool windowEvents[static_cast<unsigned int>(WindowEvent::COUNT)];
	KeyState keyboard[MAX_KEYS] = { KeyState::KEY_IDLE};
	KeyState mouseButtons[NUM_MOUSE_BUTTONS] = { KeyState::KEY_IDLE };
	float2 mouseMotion = { 0, 0 };
	float2 mouse = { 0, 0 };
	float mouseWheelMotion = 0;
};