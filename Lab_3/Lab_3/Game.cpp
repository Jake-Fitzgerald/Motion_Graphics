// Student Name: Jake Fitzgerald
// Student Number: C00288105

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1000, 500, 32U }, "One Button Platformer - Jake Fitzgerald C00288105" },
	m_exitGame{false} //when true game will exit
{
	setUpBlocks();
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

	//for (int row = 0; row < HORIZONTAL_NUM; row++)
	//{
	//	for (int col = 0; col < VERTICAL_NUM; col++)
	//	{

	//		m_level[col][row].move(-3.7, 0);
	//	}
	//}

	// Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_velocityY == 0)
	{
		m_velocityY = -11.8;
	}

	m_velocityY = m_velocityY + m_gravity;
	m_playerShape.move(0, m_velocityY);

	m_gravity = 0.6;


	//for (int row = 0; row < HORIZONTAL_NUM; row++)
	//{
	//	for (int col = 0; col < VERTICAL_NUM; col++)
	//	{
	//		if (m_velocityY >= 0)
	//		{
	//			if (levelData[col][row] == 1)
	//			{
	//				if (m_playerShape.getGlobalBounds().intersects(m_level[col][row].getGlobalBounds()))
	//				{
	//					if (m_playerShape.getPosition().y < m_level[col][row].getPosition().y)
	//					{
	//						m_gravity = 0;
	//						m_velocityY = 0;
	//						m_playerShape.setPosition(m_playerShape.getPosition().x, m_level[col][row].getPosition().y);
	//						m_playerShape.move(0, -m_playerShape.getGlobalBounds().height);
	//						break;
	//					}
	//					else 
	//					{
	//						init();
	//					}
	//				}
	//			}
	//		}
	//		if (m_velocityY < 0)
	//		{
	//			if (levelData[col][row] == 1)
	//			{
	//				if (m_playerShape.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
	//				{
	//					init();
	//				}
	//			}
	//		}
	//		if (levelData[col][row] == 2)
	//		{
	//			if (m_playerShape.getGlobalBounds().intersects(m_level[row][col].getGlobalBounds()))
	//			{
	//				init();
	//			}
	//		}
	//	}
	//}

	// Reset player's pos
	//if (m_playerShape.getPosition().y > 600)
	//{
	//	init();
	//}


	// Move level
//moveLevel(largestArray); // Move Level Left

}
		


void Game::render()
{
	m_window.clear(sf::Color::White);

	// Level
	//for (int row = 0; row < HORIZONTAL_NUM; row++)
	//{
	//	for (int col = 0; col < VERTICAL_NUM; col++)
	//	{
	//		m_window.draw(m_level[col][row]);
	//	}
	//}

	// Player
	m_window.draw(m_playerShape);


	int wallIndex = 0;

	// Level Rendering
	int dataRow = -1;
	int dataCol = 0;
	for (int i = 0; i < HORIZONTAL_NUM * VERTICAL_NUM; i++)
	{
		dataRow++;
		if (dataRow >= HORIZONTAL_NUM)
		{
			dataCol++;
			dataRow = 0;
		}

		switch (m_levelData[dataCol][dataRow])
		{
		case 1:
			m_window.draw(m_levelWalls[wallIndex]);
			wallIndex++;
			break;
		default:
			break;
		}
	}

	m_window.display();
}

void Game::setUpBlocks()
{
	int dataCol = 0; // Start before first line
	int dataRow = -1;

	for (int i = 0; i < HORIZONTAL_NUM * VERTICAL_NUM; i++)
	{
		dataRow++; // Go to first line
		if (dataRow >= HORIZONTAL_NUM)
		{
			dataCol++;
			dataRow = 0;
		}

		// Turn into Switch Statement
		if (m_levelData[dataCol][dataRow] == 1) // Make Wall
		{
			m_levelWalls.push_back(sf::RectangleShape(sf::Vector2f(25, 25))); // Add new Wall
			m_levelWalls[m_levelWalls.size() - 1].setFillColor(sf::Color::Red); // Add Colour
			m_levelWalls[m_levelWalls.size() - 1].setPosition(0 + (25 * dataRow - 1), 0 + (25 * dataCol - 1)); // Set Position
		}
	}
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

	//for (int row = 0; row < HORIZONTAL_NUM; row++)
	//{
	//	for (int col = 0; col < VERTICAL_NUM; col++)
	//	{

	//		if (levelData[col][row] == 1)
	//		{
	//			m_level[col][row].setSize(sf::Vector2f(70, 30));
	//			m_level[col][row].setPosition(row * 70, col * 30);
	//			m_level[col][row].setFillColor(sf::Color::Red);
	//		}
	//		if (levelData[col][row] == 0)
	//		{

	//			m_level[col][row].setSize(sf::Vector2f(70, 30));
	//			m_level[col][row].setPosition(row * 70, col * 30);
	//			m_level[col][row].setFillColor(sf::Color::Black);
	//		}
	//		if (levelData[col][row] == 2)
	//		{
	//			m_level[col][row].setSize(sf::Vector2f(70, 30));
	//			m_level[col][row].setPosition(row * 70, col * 30);

	//			m_level[col][row].setFillColor(sf::Color::Blue);
	//		}

	//	}
	//	std::cout << std::endl;
	//}

	// We need a dataCol and dataRow
	// When we get to the end of a row, we increment the dataCol and go to the next row.
	// 
	// 


	// Array size
	largestArray = m_levelWalls.size();
	//if (largestArray < m_levelMovingWall.size())
	//{
	//	..largestArray = m_levelMovingWall.size();
	//}
		
	


	
}

