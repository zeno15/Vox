#include "ChunkManager.hpp"

#include "Game.hpp"

ChunkManager::ChunkManager() :
m_Shader("Resources/Shaders/vert.glsl", "Resources/Shaders/frag.glsl")
{
	m_mvId  = glGetUniformLocation(m_Shader.id(), "mv");
	m_mvpId = glGetUniformLocation(m_Shader.id(), "mvp");
	m_norId = glGetUniformLocation(m_Shader.id(), "nor");

	m_ChunkTexture = new sf::Texture();
	m_ChunkTexture->loadFromFile("Resources/Textures/testcube.png");
}

ChunkManager::~ChunkManager()
{
	delete m_ChunkTexture;

	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		delete m_Chunks.at(i);
	}
}


void ChunkManager::update(float _dt)
{
	static sf::Vector3i pastChunkCoords;

	int chunkloadwidth = 3;

	sf::Vector3i chunkCoords = getCamChunkCoords();

	for (unsigned int i = 0; i < m_Chunks.size(); i += 1)
	{
		m_Chunks.at(i)->Update(_dt);

		if (m_Chunks.at(i)->getChunkCoords().x > chunkCoords.x + chunkloadwidth ||
			m_Chunks.at(i)->getChunkCoords().z > chunkCoords.z + chunkloadwidth ||
			m_Chunks.at(i)->getChunkCoords().x < chunkCoords.x - chunkloadwidth ||
			m_Chunks.at(i)->getChunkCoords().z < chunkCoords.z - chunkloadwidth)
		{
			m_ToUnload.push_back(m_Chunks.at(i));

			m_Chunks.erase(m_Chunks.begin() + i);
		}
	} 

	if (pastChunkCoords != chunkCoords)
	{
		for (int i = chunkCoords.x - chunkloadwidth; i <= chunkCoords.x + chunkloadwidth; i += 1)
		{
			for (int j = chunkCoords.z - chunkloadwidth; j <= chunkCoords.z + chunkloadwidth; j += 1)
			{
				bool loaded = false;
				for (unsigned int k = 0; k < m_Chunks.size(); k += 1)
				{
					sf::Vector3i pos = m_Chunks.at(k)->getChunkCoords();
							
					if (pos.x == i && pos.z == j)
					{
						loaded = true;
						break;
					}
				}
				if (!loaded)
				{
					m_Load.push_back(new Chunk(this, sf::Vector3i(i, 0, j)));
				}
			}
		}
	}
	
	if (m_ToUnload.size() > 0)
	{
		delete m_ToUnload.at(0);

		m_ToUnload.erase(m_ToUnload.begin());
	}

	if (m_Load.size() > 0)
	{
		m_Load.at(0)->generate();

		m_Chunks.push_back(m_Load.at(0));

		m_Load.erase(m_Load.begin());
	}


	pastChunkCoords = chunkCoords;
}
void ChunkManager::render(void)
{
	int count = 0;

	m_Shader.bind();

	glm::mat4x4 proj = sCamera.getPerspectiveMatrix();
	glm::mat4x4 view = sCamera.getProjectionMatrix();
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
		count += 1;
	}

	sf::Texture::bind(nullptr);

	m_Shader.unbind();

	m_ChunkRenderingRatio.x = count;
	m_ChunkRenderingRatio.y = m_Chunks.size();
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

sf::Vector2i ChunkManager::getRenderedChunksVsAvailable(void)
{
	return m_ChunkRenderingRatio;
}

sf::Vector3i ChunkManager::getCamChunkCoords(void)
{
	glm::vec4 pos = sCamera.getPosition();

	sf::Vector3i negOffset((pos.x < 0.0f ? -1 : 0),
						   (pos.y < 0.0f ? -1 : 0),
						   (pos.z < 0.0f ? -1 : 0));

	return sf::Vector3i(static_cast<int>(pos.x / static_cast<float>(Chunk::CHUNK_SIZE)), 
						static_cast<int>(pos.y / static_cast<float>(Chunk::CHUNK_SIZE)), 
						static_cast<int>(pos.z / static_cast<float>(Chunk::CHUNK_SIZE))) + negOffset;
}