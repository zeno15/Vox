#ifndef INCLUDED_ENTITY_HPP
#define INCLUDED_ENTITY_HPP

#include <glm/glm.hpp>
#include "Shader.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update(float _delta) = 0;
	virtual void render(void) = 0;

	glm::vec4 getPosition(void);


protected:
	glm::vec4					m_Position;
};

#endif //~ INCLUDED_ENTITY_HPP