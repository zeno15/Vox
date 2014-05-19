#ifndef INCLUDED_BLOCK_HPP
#define INCLUDED_BLOCK_HPP

#define BLOCK_SIZE 1.0f

class Block
{
public:
    Block();
    ~Block();

    bool isActive();
    void setActive(bool _active);

	
	
private:
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

    bool m_active;

    BlockType m_blockType;
};

#endif //~ INCLUDED_BLOCK_HPP