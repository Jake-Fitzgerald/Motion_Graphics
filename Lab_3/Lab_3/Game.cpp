// Student Name: Jake Fitzgerald
// Student Number: C00288105

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "One Button Platformer - Jake Fitzgerald C00288105" },
	m_exitGame{false} //when true game will exit
{


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
	m_window.clear(sf::Color::White);

	m_window.display();
}



void Game::init()
{

	// Font Setup
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_view = m_window.getDefaultView();
	// Player Setup
	m_playerShape.setSize(sf::Vector2f(20, 20));
	m_playerShape.setPosition(160, 500);

	for (int row = 0; row < HORIZONTAL_NUM; row++)
	{
		for (int col = 0; col < VERTICAL_NUM; col++)
		{

			if (levelData[row][col] == 1)
			{

				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				m_level[row][col].setFillColor(sf::Color::Red);
			}
			if (levelData[row][col] == 0)
			{

				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);
				m_level[row][col].setFillColor(sf::Color::Black);
			}
			if (levelData[row][col] == 2)
			{
				m_level[row][col].setSize(sf::Vector2f(70, 30));
				m_level[row][col].setPosition(row * 70, col * 30);

				m_level[row][col].setFillColor(sf::Color::Blue);

			}

		}
		std::cout << std::endl;

	}
}

