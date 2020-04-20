#include "Application.h"

#include "lowlevel/debugging/Log.h"

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

	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glGenBuffers(1, &m_IndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

	unsigned int indices[3] = { 0, 1, 2 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vertexSrc = R"(
		#version 330 core

		layout (location = 0) in vec3 a_Position; 

		void main(){
			gl_Position = vec4(a_Position, 1.0);
		}		
	
	)";

	std::string fragmentSrc = R"(
		#version 330 core

		layout (location = 0) out vec4 color; 

		void main(){
			color = vec4(0.8, 0.2, 0.3, 1.0);
		}		
	
	)";

	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

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
		mWindow.Update();

		glBindVertexArray(m_VertexArray);
		m_Shader->Bind();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
