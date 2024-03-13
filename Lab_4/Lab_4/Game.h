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
	void placeCursor(double& t_mouseXPos, double& t_mouseYPos);
	int mousePosToGrid(double& t_mouseXPos, double& t_mouseYPos);

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

	// Tile selection
	sf::RectangleShape m_SelectTile;
	struct SelectTileButton
	{
		sf::Sprite m_selectTileSprite;
	};
	SelectTileButton m_SelectTileButton[3];

	int m_currentlySelectedTile = 1;

	bool b_isTileSelectActive = false;

	// Level
	int m_levelSpeed = -2;
	int m_moveLevelPage = 0;

};

#endif // !GAME_HPP

