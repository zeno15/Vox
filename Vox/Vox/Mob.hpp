#ifndef INCLUDED_MOB_HPP
#define INCLUDED_MOB_HPP

#include "Entity.hpp"

class Mob : public Entity
{
public:
	Mob();
	~Mob();

	glm::vec2 getRotation(void);

	virtual glm::vec4 getFootPosition(void) = 0;

protected:
	float					m_xAngle;
	float					m_yAngle;
};

#endif //~ INCLUDED_MOB_HPP