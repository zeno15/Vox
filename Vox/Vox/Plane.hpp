#ifndef INCLUDED_PLANE_HPP
#define INCLUDED_PLANE_HPP

#include <glm/glm.hpp>

class Plane
{
public:
	Plane();
	Plane(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3);
	~Plane();

	void setPoints(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3);

	float getDistance(glm::vec3 _p);
	glm::vec3 getNormal(void);

private:

	glm::vec3				m_Normal;
	float					m_D;
};

#endif //~ INCLUDED_PLANE_HPP