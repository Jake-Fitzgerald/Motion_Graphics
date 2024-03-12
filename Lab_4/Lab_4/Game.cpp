// Name: Jake Fitzgerald - C00288105

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "Lab 4  - Level Editor - Jake Fitzgerald" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	init();

	// Squares setup
	squareRowPos = 0.0f;
	squareColPos = 0.0f;

	for (int i = 0; i < EDITOR_SIZE; i++)
	{
		m_gridStuct[i].gridSquaresShape.setFillColor(sf::Color::Red);
		m_gridStuct[i].gridSquaresShape.setSize(sf::Vector2f(100.0f, 100.0f));
		m_gridStuct[i].gridSquaresShape.setPosition(sf::Vector2f(squareRowPos, squareColPos));

		// Move next square
		squareRowPos += 100.0f;
		if (squareRowPos >= SCREEN_WIDTH * 2)
		{
			squareRowPos = 0; // Set x back to 0
			squareColPos += 100; // Move down a row
		}
	}

	// Grid Lines
	float xPos = 0.0f;
	float yPos = 0.0f;
	// Make Grid Lines
	for (int i = 0; i < MAX_LINES; i++)
	{
		if (i <= 50)
		{
			m_editorLines[i].setSize(sf::Vector2f(2, SCREEN_HEIGHT));
			m_editorLines[i].setPosition(sf::Vector2f(xPos - 1, yPos));
		}
		else
		{
			xPos = 0;
			m_editorLines[i].setSize(sf::Vector2f(SCREEN_WIDTH, 2));
			m_editorLines[i].setPosition(sf::Vector2f(xPos, yPos - 1));
		}
		if (i <= 50)
			xPos += 100;
		else
			yPos += 100;
	}
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
		m_window.draw(m_gridStuct[i].gridSquaresShape);
	}

	// Grid Lines
	for (int i = 0; i < MAX_LINES; i++)
	{
		m_window.draw(m_editorLines[i]);
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




}
