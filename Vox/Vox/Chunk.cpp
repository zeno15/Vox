#include "Chunk.hpp"

#include "ChunkManager.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>

Chunk::Chunk(ChunkManager *_chunkManager) :
m_ChunkManager(_chunkManager)
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

	createMesh();
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

	glDrawArrays(GL_TRIANGLES, 0, m_NumberVertices); //~ glDrawElements with indexes will be faster eventually

}

void Chunk::createMesh(void)
{
	sf::Clock clock;

	std::vector<sf::Vector3f> vertexes;
	std::vector<sf::Vector3f> normals;
	std::vector<sf::Vector3f> colours;
	std::vector<sf::Vector2f> textures;

	for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                if(true || m_pBlocks[x][y][z].isActive())
                {
					createCube(x, y, z, &vertexes, &normals, &colours, &textures);
                }
            }
        }
    }

	std::vector<float> v;
	std::vector<float> c;
	std::vector<float> n;
	std::vector<float> t;

	for (unsigned int i = 0; i < vertexes.size(); i += 1)
	{
		v.push_back(vertexes.at(i).x);
		v.push_back(vertexes.at(i).y);
		v.push_back(vertexes.at(i).z);

		c.push_back(colours.at(i).x);
		c.push_back(colours.at(i).y);
		c.push_back(colours.at(i).z);

		n.push_back(normals.at(i).x);
		n.push_back(normals.at(i).y);
		n.push_back(normals.at(i).z);

		t.push_back(textures.at(i).x);
		t.push_back(textures.at(i).y);
	}

	m_NumberVertices = vertexes.size();


	GLuint in_Position = glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Position");
	GLuint in_Color =    glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Color");
	GLuint in_Normal =   glGetAttribLocation(m_ChunkManager->getShaderId(), "in_Normal");
	GLuint in_TexUV =    glGetAttribLocation(m_ChunkManager->getShaderId(), "in_TexUV");

	glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

	GLuint vbo[4];
    glGenBuffers(4, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &v[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_Position);
    glVertexAttribPointer(in_Position, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* c.size(), &c[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_Color);
    glVertexAttribPointer(in_Color, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* n.size(), &n[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_Normal);
    glVertexAttribPointer(in_Normal, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* t.size(), &t[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_TexUV);
    glVertexAttribPointer(in_TexUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	

	glBindVertexArray(0);

	std::cout << "Creating " << vertexes.size() << " sized mesh took " << clock.getElapsedTime().asMilliseconds() << " microseconds." << std::endl;
}
void Chunk::createCube(int _x, int _y, int _z, std::vector<sf::Vector3f> *_vertexes, std::vector<sf::Vector3f> *_normals, std::vector<sf::Vector3f> *_colours, std::vector<sf::Vector2f> *_textureCoords)
{
	sf::Vector3f p1 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p2 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p3 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p4 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 1) * BLOCK_SIZE);
	sf::Vector3f p5 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p6 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 0) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p7 = sf::Vector3f((_x + 0) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);
	sf::Vector3f p8 = sf::Vector3f((_x + 1) * BLOCK_SIZE, (_y + 1) * BLOCK_SIZE, (_z + 0) * BLOCK_SIZE);

	

	sf::Vector3f n;

	bool front = true;
	bool back = true;
	bool left = true;
	bool right = true;
	bool top = true;
	bool bottom = true;

	if (front)
	{
		//~ Front
		n = sf::Vector3f(0.0f, 0.0f, 1.0f);
		//~ Triangle 1 {1, 2, 3}
		_vertexes->push_back(p1);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(0.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p2);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p3);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {1, 3, 4}
		_vertexes->push_back(p1);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(0.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p3);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p4);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(0.0f / 192.0f, 0.0f / 32.0f));
	}
	
	if (back)
	{
		//~ Back
		n = sf::Vector3f(0.0f, 0.0f, -1.0f);
		//~ Triangle 1 {5, 6, 7}
		_vertexes->push_back(p5);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p6);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p7);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {5, 7, 8}
		_vertexes->push_back(p5);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p7);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p8);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(32.0f / 192.0f, 0.0f / 32.0f));
	}

	if (right)
	{
		//~ Right
		n = sf::Vector3f(1.0f, 0.0f, 0.0f);
		//~ Triangle 1 {2, 5, 8}
		_vertexes->push_back(p2);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p5);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p8);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {2, 8, 3}
		_vertexes->push_back(p2);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p8);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p3);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(64.0f / 192.0f, 0.0f / 32.0f));
	}

	if (left)
	{
		//~ Left
		n = sf::Vector3f(-1.0f, 0.0f, 0.0f);
		//~ Triangle 1 {6, 1, 4}
		_vertexes->push_back(p6);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p1);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p4);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {6, 4, 7}
		_vertexes->push_back(p6);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p4);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p7);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(0.0f, 1.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(96.0f / 192.0f, 0.0f / 32.0f));
	}

	if (bottom)
	{
		//~ Bottom
		n = sf::Vector3f(0.0f, -1.0f, 0.0f);
		//~ Triangle 1 {2, 1, 6}
		_vertexes->push_back(p2);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p1);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p6);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {2, 6, 5}
		_vertexes->push_back(p2);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p6);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p5);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 1.0f, 0.0f));
		_textureCoords->push_back(sf::Vector2f(128.0f / 192.0f, 0.0f / 32.0f));
	}

	if (top)
	{
		//~ Top
		n = sf::Vector3f(0.0f, 1.0f, 0.0f);
		//~ Triangle 1 {4, 3, 8}
		_vertexes->push_back(p4);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p3);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(192.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p8);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(192.0f / 192.0f, 0.0f / 32.0f));
		//~ Triangle 2 {4, 8, 7}
		_vertexes->push_back(p4);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 32.0f / 32.0f));
		_vertexes->push_back(p8);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(192.0f / 192.0f, 0.0f / 32.0f));
		_vertexes->push_back(p7);
		_normals->push_back(n);
		_colours->push_back(sf::Vector3f(1.0f, 0.0f, 1.0f));
		_textureCoords->push_back(sf::Vector2f(160.0f / 192.0f, 0.0f / 32.0f));
	}
}
