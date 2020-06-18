#pragma once

#include <memory>
#include <string>

#include "../lowlevel/Timestep.h"

namespace Puly {

	class Window;

	class Scene2D {
	public:

		Scene2D(Window& window);
		~Scene2D();

		void OnStart();
		void OnUpdate(Timestep deltaTime);
		void Render();

		void Reset();

		void LoadSceneFromFile(std::string path);

		std::string GetPath() const { return m_Path; }

		bool GetIsDebugging() const { return m_IsDebugging; }

	private:
		//std::shared_ptr<EntityManager> m_EntityManager;
		std::string m_Path;

		bool m_IsDebugging;
	};

}