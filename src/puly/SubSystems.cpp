#include "SubSystems.h"

SubSystems::SubSystems(Window* mainWindow) : mainWindow(mainWindow)
{
}

SubSystems::~SubSystems()
{
}

bool SubSystems::Init()
{
	configurator.Init();
	Puly::Log::Init(atoi(configurator.GetValue("verbosityLog")));
	imGuiSystem.Init(mainWindow);

	return true;
}

void SubSystems::OnUpdate(Puly::Timestep dt)
{
	imGuiSystem.OnUpdate(dt);
}

bool SubSystems::Shutdown()
{
	imGuiSystem.Shutdown();
	configurator.Shutdown();

	return true;
}
