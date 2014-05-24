#include "Camera.hpp"

#define MOUSE_SENSITIVITY		40.0f
#define INVERT_UP_DOWN			1
#define TO_RADIANS				3.14159f / 180.0f
#define X_SENSITIVITY			1.0f
#define Y_SENSITIVITY			1.0f

Camera::Camera(const sf::Window *_window) :
m_Window(_window)
{
	m_Pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_FOV = 60.0f;
	m_xAngle = 180.0f;
	m_yAngle = 0.0f;
	m_CursorLocked = false;
}

Camera::~Camera()
{
}


void Camera::update(float _dt)
{
	static sf::Vector2i prevMousePos = sf::Vector2i();

	glm::vec4 dir = glm::vec4(sinf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), sinf(m_yAngle * TO_RADIANS), cosf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), 0.0f);

	if (m_CursorLocked)
	{
		sf::Vector2i mouseDelta = prevMousePos - sf::Mouse::getPosition(*m_Window);
		
		sf::Mouse::setPosition(sf::Vector2i(m_Window->getPosition().x + m_Window->getSize().x / 2u, m_Window->getPosition().y + m_Window->getSize().y / 2u));

		if (mouseDelta.x != 0)
		{
			m_xAngle += mouseDelta.x * MOUSE_SENSITIVITY * _dt * Y_SENSITIVITY;

			if (m_xAngle < -180.0f)
			{
				m_xAngle += 360.0f;
			}
			if (m_xAngle > 180.0f)
			{
				m_xAngle -= 360.0f;
			}
		}
		if (mouseDelta.y != 0)
		{
			m_yAngle += mouseDelta.y * MOUSE_SENSITIVITY * _dt  * X_SENSITIVITY * (INVERT_UP_DOWN ? -1 : 1);

			if (m_yAngle < -90.0f)
			{
				m_yAngle = -90.0f;
			}
			if (m_yAngle > 90.0f)
			{
				m_yAngle = 90.0f;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//~ Forward along x-z component of view direction
		m_Pos += glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _dt * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//~ Left along orthogonal to x-z component of view direction
		m_Pos += glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _dt * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//~ Back along x-z component of view direction
		m_Pos -= glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _dt * 10.0f, 1.0f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//~ Right along orthogonal to x-z component of view direction
		m_Pos -= glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _dt * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//~ Up along  y axis
		m_Pos += glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//~ Down along y axis
		m_Pos -= glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f, 1.0f);
	}
	
	prevMousePos = sf::Mouse::getPosition(*m_Window);
}

glm::vec4 Camera::getPosition(void)
{
	return m_Pos;
}
glm::vec4 Camera::getViewDirection(void)
{
	return glm::vec4(sinf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), 
		             sinf(m_yAngle * TO_RADIANS), 
					 cosf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), 
					 0.0f);
}
glm::vec4 Camera::getUpDirection(void)
{
	return glm::vec4(-sinf(m_xAngle * TO_RADIANS) * sinf(m_yAngle * TO_RADIANS), 
	                 cosf(m_yAngle * TO_RADIANS), 
					 cosf(m_xAngle * TO_RADIANS) * -sinf(m_yAngle * TO_RADIANS),
					 0.0f);

}
glm::vec2 Camera::getRotation(void)
{
	return glm::vec2(m_xAngle, m_yAngle);
}

float Camera::getFOV(void)
{
	return m_FOV;
}

sf::Vector2u Camera::getWindowSize(void)
{
	return m_Window->getSize();
}

void Camera::toggleMouseCapture(void)
{
	m_CursorLocked = !m_CursorLocked;
}

glm::mat4x4 Camera::getPerspectiveMatrix(void)
{
	return glm::perspective(m_FOV, (float)m_Window->getSize().x / (float)m_Window->getSize().y, 0.1f, 100.0f);
}
glm::mat4x4 Camera::getOrthoMatrix(void)
{
	return glm::ortho(0.0f, (float)m_Window->getSize().x, 0.0f, (float)m_Window->getSize().y);
}
glm::mat4x4 Camera::getProjectionMatrix(bool _offset /*= true*/)
{
	if (_offset)
	{
		return glm::lookAt(glm::vec3(m_Pos), 
						   glm::vec3(m_Pos + getViewDirection()), 
						   glm::vec3(getUpDirection()));
	}

	return glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
}