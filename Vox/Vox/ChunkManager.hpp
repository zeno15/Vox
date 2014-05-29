#ifndef INCLUDED_CHUNK_MANAGER_HPP
#define INCLUDED_CHUNK_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

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

	void threadLoadUnload(void);

	DataManager *getDataManager(void);

	sf::Vector2i getRenderedChunksVsAvailable(void);

	sf::Vector3i getCamChunkCoords(void);

private:
	Shader						m_Shader;

	GLuint						m_mvId;
	GLuint						m_mvpId;
	GLuint						m_norId;





	std::vector<Chunk *>		m_Chunks;

	std::vector<Chunk *>		m_ToUnload;

	std::vector<Chunk *>		m_Load;



	sf::Texture *				m_ChunkTexture;

	sf::Vector2i				m_ChunkRenderingRatio;
	




	DataManager					m_Data;
};

#endif //~ INCLUDED_CHUNK_MANAGER_HPP