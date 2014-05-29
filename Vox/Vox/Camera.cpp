#include "Camera.hpp"

#include "Game.hpp"

#define MOUSE_SENSITIVITY		20.0f
#define INVERT_UP_DOWN			1
#define TO_RADIANS				3.14159f / 180.0f
#define X_SENSITIVITY			1.0f
#define Y_SENSITIVITY			1.0f
#define THIRD_PERSON_DISTANCE	5.0f

Camera::Camera() :
m_FOV(60.0f),
m_ThirdPerson(false)
{
	m_CursorLocked = false;

	m_Frustrum.setCamInternals(m_FOV, (float)sWindow.getSize().x / (float)sWindow.getSize().y, 0.1f, 100.0f);
	m_Frustrum.setCamDef(glm::vec3(getPosition()), glm::vec3(getViewDirection()), glm::vec3(getUpDirection()));
}

Camera::~Camera()
{
}


void Camera::update(float _dt)
{
	/*static sf::Vector2i prevMousePos = sf::Vector2i();

	bool updateFrustrum = false;

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

			updateFrustrum = true;
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

			updateFrustrum = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//~ Forward along x-z component of view direction
		m_Pos += glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//~ Left along orthogonal to x-z component of view direction
		m_Pos += glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//~ Back along x-z component of view direction
		m_Pos -= glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//~ Right along orthogonal to x-z component of view direction
		m_Pos -= glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//~ Up along  y axis
		m_Pos += glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//~ Down along y axis
		m_Pos -= glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _dt * 10.0f, 1.0f);

		updateFrustrum = true;
	}
	
	prevMousePos = sf::Mouse::getPosition(*m_Window);

	if (updateFrustrum)
	{
		m_Frustrum.setCamDef(glm::vec3(getPosition()), glm::vec3(getViewDirection()), glm::vec3(getUpDirection()));
	}*/
}

void Camera::resize(void)
{
	m_Frustrum.setCamInternals(m_FOV, (float)sWindow.getSize().x / (float)sWindow.getSize().y, 0.1f, 100.0f);
}

glm::vec4 Camera::getPosition(void)
{
	return sPlayer.getPosition();
}
glm::vec4 Camera::getViewDirection(void)
{
	glm::vec2 rotation = sPlayer.getRotation();

	return glm::vec4(sinf(rotation.x * TO_RADIANS) * cosf(rotation.y * TO_RADIANS), 
		             sinf(rotation.y * TO_RADIANS), 
					 cosf(rotation.x * TO_RADIANS) * cosf(rotation.y * TO_RADIANS), 
					 0.0f);
}
glm::vec4 Camera::getUpDirection(void)
{
	glm::vec2 rotation = sPlayer.getRotation();

	return glm::vec4(-sinf(rotation.x * TO_RADIANS) * sinf(rotation.y * TO_RADIANS), 
	                 cosf(rotation.y * TO_RADIANS), 
					 cosf(rotation.x * TO_RADIANS) * -sinf(rotation.y * TO_RADIANS),
					 0.0f);

}
glm::vec2 Camera::getRotation(void)
{
	return sPlayer.getRotation();
}

float Camera::getFOV(void)
{
	return m_FOV;
}

sf::Vector2u Camera::getWindowSize(void)
{
	return sWindow.getSize();
}
sf::Vector2i Camera::getMousePosition(void)
{
	return sf::Mouse::getPosition(sWindow);
}

void Camera::toggleMouseCapture(void)
{
	m_CursorLocked = !m_CursorLocked;
}
void Camera::toggleThirdPerson(void)
{
	m_ThirdPerson = !m_ThirdPerson;
}

int Camera::testFrustrumBox(glm::vec3 _center, glm::vec3 _size)
{
	return m_Frustrum.boxInFrustum(_center, _size);
}
int Camera::testFrustrumSphere(glm::vec3 _center, float _radius)
{
	return m_Frustrum.sphereInFrustum(_center, _radius);
}
int Camera::testFrustrumPoint(glm::vec3 _pos)
{
	return m_Frustrum.pointInFrustum(_pos);
}

glm::mat4x4 Camera::getPerspectiveMatrix(void)
{
	return glm::perspective(m_FOV, (float)sWindow.getSize().x / (float)sWindow.getSize().y, 0.1f, 100.0f);
}
glm::mat4x4 Camera::getOrthoMatrix(void)
{
	return glm::ortho(0.0f, (float)sWindow.getSize().x, 0.0f, (float)sWindow.getSize().y);
}
glm::mat4x4 Camera::getProjectionMatrix(bool _offset /*= true*/)
{
	if (_offset)
	{
		if (m_ThirdPerson)
		{
			return glm::lookAt(glm::vec3(sPlayer.getPosition() - getViewDirection() * THIRD_PERSON_DISTANCE), 
							   glm::vec3(sPlayer.getPosition()), 
							   glm::vec3(getUpDirection()));
		}
		else
		{
			return glm::lookAt(glm::vec3(sPlayer.getPosition()), 
							   glm::vec3(sPlayer.getPosition() + getViewDirection()), 
							   glm::vec3(getUpDirection()));
		}
	}

	return glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
}