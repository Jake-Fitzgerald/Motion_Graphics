// Name: Jake Fitzgerald - C00288105
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
	void setupSprite();

	void init();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game



	// Screen size is 1000 X 1000 pixels so each tile is 100 X 100
	// 10 tiles horizontally/vertically.
	const int GRID_AMOUNT = 100;
	
	// Struct containing array of grid squares and corresponding sprite amount
	struct gridStruct
	{
		sf::RectangleShape gridSquares[100];
		sf::Sprite gridSquareSprite;
	};

	float squareSize = 100.0f;
	float squareRowPos;
	float squareColPos;

};

#endif // !GAME_HPP

