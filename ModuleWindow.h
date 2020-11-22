#pragma once

#include "Module.h"

class SDL_Window;
class SDL_Surface;

class ModuleWindow : public Module
{
public:
	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

public:
	SDL_Window* window = nullptr; 
	SDL_Surface* screenSurface = nullptr; 
};
