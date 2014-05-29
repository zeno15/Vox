#include "Player.hpp"

#include <iostream>

#include "Chunk.hpp"
#include "Game.hpp"

#define MOUSE_SENSITIVITY		20.0f
#define INVERT_UP_DOWN			1
#define TO_RADIANS				3.14159f / 180.0f
#define X_SENSITIVITY			1.0f
#define Y_SENSITIVITY			1.0f

Player::Player() :
m_GravityApplied(false),
m_CursorLocked(false),
m_3rdPerson(false),
m_Shader("Resources/Shaders/player.vert", "Resources/Shaders/player.frag")
{
	GLuint in_Position = glGetAttribLocation(m_Shader.id(), "in_Position");
	GLuint in_Color =    glGetAttribLocation(m_Shader.id(), "in_Color");

	m_mvpId = glGetUniformLocation(m_Shader.id(), "mvp");

	std::vector<float> vertexes, colours;

	sf::Vector3f p1 = sf::Vector3f(-0.5f, -1.5f,  0.5f);
	sf::Vector3f p2 = sf::Vector3f(0.5f,  -1.5f,  0.5f);
	sf::Vector3f p3 = sf::Vector3f(0.5f,   0.5f,  0.5f);
	sf::Vector3f p4 = sf::Vector3f(-0.5f,  0.5f,  0.5f);
	sf::Vector3f p5 = sf::Vector3f(0.5f,  -1.5f, -0.5f);
	sf::Vector3f p6 = sf::Vector3f(-0.5f, -1.5f, -0.5f);
	sf::Vector3f p7 = sf::Vector3f(-0.5f,  0.5f, -0.5f);
	sf::Vector3f p8 = sf::Vector3f(0.5f,   0.5f, -0.5f);

	//  1,2,3, 1,3,4, 5,6,7, 5,7,8, 2,5,8, 2,8,3, 6,1,4, 6,4,7, 2,1,6, 2,6,5, 4,3,8, 4,8,7

	addVertex(vertexes, colours, p1, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p2, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p3, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p1, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p3, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p4, 1.0f, 0.0f, 0.0f);

	addVertex(vertexes, colours, p5, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p6, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p7, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p5, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p7, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p8, 1.0f, 0.0f, 0.0f);

	addVertex(vertexes, colours, p2, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p5, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p8, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p2, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p8, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p3, 1.0f, 0.0f, 0.0f);

	addVertex(vertexes, colours, p6, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p1, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p4, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p6, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p4, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p7, 1.0f, 0.0f, 0.0f);

	addVertex(vertexes, colours, p2, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p1, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p6, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p2, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p6, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p5, 1.0f, 0.0f, 0.0f);

	addVertex(vertexes, colours, p4, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p3, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p8, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p4, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p8, 1.0f, 0.0f, 0.0f);
	addVertex(vertexes, colours, p7, 1.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

	GLuint vbo[2];
    glGenBuffers(2, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexes.size(), &vertexes[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(in_Position);
    glVertexAttribPointer(in_Position, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* colours.size(), &colours[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(in_Color);
    glVertexAttribPointer(in_Color, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glBindVertexArray(0);
}

Player::~Player()
{

}


void Player::update(float _delta)
{
	static sf::Vector2i prevMousePos = sf::Vector2i();

	glm::vec4 dir = glm::vec4(sinf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), sinf(m_yAngle * TO_RADIANS), cosf(m_xAngle * TO_RADIANS) * cosf(m_yAngle * TO_RADIANS), 0.0f);

	if (m_CursorLocked)
	{
		sf::Vector2i mouseDelta = prevMousePos - sf::Mouse::getPosition(sWindow);
		
		sf::Mouse::setPosition(sf::Vector2i(sWindow.getPosition().x + sWindow.getSize().x / 2u, sWindow.getPosition().y + sWindow.getSize().y / 2u));

		if (mouseDelta.x != 0)
		{
			m_xAngle += mouseDelta.x * MOUSE_SENSITIVITY * _delta * Y_SENSITIVITY;

			if (m_xAngle < -180.0f)
			{
				m_xAngle += 360.0f;
			}
			if (m_xAngle > 180.0f)
			{
				m_xAngle -= 360.0f;
			}
		}
		if (mouseDelta.y != 0)
		{
			m_yAngle += mouseDelta.y * MOUSE_SENSITIVITY * _delta  * X_SENSITIVITY * (INVERT_UP_DOWN ? -1 : 1);

			if (m_yAngle < -90.0f)
			{
				m_yAngle = -90.0f;
			}
			if (m_yAngle > 90.0f)
			{
				m_yAngle = 90.0f;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		//~ Forward along x-z component of view direction
		m_Position += glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _delta * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//~ Left along orthogonal to x-z component of view direction
		m_Position += glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _delta * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//~ Back along x-z component of view direction
		m_Position -= glm::vec4(glm::normalize(glm::vec3(dir.x, 0.0f, dir.z)) * _delta * 10.0f, 1.0f);

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//~ Right along orthogonal to x-z component of view direction
		m_Position -= glm::vec4(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::normalize(glm::vec3(dir.x, 0.0f, dir.z))) * _delta * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//~ Up along  y axis
		m_Position += glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _delta * 10.0f, 1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//~ Down along y axis
		m_Position -= glm::vec4(glm::vec3(0.0f, 1.0f, 0.0f) * _delta * 10.0f, 1.0f);
	}

	if (m_GravityApplied)
	{
		m_Position.y -= _delta * 9.81f;
	}

	prevMousePos = sf::Mouse::getPosition(sWindow);
}
void Player::render(void)
{
	if (!m_3rdPerson) return;
	m_Shader.bind();

	glBindVertexArray(m_VaoId);

	glm::mat4x4 proj = sCamera.getPerspectiveMatrix();
	glm::mat4x4 view = sCamera.getProjectionMatrix();
	glm::mat4x4 matrix = glm::mat4x4(1.0f);

	matrix = glm::translate(matrix, glm::vec3(m_Position));
	matrix = glm::rotate(matrix, getRotation().x, glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4x4 mvp = proj * view * matrix;
	
	glUniformMatrix4fv(m_mvpId, 1, GL_FALSE, &mvp[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(0);

	m_Shader.unbind();
}

void Player::toggleGravity(void)
{
	m_GravityApplied = !m_GravityApplied;
}
void Player::toggleCursorLocked(void)
{
	m_CursorLocked = !m_CursorLocked;
}
void Player::toggleThirdPerson(void)
{
	m_3rdPerson = !m_3rdPerson;
	sCamera.toggleThirdPerson();
}

glm::vec4 Player::getFootPosition(void)
{
	return m_Position - glm::vec4(0.0f, 1.5f, 0.0f, 0.0f);
}

sf::Vector3i Player::getChunkCoords(void)
{
	sf::Vector3i negOffset((m_Position.x < 0.0f ? -1 : 0),
						   (m_Position.y < 0.0f ? -1 : 0),
						   (m_Position.z < 0.0f ? -1 : 0));

	return sf::Vector3i(static_cast<int>(m_Position.x / static_cast<float>(Chunk::CHUNK_SIZE)),
						static_cast<int>(m_Position.y / static_cast<float>(Chunk::CHUNK_SIZE)),
						static_cast<int>(m_Position.z / static_cast<float>(Chunk::CHUNK_SIZE))) + negOffset;
}

void Player::addVertex(std::vector<float> &_vertexes, std::vector<float> &_colours, sf::Vector3f _vertex, float _r, float _g, float _b)
{
	_vertexes.push_back(_vertex.x);
	_vertexes.push_back(_vertex.y);
	_vertexes.push_back(_vertex.z);

	_colours.push_back(_r);
	_colours.push_back(_g);
	_colours.push_back(_b);
}