#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "window/WindowsInput.h"

Puly::Application::Application()
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

	mSubSystems.configurator.SetValue("lockFPS", "60");

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
		GetDeltaTime(targetFPS);

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
