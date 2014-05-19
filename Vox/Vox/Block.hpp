#ifndef INCLUDED_BLOCK_HPP
#define INCLUDED_BLOCK_HPP

#define BLOCK_SIZE 1.0f

#include <SFML/System.hpp>
#include <vector>

class Block
{
public:
	enum BlockType
	{
		BlockType_Air,
		BlockType_Grass,
		BlockType_Dirt,
		BlockType_Stone,
		BlockType_Wood,
		BlockType_Sand,

		BlockType_NumTypes
	};

	enum VertIndex
	{
		BOT_LEF,
		BOT_RIG,
		TOP_RIG,
		TOP_LEF
	};

	enum FaceIndex
	{
		FRO,
		BAC,
		RIG,
		LEF,
		BOT,
		TOP
	};

    Block(BlockType _type = BlockType::BlockType_Air);
    ~Block();

    bool isActive();
    void setActive(bool _active);

	BlockType getType(void);
	void setType(Block::BlockType _type);

	static sf::Vector2f getTexCoords(sf::Vector2i _tileSheetCoords, VertIndex _vertexIndex);
	
private:
	

    bool m_active;

    BlockType m_blockType;

};

#endif //~ INCLUDED_BLOCK_HPP