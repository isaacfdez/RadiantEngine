#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

bool ModuleEditor::Init() {
	ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->render->context);
    ImGui_ImplOpenGL3_Init();
    return true;
}

update_status ModuleEditor::PreUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::Update() {
    
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit")) {
                return update_status::UPDATE_STOP;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("External links")) {
            if (ImGui::MenuItem("Github")) {
                App->GoToBrowser("https://github.com/isaacfdez/RadiantEngine");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Console", "", &consoleEnabled);
            ImGui::MenuItem("Configuration", "", &configEnabled);
            ImGui::MenuItem("About", "", &aboutEnabled);
            ImGui::MenuItem("Properties", "", &propertiesEnabled);
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();

    if (consoleEnabled) {
        if (ImGui::Begin("Console")) {

        }
        ImGui::End();
    }

    if (configEnabled) {
        if (ImGui::Begin("Configuration")) {

        }
        ImGui::End();
    }

    if (aboutEnabled) {
        if (ImGui::Begin("About")) {

        }
        ImGui::End();
    }

    if (propertiesEnabled) {
        if (ImGui::Begin("Properties")) {

        }
        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    return update_status::UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return true;
}