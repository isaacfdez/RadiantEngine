#include "ModuleWindow.h"
#include "Application.h"

bool ModuleWindow::Init() {
	LOG("Init SDL window & surface");
	bool ret = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else {
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_DisplayMode desktopDisplay;
		SDL_GetDesktopDisplayMode(0, &desktopDisplay);

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, desktopDisplay.w, desktopDisplay.h, flags);

		if (window == NULL) {
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

bool ModuleWindow::CleanUp() {
	LOG("Destroying SDL window and quitting all SDL systems");

	if (window != NULL) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
	return true;
}

void ModuleWindow::SetWindowMode(WindowMode mode) {
	switch (mode) {
	case WindowMode::WINDOW:
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowBordered(window, SDL_TRUE);
		break;
	case WindowMode::BORDERLESS:
		SDL_SetWindowFullscreen(window, SDL_FALSE);
		SDL_SetWindowBordered(window, SDL_FALSE);
		break;
	case WindowMode::FULLSCREEN:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		SDL_SetWindowBordered(window, SDL_TRUE);
		break;
	case WindowMode::DESKTOP:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_SetWindowBordered(window, SDL_FALSE);
		break;
	}
	windowMode = mode;
}

void ModuleWindow::SetSize(int width, int height) {
	int index = SDL_GetWindowDisplayIndex(window);
	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(index), SDL_WINDOWPOS_CENTERED_DISPLAY(index));
}

WindowMode ModuleWindow::GetWindowMode()const {
	return windowMode;
}

int ModuleWindow::GetWidth() const {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return width;
}

int ModuleWindow::GetHeight() const {
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	return height;
}

bool ModuleWindow::GetResizable() const {
	return (SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE) != 0;
}

void ModuleWindow::SetResizable(bool resizable) {
	if (resizable) {
		SDL_SetWindowResizable(window, SDL_TRUE);
	}
	else {
		SDL_SetWindowResizable(window, SDL_FALSE);
	}
}

SDL_Window* ModuleWindow::GetWindow() {
	return window;
}

SDL_Surface* ModuleWindow::GetScreenSurface() {
	return screenSurface;
}
