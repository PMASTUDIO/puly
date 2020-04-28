#pragma once

#include <memory>
#include <map>
#include "DebugDrawManager.h"
#include "..//Timestep.h"

#include "..//..//objects/GameObject.h"

#include "..//..//ecs/EntityManager.h"

class Window;

namespace Puly {

	class ImguiSystem {
	public:
		ImguiSystem();
		~ImguiSystem();

		void Init(Window* window);

		void OnUpdate(Timestep dt);

		void Shutdown();

		void TextureImportMenu(bool show, std::vector<GameObject*> v_Objects, EntityManager& em);

		void PerformanceMenu(bool show, Timestep dt);

		void Render();

	private:
		std::unique_ptr<DebugDrawManager> debugDrawManager;
		Window* mWindow;

		void DebugPrimitiveMenu(Timestep dt);

		void SceneTreeMenu(std::vector<GameObject*> objects);
	};

}