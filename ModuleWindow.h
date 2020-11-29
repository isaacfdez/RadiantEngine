#pragma once
#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module {
public:

	bool Init() override;
	bool CleanUp() override;

	void SetWindowMode(WindowMode mode);
	void SetSize(int width, int height);
	WindowMode GetWindowMode() const;
	int GetWidth() const;
	int GetHeight() const;
	bool GetResizable() const;
	void SetResizable(bool resizable);

	SDL_Window* GetWindow();
	SDL_Surface* GetScreenSurface();

private:
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	WindowMode windowMode = WindowMode::WINDOW;
};
