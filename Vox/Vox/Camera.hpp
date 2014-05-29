#ifndef INCLUDED_CAMERA_HPP
#define INCLUDED_CAMERA_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Frustrum.hpp"
#include "Mob.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	void update(float _dt);

	void resize(void);

	glm::vec4 getPosition(void);
	glm::vec4 getViewDirection(void);
	glm::vec4 getUpDirection(void);
	glm::vec2 getRotation(void);

	float getFOV(void);

	sf::Vector2u getWindowSize(void);
	sf::Vector2i getMousePosition(void);

	void toggleMouseCapture(void);
	void toggleThirdPerson(void);

	int testFrustrumBox(glm::vec3 _center, glm::vec3 _size);
	int testFrustrumSphere(glm::vec3 _center, float _radius);
	int testFrustrumPoint(glm::vec3 _pos);

	glm::mat4x4 getPerspectiveMatrix(void);
	glm::mat4x4 getOrthoMatrix(void);
	glm::mat4x4 getProjectionMatrix(bool _offset = true);

private:
	float				m_FOV;

	sf::Vector2u		m_WindowSize;

	bool				m_CursorLocked;
	bool				m_ThirdPerson;

	Frustrum			m_Frustrum;
};



#endif //~ INCLUDED_CAMERA_HPP