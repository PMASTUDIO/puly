#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "./renderer/OrthographicCameraController.h"

#include "renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "renderer/SpriteRenderer.h"

// For event 

#include "lowlevel/BaseEvents.h"

#include <iostream>
#include "lowlevel/Input.h"
#include "lowlevel/KeyCodes.h"

Puly::Application::Application() : mLastFrameTime(0.0f), mWindow() // Shader should be deleted
{
	mWindow.SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	m_Shader.reset(new Shader);
}

Puly::Application::~Application()
{
}

bool Puly::Application::Init()
{
	if (!mWindow.Init(1280, 720, "My Puly Engine"))
		return false;

	Renderer::Init();

	mSubSystems.reset(new SubSystems(&mWindow));
	if (!mSubSystems->Init())
		return false;

	// Demo game
	m_CameraController.reset(new OrthographicCamera2DController(&mWindow, 1280.0f / 720.0f, false));

	demoGame.reset(new Game(&mWindow, 1280, 720));
	demoGame->Start();

	auto shaderTexts = ResourceManager::GetShaderText("resources/shaders/colorVertexShader.glsl", "resources/shaders/colorFragmentShader.glsl");
	m_Shader->Compile(std::get<0>(shaderTexts), std::get<1>(shaderTexts));

	return true;
}

bool Puly::Application::Shutdown()
{
	//m_EntityManager->ClearData();
	Renderer::Shutdown();
	mSubSystems->Shutdown();
	mWindow.Shutdown();

	return true;
}

void Puly::Application::OnEvent(Event& evt)
{
	m_CameraController->OnEvent(evt);

	EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
	//PL_LOG_INFO("{0}", evt.ToString());
}

void Puly::Application::Run()
{
	int targetFPS = atoi(mSubSystems->configurator.GetValue("lockFPS"));

	while (!mWindow.ShouldClose()) {
		Timestep deltaTime = GetDeltaTime(targetFPS);

		RenderCommand::SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		RenderCommand::Clear();

		// Demo scene
		if (!gameMinimized) {
			if (!demoGame->mainScene.GetEntityManager()->m_IsDebugging) {
				m_CameraController->SetControlActive(false);
				m_CameraController->GetCamera().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
				m_CameraController->SetZoomLevel(1.0f);
				m_CameraController->GetCamera().SetRotation(0.0f);
			}
			else {
				m_CameraController->SetControlActive(true);
			}

			m_CameraController->OnUpdate(&mWindow, deltaTime);

			Renderer::BeginScene(m_CameraController->GetCamera());

			// Demo game
			glm::mat4 scaledQuad = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
			glm::mat4 transformQuadsTest;

			#ifdef PL_DEBUG
				m_CameraController->ShowReleaseBoundingBox();
			#endif

			for (int i = 0; i < 31; i++) {
				for (int j = 0; j < 31; j++) {
					transformQuadsTest = glm::translate(scaledQuad, glm::vec3(i * 1.2f, j * 1.2f, 0.0f));
					Renderer::Draw2DQuad(m_Shader, glm::vec4(i / 31.0f, j / 31.0f, (i * j) / 62.0f, (i * j) / 62.0f), transformQuadsTest);
				}	
			}

			demoGame->Update(deltaTime);
			demoGame->Render();

			//myFirstSprite->DrawSprite(glm::vec2(0.0f), glm::vec2(1.0f), 0.0f, glm::vec3(1.0f));

			//PL_LOG_INFO("FPS: {}", 1.0f / deltaTime);

			Renderer::EndScene();
		}
		// ------- DEMO SCENE ENDED --------

		mSubSystems->OnUpdate(deltaTime);

		#ifdef PL_DEBUG
			mSubSystems->imGuiSystem->TextureImportMenu(true, &mWindow, demoGame->mainScene.GetEntityManager()->GetObjects(), *demoGame->mainScene.GetEntityManager());
			mSubSystems->imGuiSystem->SceneTreeMenu(*demoGame->mainScene.GetEntityManager(), demoGame->mainScene.GetEntityManager()->GetObjects());
			mSubSystems->imGuiSystem->PropertyPanel(*demoGame->mainScene.GetEntityManager(), demoGame->mainScene.GetEntityManager()->GetObjects());
			mSubSystems->imGuiSystem->PlayPauseMenu(*demoGame->mainScene.GetEntityManager());
			mSubSystems->imGuiSystem->PerformanceMenu(true, deltaTime);
			mSubSystems->imGuiSystem->TopMenu(demoGame->mainScene);

			mSubSystems->imGuiSystem->Render();

			if (Input::IsKeyPressed(&mWindow, PL_KEY_LEFT_CONTROL)) {
				if (Input::IsKeyPressed(&mWindow, PL_KEY_S)) {
					demoGame->mainScene.GetEntityManager()->SaveScene();
				}
			}
		#endif

		mWindow.Update();
	}
}

bool Puly::Application::OnWindowResize(WindowResizeEvent& e)
{
	if (e.GetWidth() == 0 || e.GetHeight() == 0) {
		gameMinimized = true;
		return false;
	}

	gameMinimized = false;
	Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

	float zoom = e.GetWidth() / 1280.0f;

	//m_CameraController.SetZoomLevel(zoom);

	return false;
}

float Puly::Application::GetDeltaTime(int targetFPS)
{
	float currentTime = glfwGetTime();
	Timestep timestep = currentTime - mLastFrameTime;

	if (timestep > 1.0f) {
		timestep = 1.0f / targetFPS;
	}

	mLastFrameTime = currentTime;

	return timestep;
}
