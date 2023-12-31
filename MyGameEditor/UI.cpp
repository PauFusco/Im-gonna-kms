#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>

#include "Application.h"
#include "Globals.h"
#include "UI.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

UI::UI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

UI::~UI()
{
}

bool UI::createImGuiContext()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->window->GLContext);

	

	if (ImGui_ImplOpenGL3_Init())   return true;
	else    return false;
}

void UI::setUpUI()
{
}

bool UI::Init()
{
	if (createImGuiContext())   return true;
	else    return false;
}

update_status UI::PreUpdate()
{
	//setUpUI();
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGuiDockNodeFlags dock_flags = 0;
	dock_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(0, dock_flags);

	ImGui::DockSpaceOverViewport();

	ImGui::ShowDemoWindow();

	return UPDATE_CONTINUE;
}

update_status UI::PostUpdate()
{
	// Render UI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

bool UI::CleanUp()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}