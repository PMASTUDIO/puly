#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "lowlevel/debugging/primitives/Point.h"

#include "renderer/Renderer.h"

#include <iostream>

Puly::Application::Application() : mLastFrameTime(0.0f), demoGame(1280, 720), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	mSubSystems.reset(new SubSystems(&mWindow));
	m_Shader.reset(new Shader());
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

	// Triangle test

	m_VAO.reset(VertexArray::Create());

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" }
	};
	m_VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(m_VBO);

	uint32_t indices[3] = { 0, 1, 2 };
	m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
	m_VAO->SetIndexBuffer(m_IBO);

	auto shaderTexts = ResourceManager::GetShaderText("resources/shaders/triangleVertexShader.glsl", "resources/shaders/triangleFragmentShader.glsl");
	m_Shader->Compile(std::get<0>(shaderTexts), std::get<1>(shaderTexts));

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

		// Demo game
		demoGame.Update(deltaTime);
		demoGame.Render();

		// Demo scene
		m_Camera.SetPosition(glm::vec3(0.5f, 0.5f, 0.0f));
		//m_Camera.SetRotation(45.0f);

		Renderer::BeginScene(m_Camera);
		Renderer::Submit(m_VAO, m_Shader);
		Renderer::EndScene();

		// ------- DEMO SCENE ENDED --------

		mSubSystems->OnUpdate(deltaTime);

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
