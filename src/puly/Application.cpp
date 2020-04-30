#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "lowlevel/debugging/primitives/Point.h"

#include "./renderer/OrthographicCameraController.h"

#include "renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include "renderer/SpriteRenderer.h"

// For event testing
#include "lowlevel/BaseEvents.h"

#include <iostream>

Puly::Application::Application() : mLastFrameTime(0.0f), demoGame(1280, 720), m_CameraController(&mWindow, 1280.0f / 720.0f, true)
{
	mSubSystems.reset(new SubSystems(&mWindow));
	mWindow.SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
}

Puly::Application::~Application()
{
}

bool Puly::Application::Init()
{
	if (!mWindow.Init(1280, 720, "My Puly Engine"))
		return false;

	Renderer::Init();

	if (!mSubSystems->Init())
		return false;

	// Demo game
	demoGame.Start();

	return true;
}

bool Puly::Application::Shutdown()
{
	//m_EntityManager->ClearData();
	mSubSystems->Shutdown();
	mWindow.Shutdown();

	return true;
}

void Puly::Application::OnEvent(Event& evt)
{
	m_CameraController.OnEvent(evt);

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
			if (!demoGame.m_EntityManager->m_IsDebugging) {
				m_CameraController.SetControlActive(false);
				m_CameraController.GetCamera().SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
				m_CameraController.SetZoomLevel(1.0f);
				m_CameraController.GetCamera().SetRotation(0.0f);
			}
			else {
				m_CameraController.SetControlActive(true);
			}
			m_CameraController.OnUpdate(&mWindow, deltaTime);
			

			Renderer::BeginScene(m_CameraController.GetCamera());

			// Demo game
			demoGame.Update(deltaTime);
			demoGame.Render();

			//myFirstSprite->DrawSprite(glm::vec2(0.0f), glm::vec2(1.0f), 0.0f, glm::vec3(1.0f));

			//PL_LOG_INFO("FPS: {}", 1.0f / deltaTime);

			Renderer::EndScene();
		}
		// ------- DEMO SCENE ENDED --------

		mSubSystems->OnUpdate(deltaTime);

		#ifdef PL_DEBUG
			mSubSystems->imGuiSystem->TextureImportMenu(true, demoGame.m_EntityManager->GetObjects(), *demoGame.m_EntityManager);
			mSubSystems->imGuiSystem->PlayPauseMenu(*demoGame.m_EntityManager);
			mSubSystems->imGuiSystem->PerformanceMenu(true, deltaTime);
			mSubSystems->imGuiSystem->Render();
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
