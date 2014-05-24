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
	Camera(const sf::Window *_window);
	~Camera();

	void update(float _dt);

	glm::vec4 getPosition(void);
	glm::vec4 getViewDirection(void);
	glm::vec4 getUpDirection(void);
	glm::vec2 getRotation(void);

	float getFOV(void);

	sf::Vector2u getWindowSize(void);

	void toggleMouseCapture(void);

	glm::mat4x4 getPerspectiveMatrix(void);
	glm::mat4x4 getOrthoMatrix(void);
	glm::mat4x4 getProjectionMatrix(bool _offset = true);

private:
	glm::vec4			m_Pos;

	float				m_xAngle;
	float				m_yAngle;

	float				m_FOV;

	sf::Vector2u		m_WindowSize;

	bool				m_CursorLocked;

private:
	const sf::Window *			m_Window;
};

#endif //~ INCLUDED_CAMERA_HPP