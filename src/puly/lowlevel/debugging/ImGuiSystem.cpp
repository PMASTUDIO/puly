#include "ImGuiSystem.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "..//Input.h"
#include "..//KeyCodes.h"
#include "../..//window/Window.h"
#include "Log.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../platform/windows/FileOpenDialog.h"

#include <filesystem>

float newLinePos[3];
float newLineFinalPos[3];

bool menuOpened = false;

namespace fs = std::experimental::filesystem;

static char bufIdentifier[50] = "";
float initialPos[3] = { 0.0f };

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
	}

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

void Puly::ImguiSystem::SceneTreeMenu(std::map<std::string, std::shared_ptr<GameObject>>& objects)
{
	ImGui::Begin("Scene");

	if (ImGui::CollapsingHeader("Game Objects"))
	{
		for (auto& item : objects) {
			if (ImGui::TreeNode(item.first.c_str()) /*ImGui::Selectable(item.first.c_str())*/)
			{
				ImGui::DragFloat3("Position", glm::value_ptr<float>(item.second->m_Position), 0.2f, -10.0f, 10.0f);
				ImGui::DragFloat("Rotation", &item.second->m_Rotation, 1.0f, 0, 360.0f);
				ImGui::DragFloat("Scale", &item.second->m_Scale, 0.2f, -10.0f, 10.0f);
				//item.second->m_Position = glm::vec3(transformPos[0], transformPos[1], transformPos[2]);
				ImGui::TreePop();
			}
		}
	}

	ImGui::End();
}

void Puly::ImguiSystem::TextureImportMenu(bool show, std::map<std::string, std::shared_ptr<GameObject>>& objects)
{

	if (show) {

		ImGui::Begin("Game Object Menu");

		ImGui::InputText("Identifier:", bufIdentifier, 50);
		ImGui::InputFloat3("Initial Position:", initialPos);

		if (ImGui::Button("New object from texture")) {

			std::string pathTexture = Puly::openfilename();
			PL_LOG_INFO("Path: {}", pathTexture);

			std::shared_ptr<GameObject> newObject;
			newObject.reset(new GameObject(glm::vec3(initialPos[0], initialPos[1], initialPos[2]), pathTexture));

			fs::path path = pathTexture;

			std::string fileNameString;
			
			if (strcmp(bufIdentifier, "")) {
				fileNameString = bufIdentifier;
				memset(bufIdentifier, 0, sizeof(bufIdentifier));
			}
			else {
				// if it's empty then use the texture file name
				fs::path fileName = path.stem();
				fileNameString = fileName.u8string();
			}

			objects[fileNameString] = newObject;
		}

		ImGui::End();

		SceneTreeMenu(objects);
	}

	
}

void Puly::ImguiSystem::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
