#pragma once

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

		Window* m_Owner;

		glm::vec3 m_Position, m_Velocity;
		glm::vec3 m_Scale;
		float m_Rotation;
		bool m_IsSolid;
		bool m_IsActive;

		bool m_Debugging = false;

		std::shared_ptr<SpriteRenderer> m_Sprite;

		GameObject(Window* owner, int priority, std::string debugName, glm::vec3 m_Position = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f));

		void Update(Timestep dt);
		
		virtual void Draw();

		void Destroy();

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&& ... args) {
			T* newComponent(new T(std::forward<TArgs>(args)...));

			newComponent->m_Owner = this;
			v_Components.emplace_back(newComponent);
			newComponent->Init();

			return *newComponent;
		}

		std::vector<Component*> GetComponents() const { return v_Components; }

		void ResetComponents();

		bool operator< (const GameObject& other) const {
			return m_Priority < other.m_Priority;
		}

		int m_Priority;

	private:
		std::vector<Component*> v_Components;
	};

}