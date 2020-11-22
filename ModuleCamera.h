#pragma once

#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleCamera : public Module
{
public:
	
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(int width, int height);

	void SetFOV(float h_fov);
	void SetAspectRatio(float aspect_ratio);
	void SetPlaneDistances(float near_plane, float far_plane);
	void SetPosition(float x, float y, float z);
	void SetOrientation(float x, float y, float z);
	void Translate(vec translation);
	void Rotate(float3x3 rotationMatrix);
	void LookAt(float x, float y, float z);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();

private:
	Frustum frustum;
	float movementSpeed = 5.0f;
	float rotationSpeed = 100.0f;
	float zoomSpeed = 5.0f;
};
