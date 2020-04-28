#pragma once

#include <memory>

namespace Puly {

	class GameObject;

	class Component {
	public:
		GameObject* m_Owner;
	public:

		Component() {}

		virtual ~Component() {}

		virtual void Init() {}
		virtual void Update(float deltaTime) {}
		virtual void Render() {}
	
	};

}