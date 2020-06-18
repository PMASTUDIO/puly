#include "FlappyControllerComponent.h"

#include "..//../../lowlevel/Input.h"
#include "..//../../lowlevel/KeyCodes.h"
#include "..//../../lowlevel/debugging/Log.h"

#include "imgui.h"

#include "..//../../objects/GameObject.h"

namespace Puly {
	FlappyControllerComponent::FlappyControllerComponent(float speed, float fakeGravity) : m_Speed(speed), m_Gravity(fakeGravity)
	{
	}
	void FlappyControllerComponent::Init()
	{
	}
	void FlappyControllerComponent::Update(float deltaTime)
	{
		if (m_State == PL_COMP_ACTIVE) {

			if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_W : PL_KEY_UP)) {
				m_Owner->m_Position.y += m_Speed * deltaTime;
			} else if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_S : PL_KEY_DOWN)) {
				m_Owner->m_Position.y -= m_Speed * deltaTime;
			}
			else {
				m_Owner->m_Position.y -= m_Gravity * deltaTime;
			}
		}
	}
	void FlappyControllerComponent::Render()
	{
	}
	void FlappyControllerComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Flappy Controller Component")) {
			ImGui::InputFloat("Speed", &m_Speed);
			ImGui::InputFloat("Fake Gravity", &m_Gravity);

			ImGui::Checkbox("Use KEYS", &m_UseKeys);

			if (ImGui::Button("Delete")) {
				m_Owner->RemoveComponent<FlappyControllerComponent>();
			}

			ImGui::TreePop();
		}
	}

	void FlappyControllerComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "usingKeys", std::to_string(m_UseKeys).c_str());
		levelSave.configurator.SetValue(section.c_str(), "speed", std::to_string(m_Speed).c_str());
		levelSave.configurator.SetValue(section.c_str(), "gravity", std::to_string(m_Gravity).c_str());
	}

	FlappyControllerComponent& FlappyControllerComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		float speed = std::stof(config.GetValue(section.c_str(), "speed"));
		float gravity = std::stof(config.GetValue(section.c_str(), "gravity"));
		int useKeys = std::stof(config.GetValue(section.c_str(), "usingKeys"));

		FlappyControllerComponent& newComponent = go.AddComponent<FlappyControllerComponent>(speed, gravity);
		newComponent.m_UseKeys = useKeys;

		return newComponent;
	}

}
