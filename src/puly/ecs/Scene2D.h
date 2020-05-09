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

		void Reset();

		void LoadSceneFromFile(std::string path);

		std::string GetPath() const { return m_Path; }

	private:
		std::shared_ptr<EntityManager> m_EntityManager;
		std::string m_Path;
	};

}