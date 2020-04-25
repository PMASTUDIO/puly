#include "ImGuiSystem.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "..//Input.h"
#include "..//KeyCodes.h"
#include "../..//window/Window.h"
#include "Log.h"

float newLinePos[3];
float newLineFinalPos[3];

bool menuOpened = false;

Puly::ImguiSystem::ImguiSystem()
{
	debugDrawManager.reset(new DebugDrawManager());
}

Puly::ImguiSystem::~ImguiSystem()
{
}

void Puly::ImguiSystem::Init(Window* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsDark();

	mWindow = window;
}

void Puly::ImguiSystem::OnUpdate(Timestep dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = dt;

	if (Input::IsKeyPressed(mWindow, PL_KEY_F1)) {
		menuOpened = true;
	}

	if (Input::IsKeyPressed(mWindow, PL_KEY_F2)) {
		menuOpened = false;
	}

	if (menuOpened) {
		DebugPrimitiveMenu(dt);
		TextureImportMenu(dt);
	}
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Puly::ImguiSystem::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	PL_LOG_INFO("Shutdown");
}

void Puly::ImguiSystem::DebugPrimitiveMenu(Timestep dt)
{
		
	ImGui::Begin("Debugging Primitive Menu");
	ImGui::SliderFloat3("From", newLinePos, -1.0f, 1.0f);
	ImGui::SliderFloat3("To", newLineFinalPos, -1.0f, 1.0f);

	if (ImGui::Button("Add New Line")) {
		debugDrawManager->AddLine(Point(newLinePos[0], newLinePos[1], newLinePos[2]), Point(newLineFinalPos[0], newLineFinalPos[1], newLineFinalPos[2]));
	}

	ImGui::End();

	debugDrawManager->OnUpdate();
}

void Puly::ImguiSystem::TextureImportMenu(Timestep dt)
{

	ImGui::Begin("Textures Menu");

	ImGui::ListBoxHeader("Textures");
	ImGui::ListBoxFooter();

	ImGui::End();
	
}
