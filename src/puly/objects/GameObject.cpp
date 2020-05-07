#include "GameObject.h"

Puly::GameObject::GameObject(Window& owner, int priority, std::string debugName, glm::vec3 m_Position, glm::vec3 velocity, glm::vec3 scale)
	: m_Owner(owner), m_Priority(priority), m_DebugName(debugName), m_Position(m_Position), m_Scale(scale), m_Velocity(velocity), m_Rotation(0.0f), m_IsActive(true)
{

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
	PL_LOG_INFO("Destroyed");
	m_IsActive = false;
}

void Puly::GameObject::ResetComponents()
{
	for (auto& component : v_Components) {
		//component.~Component();
	}
}

void Puly::GameObject::SaveInLevel(GameLevel& levelSave)
{
	levelSave.configurator.SetValue(m_DebugName.c_str(), "priority", std::to_string(m_Priority).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "isActive", std::to_string(m_IsActive).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "positionX", std::to_string(m_Position.x).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "positionY", std::to_string(m_Position.y).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "positionZ", std::to_string(m_Position.z).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "scaleX", std::to_string(m_Scale.x).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "scaleY", std::to_string(m_Scale.y).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "scaleZ", std::to_string(m_Scale.z).c_str());
	levelSave.configurator.SetValue(m_DebugName.c_str(), "rotation", std::to_string(m_Rotation).c_str());
	for (auto& comp : v_ComponentsTypeMap) {
		comp.second->SaveInScene(":" + m_DebugName + ">" + comp.first->name(), levelSave);
		//levelSave.configurator.SetValue(comp.first->name());
	}
}
