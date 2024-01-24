#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Pacman Basic" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

}

Game::~Game()
{
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Pacman
	m_pacmanShape.setFillColor(sf::Color::Yellow);
	m_pacmanShape.setSize(sf::Vector2f(50.0f, 50.0f));
	m_pacmanShape.setOrigin(25.0f, 25.0f);
	m_pacmanShape.setPosition(200.0f, 400.0f);

	// Ghost
	m_ghostShape.setFillColor(sf::Color::Red);
	m_ghostShape.setSize(sf::Vector2f(50.0f, 50.0f));
	m_ghostShape.setOrigin(25.0f, 25.0f);
	m_ghostShape.setPosition(600.0f, 400.0f);

	// Pellots
	for (int i = 0; i < TOTAL_PELLOT_AMOUNT; i++)
	{
		m_pellotShape[i].setFillColor(sf::Color::Yellow);
		m_pellotShape[i].setRadius(10.0f);
		m_pellotShape[i].setOrigin(5.0f, 5.0f);
		m_pellotShape[i].setPosition(80.0f * i, 394.0f);
	}

	// Big Pellot
	m_bigPellot.setFillColor(sf::Color::Cyan);
	m_bigPellot.setRadius(16.0f);
	m_bigPellot.setOrigin(8.0f, 8.0f);
	m_bigPellot.setPosition(400.0f, 390.0f);

	m_pellotCounter = 0;

	// Counter Text
	m_pellotCounterText.setFont(m_ArialBlackfont);
	m_pellotCounterText.setString("0");
	m_pellotCounterText.setCharacterSize(50);
	m_pellotCounterText.setFillColor(sf::Color::White);
	m_pellotCounterText.setStyle(sf::Text::Bold);
	m_pellotCounterText.setPosition(270.0f, 150.0f);
	m_pellotCounterText.setOutlineColor(sf::Color::Red);
	m_pellotCounterText.setOutlineThickness(0.8f);


	// Bools
	b_playerCanMove = false;
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

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	if (sf::Keyboard::Space == t_event.key.code)
	{
		// Check which direction Pacman is
		if (b_pacmanFaceRight == true)
		{
			b_pacmanFaceRight = false;
		}
		else
		{
			b_pacmanFaceRight = true;
		}

		b_playerCanMove = true;
		b_ghostCanMove = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// Movement Vector to move Pacman
	sf::Vector2f movement(0.f, 0.f);
	sf::Vector2f ghostMovement(0.f, 0.f);
	float xPos = m_pacmanShape.getPosition().x;
	float x_ghostPos = m_ghostShape.getPosition().x;


	if (b_playerCanMove == true)
	{
		if (b_pacmanFaceRight == true)
		{
			movement.x += m_pacmanSpeed;
		}
		else
		{
			movement.x -= m_pacmanSpeed;
		}

		// Movement by Delta time (last frame)  
		m_pacmanShape.move(movement * t_deltaTime.asSeconds());
	}

	// Check boundaries teleport
	if (xPos <= -25 || xPos >= 825)
	{
		if (xPos <= -25)
		{
			// Move Pacman back to right spawn
			m_pacmanShape.setPosition(824U, 400U);
		}
		else
		{
			// Move Pacman back to left spawn
			m_pacmanShape.setPosition(-24, 400U);
		}
	}

	// Ghost Movement
	if (b_ghostCanMove == true)
	{
		// If player is to the left of the ghost
		if (xPos < x_ghostPos)
		{
			// Move Ghost left
			ghostMovement.x -= m_ghostSpeed;
		}
		else
		{
			// Move Ghost right
			ghostMovement.x += m_ghostSpeed;
		}
	}
	// Movement by Delta time (last frame)  
	m_ghostShape.move(ghostMovement * t_deltaTime.asSeconds());

	// Ghost Collision
	if (m_pacmanShape.getGlobalBounds().intersects(m_ghostShape.getGlobalBounds()))
	{
		std::cout << "Collided with ghost" << std::endl;
	}

	// Pellot Collision
	for (int i = 0; i < TOTAL_PELLOT_AMOUNT; i++)
	{
		if (m_pacmanShape.getGlobalBounds().intersects(m_pellotShape[i].getGlobalBounds()))
		{
			// Move Pellot off-screen
			m_pellotShape[i].setPosition(1000.0f, 1000.0f);
			// Increment pellot counter
			m_pellotCounter++;
			// Pellot reset counter
			m_pellotResetCounter++;
		}
	}

	// Check if all the current pellots have been collected
	if (m_pellotResetCounter >= TOTAL_PELLOT_AMOUNT /* + 1*/)
	{
		std::cout << "reset pellots" << std::endl;
	}
	
	// Update score
	m_pellotCounterText.setString("Score: " + std::to_string( m_pellotCounter));
}


void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Pacman
	m_window.draw(m_pacmanShape); 
	// Ghost
	m_window.draw(m_ghostShape); 
	// Pellots
	for (int i = 0; i < TOTAL_PELLOT_AMOUNT; i++) 
	{
		m_window.draw(m_pellotShape[i]);
	}
	// Big Pellot
	m_window.draw(m_bigPellot); 

	// Counter Text
	m_window.draw(m_pellotCounterText);

	m_window.display();
}





