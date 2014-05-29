#include "Entity.hpp"


Entity::Entity() :
m_Position(8.0f, 24.0f, 24.0f, 1.0f)
{
}

Entity::~Entity()
{
}


glm::vec4 Entity::getPosition(void)
{
	return m_Position;
}