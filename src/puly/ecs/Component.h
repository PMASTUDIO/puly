#pragma once

#include <memory>

namespace Puly {

	class GameObject;

	enum COMPONENT_STATE {
		PL_COMP_ACTIVE,
		PL_COMP_DEBUGGING,
		PL_COMP_PAUSED
	};

	class Component {
	public:
		GameObject* m_Owner;
		COMPONENT_STATE m_State;
	public:

		Component() : m_State(PL_COMP_ACTIVE) {}

		virtual ~Component() {}

		virtual void Init() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
	
		virtual void DebugGUI(){}
	};

}