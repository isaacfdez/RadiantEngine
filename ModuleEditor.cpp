#include "ModuleEditor.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleModels.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "SDL_version.h"
#include "SDL_cpuinfo.h"
#include "SDL_video.h"
#include "GL/glew.h"
#include "assimp/version.h"
#include "il.h"
#include "Math/float3.h"
#include "Math/float3x3.h"
#include "Math/float4x4.h"


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
            if(ImGui::CollapsingHeader("Libraries' Version")){
                ImGui::Text("Assimp:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%i.%i.%i", aiGetVersionMajor(), aiGetVersionMinor(), aiGetVersionRevision());
                ImGui::Text("DevIL:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%i.%i.%i", IL_VERSION / 100, (IL_VERSION % 100) / 10, IL_VERSION & 10);
                ImGui::Text("GLEW:");
                ImGui::SameLine();
                ImGui::TextColored(purple, "%i.%i.%i", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
                ImGui::Text("SDL:");
                ImGui::SameLine();
                SDL_version version;
                SDL_VERSION(&version);
                ImGui::TextColored(purple, "%i.%i.%i", version.major, version.minor, version.patch);
            }
            if (ImGui::CollapsingHeader("Window")) {
                const char* windowModes[] = { "Window", "Borderless", "Fullscreen", "Desktop" };
                const char* currentMode = windowModes[int(App->window->GetWindowMode())];
                if (ImGui::BeginCombo("Window Mode", currentMode)) {
                    for (int i = 0; i < IM_ARRAYSIZE(windowModes); ++i) {
                        bool selected = (currentMode == windowModes[i]);
                        if (ImGui::Selectable(windowModes[i], selected)) {
                            App->window->SetWindowMode(WindowMode(i));
                        }
                        if (selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo();
                }

                if (App->window->GetWindowMode() == WindowMode::WINDOW || App->window->GetWindowMode() == WindowMode::BORDERLESS) {
                    bool resizable = App->window->GetResizable();
                    if (ImGui::Checkbox("Resizable", &resizable)) {
                        App->window->SetResizable(resizable);
                    }
                    if (resizable) {
                        int width = App->window->GetWidth();
                        int height = App->window->GetHeight();
                        bool sizeChanged = false;
                        ImGui::SliderInt("Width", &width, 720, 3840);
                        if (ImGui::IsItemDeactivatedAfterEdit()) {
                            sizeChanged = true;
                        }
                        ImGui::SliderInt("Height", &height, 480, 2160);
                        if (ImGui::IsItemDeactivatedAfterEdit()) {
                            sizeChanged = true;
                        }
                        if (sizeChanged) {
                            App->window->SetSize(width, height);
                        }
                    }
                }
            }

            if (ImGui::CollapsingHeader("Camera")) {
                vec front = App->camera->GetFront();
                vec up = App->camera->GetUp();
                vec position = App->camera->GetPosition();
                float nearPlane = App->camera->GetNearPlane();
                float farPlane = App->camera->GetFarPlane();
                float FOV = App->camera->GetFOV();
                float aspectRatio = App->camera->GetAspectRatio();
                float movementSpeed = App->camera->GetMovementSpeed();
                float rotationSpeed = App->camera->GetRotationSpeed();
                float zoomSpeed = App->camera->GetZoomSpeed();
                ImGui::InputFloat3("Front", front.ptr(), "%.3f");
                ImGui::InputFloat3("Up", up.ptr(), "%.3f");
                ImGui::InputFloat3("Position", position.ptr());
                ImGui::InputFloat("Near Plane", &nearPlane);
                ImGui::InputFloat("Far Plane", &farPlane);
                ImGui::InputFloat("FOV", &FOV);
                ImGui::InputFloat("Aspect Ratio", &aspectRatio);
                ImGui::InputFloat("Movement Speed", &movementSpeed);
                ImGui::InputFloat("Rotation Speed", &rotationSpeed);
                ImGui::InputFloat("Zoom Speed", &zoomSpeed);
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
            if (ImGui::CollapsingHeader("Transformation")) {
                float4x4 modelMatrix = App->model->GetModelMatrix();
                float3 position = modelMatrix.TranslatePart();
                float3 rotation = modelMatrix.RotatePart().ToEulerXYZ();
                float3 scale = modelMatrix.ExtractScale();
                ImGui::InputFloat3("Position", position.ptr(), "%.3f");
                ImGui::InputFloat3("Rotation", rotation.ptr(), "%.3f");
                ImGui::InputFloat3("Scale", scale.ptr(), "%.3f");
            }

            if (ImGui::CollapsingHeader("Geometry")) {
                std::vector<Mesh> meshes = App->model->GetMeshes();
                for (unsigned int i = 0; i < meshes.size(); ++i) {
                    char meshName[32];
                    sprintf_s(meshName, "Mesh %i", i);
                    if (ImGui::TreeNode(meshName)) {
                        ImGui::Text("Vertices:");
                        ImGui::SameLine();
                        ImGui::TextColored(purple, "%i", meshes[i].GetVertices());
                        ImGui::Text("Triangles:");
                        ImGui::SameLine();
                        ImGui::TextColored(purple, "%i", meshes[i].GetTriangles());
                        ImGui::Text("Faces:");
                        ImGui::SameLine();
                        ImGui::TextColored(purple, "%i", meshes[i].GetFaces());
                        ImGui::TreePop();
                    }
                }
            }

            if (ImGui::CollapsingHeader("Textures")) {
                std::vector<unsigned int> textures = App->model->GetTextures();
                for (unsigned int i = 0; i < textures.size(); ++i) {
                    char textureName[32];
                    sprintf_s(textureName, "Texture %i", i);
                    if (ImGui::TreeNode(textureName)) {
                        int width, height;
                        glGetTextureLevelParameteriv(textures[i], 0, GL_TEXTURE_WIDTH, &width);
                        glGetTextureLevelParameteriv(textures[i], 0, GL_TEXTURE_HEIGHT, &height);
                        ImGui::Image((ImTextureID)textures[i], ImVec2(128, 128));
                        ImGui::Text("Texture dimensions");
                        ImGui::Text("Width");
                        ImGui::SameLine();
                        ImGui::TextColored(purple, "%i", width);
                        ImGui::Text("Height");
                        ImGui::SameLine();
                        ImGui::TextColored(purple, "%i", height);
                        ImGui::TreePop();
                    }
                }
            }
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