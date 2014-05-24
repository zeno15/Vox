#include "ChunkManager.hpp"


ChunkManager::ChunkManager(Camera *_camera) :
m_Shader("Resources/Shaders/vert.glsl", "Resources/Shaders/frag.glsl"),
m_Camera(_camera)
{
	m_mvId  = glGetUniformLocation(m_Shader.id(), "mv");
	m_mvpId = glGetUniformLocation(m_Shader.id(), "mvp");
	m_norId = glGetUniformLocation(m_Shader.id(), "nor");

	m_ChunkTexture = new sf::Texture();
	m_ChunkTexture->loadFromFile("Resources/Textures/testcube.png");

	int X = 2;
	int Y = 1;
	int Z = 2;

	for (int i = 0; i < Y; i += 1)
	{
		for (int j = 0; j < X; j += 1)
		{
			for (int k = 0; k < Z; k += 1)
			{
				m_Chunks.push_back(new Chunk(this, sf::Vector3i(j, i, k)));
			}
		}
	}
}

ChunkManager::~ChunkManager()
{
	//delete m_ChunkTexture;

	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		delete m_Chunks.at(i);
	}
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
	m_Shader.bind();

	glm::mat4x4 proj = m_Camera->getPerspectiveMatrix();
	glm::mat4x4 view = m_Camera->getProjectionMatrix();
	glm::mat4x4 matrix = glm::mat4x4(1.0f);
	
	glm::mat4x4 mv, mvp, nor;

	sf::Texture::bind(m_ChunkTexture);

	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		sf::Vector3i chunkOffset = m_Chunks.at(i)->getChunkCoords();

		matrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(chunkOffset.x * Chunk::CHUNK_SIZE, chunkOffset.y * Chunk::CHUNK_SIZE, chunkOffset.z * Chunk::CHUNK_SIZE));

		mv = view * matrix;
		mvp = proj * mv;
		nor = glm::inverse(mv);

		glUniformMatrix4fv(m_mvId,  1, GL_FALSE, &mv[0][0]);
		glUniformMatrix4fv(m_mvpId, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(m_norId, 1, GL_TRUE,  &nor[0][0]);

		m_Chunks.at(i)->Render();
	}

	sf::Texture::bind(nullptr);

	m_Shader.unbind();
}

unsigned int ChunkManager::getShaderId(void)
{
	return m_Shader.id();
}

void ChunkManager::updateMeshs(sf::Vector3f _viewVector)
{
	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		m_Chunks.at(i)->updateMesh(_viewVector);
	}
}

DataManager *ChunkManager::getDataManager(void)
{
	return &m_Data;
}