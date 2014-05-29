#ifndef INCLUDED_GAME_HPP
#define INCLUDED_GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Text.hpp"
#include "Camera.hpp"
#include "ChunkManager.hpp"
#include "Player.hpp"

class Game
{
public:
	static Game& instance()
	{
		static Game game;
		return game;
	}

	void run(void);

	void initialise(sf::Vector2u _screenSize, std::string _name);

	void handleEvents(void);
	
public:
	sf::Vector2u											m_ScreenSize;

	sf::Window												m_Window;

	bool													m_Running;

	Camera *												m_Camera;
	Player *												m_Player;
	ChunkManager *											m_ChunkManager;

private:
	Game();
	~Game();
};

#define sGame		Game::instance()
#define sWindow		sGame.m_Window
#define sCamera		(*sGame.m_Camera)
#define sPlayer		(*sGame.m_Player)
#define sChunkMan	(*sGame.m_ChunkManager)

#endif //~ INCLUDED_GAME_HPP