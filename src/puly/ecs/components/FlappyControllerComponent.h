#pragma once

#include "../Component.h"

namespace Puly {

	class FlappyControllerComponent : public Component {
	public:

		FlappyControllerComponent(float speed, float fakeGravity = 11.0f);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;


		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static FlappyControllerComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		float m_Speed;
		float m_Gravity;
		bool m_UseKeys;
	};

}