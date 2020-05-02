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

	private:
		EntityManager* m_Em;
	};

}