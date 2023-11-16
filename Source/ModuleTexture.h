#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "DirectXTex.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	DirectX::ScratchImage LoadTexture(const char* file);
	unsigned CreateTexture(DirectX::ScratchImage* texture);

private:

};

