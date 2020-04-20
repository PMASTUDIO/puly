#pragma once

#include "lowlevel/Configuration.h"
#include "lowlevel/Timestep.h"
#include "lowlevel/debugging/Log.h"
#include "lowlevel/debugging/ImGuiSystem.h"

class SubSystems {
public:
	SubSystems(Window* mainWindow);
	~SubSystems();

	bool Init();
	void OnUpdate(Puly::Timestep dt);
	bool Shutdown();

	Puly::Configurations configurator;
	Puly::ImguiSystem imGuiSystem;

	Window* mainWindow;
};

