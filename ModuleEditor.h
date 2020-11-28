#pragma once

#include "Module.h"

class ModuleEditor : public Module
{
public:
	bool Init() override;
	
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;

	bool CleanUp() override;

private:
	bool consoleEnabled = true;
	bool configEnabled = true;
	bool aboutEnabled = true;
	bool propertiesEnabled = true;
};

