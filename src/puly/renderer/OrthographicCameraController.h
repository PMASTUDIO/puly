#pragma once

#include <memory>

#include "OrthographicCamera.h"
#include "..//window/Window.h"
#include "..//lowlevel/Timestep.h"

#include "GLFW/glfw3.h"

namespace Puly {
	class OrthographicCamera2DController {
	public:
		OrthographicCamera2DController(Window* window, float aspectRatio, bool rotation = false);

		OrtographicCamera& GetCamera() { return m_Camera; }

		void OnUpdate(Window* window, Timestep dt);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_Rotation;

		OrtographicCamera m_Camera;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}