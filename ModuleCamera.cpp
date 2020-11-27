#include "ModuleCamera.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL.h"
#include "Math/float3x3.h"
#include "Math/Quat.h"

bool ModuleCamera::Init() {
    frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
    frustum.SetViewPlaneDistances(0.1f, 32.0f);
    frustum.SetHorizontalFovAndAspectRatio(DEGTORAD*90.0f, 1.3f);
    frustum.SetPos(float3(0, 3, -8));
    frustum.SetFront(float3::unitZ);
    frustum.SetUp(float3::unitY);

    return true;
}

void ModuleCamera::Rotate(float3x3 rotationMatrix) {
    frustum.SetFront(rotationMatrix.MulDir(frustum.Front().Normalized()));
    frustum.SetUp(rotationMatrix.MulDir(frustum.Up().Normalized()));
}

void ModuleCamera::KeyboardMovement() {
    float3 movement(0, 0, 0);

    if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT) {
        movement += float3::unitY;
    }
    if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT) {
        movement -= float3::unitY;
    }

    if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT) {
        movement += frustum.Front();
    }
    if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT) {
        movement -= frustum.Front();
    }

    if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT) {
        movement -= frustum.WorldRight();
    }
    if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT) {
        movement += frustum.WorldRight();
    }

    frustum.Translate(movement * movementSpeed * App->getDeltaTime());
}

void ModuleCamera::KeyboardRotation() {
    float rotateY = 0.0f; float rotateX = 0.0f;

    if (App->input->GetKey(SDL_SCANCODE_UP) == KeyState::KEY_REPEAT) {
        rotateX += 1;
    }
    if (App->input->GetKey(SDL_SCANCODE_DOWN) == KeyState::KEY_REPEAT) {
        rotateX -= 1;
    }

    if (App->input->GetKey(SDL_SCANCODE_LEFT) == KeyState::KEY_REPEAT) {
        rotateY += 1;
    }
    if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KeyState::KEY_REPEAT) {
        rotateY -= 1;
    }

    Quat quatX(frustum.WorldRight(), rotateX * rotationSpeed * App->getDeltaTime());
    Quat quatY(float3::unitY, rotateY * rotationSpeed * App->getDeltaTime());

    Rotate(float3x3::FromQuat(quatX) * float3x3::FromQuat(quatY));
}

void ModuleCamera::MouseMovement(int x, int y) {
    float3 movement(0, 0, 0);

    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT && x != 0 && y != 0) {
        movement += frustum.WorldRight() + frustum.Front();
        movement.x -= (float)x;
        movement.y -= (float)y;
    }
    frustum.Translate(movement * movementSpeed * App->getDeltaTime());
}

void ModuleCamera::MouseRotation(int x, int y) {
    float rotateY = 0.0f; float rotateX = 0.0f;

    if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT && x != 0 && y != 0) {
        rotateX = -(float)y * App->getDeltaTime() * movementSpeed;
        rotateY = -(float)x * App->getDeltaTime() * movementSpeed;
    }

    Quat quatX(frustum.WorldRight(), rotateX * rotationSpeed * App->getDeltaTime());
    Quat quatY(float3::unitY, rotateY * rotationSpeed * App->getDeltaTime());

    Rotate(float3x3::FromQuat(quatX) * float3x3::FromQuat(quatY));
}

void ModuleCamera::focus() {
    if (App->input->GetKey(SDL_SCANCODE_F) == KeyState::KEY_REPEAT) {
        frustum.SetPos(float3(0, 3, -8));
        frustum.SetFront(float3::unitZ);
        frustum.SetUp(float3::unitY);
    }
}

void ModuleCamera::zoom() {
    float mouseWheelMotion = App->input->GetMouseWheelMotion();
    if (mouseWheelMotion < -FLT_EPSILON || mouseWheelMotion > FLT_EPSILON)
    {
        frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * mouseWheelMotion * 10 * zoomSpeed * App->getDeltaTime()));
    }
}

update_status ModuleCamera::PreUpdate() {
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() {
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);

    KeyboardMovement();
    KeyboardRotation();
    MouseMovement(x, y);
    MouseRotation(x, y);
    focus();
    zoom();
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate() {
    return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp() {
    return true;
}
