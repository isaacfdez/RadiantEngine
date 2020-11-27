#pragma once
#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleCamera;
class ModuleDebugDraw;
class ModuleProgram;
class ModuleTextures;
class ModuleModels;

class Application {
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	float getDeltaTime();

public:
	ModuleRender* render = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleDebugDraw* debugDraw = nullptr;
	ModuleProgram* program = nullptr;
	ModuleTextures* texture = nullptr;
	ModuleModels* model = nullptr;
	

private:
	float deltaTime = 0.0f;
	float previousTime = 0.0f;
	std::list<Module*> modules;
};

extern Application* App;