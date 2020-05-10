#include "OrthographicCameraController.h"

#include "..//lowlevel/Input.h"
#include "..//lowlevel/KeyCodes.h"

#include "..//lowlevel/debugging/Log.h"

#include "..//lowlevel/Event.h"

#include <algorithm>
#include "Renderer.h"

namespace Puly {

	#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	OrthographicCamera2DController::OrthographicCamera2DController(Window* window, float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
		
	}

	void OrthographicCamera2DController::OnUpdate(Window* window, Timestep dt)
	{
		if (m_ControlActive) {
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

			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
		}
		
	}

	void OrthographicCamera2DController::OnEvent(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCamera2DController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCamera2DController::OnWindowsResized));
	}
	void OrthographicCamera2DController::SetControlActive(float active)
	{
		m_ControlActive = active;
	}
	void OrthographicCamera2DController::ShowReleaseBoundingBox()
	{
		Renderer::Draw2DLine(glm::vec3(-m_AspectRatio, 1.0f, 0.0f), glm::vec3(m_AspectRatio, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer::Draw2DLine(glm::vec3(-m_AspectRatio, -1.0f, 0.0f), glm::vec3(m_AspectRatio, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer::Draw2DLine(glm::vec3(-m_AspectRatio, -1.0f, 0.0f), glm::vec3(-m_AspectRatio, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer::Draw2DLine(glm::vec3(m_AspectRatio, -1.0f, 0.0f), glm::vec3(m_AspectRatio, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}
	bool OrthographicCamera2DController::OnMouseScrolled(MouseScrolledEvent& evt)
	{
		if (m_ControlActive) {
			m_ZoomLevel -= evt.GetYOffset();
			m_ZoomLevel = max(m_ZoomLevel, 0.25f);
			m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		}
		return false;
	}
	bool OrthographicCamera2DController::OnWindowsResized(WindowResizeEvent& evt)
	{
		m_AspectRatio = (float)evt.GetWidth() / (float)evt.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}

