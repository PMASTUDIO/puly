#pragma once

#include <memory>
#include <map>
#include "DebugDrawManager.h"
#include "..//Timestep.h"

#include "..//..//renderer/SpriteRenderer.h"

class Window;

namespace Puly {

	class ImguiSystem {
	public:
		ImguiSystem();
		~ImguiSystem();

		void Init(Window* window);

		void OnUpdate(Timestep dt);

		void Shutdown();

		void TextureImportMenu(bool show, std::map<std::string, std::shared_ptr<SpriteRenderer>>& textures);

		void Render();

	private:
		std::unique_ptr<DebugDrawManager> debugDrawManager;
		Window* mWindow;

		void DebugPrimitiveMenu(Timestep dt);
	};

}