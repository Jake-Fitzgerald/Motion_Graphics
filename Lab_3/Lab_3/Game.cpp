// Student Name: Jake Fitzgerald
// Student Number: C00288105

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32U }, "One Button Platformer - Jake Fitzgerald C00288105" },
	m_exitGame{false} //when true game will exit
{
	setupSprites();
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

	for (int row = 0; row < HORIZONTAL_NUM; row++)
	{
		if (b_isSpeedUp == false)
		{
			for (int col = 0; col < VERTICAL_NUM; col++)
			{

				m_levelWalls[col][row].move(NORMAL_SPEED, 0);
			}
		}
		else
		{
			for (int col = 0; col < VERTICAL_NUM; col++)
			{

				m_levelWalls[col][row].move(FAST_SPEED, 0);
			}
		}

	}

	// Input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_velocityY == 0)
	{
		m_velocityY = -11.8;
		std::cout << "Jump" << "\n";
	}

	// Player Jump movement
	m_velocityY = m_velocityY + m_gravity;
	m_playerShape.move(0, m_velocityY);

	// Bonus Points movement
	m_bonusPointsShape.move(0, m_bonusShapeVelocityY);

	m_gravity = 0.6;


	for (int row = 0; row < HORIZONTAL_NUM; row++)
	{
		for (int col = 0; col < VERTICAL_NUM; col++)
		{
			if (m_velocityY >= 0)
			{
				if (m_levelData[col][row] == 1)
				{
					if (m_playerShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
					{
						if (m_playerShape.getPosition().y < m_levelWalls[col][row].getPosition().y)
						{
							m_gravity = 0;
							m_velocityY = 0;
							m_playerShape.setPosition(m_playerShape.getPosition().x, m_levelWalls[col][row].getPosition().y);
							m_playerShape.move(0, -m_playerShape.getGlobalBounds().height);
							break;
						}
						else 
						{
							init();
						}
					}
					if (m_bonusPointsShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
					{
						if (m_bonusPointsShape.getPosition().y < m_levelWalls[col][row].getPosition().y)
						{
							m_gravity = 0;
							m_bonusShapeVelocityY = 0;
							m_bonusPointsShape.setPosition(m_bonusPointsShape.getPosition().x, m_levelWalls[col][row].getPosition().y);
							m_bonusPointsShape.move(0, -m_bonusPointsShape.getGlobalBounds().height);
							break;
						}
					}
				}
			}
			if (m_velocityY < 0)
			{
				if (m_levelData[col][row] == 1)
				{
					if (m_playerShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
					{
						// Restart
						init();
					}
				}
			}
			if (m_levelData[col][row] == 2) // Grow
			{
				if (m_playerShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
				{
					b_isScaledUp = true;
				}
				else
				{
					b_isScaledUp = false;
				}
			}
			if (m_levelData[col][row] == 3) // Speed
			{
				if (m_playerShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
				{
					b_isSpeedUp = true;
				}
				else
				{
					//b_isSpeedUp = false;
				}
			}
			if (m_levelData[col][row] == 4) // Finish
			{
				if (m_playerShape.getGlobalBounds().intersects(m_levelWalls[col][row].getGlobalBounds()))
				{
					b_isGameOver = true;
				}
				else
				{
					b_isGameOver = false;
				}
			}
		}
	}

	// - - - - - - - - - - - - - - - - - - - - Powerups  - - - - - - - - - - - - - - - - - - - -
	// Scale
	if (b_isScaledUp == true)
	{
		m_playerShape.setSize(sf::Vector2f(40, 40));
		m_playerShape.setFillColor(sf::Color::Cyan);
	}

	// Speed
	if (b_isSpeedUp == true)
	{
		m_playerShape.setFillColor(sf::Color::Magenta);
	}

	 //Reset player's pos
	if (m_playerShape.getPosition().y > 600)
	{
		init();
	}

	// Bonus Collision Check
	if (m_playerShape.getGlobalBounds().intersects(m_bonusPointsShape.getGlobalBounds()))
	{
		std::cout << "B O N U S" << std::endl;
		// Move Bonus off screen
		m_bonusPointsShape.setPosition(1000.0f, 1000.0f);
	}

	// Game Over Check
	if (b_isGameOver == true)
	{
		std::cout << "Game Over" << std::endl;
	}

}
		

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Level
	for (int row = 0; row < HORIZONTAL_NUM; row++)
	{
		for (int col = 0; col < VERTICAL_NUM; col++)
		{
			m_window.draw(m_levelWalls[col][row]);
			m_levelWalls[col][row].getTexture();
		}
	}

	// Tile textures
	//m_window.draw(m_spriteTexture);

	// Player
	m_window.draw(m_playerShape);

	// Player Sprite
	//m_window.draw(m_playerSprite);

	// Bonus points
	m_window.draw(m_bonusPointsShape);

	m_window.display();
}



void Game::setupSprites()
{
	// Setup texture
	if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\Spritesheet.png"))
	{
		std::cout << "Spritesheet not found" << std::endl;
	}
	else
	{
		// Setup rectangle
	}

	// Setup sprite
	m_levelSprite.setTexture(m_spriteTexture);
	m_playerSprite.setTexture(m_spriteTexture);
}

void Game::setUpBlocks()
{
	int dataCol = 0; // Start before first line
	int dataRow = -1;

	//for (int i = 0; i < HORIZONTAL_NUM * VERTICAL_NUM; i++)
	//{
	//	dataRow++; // Go to first line
	//	if (dataRow >= HORIZONTAL_NUM)
	//	{
	//		dataCol++;
	//		dataRow = 0;
	//	}

	//	// Turn into Switch Statement
	//	if (m_levelData[dataCol][dataRow] == 1) // Make Wall
	//	{
	//		m_levelWalls.push_back(sf::RectangleShape(sf::Vector2f(25, 25))); // Add new Wall
	//		m_levelWalls[m_levelWalls.size() - 1].setFillColor(sf::Color::Red); // Add Colour
	//		m_levelWalls[m_levelWalls.size() - 1].setPosition(0 + (25 * dataRow - 1), 0 + (25 * dataCol - 1)); // Set Position
	//	}
	//}
}



void Game::init()
{
	// SFML window
	m_view = m_window.getDefaultView();

	// Font Setup
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Bool powerups
	b_isSpeedUp = false;
	b_isSpeedUp = false;
	b_isGameOver = false;

	
	// Player Setup
	m_playerShape.setSize(sf::Vector2f(20, 20));
	m_playerShape.setPosition(75, 500);
	m_playerShape.setFillColor(sf::Color::White);

	m_playerSprite.setPosition(75, 500);

	// Bonus Points
	m_bonusPointsShape.setSize(sf::Vector2f(20, 20));
	m_bonusPointsShape.setPosition(80, 250);
	m_bonusPointsShape.setFillColor(sf::Color::Yellow);
	// Texture
	m_bonusPointsShape.setTexture(&m_spriteTexture);
	m_bonusPointsShape.setTextureRect(sf::IntRect(384, 384, 128, 128));

	// Level
	for (int row = 0; row < HORIZONTAL_NUM; row++)
	{
		for (int col = 0; col < VERTICAL_NUM; col++)
		{

			if (m_levelData[col][row] == 1) // Wall
			{
				m_levelWalls[col][row].setSize(sf::Vector2f(70, 30));
				m_levelWalls[col][row].setPosition(row * 70, col * 30);
				//m_levelWalls[col][row].setFillColor(sf::Color::Red);
				m_levelWalls[col][row].setTexture(&m_spriteTexture);
				m_levelWalls[col][row].setTextureRect(sf::IntRect(384, 384, 128, 128));
			}
			if (m_levelData[col][row] == 0) // Blank
			{

				m_levelWalls[col][row].setSize(sf::Vector2f(70, 30));
				m_levelWalls[col][row].setPosition(row * 70, col * 30);
				m_levelWalls[col][row].setFillColor(sf::Color::Black);
			}
			if (m_levelData[col][row] == 2) // Grow
			{
				m_levelWalls[col][row].setSize(sf::Vector2f(30, 30));
				m_levelWalls[col][row].setPosition(row * 70, col * 30);
				m_levelWalls[col][row].setFillColor(sf::Color::Blue);
				m_levelWalls[col][row].setTexture(&m_spriteTexture);
				m_levelWalls[col][row].setTextureRect(sf::IntRect(128, 384, 128, 128));
			}
			if (m_levelData[col][row] == 3) // Speed
			{
				m_levelWalls[col][row].setSize(sf::Vector2f(30, 30));
				m_levelWalls[col][row].setPosition(row * 70, col * 30);
				//m_levelWalls[col][row].setFillColor(sf::Color::Green);
				m_levelWalls[col][row].setTexture(&m_spriteTexture);
				m_levelWalls[col][row].setTextureRect(sf::IntRect(256, 384, 128, 128));
			}
			if (m_levelData[col][row] == 4) // Finish
			{
				m_levelWalls[col][row].setSize(sf::Vector2f(70, 30));
				m_levelWalls[col][row].setPosition(row * 70, col * 30);
				//m_levelWalls[col][row].setFillColor(sf::Color::Yellow);
				m_levelWalls[col][row].setTexture(&m_spriteTexture);
				m_levelWalls[col][row].setTextureRect(sf::IntRect(0, 384, 128, 128));
			}

		}
		std::cout << std::endl;
	}



}

