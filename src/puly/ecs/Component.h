#pragma once

#include <memory>
#include "../lowlevel/Scene.h"

namespace Puly {

	enum COMPONENT_STATE {
		PL_COMP_ACTIVE,
		PL_COMP_DEBUGGING,
		PL_COMP_PAUSED
	};

	class GameObject;

	class Component {
	public:
		GameObject* m_Owner;
		COMPONENT_STATE m_State;
	public:

		Component() : m_State(PL_COMP_ACTIVE), m_Owner(nullptr){}

		virtual ~Component() {}

		virtual void Init() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
	
		virtual void DebugGUI(){}

		virtual void SaveInScene(std::string section, GameLevel& levelSave){}

	};

}