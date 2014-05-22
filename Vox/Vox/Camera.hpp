#ifndef INCLUDED_CAMERA_HPP
#define INCLUDED_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(sf::Vector2u _windowSize);
	~Camera();

	void update(float _dt);
	void updateWindowSize(sf::Vector2u _windowSize);

	glm::vec4 getPosition(void);
	glm::vec4 getViewDirection(void);

	float getFOV(void);

	sf::Vector2u getWindowSize(void);

	glm::mat4x4 getPerspectiveMatrix(void);
	glm::mat4x4 getOrthoMatrix(void);
	glm::mat4x4 getProjectionMatrix(bool _offset = true);

private:
	glm::vec4			m_Pos;
	glm::vec4			m_Dir;

	float				m_FOV;

	sf::Vector2u		m_WindowSize;
};

#endif //~ INCLUDED_CAMERA_HPP