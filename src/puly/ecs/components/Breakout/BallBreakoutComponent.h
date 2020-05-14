#pragma once

#include <glm/glm.hpp>
#include "../../Component.h"

namespace Puly {

	class BallBreakoutComponent : public Component {
	private:
		glm::vec2 m_Speed;
		bool m_Stuck;
	public:

		BallBreakoutComponent(float speed);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		bool IsStuck() const { return m_Stuck; }
		void SetStuck(bool value) { m_Stuck = value; }

		glm::vec2 GetSpeed() const { return m_Speed; }
		void SetSpeed(glm::vec2& speed);

		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static BallBreakoutComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);
	};

}