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
    frustum.SetFront(rotationMatrix*frustum.Front().Normalized());
    frustum.SetUp(rotationMatrix*frustum.Up().Normalized());
}

update_status ModuleCamera::PreUpdate() {
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::Update() {
    const float deltaTime = App->getDeltaTime();
    const float2& mouseMotion = App->input->GetMouseMotion();
    const float mouseWheelMotion = App->input->GetMouseWheelMotion();

    float finalMovementSpeed = movementSpeed;
    if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KeyState::KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RSHIFT) == KeyState::KEY_REPEAT) {
        finalMovementSpeed *= 2;
    }
    if (mouseWheelMotion < -FLT_EPSILON || mouseWheelMotion > FLT_EPSILON) {
        frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * mouseWheelMotion * 10 * zoomSpeed * App->getDeltaTime()));
    }
    if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KeyState::KEY_REPEAT) {
        Rotate(float3x3::RotateAxisAngle(frustum.WorldRight().Normalized(), -mouseMotion.y * rotationSpeed * DEGTORAD * deltaTime));
        Rotate(float3x3::RotateY(-mouseMotion.x * rotationSpeed * DEGTORAD * deltaTime));
        
        if (App->input->GetKey(SDL_SCANCODE_Q) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos()+(frustum.Up().Normalized() * -finalMovementSpeed * deltaTime));
        }
        if (App->input->GetKey(SDL_SCANCODE_E) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos() + (frustum.Up().Normalized() * finalMovementSpeed * deltaTime));
        }
        if (App->input->GetKey(SDL_SCANCODE_W) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * finalMovementSpeed * deltaTime));
        }
        if (App->input->GetKey(SDL_SCANCODE_S) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos() + (frustum.Front().Normalized() * -finalMovementSpeed * deltaTime));
        }
        if (App->input->GetKey(SDL_SCANCODE_A) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos() + (frustum.WorldRight().Normalized() * -finalMovementSpeed * deltaTime));
        }
        if (App->input->GetKey(SDL_SCANCODE_D) == KeyState::KEY_REPEAT)
        {
            frustum.SetPos(frustum.Pos() + (frustum.WorldRight().Normalized() * finalMovementSpeed * deltaTime));
        }
    }
    else if (App->input->GetKey(SDL_SCANCODE_F) == KeyState::KEY_REPEAT) {
        frustum.SetPos(float3(0, 3, -8));
        frustum.SetFront(float3::unitZ);
        frustum.SetUp(float3::unitY);
    }
    else if (App->input->GetKey(SDL_SCANCODE_LALT) == KeyState::KEY_REPEAT && App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT) {

    }

    return update_status::UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate() {
    return update_status::UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp() {
    return true;
}

float4x4 ModuleCamera::GetProjectionMatrix() const {
    return frustum.ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix() const {
    return frustum.ViewMatrix();
}

vec ModuleCamera::GetFront() const
{
    return frustum.Front();
}

vec ModuleCamera::GetUp() const
{
    return frustum.Up();
}

vec ModuleCamera::GetPosition() const
{
    return frustum.Pos();
}

float ModuleCamera::GetNearPlane() const
{
    return frustum.NearPlaneDistance();
}

float ModuleCamera::GetFarPlane() const
{
    return frustum.FarPlaneDistance();
}

float ModuleCamera::GetFOV() const
{
    return frustum.VerticalFov();
}

float ModuleCamera::GetAspectRatio() const
{
    return frustum.AspectRatio();
}

float ModuleCamera::GetMovementSpeed() const
{
    return movementSpeed;
}

float ModuleCamera::GetRotationSpeed() const
{
    return rotationSpeed;
}

float ModuleCamera::GetZoomSpeed() const
{
    return zoomSpeed;
}
