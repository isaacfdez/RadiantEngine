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

private:
	void Rotate(float3x3 rotationMatrix);

public:
	Frustum frustum;
	float movementSpeed = 5.0f;
	float rotationSpeed = 25.0f;
	float zoomSpeed = 5.0f;

};

