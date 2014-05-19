#ifndef INCLUDED_CHUNK_MANAGER_HPP
#define INCLUDED_CHUNK_MANAGER_HPP

#include "Chunk.hpp"
#include "Shader.hpp"
#include "DataManager.hpp"

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void update(float _dt);
	void render(void);

	unsigned int getShaderId(void);

	void updateMeshs(sf::Vector3f _viewVector);

	DataManager *getDataManager(void);

private:
	std::vector<Chunk *> m_Chunks;

	Shader				m_Shader;

	DataManager			m_Data;
};

#endif //~ INCLUDED_CHUNK_MANAGER_HPP