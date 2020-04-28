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
#include <string>

#include <windows.h>

#include "..//dataStructures/ArrayStack.h"
#include "..//..//platform/FileOp.h"

#include <queue>

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

	///*if (Input::IsKeyPressed(mWindow, PL_KEY_F1)) {
	//	menuOpened = true;
	//}

	//if (Input::IsKeyPressed(mWindow, PL_KEY_F2)) {
	//	menuOpened = false;
	//}*/

	//if (menuOpened) {
	//	DebugPrimitiveMenu(dt);
	//}
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

void Puly::ImguiSystem::PropertyPanel(std::vector<GameObject*> v_Objects)
{
	if (selectedGameObject != -1) {
		std::string pageName = "Properties for " + v_Objects[selectedGameObject]->m_DebugName;
		ImGui::Begin(pageName.c_str());

		for (auto& component : v_Objects[selectedGameObject]->GetComponents()) {
			component->DebugGUI();
		}

		ImGui::End();
	}
}

void Puly::ImguiSystem::SceneTreeMenu(std::vector<GameObject*> objects)
{
	ImGui::Begin("Scene");

	if (ImGui::CollapsingHeader("Game Objects"))
	{
		int i = 0;
		for (auto& item : objects) {
			if (ImGui::TreeNode(item->m_DebugName.c_str())) /*ImGui::Selectable(item.first.c_str())*/
			{
				ImGui::DragFloat3("Position", glm::value_ptr<float>(item->m_Position), 0.2f, -10.0f, 10.0f);
				ImGui::DragFloat("Rotation", &item->m_Rotation, 1.0f, 0, 360.0f);
				ImGui::DragFloat("Scale", &item->m_Scale, 0.2f, 0.0f, 10.0f);

				if(ImGui::Button("Edit")) {
					selectedGameObject = i;
				}

				ImGui::TreePop();
			}
			i++;
		}
	}

	ImGui::End();
}

void Puly::ImguiSystem::TextureImportMenu(bool show, std::vector<GameObject*> v_Objects, EntityManager& em)
{

	if (show) {

		ImGui::Begin("Game Object Menu");

		ImGui::InputText("Identifier:", bufIdentifier, 50);
		ImGui::InputFloat3("Initial Position:", initialPos);

		if (ImGui::Button("New object from texture")) {

			std::string pathTexture = Puly::openfilename();
			PL_LOG_INFO("Path: {}", pathTexture);

			fs::path absolutePath = fs::current_path();
			fs::path resourcesPath = absolutePath.append("resources/textures/");

			PL_LOG_INFO(resourcesPath.u8string());

			copyFile(pathTexture, resourcesPath);


			fs::path path = pathTexture;
			fs::path relativePath = fs::path("resources/textures/").append(path.filename());

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

			Puly::GameObject& bird(em.AddObject(fileNameString));
			bird.AddComponent<Puly::SpriteRenderer>(relativePath.u8string().c_str());
			//objects[fileNameString] = newObject;
		}

		ImGui::End();

		SceneTreeMenu(v_Objects);
		PropertyPanel(v_Objects);
	}

	
}

std::queue<float> performanceStack;

void Puly::ImguiSystem::PerformanceMenu(bool show, Timestep dt)
{
	if (show) {
		ImGui::Begin("Performance");

		ImGui::Text("Delta Time: %f", (float)dt);
		ImGui::Text("FPS: %f", 1.0f / dt);

		if (performanceStack.size() < 100) {
			performanceStack.push(dt);
		}
		else {
			performanceStack.pop();
			performanceStack.push(dt);
		}

		float* performanceArray = &performanceStack.front();

		//performanceArr.display();

		ImGui::PlotLines("Graph", performanceArray, performanceStack.size(), 5);

		ImGui::End();
	}
}

void Puly::ImguiSystem::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
