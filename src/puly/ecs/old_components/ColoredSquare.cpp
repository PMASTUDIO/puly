#include "ColoredSquare.h"

#include "..//../lowlevel/Input.h"
#include "..//../lowlevel/KeyCodes.h"
#include "..//../lowlevel/debugging/Log.h"

#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

#include "..//../objects/GameObject.h"
#include "../../lowlevel/ResourceManager.h"
#include "../../renderer/Renderer.h"
#include "glm/gtc/type_ptr.hpp"

namespace Puly {
	ColoredComponent::ColoredComponent(glm::vec4& color) : m_Color(color)
	{
		m_Shader.reset(new Shader);
	}
	void ColoredComponent::Init()
	{
		m_Shader = ResourceManager::GetShader("resources/shaders/colorVertexShader.glsl", "resources/shaders/colorFragmentShader.glsl");
	}
	void ColoredComponent::Update(float deltaTime)
	{
		
	}
	void ColoredComponent::Render()
	{
		glm::vec2 position = glm::vec2(m_Owner->m_Position.x, m_Owner->m_Position.y);

		glm::vec2 size = glm::vec2(m_Owner->m_Scale.x, m_Owner->m_Scale.y);
		float rotate = glm::radians(m_Owner->m_Rotation);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(position, 0.0f));

		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
		model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

		model = glm::scale(model, glm::vec3(size, 1.0f));

		Renderer::Draw2DQuad(m_Shader, m_Color, model);
	}
	void ColoredComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Colored Component")) {
			ImGui::ColorPicker4("Color", glm::value_ptr(m_Color));

			if (ImGui::Button("Delete")) {
				m_Owner->RemoveComponent<ColoredComponent>();
			}

			ImGui::TreePop();
		}
	}

	void ColoredComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
		levelSave.configurator.SetValue(section.c_str(), "colorR", std::to_string(m_Color.r).c_str());
		levelSave.configurator.SetValue(section.c_str(), "colorG", std::to_string(m_Color.g).c_str());
		levelSave.configurator.SetValue(section.c_str(), "colorB", std::to_string(m_Color.b).c_str());
		levelSave.configurator.SetValue(section.c_str(), "colorA", std::to_string(m_Color.a).c_str());
	}

	ColoredComponent& ColoredComponent::GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config)
	{
		float r = atof(config.GetValue(section.c_str(), "colorR"));
		float g = atof(config.GetValue(section.c_str(), "colorG"));
		float b = atof(config.GetValue(section.c_str(), "colorB"));
		float a = atof(config.GetValue(section.c_str(), "colorA"));

		ColoredComponent& newComponent = go.AddComponent<ColoredComponent>(glm::vec4(r, g, b, a));

		return newComponent;
	}

}
