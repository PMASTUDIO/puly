#pragma once

#include <memory>
#include "EntityManager.h"

namespace Puly {

	class Scene2D {
	public:

		Scene2D(Window& window);
		~Scene2D();

		std::shared_ptr<EntityManager> GetEntityManager() const { return m_EntityManager; }

		void OnStart();
		void OnUpdate(Timestep deltaTime);
		void Render();

		void LoadSceneFromFile(std::string path);

	private:
		std::shared_ptr<EntityManager> m_EntityManager;
	};

}