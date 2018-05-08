#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera
{
private:
	glm::vec3 m_cameraPosition;

	glm::vec3 m_cameraRight;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

	float m_speed = 3.5f;
	float m_sensitivity = 0.075f;

	float m_pitch = 0.0f;
	float m_yaw = -90.0f;
	float m_fov = 45.0f;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));

	enum Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	glm::mat4x4 getViewMatrix();
	glm::mat4x4 getPerspectiveProjectionMatrix(int a_windowWidth, int a_windowHeight);

	void processKeyboard(Movement a_movement, float a_deltaTime);
	void processMousePosition(double a_xoffset, double a_yoffset);
	void processMouseScroll(double a_xoffset, double a_yoffset);

private:
	void updateCoordSystem();
};

#endif