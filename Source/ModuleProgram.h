#pragma once
#include "Module.h"
#include "Globals.h"
class ModuleProgram : public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	const Uint8* keyboard = NULL;
};

