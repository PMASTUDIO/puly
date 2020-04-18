#pragma once

#include "lowlevel/Configuration.h"

class SubSystems {
public:
	SubSystems();
	~SubSystems();

	bool Init();
	bool Shutdown();

	Puly::Configurations configurator;
};

