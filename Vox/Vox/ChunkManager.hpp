#ifndef INCLUDED_CHUNK_MANAGER_HPP
#define INCLUDED_CHUNK_MANAGER_HPP

#include "Chunk.hpp"
#include "Shader.hpp"

class ChunkManager
{
public:
	ChunkManager();
	~ChunkManager();

	void update(float _dt);
	void render(void);

	unsigned int getShaderId(void);

private:
	std::vector<Chunk *> m_Chunks;

	Shader			m_Shader;
};

#endif //~ INCLUDED_CHUNK_MANAGER_HPP