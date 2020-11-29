#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"
#include "ModuleTextures.h"
#include "ModuleModels.h"
#include "ModuleEditor.h"

using namespace std;

Application::Application() {
	modules.push_back(window = new ModuleWindow());
	modules.push_back(input = new ModuleInput());
	modules.push_back(camera = new ModuleCamera());
	modules.push_back(texture = new ModuleTextures());
	modules.push_back(program = new ModuleProgram());
	modules.push_back(model = new ModuleModels());
	modules.push_back(render = new ModuleRender());
	modules.push_back(debugDraw = new ModuleDebugDraw());
	modules.push_back(editor = new ModuleEditor());

}

Application::~Application() {
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it) {
		delete* it;
	}
}

bool Application::Init() {
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

update_status Application::Update() {
	float currentTime = SDL_GetTicks();
	deltaTime = (currentTime - previousTime) / 1000;
	logFPS(deltaTime);
	previousTime = currentTime;

	update_status ret = update_status::UPDATE_CONTINUE;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp() {
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}

float Application::getDeltaTime() {
	return deltaTime;
}

void Application::GoToBrowser(const char* url) {
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}