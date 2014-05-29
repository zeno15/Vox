#ifndef INCLUDED_TEXT_HPP
#define INCLUDED_TEXT_HPP

#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Block.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class Text
{
public:
	Text(std::string _text, unsigned int _x, unsigned int _y);
	~Text();

	void render(void);

	void toggle(void);

	void update(std::string _text);
	void addChar(char _ascii, std::vector<float> &_v, std::vector<float> &_t, std::vector<float> &_c, sf::Vector3f _col, float _alpha, sf::Vector2f _charOffset);

private:

	GLuint				m_VaoId;
	GLuint				m_mvpId;

	unsigned int		m_NumberVertices;

	Shader *			m_TextShader;

	sf::Texture			m_Texture;

	sf::Vector2u		m_Offset;

	bool				m_Active;
};

#endif //~ INCLUDED_TEXT_HPP