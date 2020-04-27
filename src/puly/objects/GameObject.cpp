#include "GameObject.h"

Puly::GameObject::GameObject(glm::vec3 m_Position, glm::vec3 velocity, float scale)
	: m_Position(m_Position), m_Scale(scale), m_Velocity(velocity), m_Rotation(0.0f), m_IsSolid(false), m_IsActive(true)
{
	//m_Sprite = std::make_shared<SpriteRenderer>(pathToTexture.c_str());
}

void Puly::GameObject::Update(Timestep dt)
{
	for (auto& component : v_Components) {
		component->Update(dt);
	}
}

void Puly::GameObject::Draw()
{
	for (auto& component : v_Components) {
		component->Render();
	}
	//	m_Sprite->DrawSprite(glm::vec2(m_Position.x, m_Position.y), glm::vec2(m_Scale), glm::radians(m_Rotation), glm::vec3(1.0f));
}

void Puly::GameObject::Destroy()
{
	m_IsActive = false;
}
