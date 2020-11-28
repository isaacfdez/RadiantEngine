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

	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:
	void Rotate(float3x3 rotationMatrix);

private:
	Frustum frustum;
	float movementSpeed = 5.0f;
	float rotationSpeed = 25.0f;
	float zoomSpeed = 5.0f;

};

