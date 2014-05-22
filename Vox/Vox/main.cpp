#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Text.hpp"
#include "Camera.hpp"
#include "ChunkManager.hpp"

int main()
{
	sf::ContextSettings settings = sf::ContextSettings(24, 8, 16, 4, 3);

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

	window.setFramerateLimit(60);

	glewInit();
	
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	
	Camera cam = Camera(window.getSize());
	ChunkManager chunkMan = ChunkManager(&cam);

	sf::Clock clock;

	Text text = Text(&cam, "", 0, 0);

	bool running = true;

	bool F1 = false;

    while (running)
    {
		cam.update(clock.getElapsedTime().asSeconds());

		chunkMan.update(clock.getElapsedTime().asSeconds());

		text.update("FPS:" + std::to_string(static_cast<int>(1.0f / clock.getElapsedTime().asSeconds())) + "\nX:" + std::to_string(static_cast<int>(cam.getPosition().x)) + "\nY:" + std::to_string(static_cast<int>(cam.getPosition().y)) + "\nZ:" + std::to_string(static_cast<int>(cam.getPosition().z)));

		clock.restart();

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
				cam.updateWindowSize(sf::Vector2u(event.size.width, event.size.height));
            }
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)
				{
					text.toggle();
				}
			}
        }
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		chunkMan.render();
		text.render();

        window.display();
    }


    return 0;
}
