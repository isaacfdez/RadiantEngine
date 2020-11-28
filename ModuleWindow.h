#pragma once
#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module {
public:

	bool Init() override;
	bool CleanUp() override;

public:
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
};
