#pragma once

#include <memory>

class GameObject;

namespace Puly {

	class Component {
	public:
		
		virtual ~Component();

		virtual void Init();
		virtual void Update(float deltaTime);
		virtual void Render();

	private:
		std::shared_ptr<GameObject>& owner;
	};

}