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
