#include "BallBreakoutComponent.h"

#include "../..//../lowlevel/Input.h"
#include "../..//../lowlevel/KeyCodes.h"
#include "../..//../lowlevel/debugging/Log.h"

#include "imgui.h"

#include "../..//../objects/GameObject.h"
#include "glm/gtc/type_ptr.hpp"

namespace Puly {
	BallBreakoutComponent::BallBreakoutComponent(float speed) : m_Speed(speed), m_Stuck(true)
	{
	}
	void BallBreakoutComponent::Init()
	{
	}
	void BallBreakoutComponent::Update(float deltaTime)
	{
		if (m_State == PL_COMP_ACTIVE) {

			float aspectRatio = 16.0f / 9.0f;

			if (!m_Stuck) {
				m_Owner->m_Position.x += m_Speed.x * deltaTime;
				m_Owner->m_Position.y += m_Speed.y * deltaTime;

				if (m_Owner->m_Position.x <= -aspectRatio + m_Owner->m_Scale.x)
				{
					m_Speed.x = -m_Speed.x;
					m_Owner->m_Position.x = -aspectRatio + m_Owner->m_Scale.x;
				}
				else if (m_Owner->m_Position.x >= aspectRatio - m_Owner->m_Scale.x)
				{
					m_Speed.x = -m_Speed.x;
					m_Owner->m_Position.x = aspectRatio - m_Owner->m_Scale.x;
				}

				if (m_Owner->m_Position.y >= 1.0f) {
					m_Speed.y = -m_Speed.y;
					m_Owner->m_Position.y = 0.99f;
				}
			}

			if (Input::IsKeyPressed(&m_Owner->m_Owner, PL_KEY_LEFT)) {

				if (m_Stuck) {
					if (m_Owner->m_Position.x >= -aspectRatio + m_Owner->m_Scale.x)
					{
						m_Owner->m_Position.x -= m_Speed.x * deltaTime;
					}

				}

			}

			if (Input::IsKeyPressed(&m_Owner->m_Owner, PL_KEY_RIGHT)) {
				if (m_Stuck) {
					if (m_Owner->m_Position.x <= aspectRatio - m_Owner->m_Scale.x)
					{
						m_Owner->m_Position.x += m_Speed.x * deltaTime;
					}
				}

			}

			if (Input::IsKeyPressed(&m_Owner->m_Owner, PL_KEY_SPACE)) {
				m_Stuck = false;
			}
		}
	}
	void BallBreakoutComponent::Render()
	{
	}
	void BallBreakoutComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Breakout ball Component")) {
			ImGui::InputFloat2("Speed", glm::value_ptr(m_Speed));

			if (ImGui::Button("Delete")) {
				m_Owner->RemoveComponent<BallBreakoutComponent>();
			}

			ImGui::TreePop();
		}
	}

	void BallBreakoutComponent::SetSpeed(glm::vec2& speed)
	{
		m_Speed = speed;
	}

	void BallBreakoutComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "speed", std::to_string(m_Speed.x).c_str());
		//levelSave.configurator.SetValue(section.c_str(), "speedY", std::to_string(m_Speed.y).c_str());
	}

	BallBreakoutComponent& BallBreakoutComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		float speed = atof(config.GetValue(section.c_str(), "speed"));

		BallBreakoutComponent& newComponent = go.AddComponent<BallBreakoutComponent>(speed);

		return newComponent;
	}

}
