#pragma once

#include "../Component.h"

#include <glm/glm.hpp>

namespace Puly {

	class BulletComponent : public Component {
	public:

		BulletComponent(float speed, float angle = 90.0f, float lifetime = 10.0f);

		virtual void Init() override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static BulletComponent& GetComponentFromScene(GameObject& go, std::string section, SceneConfig& config);

	private:
		float m_Speed;
		float m_Angle;
		float m_AngleDeg;
		float m_Lieftime;

		glm::vec3 m_Origin;
	};

}