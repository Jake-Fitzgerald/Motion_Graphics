#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Terrain.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	
	// Player
	sf::RectangleShape m_playerShape;
	float playerSpeed = 1.5f;

	bool b_PlayerMoveRight;
	bool b_PlayerMoveLeft;
	bool m_exitGame; // control exiting game

	// Terrain
	// Array
	int terrainArray[15]
		= { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1
		  };
	const int terrainAmount = 15;

	// Shape
	sf::RectangleShape m_terrainShape[1000];

	// Screen Dimensions
	const int SCREEN_WIDTH = 800U;
	const int SCREEN_HEIGHT = 600U;
};

#endif // !GAME_HPP

