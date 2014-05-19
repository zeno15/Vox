#ifndef INCLUDED_DATA_MANAGER_HPP
#define INCLUDED_DATA_MANAGER_HPP

#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>

#include "Block.hpp"

class DataManager
{
public:
	DataManager();
	~DataManager();

	sf::Vector2i getTileSheetCoords(Block::BlockType _blockId, Block::FaceIndex _face);

private:
	std::vector<int> gettileFaceCoordsFromString(std::string _str);

	
	std::vector<std::vector<sf::Vector2i>>				m_TileFaceTextureCoords;
};

#endif //~ INCLUDED_DATA_MANAGER_HPP