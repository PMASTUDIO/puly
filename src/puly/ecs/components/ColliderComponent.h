#pragma once

#include "../Component.h"
#include "../EntityManager.h"

namespace Puly {

	class ColliderComponent : public Component {
	public:
		ColliderComponent(EntityManager* em = nullptr) : m_Em(em){}

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		virtual void DebugGUI() override;

		void SetEntityManager(EntityManager* em);

		void SaveInScene(std::string section, GameLevel& levelSave) override;
		static ColliderComponent& GetComponentFromScene(EntityManager* em, GameObject& go, std::string section, SceneConfig& config);

	private:
		EntityManager* m_Em;
	};

}