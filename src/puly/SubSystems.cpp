#include "SubSystems.h"

SubSystems::SubSystems(Window* mainWindow) : mainWindow(mainWindow)
{
	imGuiSystem = std::make_shared<Puly::ImguiSystem>();
}

SubSystems::~SubSystems()
{
}

bool SubSystems::Init()
{
	configurator.Init();
	Puly::Log::Init(atoi(configurator.GetValue("verbosityLog")));

	#ifdef PL_DEBUG
		imGuiSystem->Init(mainWindow);
	#endif

	return true;
}

void SubSystems::OnUpdate(Puly::Timestep dt)
{
	#ifdef PL_DEBUG
		imGuiSystem->OnUpdate(dt);
	#endif
}

bool SubSystems::Shutdown()
{
	#ifdef PL_DEBUG
		imGuiSystem->Shutdown();
	#endif
	configurator.Shutdown();

	return true;
}
