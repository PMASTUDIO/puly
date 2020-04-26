#include "OrthographicCameraController.h"

#include "..//lowlevel/Input.h"
#include "..//lowlevel/KeyCodes.h"

#include "..//lowlevel/debugging/Log.h"

namespace Puly {

	OrthographicCamera2DController::OrthographicCamera2DController(Window* window, float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
		
	}

	void OrthographicCamera2DController::OnUpdate(Window* window, Timestep dt)
	{
		if (Input::IsKeyPressed(window, PL_KEY_UP)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * dt;
		}
		else if (Input::IsKeyPressed(window, PL_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * dt;
		}

		if (Input::IsKeyPressed(window, PL_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * dt;
		}
		else if (Input::IsKeyPressed(window, PL_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * dt;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(window, PL_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * dt;
			}
			else if (Input::IsKeyPressed(window, PL_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * dt;
			}
		}

		if (Input::IsKeyPressed(window, PL_KEY_KP_ADD)) {
			m_ZoomLevel -= 1.0f  * dt;
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		} else if (Input::IsKeyPressed(window, PL_KEY_KP_SUBTRACT)) {
			m_ZoomLevel += 1.0f * dt;
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}
	
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
	}
}

