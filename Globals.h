#pragma once

#include <windows.h>
#include <stdio.h>
#include <string>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define DEGTORAD pi/180

void log(const char file[], int line, const char* format, ...);
void logFPS(float deltaTime);

extern std::string logs;
extern int FPSIndex;
extern float logsFPS[];
extern float logsMiliseconds[];

enum class update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum class WindowEvent {
	QUIT = 0,
	HIDE,
	SHOW,
	COUNT
};

enum class KeyState {
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum class WindowMode {
	WINDOW,
	BORDERLESS,
	FULLSCREEN,
	DESKTOP
};

// Configuration -----------
#define SCREEN_SIZE 2
#define VSYNC true
#define TITLE "Radiant Engine"
#define AUTHORS "Isaac Fernandez Fontao"
#define LIBRARIES "Assimp, Dear ImGui, DevIL, GLEW, MathGeoLib, SDL"
#define LICENSE "MIT License"
