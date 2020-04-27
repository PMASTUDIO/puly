#pragma once

#include <map>
#include <string>

#include "..//objects/GameObject.h"

namespace Puly {
	class EntityManager {
	private:
		std::map<std::string, std::shared_ptr<GameObject>> v_Objects;
	public:
		void Update(float deltaTime);
		void Render();

		bool IsEmpty() const;
		std::shared_ptr<Puly::GameObject>& AddObject(std::string name);

		std::map<std::string, std::shared_ptr<GameObject>> GetObjects() const;
		 
		void ClearData();

		unsigned int GetObjectCount();
	};
}