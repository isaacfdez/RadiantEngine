#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"

static ImVec4 purple = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);

bool ModuleEditor::Init() {
	ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(App->window->GetWindow(), App->render->getContext());
    ImGui_ImplOpenGL3_Init();
    return true;
}

update_status ModuleEditor::PreUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->GetWindow());
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
            ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::TextUnformatted(logs.c_str());
            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            {
                ImGui::SetScrollHereY(1.0f);
            }
            ImGui::EndChild();
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
            ImGui::Text("Engine Name:");
            ImGui::SameLine();
            ImGui::TextColored(purple, TITLE);
            ImGui::Text("Authors:");
            ImGui::SameLine();
            ImGui::TextColored(purple, AUTHORS);
            ImGui::Text("Libraries used:");
            ImGui::SameLine();
            ImGui::TextColored(purple, LIBRARIES);
            ImGui::Text("License:");
            ImGui::SameLine();
            ImGui::TextColored(purple, LICENSE);
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