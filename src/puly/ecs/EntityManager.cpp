#include "EntityManager.h"

namespace Puly {
	void Puly::EntityManager::Update(float deltaTime)
	{
		for (auto& object : v_Objects) {
			object.second->Update(deltaTime);
		}
	}

	void Puly::EntityManager::Render()
	{
		for (auto& object : v_Objects) {
			object.second->Draw();
		}
	}

	bool Puly::EntityManager::IsEmpty() const
	{
		return v_Objects.size() == 0;
	}

	std::shared_ptr<Puly::GameObject>& Puly::EntityManager::AddObject(std::string name)
	{
		std::shared_ptr<Puly::GameObject> newObject;
		newObject = std::make_shared<Puly::GameObject>();

		v_Objects.emplace(name, newObject);

		return newObject;
	}

	std::map<std::string, std::shared_ptr<GameObject>> EntityManager::GetObjects() const
	{
		return v_Objects;
	}


	void Puly::EntityManager::ClearData()
	{
		for (auto& object : v_Objects) {
			object.second->Destroy();
		}
	}
	unsigned int EntityManager::GetObjectCount()
	{
		return v_Objects.size();
	}
}


