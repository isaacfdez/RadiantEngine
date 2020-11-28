#pragma once
#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module {
public:

	bool Init() override;
	bool CleanUp() override;

	SDL_Window* GetWindow();
	SDL_Surface* GetScreenSurface();

private:
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
};
