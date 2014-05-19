#ifndef INCLUDED_CHUNK_HPP
#define INCLUDED_CHUNK_HPP

#include <vector>
#include <SFML/System.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "Block.hpp"
#include "Shader.hpp"

class ChunkManager;

class Chunk
{
public:
    Chunk(ChunkManager *_chunkManager);
    ~Chunk();

    void Update(float _dt);

    void Render();

	
	void updateMesh(sf::Vector3f _viewVector);
	void createMesh(void);
	void createCube(int _x, int _y, int _z, std::vector<sf::Vector3f> *_vertexes, std::vector<sf::Vector3f> *_normals, std::vector<sf::Vector3f> *_colours, std::vector<sf::Vector2f> *_textureCoords);

	

    static const int CHUNK_SIZE = 8;
private:
    // The blocks data
    Block***						m_pBlocks;

	GLuint							m_VAO;

	unsigned int					m_NumberVertices;

	ChunkManager *					m_ChunkManager;

	std::vector<unsigned int>		m_Indexes;
};

#endif //~ INCLUDED_CHUNK_HPP