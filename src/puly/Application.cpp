#include "Application.h"

#include "lowlevel/debugging/Log.h"
#include "lowlevel/ResourceManager.h"

#include "lowlevel/debugging/primitives/Point.h"

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

	debugDrawManager.reset(new DebugDrawManager());

	debugDrawManager->AddLine( Point(1.0f, 1.0f, 1.0f), Point(0.0f, 0.0f, 0.0f) );

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

		debugDrawManager->OnUpdate();

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
