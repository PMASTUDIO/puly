#include "MoveComponent.h"

#include "..//../lowlevel/Input.h"
#include "..//../lowlevel/KeyCodes.h"
#include "..//../lowlevel/debugging/Log.h"

#include "imgui.h"

#include "..//../objects/GameObject.h"

namespace Puly {
	MoveComponent::MoveComponent(float speed) : m_Speed(speed)
	{
	}
	void MoveComponent::Init()
	{
	}
	void MoveComponent::Update(float deltaTime)
	{
		if (m_State == PL_COMP_ACTIVE) {

			if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_W : PL_KEY_UP)) {
				m_Owner->m_Position.y += m_Speed * deltaTime;
			} else if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_S : PL_KEY_DOWN)) {
				m_Owner->m_Position.y -= m_Speed * deltaTime;
			}

			if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_A : PL_KEY_LEFT)) {
				m_Owner->m_Position.x -= m_Speed * deltaTime;
			}
			else if (Input::IsKeyPressed(&m_Owner->m_Owner, !m_UseKeys ? PL_KEY_D : PL_KEY_RIGHT)) {
				m_Owner->m_Position.x += m_Speed * deltaTime;
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
			ImGui::TreePop();
		}
	}
}
