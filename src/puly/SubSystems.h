#pragma once

#include "lowlevel/Configuration.h"
#include "lowlevel/Timestep.h"

class SubSystems {
public:
	SubSystems();
	~SubSystems();

	bool Init();
	bool Shutdown();

	Puly::Configurations configurator;
};

