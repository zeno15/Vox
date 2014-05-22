#ifndef INCLUDED_CHUNK_MANAGER_HPP
#define INCLUDED_CHUNK_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include "Chunk.hpp"
#include "Shader.hpp"
#include "DataManager.hpp"
#include "Camera.hpp"

class ChunkManager
{
public:
	ChunkManager(Camera *_camera);
	~ChunkManager();

	void update(float _dt);
	void render(void);

	unsigned int getShaderId(void);

	void updateMeshs(sf::Vector3f _viewVector);

	DataManager *getDataManager(void);

private:
	std::vector<Chunk *> m_Chunks;

	Shader				m_Shader;

	GLuint				m_mvId;
	GLuint				m_mvpId;
	GLuint				m_norId;

	DataManager			m_Data;

	Camera *			m_Camera;

	sf::Texture *		m_ChunkTexture;
};

#endif //~ INCLUDED_CHUNK_MANAGER_HPP