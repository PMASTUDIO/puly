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

	// Triangle test

	m_VAO.reset(VertexArray::Create());

	float vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f
	};

	m_VBO.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float2, "a_TexCoord" }
	};
	m_VBO->SetLayout(layout);
	m_VAO->AddVertexBuffer(m_VBO);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
	m_IBO.reset(IndexBuffer::Create(indices, sizeof(indices)));
	m_VAO->SetIndexBuffer(m_IBO);

	auto shaderTexts = ResourceManager::GetShaderText("resources/shaders/triangleVertexShader.glsl", "resources/shaders/triangleFragmentShader.glsl");
	m_Shader->Compile(std::get<0>(shaderTexts), std::get<1>(shaderTexts));

	auto textureShaderTexts = ResourceManager::GetShaderText("resources/shaders/textureVertexShader.glsl", "resources/shaders/textureFragmentShader.glsl");
	m_TextureShader->Compile(std::get<0>(textureShaderTexts), std::get<1>(textureShaderTexts));

	m_Texture = Puly::Texture2D::Create("resources/textures/checkerboard.png");

	m_TextureShader->Bind();
	m_TextureShader->UploadUniform1i("u_Texture", 0);

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
		OrthographicCamera2DController::HandleCameraWithInput(&m_Camera, &mWindow, deltaTime, 1.0f);

		Renderer::BeginScene(m_Camera);

		glm::mat4 squaresScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.13f, 1.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * squaresScale;
				Renderer::Submit(m_VAO, m_Shader, transform);
			}
		}

		m_Texture->Bind();

		Renderer::Submit(m_VAO, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

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
