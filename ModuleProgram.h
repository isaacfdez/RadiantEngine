#pragma once
#include "Module.h"

class ModuleProgram : public Module
{
public:
	bool Init();
	bool CleanUp();

private:
	unsigned program = 0;
};

