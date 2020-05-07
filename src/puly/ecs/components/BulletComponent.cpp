#include "BulletComponent.h"

#include "..//../lowlevel/Input.h"
#include "..//../lowlevel/KeyCodes.h"
#include "..//../lowlevel/debugging/Log.h"

#include "imgui.h"

#include "..//../objects/GameObject.h"

namespace Puly {
	BulletComponent::BulletComponent(float speed, float angle, float lifetime) : m_Speed(speed), m_Lieftime(lifetime), m_Origin(0.0f), m_AngleDeg(angle)
	{
		m_Angle = glm::radians(m_AngleDeg);
	}
	void BulletComponent::Init()
	{
		m_Origin = m_Owner->m_Position;
	}
	void BulletComponent::Update(float deltaTime)
	{

		if (m_State == PL_COMP_ACTIVE) {

				m_Angle = glm::radians(m_AngleDeg);

				m_Owner->m_Position.x += glm::cos(m_Angle) * m_Speed * deltaTime;
				m_Owner->m_Position.y -= glm::sin(m_Angle) * m_Speed * deltaTime;

				if (glm::distance(m_Owner->m_Position, m_Origin) > m_Lieftime) {
					m_Owner->Destroy();
				}
		}
	}
	void BulletComponent::Render()
	{
	}
	void BulletComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Bullet Component")) {
			ImGui::InputFloat("Speed", &m_Speed);
			ImGui::InputFloat("Angle", &m_AngleDeg);
			ImGui::InputFloat("Lifetime", &m_Lieftime);

			ImGui::TreePop();
		}
	}

	void BulletComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "angle", std::to_string(m_Angle).c_str());
		levelSave.configurator.SetValue(section.c_str(), "speed", std::to_string(m_Speed).c_str());
		levelSave.configurator.SetValue(section.c_str(), "lifetime", std::to_string(m_Lieftime).c_str());
	}

	BulletComponent& BulletComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		float speed = std::stof(config.GetValue(section.c_str(), "speed"));
		float angle = std::stof(config.GetValue(section.c_str(), "angle"));
		float lifetime = std::stof(config.GetValue(section.c_str(), "lifetime"));

		BulletComponent& newComponent = go.AddComponent<BulletComponent>(speed, angle, lifetime);

		return newComponent;
	}

}
