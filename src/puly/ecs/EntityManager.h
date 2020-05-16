#pragma once

#include <vector>
#include <string>

#include "..//objects/GameObject.h"

#include "components/ColliderComponent.h"

namespace Puly {

	class EntityManager {
	private:
		std::vector<GameObject*> v_Objects;
		Window* m_Window;
		std::string currentlyModifyingLevel;
	public:
		EntityManager(Window* window) : m_Window(window), currentlyModifyingLevel("") {}

		void Update(float deltaTime);
		void Render();

		bool IsEmpty() const;
	    Puly::GameObject& AddObject(int priority, std::string name, bool procedural = false);

		std::vector<GameObject*> GetObjects() const;
		void ResetObjects();

		void ClearData();

		std::vector<GameObject*> SortByPriority();

		Window* GetWindow() const { return m_Window; }

		void SetWorkingScene(std::string pathForScene) {
			currentlyModifyingLevel = pathForScene;
		}

		unsigned int GetObjectCount();

		GameObject* GetObjectByDebugName(std::string name) const { 
			auto iter = std::find_if(v_Objects.begin(), v_Objects.end(), [&name](const GameObject* obj) {
				return obj->m_DebugName == name;
			});

			if (iter != v_Objects.end()) {
				auto index = std::distance(v_Objects.begin(), iter);
				return v_Objects[index];
			}
			else {
				return nullptr;
			}
		}

		std::string CheckEntityCollider(GameObject& entity);

		std::string SaveScene(bool useLastPath = true);

	public:
		
		#ifdef PL_DEBUG
			bool m_IsDebugging = true;
		#else
			bool m_IsDebugging = false;
		#endif	
	};

}