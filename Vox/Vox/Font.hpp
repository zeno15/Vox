#ifndef INCLUDED_FONT_HPP
#define INCLUDED_FONT_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

#include "Shader.hpp"

class Font
{
public:
	Font(std::string _path);
	~Font();

	void generateText(std::string _text);
private:
	sf::Texture						m_AtlasTexture;

	GLuint							m_VAO;

	Shader							m_Shader;
};

#endif //~ INCLUDED_FONT_HPP