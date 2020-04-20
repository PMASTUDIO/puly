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
	Puly::Log::Init();

	return true;
}

bool SubSystems::Shutdown()
{
	configurator.Shutdown();

	return true;
}
