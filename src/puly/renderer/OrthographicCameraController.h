#pragma once

#include <memory>

#include "OrthographicCamera.h"
#include "..//window/Window.h"
#include "..//lowlevel/Timestep.h"

#include "GLFW/glfw3.h"

#include "..//lowlevel/BaseEvents.h"

namespace Puly {

	class Event;

	class OrthographicCamera2DController {
	public:
		OrthographicCamera2DController(Window* window, float aspectRatio, bool rotation = false);

		OrtographicCamera& GetCamera() { return m_Camera; }

		void OnUpdate(Window* window, Timestep dt);

		void OnEvent(Event& evt);

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }

		void SetControlActive(float active);

	private:
		bool OnMouseScrolled(MouseScrolledEvent& evt);
		bool OnWindowsResized(WindowResizeEvent& evt);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_ControlActive = true;

		bool m_Rotation;

		OrtographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}