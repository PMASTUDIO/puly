#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "..//renderer/SpriteRenderer.h"
#include "..//ecs/Component.h"

#include "../lowlevel/Timestep.h"
//class Component;

namespace Puly {

	class EntityManager;

	class GameObject {
	public:
		std::string m_DebugName;

		glm::vec3 m_Position, m_Velocity;
		float m_Scale;
		float m_Rotation;
		bool m_IsSolid;
		bool m_IsActive;

		std::shared_ptr<SpriteRenderer> m_Sprite;

		GameObject(std::string debugName, glm::vec3 m_Position = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f), float scale = 1.0f);

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

	private:
		std::vector<Component*> v_Components;
	};

}