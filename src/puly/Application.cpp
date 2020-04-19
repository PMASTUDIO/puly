#include "Application.h"

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
	while (!mWindow.ShouldClose()) {
		mWindow.Update();
	}
}
