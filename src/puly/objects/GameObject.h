#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "..//renderer/SpriteRenderer.h"
#include "..//ecs/Component.h"

#include "../lowlevel/Timestep.h"

#include "../window/Window.h"
#include "../lowlevel/Scene.h"

#include "../ecs/Scene2D.h"
//class Component;

namespace Puly {

	class GameObject {
	public:
		std::string m_DebugName;

		Window& m_Owner;

		glm::vec3 m_Position, m_Velocity, m_Scale;
		float m_Rotation;
		bool m_IsActive;

		bool m_Debugging = false;

		GameObject() = default;
		GameObject(Window& owner, int priority, std::string debugName, entt::entity handle, Scene2D* sceneOwner, bool isProcedural = false);

		void Update(Timestep dt);
		
		virtual void Draw();

		void Destroy();

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&& ... args) {
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<TArgs>(args)...);
		}

		template <typename T>
		void RemoveComponent() {
			m_Scene->m_Registry.remove<T>();
		}

		template <typename T>
		bool HasComponent() const {
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template <typename T>
		T* GetComponent() {
			return m_Scene->m_Registry.try_get<T>(m_EntityHandle);
		}

		//std::vector<Component*> GetComponents() const { return v_Components; }

		void ResetComponents();

		bool operator< (const GameObject& other) const {
			return m_Priority < other.m_Priority;
		}

		int m_Priority;

		void SaveInLevel(GameLevel& levelSave);

	private:
		entt::entity m_EntityHandle;
		Scene2D* m_Scene = nullptr;

		friend class Scene2D;
/*
		std::vector<Component*> v_Components;
		std::map<const std::type_info* , Component*> v_ComponentsTypeMap;*/
		bool m_IsProcedural;
	};

}