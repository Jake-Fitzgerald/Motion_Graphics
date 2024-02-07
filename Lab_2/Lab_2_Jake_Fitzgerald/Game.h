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
	void playerShoot();
	
	void setupFontAndText();

	void resetGame();

	sf::RenderWindow m_window; // main SFML window
	// Display centre line
	sf::RectangleShape m_centreLineShape;
	
	// Player
	sf::RectangleShape m_playerShape;
	float m_playerSpeed = 1.5f;

	// Bullet
	sf::RectangleShape m_bulletShape[1];
	//std::vector<sf::RectangleShape> m_bulletShape;
	float m_bulletSpeed = 2.0f;
	int m_waitToFireInterval;
	int m_waitToFireCounter;
	sf::Vector2f m_offScreenPos;
	sf::Vector2f m_bulletSize;
	const int NUM_BULLETS = 10;


	// Movement
	bool b_PlayerMoveRight;
	bool b_PlayerMoveLeft;
	// Shooting
	bool b_canPlayerShoot;
	bool b_shootBullet;
	// Game States
	bool b_isGameOver;
	bool b_isGameWin;
	bool b_isGamePlaying;
	// Terrain
	bool b_terrainCanMove;

	bool m_exitGame; // control exiting game

	// Terrain
	// Draw entire array from bottom up then it moves downwards
	// Array - column = 5
	int terrainArray[5]
		= { 1, 0, 0, 0, 1
		  };
	const int TERRAIN_AMOUNT = 5;
	float m_terrainSpeed = 2.0f;

	// Shape
	sf::RectangleShape m_terrainShape[15];

	// Score
	int m_score;

	// Screen Dimensions
	const int SCREEN_WIDTH = 800U;
	const int SCREEN_HEIGHT = 600U;

	// Text
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_GameOverText;
	sf::Text m_GameWinText;
	sf::Text m_RestartText;

	sf::RectangleShape m_gameOverBGShape;
};

#endif // !GAME_HPP

