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

			std::string collidingWidth = m_Em->CheckEntityCollider(*m_Owner);
			
			if (collidingWidth.compare("") != 0) {
				ImGui::Text("Currently colliding with: %s", collidingWidth.c_str());
			}

			ImGui::TreePop();
		}
	}

}