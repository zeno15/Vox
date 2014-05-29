#include "Text.hpp"

#include <iostream>

#include "Game.hpp"

Text::Text(std::string _text, unsigned int _x, unsigned int _y) :
m_Offset(_x, _y),
m_Active(true)
{
	m_TextShader = new Shader("Resources/Shaders/textVert.glsl", "Resources/Shaders/textFrag.glsl");

	m_mvpId = glGetUniformLocation(m_TextShader->id(), "mvp");

	m_Texture.loadFromFile("Resources/Fonts/freemono.png");

	update(_text);
}

Text::~Text()
{
}


void Text::render(void)
{
	if (!m_Active) return;

	m_TextShader->bind();
	sf::Texture::bind(&m_Texture);

	glm::mat4x4 proj = sCamera.getProjectionMatrix(false);
	glm::mat4x4 view = sCamera.getOrthoMatrix();

	glm::mat4x4 mvp = proj * view;

	glUniformMatrix4fv(m_mvpId, 1, GL_FALSE, &mvp[0][0]);

	glBindVertexArray(m_VaoId);
	glDrawArrays(GL_TRIANGLES, 0, m_NumberVertices);

	sf::Texture::bind(nullptr);
	m_TextShader->unbind();
}

void Text::toggle(void)
{
	m_Active = !m_Active;
}

void Text::addChar(char _ascii, std::vector<float> &_v, std::vector<float> &_t, std::vector<float> &_c, sf::Vector3f _col, float _alpha, sf::Vector2f _charOffset)
{
	float size = 32;

	int ascii = static_cast<int>(_ascii) - 32;

	if (ascii < 0 || ascii > 93)
	{
		ascii = 0;
	}

	sf::Vector2f windowSize = sf::Vector2f(static_cast<float>(sCamera.getWindowSize().x), static_cast<float>(sCamera.getWindowSize().y));

	float windowX = windowSize.x / size;
	float windowY = windowSize.y / size;

	float x = static_cast<float>(ascii % 16) / 16.0f;
	float y = static_cast<float>(ascii / 16) / 16.0f;

	float xOff = 1.0f / 16.0f;
	float yOff = 1.0f / 16.0f;

	float xVoff = _charOffset.x;
	float yVoff = windowY - 1.0f -_charOffset.y;

	_v.push_back((xVoff + 0.0f) * size);
	_v.push_back((yVoff + 0.0f) * size);
	_t.push_back(x);
	_t.push_back(y + yOff);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);


	_v.push_back((xVoff + 1.0f) * size);
	_v.push_back((yVoff + 0.0f) * size);
	_t.push_back(x + xOff);
	_t.push_back(y + yOff);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);

	_v.push_back((xVoff + 1.0f) * size);
	_v.push_back((yVoff + 1.0f) * size);
	_t.push_back(x + xOff);
	_t.push_back(y);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);

	_v.push_back((xVoff + 0.0f) * size);
	_v.push_back((yVoff + 0.0f) * size);
	_t.push_back(x);
	_t.push_back(y + yOff);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);

	_v.push_back((xVoff + 1.0f) * size);
	_v.push_back((yVoff + 1.0f) * size);
	_t.push_back(x + xOff);
	_t.push_back(y);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);

	_v.push_back((xVoff + 0.0f) * size);
	_v.push_back((yVoff + 1.0f) * size);
	_t.push_back(x);
	_t.push_back(y);
	_c.push_back(_col.x);
	_c.push_back(_col.y);
	_c.push_back(_col.z);
	_c.push_back(_alpha);
}

void Text::update(std::string _text)
{
	if (!m_Active) return;
	if (_text.size() == 0) return;

	GLuint in_Position = glGetAttribLocation(m_TextShader->id(), "in_Position");
	GLuint in_Color =    glGetAttribLocation(m_TextShader->id(), "in_Color");
	GLuint in_TexUV =    glGetAttribLocation(m_TextShader->id(), "in_TexUV");

	std::vector<float> c, v, t;

	float yCount = 0.0f;
	float xCount = 0.0f;

	for (unsigned int i = 0; i < _text.size(); i += 1)
	{
		if (_text.at(i) == '\n')
		{
			yCount += 1.0f;
			xCount = 0.0f;
			continue;
		}
		
		addChar(_text.at(i), v, t, c, sf::Vector3f(1.0f, 1.0f, 1.0f), 1.0f, sf::Vector2f(static_cast<float>(xCount + m_Offset.x), static_cast<float>(yCount + m_Offset.y)));

		xCount += 1.0f;
	}
	

	glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

	GLuint vbo[3];
    glGenBuffers(3, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &v[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(in_Position);
    glVertexAttribPointer(in_Position, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * c.size(), &c[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(in_Color);
    glVertexAttribPointer(in_Color, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), &t[0], GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(in_TexUV);
    glVertexAttribPointer(in_TexUV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(0);

	m_NumberVertices = v.size() / 2;
}