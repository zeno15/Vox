#include "Game.hpp"


Game::Game()
{
}

Game::~Game()
{
	delete m_Camera;
	delete m_Player;
	delete m_ChunkManager;
}


void Game::run(void)
{
	bool mouseVisible = true;

	sf::Clock clock;

	Text text = Text("", 0, 0);

	while (m_Running)
	{

		sPlayer.update(clock.getElapsedTime().asSeconds());
		sCamera.update(clock.getElapsedTime().asSeconds());
		sChunkMan.update(clock.getElapsedTime().asSeconds());

		text.update("FPS:" + std::to_string(static_cast<int>(1.0f / clock.restart().asSeconds())) + "\nX:" + std::to_string(static_cast<int>(sCamera.getPosition().x)) +
			"\nY:" + std::to_string(static_cast<int>(sCamera.getPosition().y)) + "\nZ:" + std::to_string(static_cast<int>(sCamera.getPosition().z)) + "\nRotation\nX:" +
			std::to_string(static_cast<int>(sCamera.getRotation().x)) + "\nY:" + std::to_string(static_cast<int>(sCamera.getRotation().y)) + "\nChunks " + std::to_string(sChunkMan.getRenderedChunksVsAvailable().x)
			+ " (" + std::to_string(sChunkMan.getRenderedChunksVsAvailable().y) + ")");


		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				glViewport(0, 0, event.size.width, event.size.height);
				sCamera.resize();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F1)
				{
					text.toggle();
				}
				if (event.key.code == sf::Keyboard::Tab)
				{
					sPlayer.toggleCursorLocked();
					mouseVisible = !mouseVisible;
					m_Window.setMouseCursorVisible(mouseVisible);
				}
				if (event.key.code == sf::Keyboard::G)
				{
					sPlayer.toggleGravity();
				}
				if (event.key.code == sf::Keyboard::F3)
				{
					sPlayer.toggleThirdPerson();
				}
			}
		}
		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sChunkMan.render();
		sPlayer.render();
		text.render();

		m_Window.display();
	}
}

void Game::initialise(sf::Vector2u _screenSize, std::string _name)
{
	sf::ContextSettings settings = sf::ContextSettings(24, 8, 16, 4, 3);

	m_Window.create(sf::VideoMode(_screenSize.x, _screenSize.y), _name, sf::Style::Default, settings);

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	m_Running = true;
	
	m_Player = new Player();
	m_Camera = new Camera();
	m_ChunkManager = new ChunkManager();

	run();
}

void Game::handleEvents(void)
{
}