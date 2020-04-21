#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include <iostream>

Puly::Application::Application() : mLastFrameTime(0.0f), mSubSystems(&mWindow)
{
}

Puly::Application::~Application()
{
}

bool Puly::Application::Init()
{
	if (!mWindow.Init(1280, 720, "My Puly Engine"))
		return false;

	if (!mSubSystems.Init())
		return false;
	
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = {
		{ ShaderDataType::Float3, "a_Position" }
	};

	uint32_t index = 0;
	for (const auto& element : layout) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGl(element.Type), 
			element.Normalized ? GL_TRUE : GL_FALSE, 
			layout.GetStride(), 
			(const void*)element.Offset
		);

		index++;
	}

	unsigned int indices[3] = { 0, 1, 2 };
	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
	
	// Shaders
	auto shaderFromFile = ResourceManager::GetShaderText("resources/shaders/triangleVertexShader.glsl", "resources/shaders/triangleFragmentShader.glsl");
	m_Shader.Compile(std::get<0>(shaderFromFile), std::get<1>(shaderFromFile));

	return true;
}

bool Puly::Application::Shutdown()
{
	mSubSystems.Shutdown();
	mWindow.Shutdown();

	return true;
}

void Puly::Application::Run()
{
	int targetFPS = atoi(mSubSystems.configurator.GetValue("lockFPS"));

	while (!mWindow.ShouldClose()) {
		Timestep deltaTime = GetDeltaTime(targetFPS);

		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader.Bind();

		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

		mWindow.Update();
		mSubSystems.OnUpdate(deltaTime);
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
