#include "Block.hpp"


Block::Block(BlockType _type /*= BlockType::BlockType_Air*/) :
m_active(true),
m_blockType(_type)
{
	if (m_blockType == BlockType::BlockType_Air)
	{
		m_active = false;
	}
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

Block::BlockType Block::getType(void)
{
	return m_blockType;
}
void Block::setType(Block::BlockType _type)
{
	m_blockType = _type;

	m_active = !(m_blockType == BlockType::BlockType_Air);
}

sf::Vector2f Block::getTexCoords(sf::Vector2i _tileSheetCoords, VertIndex _vertexIndex)
{
	sf::Vector2f coords((float)(_tileSheetCoords.x) * 32.0f, (float)(_tileSheetCoords.y) * 32.0f);

	if (_vertexIndex == 0 || _vertexIndex == 1)
	{
		coords.y += 32.0f;
	}
	if (_vertexIndex == 1 || _vertexIndex == 2)
	{
		coords.x += 32.0f;
	}

	return coords / 2048.0f;
}