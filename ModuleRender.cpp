#include "ModuleRender.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleWindow.h"
#include "ModuleProgram.h"
#include "ModuleTextures.h"
#include "ModuleModels.h"
#include "Math/float4x4.h"
#include "SDL.h"
#include <GL\glew.h>

bool ModuleRender::Init() {
	LOG("Creating Renderer context");

	SDL_GLContext context = SDL_GL_CreateContext(App->window->window);
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	App->model->Load("BakerHouse.fbx", "vertex.glsl", "fragment.glsl");

	return true;
}

update_status ModuleRender::PreUpdate() {
	SDL_GetWindowSize(App->window->window, NULL, NULL);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update() {
	int w, h;
	SDL_GetWindowSize(App->window->window, &w, &h);

	float4x4 proj = App->camera->frustum.ProjectionMatrix();
	float4x4 view = App->camera->frustum.ViewMatrix();

	App->model->Draw();

	App->debugDraw->Draw(view, proj, w, h);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate() {
	SDL_GL_SwapWindow(App->window->window);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp() {
	LOG("Destroying renderer");

	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height) {}

void* ModuleRender::getContext() {
	return context;
}