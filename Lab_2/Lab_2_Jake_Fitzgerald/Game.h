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
	sf::RectangleShape m_bulletShape[10];
	//std::vector<sf::RectangleShape> m_bulletShape;
	float m_bulletSpeed = 500.0f;
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
	// Array = 10 by 10
	int terrainArray[200]
		= { 1, 1, 1, 3, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 2, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, // 100
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 0, 3, 0, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 0, 0, 1, 1, 1,
		1, 1, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, // 200


		  };
	const int TERRAIN_AMOUNT = 200;
	float m_terrainSpeed = 0.5f;
	float m_terrainSize = 80.0f; // 1000U wide ---> 10 by 100 (use for debuggin)
	float m_initY;

	// Shape
	sf::RectangleShape m_terrainShape[200];

	// Score
	int m_score;

	// Screen Dimensions
	const int SCREEN_WIDTH = 1000U;
	const int SCREEN_HEIGHT = 600U;

	// Text
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_GameOverText;
	sf::Text m_GameWinText;
	sf::Text m_RestartText;
	sf::Text m_scoreText;

	sf::RectangleShape m_gameOverBGShape;
};

#endif // !GAME_HPP

