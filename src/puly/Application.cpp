#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "lowlevel/debugging/primitives/Point.h"

#include "./renderer/OrthographicCameraController.h"

#include "renderer/Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Puly::Application::Application() : mLastFrameTime(0.0f), demoGame(1280, 720), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	mSubSystems.reset(new SubSystems(&mWindow));
	m_Shader.reset(new Shader());
	m_TextureShader.reset(new Shader());
}

Puly::Application::~Application()
{
}

bool Puly::Application::Init()
{
	if (!mWindow.Init(1280, 720, "My Puly Engine"))
		return false;

	if (!mSubSystems->Init())
		return false;

	// Demo game
	demoGame.Start();

	//myFirstSprite.reset(new SpriteRenderer(m_TextureShader, "resources/textures/checkerboard.png"));

	return true;
}

bool Puly::Application::Shutdown()
{
	mSubSystems->Shutdown();
	mWindow.Shutdown();

	return true;
}

void Puly::Application::Run()
{
	int targetFPS = atoi(mSubSystems->configurator.GetValue("lockFPS"));

	while (!mWindow.ShouldClose()) {
		Timestep deltaTime = GetDeltaTime(targetFPS);

		RenderCommand::SetClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		RenderCommand::Clear();

		// Demo scene
		OrthographicCamera2DController::HandleCameraWithInput(&m_Camera, &mWindow, deltaTime, 1.0f);

		Renderer::BeginScene(m_Camera);

		// Demo game
		demoGame.Update(deltaTime);
		demoGame.Render();

		//myFirstSprite->DrawSprite(glm::vec2(0.0f), glm::vec2(1.0f), 0.0f, glm::vec3(1.0f));

		Renderer::EndScene();

		// ------- DEMO SCENE ENDED --------

		mSubSystems->OnUpdate(deltaTime);
		mSubSystems->imGuiSystem->TextureImportMenu(true, demoGame.v_SpriteRenderers);
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
