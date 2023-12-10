#pragma once
#include "Module.h"
#include "Globals.h"
#include "GL/glew.h"
#include "FrameBuffer.h"
#include <vector>
#include <string>

class ModuleEditor : public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;
	void DrawConsole(const char* title);
	void DrawFunctionalities();
	void DrawMenu();
	void DrawConfig();
	void DrawVariables();
	void AddLogs(std::string log);
	void ClearLogs();
	FrameBuffer GetSceneBuffer() const { return sceneBuffer; }
private:
	std::vector<std::string> m_logs;
	FrameBuffer sceneBuffer;
};