#include "Plane.hpp"

#include <cmath>
#include <iostream>

Plane::Plane(void) :
Plane(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))
{
}

Plane::Plane(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3)
{
	setPoints(_p1, _p2, _p3);
}

Plane::~Plane()
{
}


void Plane::setPoints(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3)
{
	glm::vec3 u = _p3 - _p2;
	glm::vec3 v = _p1 - _p2;
	
	glm::vec3 normal = glm::cross(u, v);

	normal = glm::normalize(normal);
		
	float d = normal.x * _p1.x + normal.y * _p1.y + normal.z * _p1.z;

	m_Normal = normal;
	m_D = d;
}

float Plane::getDistance(glm::vec3 _p)
{
	return m_Normal.x * _p.x + m_Normal.y * _p.y + m_Normal.z * _p.z + m_D;
}
glm::vec3 Plane::getNormal(void)
{
	return m_Normal;
}