#include "ModuleInput.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleModels.h"
#include "SDL.h"

bool ModuleInput::Init() {
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleInput::Update() {
	SDL_Event event;

	mouseMotion = { 0, 0 };
	mouseWheelMotion = 0;
	memset(windowEvents, false, static_cast<unsigned int>(WindowEvent::COUNT) * sizeof(bool));

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i) {
		if (keys[i] == 1) {
			if (keyboard[i] == KeyState::KEY_IDLE)
				keyboard[i] = KeyState::KEY_DOWN;
			else
				keyboard[i] = KeyState::KEY_REPEAT;
		}
		else {
			if (keyboard[i] == KeyState::KEY_REPEAT || keyboard[i] == KeyState::KEY_DOWN)
				keyboard[i] = KeyState::KEY_UP;
			else
				keyboard[i] = KeyState::KEY_IDLE;
		}
	}

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i) {
		if (mouseButtons[i] == KeyState::KEY_DOWN)
			mouseButtons[i] = KeyState::KEY_REPEAT;

		if (mouseButtons[i] == KeyState::KEY_UP)
			mouseButtons[i] = KeyState::KEY_IDLE;
	}

	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			windowEvents[static_cast<unsigned int>(WindowEvent::QUIT)] = true;
			break;

		case SDL_WINDOWEVENT:
			switch (event.window.event) {
			case SDL_WINDOWEVENT_HIDDEN:
			case SDL_WINDOWEVENT_MINIMIZED:
			case SDL_WINDOWEVENT_FOCUS_LOST:
				windowEvents[static_cast<unsigned int>(WindowEvent::HIDE)] = true;
				break;

			case SDL_WINDOWEVENT_SHOWN:
			case SDL_WINDOWEVENT_FOCUS_GAINED:
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
				windowEvents[static_cast<unsigned int>(WindowEvent::SHOW)] = true;
				break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			mouseButtons[event.button.button - 1] = KeyState::KEY_DOWN;
			break;

		case SDL_MOUSEBUTTONUP:
			mouseButtons[event.button.button - 1] = KeyState::KEY_UP;
			break;

		case SDL_MOUSEMOTION:
			mouseMotion.x = event.motion.xrel / SCREEN_SIZE;
			mouseMotion.y = event.motion.yrel / SCREEN_SIZE;
			mouse.x = event.motion.x / SCREEN_SIZE;
			mouse.y = event.motion.y / SCREEN_SIZE;
			break;

		case SDL_MOUSEWHEEL:
			if (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
				mouseWheelMotion = event.wheel.x;
			}
			else {
				mouseWheelMotion = event.wheel.y;
			}
			break;

		case SDL_DROPFILE:
			App->model->Load(event.drop.file);
			break;
		}
		
	}

	if (GetWindowEvent(WindowEvent::QUIT) == true || GetKey(SDL_SCANCODE_ESCAPE) == KeyState::KEY_DOWN)
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

bool ModuleInput::CleanUp() {
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
