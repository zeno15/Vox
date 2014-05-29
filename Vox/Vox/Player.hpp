#ifndef INCLUDED_PLAYER_HPP
#define INCLUDED_PLAYER_HPP

#include "Mob.hpp"

#include <SFML/Graphics.hpp>

class Player : public Mob
{
public:
	Player();
	~Player();

	virtual void update(float _delta);
	virtual void render(void);

	void toggleGravity(void);
	void toggleCursorLocked(void);
	void toggleThirdPerson(void);

	virtual glm::vec4 getFootPosition(void);

	sf::Vector3i getChunkCoords(void);

	void addVertex(std::vector<float> &_vertexes, std::vector<float> &_colours, sf::Vector3f _vertex, float _r, float _g, float _b);

private:
	Shader									m_Shader;

	GLuint									m_mvpId;

	GLuint									m_VaoId;

	bool									m_GravityApplied;
	bool									m_CursorLocked;
	bool									m_3rdPerson;
};

#endif //~ INCLUDED_PLAYER_HPP