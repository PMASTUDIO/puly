#include "GameObject.h"

Puly::GameObject::GameObject(Window* owner, int priority, std::string debugName, glm::vec3 m_Position, glm::vec3 velocity, glm::vec3 scale)
	: m_Owner(owner), m_Priority(priority),m_DebugName(debugName), m_Position(m_Position), m_Scale(scale), m_Velocity(velocity), m_Rotation(0.0f), m_IsSolid(false), m_IsActive(true)
{
	//m_Sprite = std::make_shared<SpriteRenderer>(pathToTexture.c_str());
}

void Puly::GameObject::Update(Timestep dt)
{
	for (auto& component : v_Components) {
		if (m_Debugging) {
			component->m_State = PL_COMP_DEBUGGING;
		}
		else {
			component->m_State = PL_COMP_ACTIVE;
		}
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

void Puly::GameObject::ResetComponents()
{
	for (auto& component : v_Components) {
		//component.~Component();
	}
}
