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

#include <typeindex>

#include "../../platform/windows/FileOpenDialog.h"

#include <filesystem>
#include <string>
#include "..//..//platform/FileOp.h"

#include "../..//ecs/components/MoveComponent.h"

#include <queue>
#include "../../ecs/components/Flappy/FlappyControllerComponent.h"
#include "../../ecs/components/BulletComponent.h"
#include "../../ecs/components/ColoredSquare.h"
#include "../../ecs/components/Breakout/BallBreakoutComponent.h"
#include "../../ecs/components/Effects/ParticleEmitterComponent.h"

float newLinePos[3];
float newLineFinalPos[3];

bool menuOpened = false;

namespace fs = std::experimental::filesystem;

static char bufIdentifier[50] = "";
float initialPos[3] = { 0.0f };

Puly::ImguiSystem::ImguiSystem()
{
}

Puly::ImguiSystem::~ImguiSystem()
{
}

void Puly::ImguiSystem::Init(Window* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	/*ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init();

	ImGui::StyleColorsClassic();

	mWindow = window;*/

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Puly::ImguiSystem::OnUpdate(Timestep dt)
{
	/*ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = dt;
*/
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace Demo", &dockspaceOpen, ImGuiWindowFlags_MenuBar|ImGuiWindowFlags_NoDocking);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
}

void Puly::ImguiSystem::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Puly::ImguiSystem::PropertyPanel(EntityManager& em, std::vector<GameObject*>& v_Objects)
{

	if (selectedGameObject > v_Objects.size() || em.IsEmpty()) {
		selectedGameObject = -1;
	}

	if (selectedGameObject != -1) {
		ImGui::Begin("Properties");

		std::string pageName = "Properties for " + v_Objects[selectedGameObject]->m_DebugName;
		ImGui::Text(pageName.c_str());

		for (auto& component : v_Objects[selectedGameObject]->GetComponents()) {
			component->DebugGUI();
		}

		ImGui::Separator();

		const char* listbox_items[] = { "2D Move Component", "Collider Component", "Flappy Controller Component", "Bullet Component", "Colored Component", "Breakout Ball Component", "Particle Component" };
		static int listbox_item_current = 0;

		//ImGui::ListBoxHeader("New Component", ImVec2(0, 200));
		ImGui::ListBox("Components", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items));
		//ImGui::ListBoxFooter();

		if (ImGui::Button("Add Component")) {
			switch (listbox_item_current)
			{
			case 0:
				v_Objects[selectedGameObject]->AddComponent<MoveComponent>(0.5f);
				break;
			case 1:
				v_Objects[selectedGameObject]->AddComponent<ColliderComponent>(&em);
				break;
			case 2:
				v_Objects[selectedGameObject]->AddComponent<FlappyControllerComponent>(0.5f, 1.0f);
				break;
			case 3:
				v_Objects[selectedGameObject]->AddComponent<BulletComponent>(0.5f);
				break;
			case 4:
				v_Objects[selectedGameObject]->AddComponent<ColoredComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			case 5:
				v_Objects[selectedGameObject]->AddComponent<BallBreakoutComponent>(5.0f);
				break;
			case 6:
				v_Objects[selectedGameObject]->AddComponent<ParticleEmitterComponent>();
				break;
			default:
				break;
			}
		}

		ImGui::End();
	}
}

void Puly::ImguiSystem::SceneTreeMenu(EntityManager& em, std::vector<GameObject*>& objects)
{
	ImGui::Begin("Scene");

	if (ImGui::CollapsingHeader("Game Objects"))
	{
		int i = 0;
		for (auto& item : objects) {

			if (item->m_IsActive) {

				if (ImGui::TreeNode(item->m_DebugName.c_str())) /*ImGui::Selectable(item.first.c_str())*/
				{
					ImGui::DragFloat3("Position", glm::value_ptr<float>(item->m_Position), 0.2f, -10.0f, 10.0f);
					ImGui::DragFloat("Rotation", &item->m_Rotation, 1.0f, 0, 360.0f);
					ImGui::DragFloat3("Scale", glm::value_ptr<float>(item->m_Scale), 0.2f, 0.0f, 10.0f);
					if (ImGui::DragInt("Z-Index", &item->m_Priority)) {
						em.SortByPriority();
					}

					if (ImGui::Button("Edit")) {
						selectedGameObject = i;
					}

					if (ImGui::Button("Delete")) {
						selectedGameObject = -1;
						item->Destroy();
					}

					ImGui::TreePop();
				}
			}
			i++;
		}
	}

	ImGui::End();
}

int Puly::ImguiSystem::selectedGameObject = -1;

void Puly::ImguiSystem::TopMenu(Scene2D& scene)
{
	if (ImGui::BeginMainMenuBar()) {
	
		if (ImGui::BeginMenu("File")) {
		
			if (ImGui::MenuItem("New Level")) {
				scene.Reset();
			}

			if (ImGui::MenuItem("Save Level")) {
				scene.GetEntityManager()->SaveScene();
			}

			if (ImGui::MenuItem("Save Level As")) {
				scene.GetEntityManager()->SaveScene(false);
			}

			if (ImGui::MenuItem("Load Level")) {
				scene.Reset();
				scene.LoadSceneFromFile(openfilename());
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Reset Level")) {
				scene.LoadSceneFromFile(scene.GetPath());
			}
			
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
		
	}
}

void Puly::ImguiSystem::TextureImportMenu(bool show, Window* window, std::vector<GameObject*> v_Objects, EntityManager& em)
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

			Puly::GameObject& bird(em.AddObject(1, fileNameString));
			bird.AddComponent<Puly::SpriteRenderer>(relativePath.u8string().c_str());
		}

		if (ImGui::Button("New empty object")) {
			std::string fileNameString;

			if (strcmp(bufIdentifier, "")) {
				fileNameString = bufIdentifier;
				memset(bufIdentifier, 0, sizeof(bufIdentifier));
			}
			else {
				// if it's empty then use the texture file name
				fileNameString = "empty";
			}

			Puly::GameObject& newObj(em.AddObject(1, fileNameString));
		}

		ImGui::End();
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

		ImGui::ShowMetricsWindow();

		ImGui::ShowStyleSelector("Editor Style");

		ImGui::End();
	}
}

void Puly::ImguiSystem::PlayPauseMenu(EntityManager& em)
{
	ImGui::Begin("Runtime");
	
	if(ImGui::Button("Play")) {
		em.m_IsDebugging = false;
	}

	if (ImGui::Button("Pause")) {
		em.m_IsDebugging = true;
		//em.ResetObjects();
	}

	ImGui::End();
}

void Puly::ImguiSystem::Render(Window* window)
{
	ImGui::End();

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}
