#include "ChunkManager.hpp"


ChunkManager::ChunkManager() :
m_Shader("Resources/Shaders/vert.glsl", "Resources/Shaders/frag.glsl")
{
	m_Shader.bind();

	m_Chunks.push_back(new Chunk(this));
}

ChunkManager::~ChunkManager()
{
	m_Shader.unbind();
}


void ChunkManager::update(float _dt)
{
	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		m_Chunks.at(i)->Update(_dt);
	}
}
void ChunkManager::render(void)
{
	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		m_Chunks.at(i)->Render();
	}
}

unsigned int ChunkManager::getShaderId(void)
{
	return m_Shader.id();
}