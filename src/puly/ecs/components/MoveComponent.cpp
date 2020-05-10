#include "MoveComponent.h"

#include "..//../lowlevel/Input.h"
#include "..//../lowlevel/KeyCodes.h"
#include "..//../lowlevel/debugging/Log.h"

#include "imgui.h"

#include "..//../objects/GameObject.h"

namespace Puly {
	MoveComponent::MoveComponent(float speed, bool horizontal, bool vertical) : m_Speed(speed), m_HorizontalAxis(horizontal), m_VerticalAxis(vertical)
	{
	}
	void MoveComponent::Init()
	{
	}
	void MoveComponent::Update(float deltaTime)
	{
		if (m_State == PL_COMP_ACTIVE) {

			if (m_VerticalAxis) {
				if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_W : PL_KEY_UP)) {
					m_Owner->m_Position.y += m_Speed * deltaTime;
				}
				else if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_S : PL_KEY_DOWN)) {
					m_Owner->m_Position.y -= m_Speed * deltaTime;
				}
			}
			
			if (m_HorizontalAxis) {
				if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_A : PL_KEY_LEFT)) {
					m_Owner->m_Position.x -= m_Speed * deltaTime;
				}
				else if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_D : PL_KEY_RIGHT)) {
					m_Owner->m_Position.x += m_Speed * deltaTime;
				}
			}
		}
	}
	void MoveComponent::Render()
	{
	}
	void MoveComponent::DebugGUI()
	{
		if (ImGui::TreeNode("2D Move Component")) {
			ImGui::InputFloat("Speed", &m_Speed);

			ImGui::Checkbox("Use KEYS", &m_UseKeys);
			ImGui::Checkbox("Horizontal Axis", &m_HorizontalAxis);
			ImGui::Checkbox("Vertical Axis", &m_VerticalAxis);

			if (ImGui::Button("Delete")) {
				m_Owner->RemoveComponent<MoveComponent>();
			}

			ImGui::TreePop();
		}
	}

	void MoveComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "usingKeys", std::to_string(m_UseKeys).c_str());
		levelSave.configurator.SetValue(section.c_str(), "speed", std::to_string(m_Speed).c_str());
		levelSave.configurator.SetValue(section.c_str(), "horizontal", std::to_string(m_HorizontalAxis).c_str());
		levelSave.configurator.SetValue(section.c_str(), "vertical", std::to_string(m_VerticalAxis).c_str());
	}

	MoveComponent& MoveComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		int speed = atoi(config.GetValue(section.c_str(), "speed"));
		int useKeys = atoi(config.GetValue(section.c_str(), "usingKeys"));
		int horizontal = atoi(config.GetValue(section.c_str(), "horizontal"));
		int vertical = atoi(config.GetValue(section.c_str(), "vertical"));

		MoveComponent& newComponent = go.AddComponent<MoveComponent>(speed, horizontal, vertical);
		newComponent.m_UseKeys = useKeys;

		return newComponent;
	}

}
