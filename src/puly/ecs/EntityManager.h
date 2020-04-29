#pragma once

#include <vector>
#include <string>

#include "..//objects/GameObject.h"

namespace Puly {

	class EntityManager {
	private:
		std::vector<GameObject*> v_Objects;
	public:
		EntityManager() {}

		void Update(float deltaTime);
		void Render();

		bool IsEmpty() const;
	    Puly::GameObject& AddObject(std::string name);

		std::vector<GameObject*> GetObjects() const;
		 
		void ClearData();

		unsigned int GetObjectCount();

	public:
		bool m_IsDebugging = false;
	};

}