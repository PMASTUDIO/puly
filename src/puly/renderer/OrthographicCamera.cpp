#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

Puly::OrtographicCamera::OrtographicCamera(float leftBound, float rightBound, float bottomBound, float topBound)
	: m_ProjectionMatrix(glm::ortho(leftBound, rightBound, bottomBound, topBound, -1.0f, 1.0f)), m_ViewMatrix(1.0f), m_Position(0.0f, 0.0f, 0.0f)
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Puly::OrtographicCamera::RecalculateViewMatrix()
{
	glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), m_Position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

	m_ViewMatrix = glm::inverse(transform);
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}