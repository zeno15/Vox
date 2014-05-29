#include "Chunk.hpp"

#include "ChunkManager.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

//#define ELEMENTS

Chunk::Chunk(ChunkManager *_chunkManager, sf::Vector3i _chunkCoords) :
m_ChunkManager(_chunkManager),
m_ChunkCoords(_chunkCoords),
m_Generated(false)
{
    // Create the blocks
    m_pBlocks = new Block**[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++)
    {
        m_pBlocks[i] = new Block*[CHUNK_SIZE];

        for(int j = 0; j < CHUNK_SIZE; j++)
        {
            m_pBlocks[i][j] = new Block[CHUNK_SIZE];
        }
    }
}

Chunk::~Chunk()
{
    // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            delete [] m_pBlocks[i][j];
        }

        delete [] m_pBlocks[i];
    }
    delete [] m_pBlocks;

	glDeleteVertexArrays(1, &m_VAO);
}


void Chunk::Update(float _dt)
{
}

void Chunk::Render()
{
	glBindVertexArray(m_VAO);
	
	#ifndef ELEMENTS

	glDrawArrays(GL_TRIANGLES, 0, m_NumberVertices);

	#endif

	#ifdef ELEMENTS

	glDrawElements(GL_TRIANGLES, m_Indexes.size(), GL_UNSIGNED_INT, &m_Indexes[0]);

	#endif 
}

