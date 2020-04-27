#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "..//renderer/SpriteRenderer.h"
#include "..//ecs/Component.h"

#include "../lowlevel/Timestep.h"

class EntityManager;
//class Component;

namespace Puly {

	class GameObject {
	public:
		glm::vec3 m_Position, m_Velocity;
		float m_Scale;
		float m_Rotation;
		bool m_IsSolid;
		bool m_IsActive;

		std::shared_ptr<SpriteRenderer> m_Sprite;

		GameObject(glm::vec3 m_Position = glm::vec3(0.0f), glm::vec3 velocity = glm::vec3(0.0f), float scale = 1.0f);

		void Update(Timestep dt);
		
		virtual void Draw();

		void Destroy();

	private:
		std::vector<Component*> v_Components;
	};

}