#pragma once

#include <map>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "..//renderer/SpriteRenderer.h"
#include "..//ecs/Component.h"

#include "../lowlevel/Timestep.h"

#include "../window/Window.h"
//class Component;

namespace Puly {

	class EntityManager;

	class GameObject {
	public:
		std::string m_DebugName;

		Window& m_Owner;

		glm::vec3 m_Position, m_Velocity;
		glm::vec3 m_Scale;
		float m_Rotation;
		bool m_IsSolid;
		bool m_IsActive;

		bool m_Debugging = false;

		std::shared_ptr<SpriteRenderer> m_Sprite;

		GameObject(Window& owner, int priority, std::string debugName, glm::vec3 m_Position = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

		void Update(Timestep dt);
		
		virtual void Draw();

		void Destroy();

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&& ... args) {
			T* newComponent(new T(std::forward<TArgs>(args)...));

			newComponent->m_Owner = this;
			v_Components.emplace_back(newComponent);
			v_ComponentsTypeMap[&typeid(*newComponent)] = newComponent;
			newComponent->Init();

			return *newComponent;
		}

		template <typename T>
		bool HasComponent() const {
			return v_ComponentsTypeMap.count(&typeid(T));
		}

		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(v_ComponentsTypeMap[&typeid(T)]);
		}

		std::vector<Component*> GetComponents() const { return v_Components; }

		void ResetComponents();

		bool operator< (const GameObject& other) const {
			return m_Priority < other.m_Priority;
		}

		int m_Priority;

	private:
		std::vector<Component*> v_Components;
		std::map<const std::type_info* , Component*> v_ComponentsTypeMap;
	};

}