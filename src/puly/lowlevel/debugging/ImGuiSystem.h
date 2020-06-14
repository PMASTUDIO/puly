#pragma once

#include <memory>
#include <map>

#include "..//Timestep.h"

#include "..//..//objects/GameObject.h"

#include "..//..//ecs/EntityManager.h"
#include "../../ecs/Scene2D.h"

class Window;

namespace Puly {

	class ImguiSystem {
	public:
		ImguiSystem();
		~ImguiSystem();

		void Init(Window* window);

		void OnUpdate(Timestep dt);

		void Shutdown();

		static void ResetSelectedObj() { selectedGameObject = -1; };

		void TextureImportMenu(bool show, Window* window, std::vector<GameObject*> v_Objects, EntityManager& em);
		void PerformanceMenu(bool show, Timestep dt);
		void PlayPauseMenu(EntityManager& em);
		void TopMenu(Scene2D& scene);

		void PropertyPanel(EntityManager& em, std::vector<GameObject*>& v_Objects);
		void SceneTreeMenu(EntityManager& em, std::vector<GameObject*>& objects);

		void BeginDockable();
		void EndDockable();

		void Render(Window* window);

	private:
		Window* mWindow;

		static int selectedGameObject;
	};

}