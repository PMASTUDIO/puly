#pragma once

#include <memory>
#include "DebugDrawManager.h"
#include "..//Timestep.h"

class Window;

namespace Puly {

	class ImguiSystem {
	public:
		ImguiSystem();
		~ImguiSystem();

		void Init(Window* window);

		void OnUpdate(Timestep dt);

		void Shutdown();

	private:
		std::unique_ptr<DebugDrawManager> debugDrawManager;
		Window* mWindow;

		void DebugPrimitiveMenu(Timestep dt);

		void TextureImportMenu(Timestep dt);
	};

}