#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "SDL_version.h"
#include "SDL_cpuinfo.h"
#include "SDL_video.h"
#include "GL/glew.h"


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
            if (ImGui::CollapsingHeader("FPS Graph")) {
                char title[25];
                sprintf_s(title, 25, "Framerate %.1f", logsFPS[FPSIndex]);
                ImGui::PlotHistogram("##framerate", &logsFPS[0], 100, FPSIndex, title, 0.0f, 100.0f, ImVec2(310, 100));
                sprintf_s(title, 25, "Miliseconds %.1f", logsMiliseconds[FPSIndex]);
                ImGui::PlotHistogram("##miliseconds", &logsMiliseconds[0], 100, FPSIndex, title, 0.0f, 40.0f, ImVec2(310, 100));
            }

            if (ImGui::CollapsingHeader("Hardware Information")) {
                ImGui::Text("Number of CPUs:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%i", SDL_GetCPUCount());
                ImGui::Text("RAM Memory:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%.1f Gb", SDL_GetSystemRAM() / 1000.0f);
                ImGui::Text("GPU Vendor:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%s", (const char*)glGetString(GL_VENDOR));
                ImGui::Text("GPU Model:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%s", (const char*)glGetString(GL_RENDERER));
                ImGui::Text("GPU OpenGL Version:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%s", (const char*)glGetString(GL_VERSION));
                ImGui::Text("VRAM Available:");
                ImGui::SameLine();
                int vramAvailable;
                glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &vramAvailable);
                ImGui::TextColored(purple, "%.1f Mb", vramAvailable / 1000.0f);
                ImGui::Text("VRAM Budget:");
                ImGui::SameLine();
                int vramBudget;
                glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &vramBudget);
                ImGui::TextColored(purple, "%.1f Mb", vramBudget / 1000.0f);
                ImGui::Text("VRAM Usage:");
                ImGui::SameLine();
                int vramUsage = vramBudget - vramAvailable ;
                ImGui::TextColored(purple, "%.1f Mb", vramUsage / 1000.0f);

            }
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