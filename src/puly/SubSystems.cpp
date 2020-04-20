#include "SubSystems.h"

SubSystems::SubSystems()
{
}

SubSystems::~SubSystems()
{
}

bool SubSystems::Init()
{
	configurator.Init();
	Puly::Log::Init(atoi(configurator.GetValue("verbosityLog")));

	return true;
}

bool SubSystems::Shutdown()
{
	configurator.Shutdown();

	return true;
}
