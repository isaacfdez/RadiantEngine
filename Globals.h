#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
#define DEGTORAD pi/180

void log(const char file[], int line, const char* format, ...);

enum class update_status {
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum class WindowEvent {
	kQuit = 0,
	kHide,
	kShow,
	kCount
};

enum class KeyState {
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

// Configuration -----------
#define SCREEN_SIZE 2
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Radiant Engine"
#define AUTHORS "Isaac Fernandez Fontao"
#define LIBRARIES "Assimp, Dear ImGui, DevIL, GLEW, MathGeoLib, SDL"
#define LICENSE "MIT License"
