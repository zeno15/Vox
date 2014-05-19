#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ChunkManager.hpp"

int main()
{
	sf::ContextSettings settings = sf::ContextSettings(24, 8, 0, 4, 3);

	sf::Window window(sf::VideoMode(1280, 720), "Vox v0.0", sf::Style::Default, settings);

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

	sf::Texture::bind(&tex);
	
	sf::Clock clock;

	float angle1 = 0.0f;
	float angle2 = 0.0f;

	std::vector<float> lightPos(3, 10.0f);

	bool running = true;

    while (running)
    {
		sf::sleep(sf::milliseconds(10));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			angle1 -= 100.0f * clock.getElapsedTime().asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			angle1 += 100.0f * clock.getElapsedTime().asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			angle2 -= 100.0f * clock.getElapsedTime().asSeconds();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			angle2 += 100.0f * clock.getElapsedTime().asSeconds();
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

		float x = 10.0f * sinf(angle1 * 3.14159265f / 180.0f);
		float z = 10.0f * cosf(angle1 * 3.14159265f / 180.0f);

		float mid = BLOCK_SIZE * 0.5f;

		glm::mat4 proj = glm::perspective(45.0f, 16.0f / 9.0f, 1.0f, 100.0f);  //perspective projection matrix
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(mid, mid, mid), glm::vec3(0.0, 1.0, 0.0)); //view matrix
		glm::mat4 matrix = glm::mat4x4(1.0f);
			
		matrix = glm::rotate(matrix, angle1, glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, angle2, glm::vec3(1, 0, 0));
		matrix = glm::translate(matrix, glm::vec3(-mid, -mid, -mid));

		//glm::mat4x4 matrix = glm::mat4x4(1.0f);

		glm::mat4x4 mv, mvp, nor;

		mv = view * matrix;
		mvp = proj * mv;
		nor = glm::inverse(mv);

		glUniformMatrix4fv(mvID, 1, GL_FALSE, &mv[0][0]);
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(norID, 1, GL_TRUE, &nor[0][0]);

		glUniform3fv(lightID, 1, &lightPos[0]);

		chunkMan.render();

        window.display();
    }


    return 0;
}