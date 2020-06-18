#pragma once

#include "../Component.h"
#include <glm/glm.hpp>
#include "../../renderer/Shader.h"

namespace Puly {

	class ColoredComponent : public Component {
	public:

		ColoredComponent(glm::vec4& color);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;


		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static ColoredComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		std::shared_ptr<Shader> m_Shader;
		glm::vec4 m_Color;
	};

}