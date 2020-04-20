#include "Application.h"

#include <iostream>

Puly::Application::Application() : mLastFrameTime(0.0f)
{
}

Puly::Application::~Application()
{
}

bool Puly::Application::Init()
{
	if (!mSubSystems.Init())
		return false;

	if (!mWindow.Init(1280, 720, "My Puly Engine"))
		return false;

	return true;
}

bool Puly::Application::Shutdown()
{
	mWindow.Shutdown();
	mSubSystems.Shutdown();

	return true;
}

void Puly::Application::Run()
{
	int targetFPS = atoi(mSubSystems.configurator.GetValue("lockFPS"));

	while (!mWindow.ShouldClose()) {
		Timestep deltaTime = GetDeltaTime(targetFPS);

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
