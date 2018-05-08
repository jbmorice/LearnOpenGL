#include "camera.h"

Camera::Camera(glm::vec3 position) :
	m_cameraPosition(position)
{
	updateCoordSystem();
}

glm::mat4x4 Camera::getViewMatrix()
{
	return glm::lookAt(m_cameraPosition, m_cameraPosition + m_cameraFront, m_cameraUp);
}

glm::mat4x4 Camera::getPerspectiveProjectionMatrix(int a_windowWidth, int a_windowHeight)
{
	return glm::perspective(glm::radians(m_fov), (float)a_windowWidth / (float)a_windowHeight, 0.1f, 100.0f);
}

void Camera::processKeyboard(Movement a_movement, float a_deltaTime)
{
	float velocity = m_speed * a_deltaTime;

	switch (a_movement)
	{
	case Movement::FORWARD:
		m_cameraPosition += m_cameraFront * velocity;
		break;

	case Movement::BACKWARD:
		m_cameraPosition -= m_cameraFront * velocity;
		break;

	case Movement::LEFT:
		m_cameraPosition -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
		break;

	case Movement::RIGHT:
		m_cameraPosition += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * velocity;
		break;
	}
}

void Camera::processMousePosition(double a_xoffset, double a_yoffset)
{
	a_xoffset *= m_sensitivity;
	a_yoffset *= m_sensitivity;

	m_yaw += a_xoffset;
	m_pitch += a_yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	updateCoordSystem();
}

void Camera::processMouseScroll(double a_xoffset, double a_yoffset)
{
	if (m_fov >= 1.0f && m_fov <= 45.0f)
		m_fov -= a_yoffset;
	if (m_fov <= 1.0f)
		m_fov = 1.0f;
	if (m_fov >= 45.0f)
		m_fov = 45.0f;
}

void Camera::updateCoordSystem()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_cameraFront = glm::normalize(front);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_cameraRight = glm::normalize(glm::cross(m_cameraFront, up));
	m_cameraUp = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}
