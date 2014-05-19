#include "Block.hpp"


Block::Block() :
m_active(false)
{
}

Block::~Block()
{
}


bool Block::isActive()
{
	return m_active;
}
void Block::setActive(bool _active)
{
	m_active = _active;
}