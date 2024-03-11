// Name: Jake Fitzgerald - C00288105

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "Lab 4  - Level Editor - Jake Fitzgerald" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	init();
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	
	// Grid Squares
	for (int i = 0; i < GRID_AMOUNT; i++)
	{
		//m_window.draw(gridSquares[i]);
		//m_window.draw()
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	//m_welcomeMessage.setFont(m_ArialBlackfont);
	//m_welcomeMessage.setString("SFML Game");
	//m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	//m_welcomeMessage.setPosition(40.0f, 40.0f);
	//m_welcomeMessage.setCharacterSize(80U);
	//m_welcomeMessage.setOutlineColor(sf::Color::Red);
	//m_welcomeMessage.setFillColor(sf::Color::Black);
	//m_welcomeMessage.setOutlineThickness(3.0f);

}

void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}

void Game::init()
{
	// Create instance of our struct
	gridStruct gridstruct;

	// Set the amout of squares to 100
	gridstruct.gridSquares[GRID_AMOUNT];

	//gridSquares[GRID_AMOUNT];
	squareRowPos = 0.0f;
	squareColPos = 0.0f;

	for (int i = 0; i < GRID_AMOUNT; i++)
	{
		gridstruct.gridSquares[i].setScale(squareSize, squareSize);
		gridstruct.gridSquares[i].setFillColor(sf::Color::Blue);
		// Fill first row
		gridstruct.gridSquares[i].setPosition(squareRowPos + 100.0f, squareColPos);
		if (squareRowPos >= 1000.0f)
		{
			squareColPos += 100.0f; // Move down a row
			std::cout << "Create new line" << std::endl;
		}
		
		
	}
}
