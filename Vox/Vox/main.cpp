#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>

#include "ChunkManager.hpp"

int main()
{
	sf::ContextSettings settings = sf::ContextSettings(24, 8, 0, 4, 3);

	sf::Window window(sf::VideoMode(1440, 900), "Vox v0.0", sf::Style::Default, settings);

	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);

	GLint major, minor;

	glGetIntegerv(GL_MINOR_VERSION, &minor);
	glGetIntegerv(GL_MAJOR_VERSION, &major);

	std::cout << "OpenGL version: " << version << " (" << major << "." << minor << ")" << std::endl;
	std::cout << "OpenGL vendor: " << vendor << std::endl;
	std::cout << "OpenGL renderer: " << renderer << std::endl;

	glewInit();
	
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	ChunkManager chunkMan = ChunkManager();

	GLuint mvID = glGetUniformLocation(chunkMan.getShaderId(), "mv");
	GLuint mvpID = glGetUniformLocation(chunkMan.getShaderId(), "mvp");
	GLuint norID = glGetUniformLocation(chunkMan.getShaderId(), "nor");
	GLuint lightID = glGetUniformLocation(chunkMan.getShaderId(), "light");

	sf::Texture tex;
	tex.loadFromFile("Resources/Textures/testcube.png");
	
	sf::Clock clock;

	glm::vec4 pos = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 dir = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);

	std::vector<float> lightPos(3, 10.0f);

	bool running = true;

    while (running)
    {
		sf::sleep(sf::milliseconds(10));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//~ Forward along x-z component of view direction
			glm::vec3 tempPos = glm::vec3(dir.x, 0.0f, dir.z) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//~ Left along orthogonal to x-z component of view direction
			glm::vec3 tempPos = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(dir.x, 0.0f, dir.z)) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//~ Back along x-z component of view direction
			glm::vec3 tempPos = glm::vec3(dir.x, 0.0f, dir.z) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//~ Right along orthogonal to x-z component of view direction
			glm::vec3 tempPos = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(dir.x, 0.0f, dir.z)) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//~ Up along  y axis
			glm::vec3 tempPos = glm::vec3(0.0f, dir.y, 0.0f) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos += glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//~ Down along y axis
			glm::vec3 tempPos = glm::vec3(0.0f, dir.y, 0.0f) * clock.getElapsedTime().asSeconds() * 10.0f;

			pos -= glm::vec4(tempPos.x, tempPos.y, tempPos.z, 1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			dir = glm::rotate(glm::mat4x4(1.0f), 1.0f, glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(dir.x, 0.0f, dir.z))) * dir;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dir = glm::rotate(glm::mat4x4(1.0f), -1.0f, glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(dir.x, 0.0f, dir.z))) * dir;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			dir = glm::rotate(glm::mat4x4(1.0f), 1.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * dir;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			dir = glm::rotate(glm::mat4x4(1.0f), -1.0f, glm::vec3(0.0f, 1.0f, 0.0f)) * dir;
		}

		chunkMan.update(clock.getElapsedTime().asSeconds());

		clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glm::mat4 proj = glm::perspective(60.0f, (float)window.getSize().x / (float)window.getSize().y, 1.0f, 100.0f);  //perspective projection matrix
		glm::mat4 view = glm::lookAt(glm::vec3(pos),  glm::vec3(pos) + glm::vec3(dir), glm::vec3(0.0, 1.0, 0.0)); //view matrix
		glm::mat4 matrix = glm::mat4x4(1.0f);
			



		glm::mat4x4 mv, mvp, nor;

		mv = view * glm::mat4x4(1.0f);
		mvp = proj * mv;
		nor = glm::inverse(mv);

		glUniformMatrix4fv(mvID, 1, GL_FALSE, &mv[0][0]);
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(norID, 1, GL_TRUE, &nor[0][0]);

		glUniform3fv(lightID, 1, &lightPos[0]);
		sf::Texture::bind(&tex);
		chunkMan.render();

        window.display();
    }


    return 0;
}