void Chunk::updateMesh(sf::Vector3f _viewVector)
{
	m_Indexes.clear();

	for (unsigned int i = 0; i < m_NumberVertices / 36; i += 1)
	{
		if (_viewVector.x > 0.0f)
		{
			//~ Draw left 18 - 23
			m_Indexes.push_back(i * 6 + 18);
			m_Indexes.push_back(i * 6 + 19);
			m_Indexes.push_back(i * 6 + 20);
			m_Indexes.push_back(i * 6 + 21);
			m_Indexes.push_back(i * 6 + 22);
			m_Indexes.push_back(i * 6 + 23);
		}
		else
		{
			//~ Draw right 12 - 17
			m_Indexes.push_back(i * 6 + 12);
			m_Indexes.push_back(i * 6 + 13);
			m_Indexes.push_back(i * 6 + 14);
			m_Indexes.push_back(i * 6 + 15);
			m_Indexes.push_back(i * 6 + 16);
			m_Indexes.push_back(i * 6 + 17);
		}
		if (_viewVector.y > 0.0f)
		{
			//~ Draw bottom 24 - 29
			m_Indexes.push_back(i * 6 + 24);
			m_Indexes.push_back(i * 6 + 25);
			m_Indexes.push_back(i * 6 + 26);
			m_Indexes.push_back(i * 6 + 27);
			m_Indexes.push_back(i * 6 + 28);
			m_Indexes.push_back(i * 6 + 29);
		}
		else
		{
			//~ Draw top 30 - 35
			m_Indexes.push_back(i * 6 + 30);
			m_Indexes.push_back(i * 6 + 31);
			m_Indexes.push_back(i * 6 + 32);
			m_Indexes.push_back(i * 6 + 33);
			m_Indexes.push_back(i * 6 + 34);
			m_Indexes.push_back(i * 6 + 35);
		}
		if (_viewVector.z > 0.0f)
		{
			//~ Draw back 6 - 11
			m_Indexes.push_back(i * 6 + 6);
			m_Indexes.push_back(i * 6 + 7);
			m_Indexes.push_back(i * 6 + 8);
			m_Indexes.push_back(i * 6 + 9);
			m_Indexes.push_back(i * 6 + 10);
			m_Indexes.push_back(i * 6 + 11);
		}
		else
		{
			//~ Draw front 0 - 5
			m_Indexes.push_back(i * 6 + 0);
			m_Indexes.push_back(i * 6 + 1);
			m_Indexes.push_back(i * 6 + 2);
			m_Indexes.push_back(i * 6 + 3);
			m_Indexes.push_back(i * 6 + 4);
			m_Indexes.push_back(i * 6 + 5);
		}
	}
}
void Chunk::updateIndexes(void)
{
	m_Indexes.clear();

	unsigned int toBlock = 0;

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				bool front =	true;
				bool back =		true;
				bool left =		true;
				bool right =	true;
				bool top =		true;
				bool bottom =	true;

				if (m_pBlocks[x][y][z].isActive())
				{
					if (x > 0)
					{
						if (m_pBlocks[x - 1][y][z].isActive())
						{
							left = false;
						}
					}
					if (x + 1 < CHUNK_SIZE)
					{
						if (m_pBlocks[x + 1][y][z].isActive())
						{
							right = false;
						}
					}
					if (y > 0)
					{
						if (m_pBlocks[x][y - 1][z].isActive())
						{
							bottom = false;
						}
					}
					if (y + 1 < CHUNK_SIZE)
					{
						if (m_pBlocks[x][y + 1][z].isActive())
						{
							top = false;
						}
					}
					if (z > 0)
					{
						if (m_pBlocks[x][y][z - 1].isActive())
						{
							back = false;
						}
					}
					if (z + 1 < CHUNK_SIZE)
					{
						if (m_pBlocks[x][y][z + 1].isActive())
						{
							front = false;
						}
					}


					if (!front)
					{
						//~ 0-5
						m_Indexes.push_back(toBlock + 0);
						m_Indexes.push_back(toBlock + 1);
						m_Indexes.push_back(toBlock + 2);
						m_Indexes.push_back(toBlock + 3);
						m_Indexes.push_back(toBlock + 4);
						m_Indexes.push_back(toBlock + 5);
					}
					if (!back)
					{
						//~ 6-11
						m_Indexes.push_back(toBlock + 6);
						m_Indexes.push_back(toBlock + 7);
						m_Indexes.push_back(toBlock + 8);
						m_Indexes.push_back(toBlock + 9);
						m_Indexes.push_back(toBlock + 10);
						m_Indexes.push_back(toBlock + 11);
					}
					if (!left)
					{
						//~ 12-17
						m_Indexes.push_back(toBlock + 12);
						m_Indexes.push_back(toBlock + 13);
						m_Indexes.push_back(toBlock + 14);
						m_Indexes.push_back(toBlock + 15);
						m_Indexes.push_back(toBlock + 16);
						m_Indexes.push_back(toBlock + 17);
					}
					if (!right)
					{
						//~ 18-23
						m_Indexes.push_back(toBlock + 18);
						m_Indexes.push_back(toBlock + 19);
						m_Indexes.push_back(toBlock + 20);
						m_Indexes.push_back(toBlock + 21);
						m_Indexes.push_back(toBlock + 22);
						m_Indexes.push_back(toBlock + 23);
					}
					if (!top)
					{
						//~ 24-29
						m_Indexes.push_back(toBlock + 24);
						m_Indexes.push_back(toBlock + 25);
						m_Indexes.push_back(toBlock + 26);
						m_Indexes.push_back(toBlock + 27);
						m_Indexes.push_back(toBlock + 28);
						m_Indexes.push_back(toBlock + 29);
					}
					if (!bottom)
					{
						//~ 30-35
						m_Indexes.push_back(toBlock + 30);
						m_Indexes.push_back(toBlock + 31);
						m_Indexes.push_back(toBlock + 32);
						m_Indexes.push_back(toBlock + 33);
						m_Indexes.push_back(toBlock + 34);
						m_Indexes.push_back(toBlock + 35);
					}
				}

				toBlock += 36;
			}
		}
	}
	
}
void Chunk::createMesh(void)
{
	

	std::vector<float> vertexes;
	std::vector<float> normals;
	std::vector<float> colours;
	std::vector<float> textures;

	GLuint in_Position = glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Position");
	GLuint in_Color =    glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Color");
	GLuint in_Normal =   glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Normal");
	GLuint in_TexUV =    glGetAttribLocation(m_ChunkManager->getShaderId(), "in_TexUV");

	#ifndef ELEMENTS
	
	for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if(m_pBlocks[x][y][z].isActive())
                {
					createCube(x, y, z, &vertexes, &normals, &colours, &textures);
                }
            }
        }
    }

	m_NumberVertices = vertexes.size() / 3;


	#endif 

	#ifdef ELEMENTS

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				createCube(x, y, z, &vertexes, &normals, &colours, &textures, true);
			}
		}
	}

	updateIndexes();

	#endif

	glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

	GLuint vbo[4];
    glGenBuffers(4, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexes.size(), &vertexes[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_Position);
    glVertexAttribPointer(in_Position, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* colours.size(), &colours[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_Color);
    glVertexAttribPointer(in_Color, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_Normal);
    glVertexAttribPointer(in_Normal, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* textures.size(), &textures[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_TexUV);
    glVertexAttribPointer(in_TexUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glBindVertexArray(0);
}
void Chunk::createCube(int _x, int _y, int _z, std::vector<float> *_vertexes, std::vector<float> *_normals, std::vector<float> *_colours, std::vector<float> *_textureCoords, bool _allActive /*= false*/)
{
	if (!m_pBlocks[_x][_y][_z].isActive()) return;

	sf::Vector3f p1 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p2 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p3 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p4 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p5 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p6 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p7 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p8 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);

	sf::Vector3f n;
	sf::Vector2f tex;

	DataManager *data = m_ChunkManager->getDataManager();

	Block::BlockType btype = m_pBlocks[_x][_y][_z].getType();

	bool front =	true;
	bool back =		true;
	bool left =		true;
	bool right =	true;
	bool top =		true;
	bool bottom =	true;

	if (!_allActive)
	{

		if (_x > 0)
		{
			if (m_pBlocks[_x - 1][_y][_z].isActive())
			{
				left = false;
			}
		}
		if (_x + 1 < CHUNK_SIZE)
		{
			if (m_pBlocks[_x + 1][_y][_z].isActive())
			{
				right = false;
			}
		}
		if (_y > 0)
		{
			if (m_pBlocks[_x][_y - 1][_z].isActive())
			{
				bottom = false;
			}
		}
		if (_y + 1 < CHUNK_SIZE)
		{
			if (m_pBlocks[_x][_y + 1][_z].isActive())
			{
				top = false;
			}
		}
		if (_z > 0)
		{
			if (m_pBlocks[_x][_y][_z - 1].isActive())
			{
				back = false;
			}
		}
		if (_z + 1 < CHUNK_SIZE)
		{
			if (m_pBlocks[_x][_y][_z + 1].isActive())
			{
				front = false;
			}
		}

	}


	if (front)
	{
		//~ Front
		n = sf::Vector3f(0.0f, 0.0f, 1.0f);
		//~ Triangle 1 {1, 2, 3}
		_vertexes->push_back(p1.x);			_vertexes->push_back(p1.y);			_vertexes->push_back(p1.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p2.x);			_vertexes->push_back(p2.y);			_vertexes->push_back(p2.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p3.x);			_vertexes->push_back(p3.y);			_vertexes->push_back(p3.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {1, 3, 4}
		_vertexes->push_back(p1.x);			_vertexes->push_back(p1.y);			_vertexes->push_back(p1.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p3.x);			_vertexes->push_back(p3.y);			_vertexes->push_back(p3.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p4.x);			_vertexes->push_back(p4.y);			_vertexes->push_back(p4.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::FRO), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}
	
	if (back)
	{
		//~ Back
		n = sf::Vector3f(0.0f, 0.0f, -1.0f);
		//~ Triangle 1 {5, 6, 7}
		_vertexes->push_back(p5.x);			_vertexes->push_back(p5.y);			_vertexes->push_back(p5.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p6.x);			_vertexes->push_back(p6.y);			_vertexes->push_back(p6.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p7.x);			_vertexes->push_back(p7.y);			_vertexes->push_back(p7.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {5, 7, 8}
		_vertexes->push_back(p5.x);			_vertexes->push_back(p5.y);			_vertexes->push_back(p5.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p7.x);			_vertexes->push_back(p7.y);			_vertexes->push_back(p7.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p8.x);			_vertexes->push_back(p8.y);			_vertexes->push_back(p8.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BAC), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}

	if (right)
	{
		//~ Right
		n = sf::Vector3f(1.0f, 0.0f, 0.0f);
		//~ Triangle 1 {2, 5, 8}
		_vertexes->push_back(p2.x);			_vertexes->push_back(p2.y);			_vertexes->push_back(p2.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p5.x);			_vertexes->push_back(p5.y);			_vertexes->push_back(p5.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p8.x);			_vertexes->push_back(p8.y);			_vertexes->push_back(p8.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {2, 8, 3}
		_vertexes->push_back(p2.x);			_vertexes->push_back(p2.y);			_vertexes->push_back(p2.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p8.x);			_vertexes->push_back(p8.y);			_vertexes->push_back(p8.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p3.x);			_vertexes->push_back(p3.y);			_vertexes->push_back(p3.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::RIG), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}

	if (left)
	{
		//~ Left
		n = sf::Vector3f(-1.0f, 0.0f, 0.0f);
		//~ Triangle 1 {6, 1, 4}
		_vertexes->push_back(p6.x);			_vertexes->push_back(p6.y);			_vertexes->push_back(p6.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p1.x);			_vertexes->push_back(p1.y);			_vertexes->push_back(p1.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p4.x);			_vertexes->push_back(p4.y);			_vertexes->push_back(p4.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {6, 4, 7}
		_vertexes->push_back(p6.x);			_vertexes->push_back(p6.y);			_vertexes->push_back(p6.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p4.x);			_vertexes->push_back(p4.y);			_vertexes->push_back(p4.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p7.x);			_vertexes->push_back(p7.y);			_vertexes->push_back(p7.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::LEF), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}

	if (bottom)
	{
		//~ Bottom
		n = sf::Vector3f(0.0f, -1.0f, 0.0f);
		//~ Triangle 1 {2, 1, 6}
		_vertexes->push_back(p2.x);			_vertexes->push_back(p2.y);			_vertexes->push_back(p2.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p1.x);			_vertexes->push_back(p1.y);			_vertexes->push_back(p1.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p6.x);			_vertexes->push_back(p6.y);			_vertexes->push_back(p6.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {2, 6, 5}
		_vertexes->push_back(p2.x);			_vertexes->push_back(p2.y);			_vertexes->push_back(p2.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p6.x);			_vertexes->push_back(p6.y);			_vertexes->push_back(p6.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p5.x);			_vertexes->push_back(p5.y);			_vertexes->push_back(p5.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::BOT), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}

	if (top)
	{
		//~ Top
		n = sf::Vector3f(0.0f, 1.0f, 0.0f);
		//~ Triangle 1 {4, 3, 8}
		_vertexes->push_back(p4.x);			_vertexes->push_back(p4.y);			_vertexes->push_back(p4.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p3.x);			_vertexes->push_back(p3.y);			_vertexes->push_back(p3.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::BOT_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p8.x);			_vertexes->push_back(p8.y);			_vertexes->push_back(p8.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		//~ Triangle 2 {4, 8, 7}
		_vertexes->push_back(p4.x);			_vertexes->push_back(p4.y);			_vertexes->push_back(p4.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::BOT_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p8.x);			_vertexes->push_back(p8.y);			_vertexes->push_back(p8.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::TOP_RIG);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
		_vertexes->push_back(p7.x);			_vertexes->push_back(p7.y);			_vertexes->push_back(p7.z);
		_normals->push_back(n.x);			_normals->push_back(n.y);			_normals->push_back(n.z);
		_colours->push_back(0.0f);			_colours->push_back(1.0f);			_colours->push_back(0.0f);
		tex = Block::getTexCoords(data->getTileSheetCoords(btype, Block::FaceIndex::TOP), Block::VertIndex::TOP_LEF);
		_textureCoords->push_back(tex.x);	_textureCoords->push_back(tex.y);
	}
}

void Chunk::generate(void)
{
	sf::Clock clock;
	for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
				m_pBlocks[x][y][z].setType((Block::BlockType)(rand() % Block::BlockType::BlockType_NumTypes));
            }
        }
    }

	createMesh();

	m_Generated = true;

	//std::cout << "Generating took: " << clock.getElapsedTime().asMicroseconds() << " microseconds." << std::endl;
}
bool Chunk::generated(void)
{
	return m_Generated;
}

sf::Vector3i Chunk::getChunkCoords(void)
{
	return m_ChunkCoords;
}