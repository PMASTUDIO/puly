#pragma once

#include <memory>

#include "OrthographicCamera.h"
#include "..//window/Window.h"
#include "..//lowlevel/Timestep.h"

namespace Puly {
	class OrthographicCamera2DController {
	public:
		
		static void HandleCameraWithInput(OrtographicCamera* camera, Window* window, Timestep deltaTime, float speed);

	};
}