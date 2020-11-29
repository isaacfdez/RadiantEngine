#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleCamera : public Module {
public:
	bool Init() override;

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp() override;

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;
	vec GetFront() const;
	vec GetUp() const;
	vec GetPosition() const;
	float GetNearPlane() const;
	float GetFarPlane() const;
	float GetFOV() const;
	float GetAspectRatio() const;
	float GetMovementSpeed() const;
	float GetRotationSpeed() const;
	float GetZoomSpeed() const;

private:
	void Rotate(float3x3 rotationMatrix);

private:
	Frustum frustum;
	float movementSpeed = 5.0f;
	float rotationSpeed = 25.0f;
	float zoomSpeed = 5.0f;
	float distanceFocus = 10.0f;
};

