// Name: Jake Fitzgerald - C00288105
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void mouseKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	void init();

	// Cursor
	void moveCursor();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	bool m_exitGame; // control exiting game

	// Game States
	enum class gameState {SelectTile, PlaceTile, Gameplay}; // Different game states
	gameState m_currentGameState = gameState::SelectTile; // Initial State on startup

	// Screen size is 1000 X 1000 pixels so each tile is 100 X 100
	// 10 tiles horizontally/vertically.
	const int GRID_AMOUNT = 100;
	
	// Struct containing array of grid squares and corresponding sprite amount
	struct GridStruct
	{
		sf::RectangleShape gridSquaresShape;
		sf::Sprite gridSquareSprite;
		bool b_isSquareActive = false;
	};
	GridStruct m_gridStuct[EDITOR_SIZE];

	float squareSize = 100.0f;
	float squareRowPos;
	float squareColPos;

	// Editor Lines
	sf::RectangleShape m_editorLines[MAX_LINES];

	// Cursor
	sf::Texture m_tileTexture;
	sf::Sprite m_cursorSprite;
	bool b_isCursorVisible = false;

};

#endif // !GAME_HPP

