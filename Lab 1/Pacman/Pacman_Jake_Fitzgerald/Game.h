#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	void pellotCollision();
	void checkPellotsCollected();
	void ghostMovement();
	void ghostCollision();
	void checkPacmanPowerUp();

	void resetPellots();
	void resetScores();
	void resetGhostPos();
	void resetPacman();

	void resetGame();


	void checkBoundaries();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	bool m_exitGame; // control exiting game

	// Pellot Amount
	int m_TOTAL_PELLOT_AMOUNT = 10;
	int m_CurrentPellotAmount;
	int m_PersonalBestAmount;

	// Pacman 
	sf::CircleShape m_PacmanShape;
	// Pellot
	sf::CircleShape m_PellotShape[10];
	//sf::CircleShape m_PellotShape[];
	// Large Pellot
	sf::CircleShape m_LargePellotShape;
	// Ghost
	sf::RectangleShape m_GhostShape;

	// Environment
	// Top Blue Bar
	sf::RectangleShape m_TopBlueBar;
	// Bottom Blue Bar
	sf::RectangleShape m_BottomBlueBar;
	// Green Centre Line
	sf::RectangleShape m_GreenCentreLine;

	// Ghost Movement Values
	int m_GhostSpeed = 3;
	int m_ghostXPos;
	bool b_GhostSwitchDirection = false;

	// Movement Bools
	bool b_PacmanMoveRight = false;
	bool b_PacmanMoveLeft = false;

	// Health Bools
	bool b_IsPacmanAlive = true;
	bool b_IsGhostAlive = true;
	bool b_IsPacmanPoweredUp = false;

	// Pellot Bool
	bool b_ResetPellots = false;

	// Screen
	int m_screenWidth;
	int m_screenHeight;
	
	// Text
	sf::Text m_TextPacman;
	sf::Text m_TextPellotCounter;
	sf::Text m_TextPersonalBest;
	

};

#endif // !GAME_HPP

