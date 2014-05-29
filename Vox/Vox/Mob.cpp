#include "Mob.hpp"


Mob::Mob() :
m_xAngle(180.0f),
m_yAngle(0.0f)
{
}

Mob::~Mob()
{
}


glm::vec2 Mob::getRotation(void)
{
	return glm::vec2(m_xAngle, m_yAngle);
}