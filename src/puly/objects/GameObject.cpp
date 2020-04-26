#include "GameObject.h"

Puly::GameObject::GameObject() 
	: m_Position(0.0f), m_Scale(1.0f), m_Velocity(0.0f), m_Rotation(0.0f), m_IsSolid(false), m_IsDestroyed(false)
{
}

Puly::GameObject::GameObject(glm::vec3 m_Position, std::string pathToTexture, glm::vec3 velocity, float scale)
	: m_Position(m_Position), m_Scale(scale), m_Velocity(velocity), m_Rotation(0.0f), m_IsSolid(false), m_IsDestroyed(false)
{
	m_Sprite = std::make_shared<SpriteRenderer>(pathToTexture.c_str());
}

void Puly::GameObject::Draw()
{
	m_Sprite->DrawSprite(glm::vec2(m_Position.x, m_Position.y), glm::vec2(m_Scale), glm::radians(m_Rotation), glm::vec3(1.0f));
}
