#pragma once

#include "../../Component.h"

namespace Puly {

	class BallBreakoutComponent : public Component {
	public:

		BallBreakoutComponent(float speed);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		bool IsStuck() const { return m_Stuck; }
		void SetStuck(bool value) { m_Stuck = value; }

		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static BallBreakoutComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		float m_Speed;
		bool m_Stuck;
	};

}