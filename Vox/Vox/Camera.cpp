#include "Camera.hpp"

#define ROTATE_SPEED 150.0f

Camera::Camera(sf::Vector2u _windowSize) :
m_WindowSize(_windowSize)
{
	m_Pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_Dir = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	m_FOV = 60.0f;
}

Camera::~Camera()
{
}


void Camera::update(float _dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//~ Forward along x-z component of view direction
		glm::vec3 normxz = glm::normalize(glm::vec3(m_Dir.x, 0.0f, m_Dir.z));

		glm::vec3 tempPos = normxz * _dt * 10.0f;

		m_Pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//~ Left along orthogonal to x-z component of view direction
		glm::vec3 normxz = glm::normalize(glm::vec3(m_Dir.x, 0.0f, m_Dir.z));

		glm::vec3 tempPos = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), normxz) * _dt * 10.0f;

		m_Pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//~ Back along x-z component of view direction
		glm::vec3 normxz = glm::normalize(glm::vec3(m_Dir.x, 0.0f, m_Dir.z));

		glm::vec3 tempPos = normxz * _dt * 10.0f;

		m_Pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//~ Right along orthogonal to x-z component of view direction
		glm::vec3 normxz = glm::normalize(glm::vec3(m_Dir.x, 0.0f, m_Dir.z));

		glm::vec3 tempPos = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), normxz) * _dt * 10.0f;

		m_Pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//~ Up along  y axis
		glm::vec3 tempPos = glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f;

		m_Pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//~ Down along y axis
		glm::vec3 tempPos = glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f;

		m_Pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_Dir = glm::rotate(glm::mat4x4(1.0f), ROTATE_SPEED * _dt, glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(m_Dir.x, 0.0f, m_Dir.z))) * m_Dir;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_Dir = glm::rotate(glm::mat4x4(1.0f), - ROTATE_SPEED * _dt, glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(m_Dir.x, 0.0f, m_Dir.z))) * m_Dir;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_Dir = glm::rotate(glm::mat4x4(1.0f), ROTATE_SPEED * _dt, glm::vec3(0.0f, 1.0f, 0.0f)) * m_Dir;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_Dir = glm::rotate(glm::mat4x4(1.0f), - ROTATE_SPEED * _dt, glm::vec3(0.0f, 1.0f, 0.0f)) * m_Dir;
	}
}
void Camera::updateWindowSize(sf::Vector2u _windowSize)
{
	m_WindowSize = _windowSize;
}

glm::vec4 Camera::getPosition(void)
{
	return m_Pos;
}
glm::vec4 Camera::getViewDirection(void)
{
	return m_Dir;
}

float Camera::getFOV(void)
{
	return m_FOV;
}

sf::Vector2u Camera::getWindowSize(void)
{
	return m_WindowSize;
}

glm::mat4x4 Camera::getPerspectiveMatrix(void)
{
	return glm::perspective(m_FOV, (float)m_WindowSize.x / (float)m_WindowSize.y, 0.1f, 100.0f);
}
glm::mat4x4 Camera::getOrthoMatrix(void)
{
	return glm::ortho(0.0f, (float)m_WindowSize.x, 0.0f, (float)m_WindowSize.y);
}
glm::mat4x4 Camera::getProjectionMatrix(bool _offset /*= true*/)
{
	if (_offset)
	{
		return glm::lookAt(glm::vec3(m_Pos), glm::vec3(m_Pos) + glm::vec3(m_Dir), glm::vec3(0.0, 1.0, 0.0));
	}

	return glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
}