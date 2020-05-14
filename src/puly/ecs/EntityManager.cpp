#include "EntityManager.h"
#include "../physics/Collision.h"
#include "../lowlevel/Scene.h"

#include "../platform/windows/FileOpenDialog.h"
#include "../lowlevel/debugging/ImGuiSystem.h"

namespace Puly {
	void Puly::EntityManager::Update(float deltaTime)
	{
		int i = 0;
		for (auto& object : v_Objects) {
			if (m_IsDebugging) {
				object->m_Debugging = true;
			}
			else {
				object->m_Debugging = false;
			}

			if (!object->m_IsActive) {
				v_Objects.erase(v_Objects.begin() + i);
				return;
			}
			else {
				object->Update(deltaTime);
			}

			i++;
		}
	}

	void Puly::EntityManager::Render()
	{
		for (auto& object : v_Objects) {
			if (object->m_IsActive) {
				object->Draw();
			}
		}
	}

	bool Puly::EntityManager::IsEmpty() const
	{
		return v_Objects.size() == 0;
	}

	Puly::GameObject& EntityManager::AddObject(int priority, std::string name)
	{
		Puly::GameObject* newObject = new Puly::GameObject(*m_Window, priority, name);

		v_Objects.emplace_back(newObject);

		SortByPriority();

		return *newObject;
	}

	std::vector<GameObject*> EntityManager::GetObjects() const
	{
		return v_Objects;
	}

	void EntityManager::ResetObjects()
	{
		for (auto& object : v_Objects) {
			std::string objectOldName = object->m_DebugName;

			object = new Puly::GameObject(object->m_Owner, 0, objectOldName);
		}
	}


	void Puly::EntityManager::ClearData()
	{
		for (auto& object : v_Objects) {
			object->Destroy();
		}
	}

	std::vector<GameObject*> EntityManager::SortByPriority()
	{
		std::sort(v_Objects.begin(), v_Objects.end(), [](const GameObject* priority1, const GameObject* priority2) {
			return priority1->m_Priority < priority2->m_Priority;
		});
		return v_Objects;
	}

	unsigned int EntityManager::GetObjectCount()
	{
		return v_Objects.size();
	}
	
	std::string EntityManager::CheckEntityCollider(GameObject& entity)
	{
		for (auto obj : v_Objects) {
			if (entity.m_DebugName.compare(obj->m_DebugName) != 0) {
				if (obj->HasComponent<ColliderComponent>()) {
					if (CheckRectCollision2D(entity, *obj)) {
						return obj->m_DebugName;
					}
				}
			}
		}

		return "";
	}
	std::string EntityManager::SaveScene()
	{
		std::string pathToSave = Puly::savefile("ini;");
		GameLevel levelSave(pathToSave + ".ini");

		for (auto& object : v_Objects) {
			if (object->m_IsActive) {
				object->SaveInLevel(levelSave);
			}
		}

		return pathToSave;
	}
}


