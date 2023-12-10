#include "ModuleEditor.h"
#include "Globals.h"

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "ModuleCamera.h"
#include "ModuleRenderExercise.h"
#include "ModelObject.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "GL/glew.h"
#include "SDL.h"
#include <string>
#include <Windows.h>

ModuleEditor::ModuleEditor()
{
}
// Destructor
ModuleEditor::~ModuleEditor()
{
}
// Called before render is available
bool ModuleEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->GetWindow(), App->GetOpenGL()->GetContext());
	ImGui_ImplOpenGL3_Init("#version 440");

	int width, height;
	SDL_GetWindowSize(App->GetWindow()->GetWindow(), &width, &height);
	sceneBuffer = FrameBuffer(width, height);

	return true;
}
update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->GetWindow()->GetWindow());
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}
void ModuleEditor::DrawFunctionalities() 
{
        DrawMenu();
if (!ImGui::Begin("Functionalities")) {
        ImGui::End();
        return;
    }
    DrawConfig();
    DrawVariables();

    ImGui::End();
}
void ModuleEditor::DrawConfig()
{
    if (!ImGui::CollapsingHeader("Config"))
        return;
    float fps = 1.0f / ImGui::GetIO().DeltaTime;
    // Display FPS as text
    ImGui::Text("FPS: %.2f", fps);

    // Display FPS graph (assuming you have a history of FPS values)
    static float fpsHistory[100] = { 0 };
    ImGui::PlotLines("FPS History", fpsHistory, IM_ARRAYSIZE(fpsHistory));

    // Display memory consumption
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(memoryStatus);
    if (GlobalMemoryStatusEx(&memoryStatus)) {
        ImGui::Text("Total Physical Memory: %.2f MB", static_cast<float>(memoryStatus.ullTotalPhys) / (1024 * 1024));
        ImGui::Text("Available Physical Memory: %.2f MB", static_cast<float>(memoryStatus.ullAvailPhys) / (1024 * 1024));
    }
    else ImGui::Text("Error getting memory information");

    // Display hardware information
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    std::string cpu;
    switch (sysInfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        cpu = "x64 (AMD or Intel)";
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        cpu = "ARM";
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        cpu = "Intel Itanium-based";
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        cpu = "x86";
        break;
    default:
        cpu = "Unknown";
        break;
    }
    ImGui::Text("CPU: %s", cpu.c_str());
    // You can add more hardware information as needed

    // Display software versions
    SDL_version sdlVersion;
    SDL_GetVersion(&sdlVersion);
    ImGui::Text("SDL Version: %d.%d.%d", sdlVersion.major, sdlVersion.minor, sdlVersion.patch);
    ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION));
}

void ModuleEditor::DrawVariables()
{
    if (!ImGui::CollapsingHeader("Variables"))
        return;
    ImGui::SeparatorText("Camera");
    float i0 = App->GetCamera()->GetSpeed();
    ImGui::InputFloat("Speed", &i0);
    App->GetCamera()->SetSpeed(i0);
    float i1 = App->GetCamera()->GetSpeedRot();
    ImGui::InputFloat("Speed Rotation", &i1);
    App->GetCamera()->SetSpeedRot(i1);

    ImGui::SeparatorText("Model Properties");
    ImGui::Text("Number of triangles %i", App->GetExercise()->GetModel()->CountTriangles());



}


void ModuleEditor::DrawMenu() {
    static bool show_about_window = false;
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Visit GitHub")) {
                // Handle visit GitHub option
                // Open the GitHub page in a browser or perform any other action
                ShellExecute(0, 0, "https://github.com/Akiramei11/MyAwesomeEngine", 0, 0, SW_SHOW);
            }
            if (ImGui::MenuItem("About")) {
                show_about_window = !show_about_window;
            }
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                // Handle quit option
                SDL_Event quitEvent;
                quitEvent.type = SDL_QUIT;
                SDL_PushEvent(&quitEvent);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    if (show_about_window) {
        ImGui::Begin("About", &show_about_window, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
        ImGui::Separator();
        ImGui::Text("By Omar Cornut and all Dear ImGui contributors.");
        ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");
        ImGui::End();
    }
}


void ModuleEditor::DrawConsole(const char* title)
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(title)) {
        ImGui::End();
        return;
    }
    ImGui::TextWrapped(
        "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
        "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
    ImGui::TextWrapped("Enter 'HELP' for help.");

    if (ImGui::SmallButton("Add Debug Text")) { AddLogs("%d some text"); AddLogs("some more text"); AddLogs("display very important message here!"); }
    ImGui::SameLine();
    if (ImGui::SmallButton("Add Debug Error")) { AddLogs("[error] something went wrong"); }
    ImGui::SameLine();
    if (ImGui::SmallButton("Clear")) { ClearLogs(); }
    ImGui::SameLine();
    bool copy_to_clipboard = ImGui::SmallButton("Copy");

    ImGui::Separator();

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLogs();
            ImGui::EndPopup();
        }
        // Display every line as a separate entry so we can change their color or add custom widgets.
        // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        // to only process visible items. The clipper will automatically measure the height of your first item and then
        // "seek" to display only items in the visible area.
        // To use the clipper we can replace your standard loop:
        //      for (int i = 0; i < Items.Size; i++)
        //   With:
        //      ImGuiListClipper clipper;
        //      clipper.Begin(Items.Size);
        //      while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // - That your items are evenly spaced (same height)
        // - That you have cheap random access to your elements (you can access them given their index,
        //   without processing all the ones before)
        // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        // We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        // to improve this example code!
        // If your items are of variable height:
        // - Split them into same height items would be simpler and facilitate random-seeking into your list.
        // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (const std::string& item : m_logs)
        {
            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.) Modify it in Log.cpp
            ImVec4 color;
            bool has_color = false;

            if (item.find("[error]") != std::string::npos) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (item.compare(0, 2, "# ") == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item.c_str());
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        ImGui::SetScrollHereY(1.0f);

        ImGui::PopStyleVar();
    }
    ImGui::EndChild();
    ImGui::End();
}

// Called every draw update
update_status ModuleEditor::Update()
{
	// Do your freestyle .................
	DrawConsole("Console");
    DrawFunctionalities();
	//ImGui::ShowDemoWindow();
	// End your freestyle.................
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	//Destroy window
	return true;
}

void ModuleEditor::AddLogs(std::string log) {
	m_logs.push_back(log);
}

void ModuleEditor::ClearLogs()
{
    m_logs.clear();
}
