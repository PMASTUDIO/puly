#pragma once

#include "lowlevel/Configuration.h"
#include "lowlevel/Timestep.h"
#include "lowlevel/debugging/Log.h"

class SubSystems {
public:
	SubSystems();
	~SubSystems();

	bool Init();
	bool Shutdown();

	Puly::Configurations configurator;
};

