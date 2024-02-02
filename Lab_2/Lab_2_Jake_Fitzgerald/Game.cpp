// Student Name : Jake Fitzgerald
// Student No. : C00288105
#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 800U, 32U }, "Jake Fitzgerald" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

	// Setup player
	m_playerShape.setFillColor(sf::Color::Blue);
	m_playerShape.setSize(sf::Vector2f(100.0f, 100.0f));
	m_playerShape.setOrigin(50.0f, 50.0f);
	m_playerShape.setPosition(SCREEN_WIDTH / 2, 500.0F);

	// Setup Terrain
	// for loop
	for (int i = 0; i < terrainAmount; i++)
	{
		m_terrainShape[i].setFillColor(sf::Color::Magenta);
		m_terrainShape[i].setSize(sf::Vector2f(50.0f, 50.0f));
		m_terrainShape[i].setOrigin(25.0f, 25.0f);

		//int current_xPos = terrainArray[i];

		// Set positions ---> go to next index position
		m_terrainShape[i].setPosition(10.0f * i * 4, 0.0f);
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

	// Movement
	// Move Right
	if (sf::Keyboard::A == t_event.key.code)
	{
		b_PlayerMoveRight = false; // Stops moving right
		b_PlayerMoveLeft = true;
	}
	// Move Left
	if (sf::Keyboard::D == t_event.key.code)
	{
		b_PlayerMoveLeft = false; // Stops moving left
		b_PlayerMoveRight = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// Movement Vector to move Player
	sf::Vector2f movement(0.f, 0.f);

	// Check if A has been pressed
	if (b_PlayerMoveRight == true && b_PlayerMoveLeft == false)
	{
		movement.x += 100.0f;
	}
	// Check if D has been pressed
	if (b_PlayerMoveLeft == true && b_PlayerMoveRight == false)
	{
		movement.x -= 100.0f;
	}

	// Movement by Delta time (last frame)  
	m_playerShape.move(movement * playerSpeed * t_deltaTime.asSeconds());
	//m_playerShape.setPosition(movement.x, movement.y);

	// Player and Terrain collision
	for (int i = 0; i < terrainAmount; i++)
	{
		if (m_playerShape.getGlobalBounds().intersects(m_terrainShape[i].getGlobalBounds()))
		{
			std::cout << "Player collided with terrain!" << std::endl;
		}
	}


}


void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Player
	m_window.draw(m_playerShape);

	// Terain
	for (int i = 0; i < terrainAmount; i++)
	{
		m_window.draw(m_terrainShape[i]);
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	//if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	//{
	//	std::cout << "problem loading arial black font" << std::endl;
	//}



}

