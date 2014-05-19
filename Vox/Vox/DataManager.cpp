#include "DataManager.hpp"

#include <string>
#include <fstream>

DataManager::DataManager()
{
	m_TileFaceTextureCoords;

	std::ifstream file;

	file.open("Resources/Data/textureCoordinateData.data");

	std::string line;
	
	while (file.good())
	{
		std::getline(file, line);

		if (line.size() > 0)
		{
			if (line.at(0) == '#')
			{
				continue;
			}

			std::vector<int> coords = gettileFaceCoordsFromString(line);
			
			m_TileFaceTextureCoords.push_back(std::vector<sf::Vector2i>());

			for (unsigned int i = 0; i < coords.size() / 2; i += 1)
			{
				m_TileFaceTextureCoords.back().push_back(sf::Vector2i(coords.at(i * 2 + 0), coords.at(i * 2 + 1)));
			}
		}
	}
}

DataManager::~DataManager()
{
}

sf::Vector2i DataManager::getTileSheetCoords(Block::BlockType _blockId, Block::FaceIndex _face)
{
	return m_TileFaceTextureCoords.at(_blockId).at(_face);
}

std::vector<int> DataManager::gettileFaceCoordsFromString(std::string _str)
{
	std::vector<int> container;

	std::string token;
	std::stringstream sin(_str);
	while (std::getline(sin, token, '/'))
	{
		int number;
		std::stringstream converter(token);
		converter >> number;
		container.push_back(number);
	}

	return container;
}