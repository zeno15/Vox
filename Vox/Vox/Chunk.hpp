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
    Chunk(ChunkManager *_chunkManager, sf::Vector3i _chunkCoords);
    ~Chunk();

    void Update(float _dt);

    void Render();

	void updateMesh(sf::Vector3f _viewVector);
	void updateIndexes(void);
	void createMesh(void);
	void createCube(int _x, int _y, int _z, std::vector<float> *_vertexes, std::vector<float> *_normals, std::vector<float> *_colours, std::vector<float> *_textureCoords, bool _allActive = false);

	void generate(void);

	bool generated(void);

	sf::Vector3i getChunkCoords(void);

    static const int CHUNK_SIZE = 16;
private:
    // The blocks data
    Block***						m_pBlocks;

	GLuint							m_VAO;

	unsigned int					m_NumberVertices;

	ChunkManager *					m_ChunkManager;

	std::vector<unsigned int>		m_Indexes;

	sf::Vector3i					m_ChunkCoords;

	bool							m_Generated;
};

#endif //~ INCLUDED_CHUNK_HPP