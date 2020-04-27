#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "lowlevel/debugging/primitives/Point.h"

#include "./renderer/OrthographicCameraController.h"

#include "renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

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
	mSubSystems->Shutdown();
	mWindow.Shutdown();

	return true;
}

void Puly::Application::OnEvent(Event& evt)
{
	m_CameraController.OnEvent(evt);
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
		m_CameraController.OnUpdate(&mWindow, deltaTime);

		Renderer::BeginScene(m_CameraController.GetCamera());

		// Demo game
		demoGame.Update(deltaTime);
		demoGame.Render();

		//myFirstSprite->DrawSprite(glm::vec2(0.0f), glm::vec2(1.0f), 0.0f, glm::vec3(1.0f));

		//PL_LOG_INFO("FPS: {}", 1.0f / deltaTime);

		Renderer::EndScene();

		// ------- DEMO SCENE ENDED --------

		mSubSystems->OnUpdate(deltaTime);
		mSubSystems->imGuiSystem->TextureImportMenu(true, demoGame.v_Objects);
		mSubSystems->imGuiSystem->Render();

		mWindow.Update();
	}
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
