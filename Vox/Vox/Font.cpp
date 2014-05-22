#include "Font.hpp"


Font::Font(std::string _path)
{
	m_AtlasTexture.loadFromFile(_path);


}


Font::~Font()
{
}


void Font::generateText(std::string _text)
{
	glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

	std::vector<float> v;
	std::vector<float> c;
	std::vector<float> t;





	GLuint in_Position = glGetAttribLocation(m_Shader.id(), "in_Position");
	GLuint in_Color =    glGetAttribLocation(m_Shader.id(), "in_Color");
	GLuint in_TexUV =    glGetAttribLocation(m_Shader.id(), "in_TexUV");

	GLuint vbo[3];
    glGenBuffers(3, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &v[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_Position);
    glVertexAttribPointer(in_Position, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * c.size(), &c[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_Color);
    glVertexAttribPointer(in_Color, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), &t[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_TexUV);
    glVertexAttribPointer(in_TexUV, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(0);
}