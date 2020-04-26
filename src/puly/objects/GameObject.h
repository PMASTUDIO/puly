#pragma once

#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "..//renderer/SpriteRenderer.h"

namespace Puly {

	class GameObject {
	public:
		glm::vec3 m_Position, m_Velocity;
		float m_Scale;
		float m_Rotation;
		bool m_IsSolid;
		bool m_IsDestroyed;

		std::shared_ptr<SpriteRenderer> m_Sprite;

		GameObject();
		GameObject(glm::vec3 m_Position, std::string pathToTexture, glm::vec3 velocity = glm::vec3(0.0f), float scale = 1.0f);

		virtual void Draw();
	};

}