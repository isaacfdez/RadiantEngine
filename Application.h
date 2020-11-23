#pragma once

#include <list>
#include "Globals.h"

class Module;
class ModuleRender;
class ModuleCamera;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleEditor;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	float GetDeltaTime();

public:
	ModuleRender* renderer = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;	
	ModuleProgram* program = nullptr;
	ModuleEditor* editor = nullptr;

private:
	float deltaTime = 0.0f;
	unsigned previousTime = 0;

	std::list<Module*> modules;
};

extern Application* App;
