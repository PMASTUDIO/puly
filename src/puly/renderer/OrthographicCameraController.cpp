#include "OrthographicCameraController.h"

#include "..//lowlevel/Input.h"
#include "..//lowlevel/KeyCodes.h"


namespace Puly {
	void OrthographicCamera2DController::HandleCameraWithInput(OrtographicCamera* camera, Window* window, Timestep deltaTime, float speed)
	{
		if (Input::IsKeyPressed(window, PL_KEY_UP)) {
			camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y + (speed * deltaTime), camera->GetPosition().z));
		}
		else if (Input::IsKeyPressed(window, PL_KEY_DOWN)) {
			camera->SetPosition(glm::vec3(camera->GetPosition().x, camera->GetPosition().y - (speed * deltaTime), camera->GetPosition().z));
		}

		if (Input::IsKeyPressed(window, PL_KEY_RIGHT)) {
			camera->SetPosition(glm::vec3(camera->GetPosition().x + (speed * deltaTime), camera->GetPosition().y, camera->GetPosition().z));
		}
		else if (Input::IsKeyPressed(window, PL_KEY_LEFT)) {
			camera->SetPosition(glm::vec3(camera->GetPosition().x - (speed * deltaTime), camera->GetPosition().y, camera->GetPosition().z));
		}
	}
}

