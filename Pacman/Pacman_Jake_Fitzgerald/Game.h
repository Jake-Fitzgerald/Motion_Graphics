/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
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

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	bool m_exitGame; // control exiting game

	// Pacman 
	sf::CircleShape m_PacmanShape;
	// Pellot
	sf::CircleShape m_PellotShape;
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

	// Pellot Amount
	int m_CurrentPellotAmount;
	int m_PersonalBestAmount;

	// Movement Bools
	bool b_PacmanMoveRight = false;
	bool b_PacmanMoveLeft = false;

	// Health Bools
	bool b_IsPacmanAlive = true;

	// Pellot bools
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

