#include "GameObject.h"

Puly::GameObject::GameObject(std::string debugName, glm::vec3 m_Position, glm::vec3 velocity, float scale)
	: m_DebugName(debugName), m_Position(m_Position), m_Scale(scale), m_Velocity(velocity), m_Rotation(0.0f), m_IsSolid(false), m_IsActive(true)
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
}

void Puly::GameObject::Destroy()
{
	m_IsActive = false;
}
