#pragma once
#include "Module.h"

class ModuleTextures : public Module {

public:
	bool Init() override;
	
	unsigned int LoadTexture(const char* path);

	bool CleanUp() override;
};
