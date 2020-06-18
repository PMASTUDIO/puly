#include "ColliderComponent.h"
#include <imgui.h>
#include "../EntityManager.h"

namespace Puly {

	void ColliderComponent::Update(float deltaTime)
	{

	}

	void ColliderComponent::Render()
	{

	}

	void ColliderComponent::DebugGUI()
	{
		if (ImGui::TreeNode("Collider Component")) {

			if (m_Em != nullptr) {
				std::string collidingWidth = m_Em->CheckEntityCollider(*m_Owner);

				if (collidingWidth.compare("") != 0) {
					ImGui::Text("Currently colliding with: %s", collidingWidth.c_str());
				}

				if (ImGui::Button("Delete")) {
					m_Owner->RemoveComponent<ColliderComponent>();
				}
			}

			ImGui::TreePop();
		}
	}

	void ColliderComponent::SetEntityManager(EntityManager* em)
	{
		m_Em = em;
	}

	void ColliderComponent::SaveInScene(std::string section, GameLevel& levelSave)
	{
		levelSave.configurator.SetValue(section.c_str(), "owner", m_Owner->m_DebugName.c_str());
		levelSave.configurator.SetValue(section.c_str(), "state", std::to_string(m_State).c_str());
	}

	ColliderComponent& ColliderComponent::GetComponentFromScene(EntityManager* em, GameObject& go, std::string section, SceneConfig& config)
	{
		if (em != nullptr) {
			ColliderComponent& newCollider = go.AddComponent<ColliderComponent>(em);
			newCollider.SetEntityManager(em);
			return newCollider;
		}
		else {
			PL_LOG_ERROR("New collider component is not being created because EM is nullptr!!!");
			throw "New collider component is not being created because EM is nullptr!!!";
		}
	}

}