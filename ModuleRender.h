#pragma once
#include "Module.h"

class ModuleRender : public Module {
public:
	bool Init() override;

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp() override;

	void WindowResized(unsigned width, unsigned height);
	void* getContext();

private:
	void* context = nullptr;

};