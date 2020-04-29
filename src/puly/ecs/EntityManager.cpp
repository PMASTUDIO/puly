#include "EntityManager.h"

namespace Puly {
	void Puly::EntityManager::Update(float deltaTime)
	{
		for (auto object : v_Objects) {
			if (m_IsDebugging) {
				object->m_Debugging = true;
			}
			else {
				object->m_Debugging = false;
			}
			object->Update(deltaTime);
		}
	}

	void Puly::EntityManager::Render()
	{
		for (auto& object : v_Objects) {
			object->Draw();
		}
	}

	bool Puly::EntityManager::IsEmpty() const
	{
		return v_Objects.size() == 0;
	}

	Puly::GameObject& EntityManager::AddObject(std::string name)
	{
		Puly::GameObject* newObject = new Puly::GameObject(name);

		v_Objects.emplace_back(newObject);

		return *newObject;
	}

	std::vector<GameObject*> EntityManager::GetObjects() const
	{
		return v_Objects;
	}


	void Puly::EntityManager::ClearData()
	{
		for (auto& object : v_Objects) {
			object->Destroy();
		}
	}
	unsigned int EntityManager::GetObjectCount()
	{
		return v_Objects.size();
	}
}


