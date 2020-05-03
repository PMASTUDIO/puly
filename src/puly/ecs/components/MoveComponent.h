#pragma once

#include "../Component.h"

namespace Puly {

	class MoveComponent : public Component {
	public:

		MoveComponent(float speed);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;


		void SaveInScene(std::string section, GameLevel& levelSave) override;

	private:
		float m_Speed;
		bool m_UseKeys;
	};

}