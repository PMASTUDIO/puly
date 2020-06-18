#pragma once

#include "../Component.h"

namespace Puly {

	class MoveComponent : public Component {
	public:

		MoveComponent(float speed, bool horizontal = true, bool vertical = true, bool staticBoundsCollision = false);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;


		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static MoveComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		float m_Speed;
		bool m_UseKeys;
		bool m_HorizontalAxis;
		bool m_VerticalAxis;

		bool m_StaticBoundsCollision;
	};

}