#pragma once

#include <memory>
#include <string>
#include "entt/entt.hpp"

#include "../lowlevel/Timestep.h"

namespace Puly {

	class Window;
	class GameObject;

	class Scene2D {
	public:

		Scene2D(Window& window, const std::string& debugName = "Scene");
		~Scene2D();

		void OnStart();
		void OnUpdate(Timestep deltaTime);
		void Render();

		void Reset();

		void LoadSceneFromFile(std::string path);

		std::string GetPath() const { return m_Path; }

		bool GetIsDebugging() const { return m_IsDebugging; }

		GameObject CreateEntity(Window& windowOwner, int priority, const std::string& name = "");
		void DestroyEntity(GameObject entity);


	private:
		uint32_t m_SceneID;
		entt::entity m_SceneEntity;

		entt::registry m_Registry;

		std::string m_DebugName;

		std::string m_Path;

		bool m_IsDebugging;

		friend class GameObject;
	};

}