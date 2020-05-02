#pragma once

#include <vector>
#include <string>

#include "..//objects/GameObject.h"

namespace Puly {

	class EntityManager {
	private:
		std::vector<GameObject*> v_Objects;
		Window* m_Window;
	public:
		EntityManager(Window window) : m_Window(&window) {}

		void Update(float deltaTime);
		void Render();

		bool IsEmpty() const;
	    Puly::GameObject& AddObject(int priority, std::string name);

		std::vector<GameObject*> GetObjects() const;
		void ResetObjects();

		void ClearData();

		std::vector<GameObject*> SortByPriority();

		unsigned int GetObjectCount();

	public:
		
		#ifdef PL_DEBUG
			bool m_IsDebugging = true;
		#else
			bool m_IsDebugging = false;
		#endif	
	};

}