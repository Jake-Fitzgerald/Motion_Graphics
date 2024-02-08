// Student Name : Jake Fitzgerald
// Student No. : C00288105
#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 800U, 32U }, "Jake Fitzgerald" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

	// Bools setup
	b_isGameOver = false;
	b_isGameWin = false;
	b_isGamePlaying = true;
	b_terrainCanMove = true;
	b_canPlayerShoot = true;

	// Setup player
	m_playerShape.setFillColor(sf::Color::Blue);
	m_playerShape.setSize(sf::Vector2f(50.0f, 50.0f));
	m_playerShape.setOrigin(25.0f, 25.0f);
	m_playerShape.setPosition(500.0f, 600.0f);

	// Setup Bullet
	m_waitToFireInterval = 10;
	m_waitToFireCounter = m_waitToFireInterval;

	m_offScreenPos = { -2000, -2000 };
	m_bulletSize = {20.0f, 20.0f};

	m_bulletShape[NUM_BULLETS];

	for (int i = 0; i < NUM_BULLETS; i++)
	{
		m_bulletShape[i].setFillColor(sf::Color::Yellow);
		m_bulletShape[i].setSize(m_bulletSize);
		m_bulletShape[i].setOrigin(10.0f, 20.0f);
		m_bulletShape[i].setPosition(m_offScreenPos);
	}


	// Setup Terrain
	// for loop
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		// Check if it's a 1
		if (terrainArray[i] == 1)
		{
			// i % 10 since there are 10 vertical rows, i / 10 because of sets of 10 ---> 10 by 200 array
			m_terrainShape[i].setPosition(m_terrainSize * (i % 10), i/10 * m_terrainSize);
			m_terrainShape[i].setSize(sf::Vector2f(m_terrainSize, m_terrainSize));
			m_terrainShape[i].setFillColor((sf::Color::Red));
			m_terrainShape[i].setOrigin(40.0f, 40.0f);
			std::cout << i / 10 << std::endl;
		}

		// Enemy
		if (terrainArray[i] == 2)
		{
			m_terrainShape[i].setFillColor((sf::Color::Magenta));
			m_terrainShape[i].setPosition(m_terrainSize * (i % 10), i / 10 * m_terrainSize);
			m_terrainShape[i].setSize(sf::Vector2f(m_terrainSize, m_terrainSize));
			m_terrainShape[i].setOrigin(40.0f, 40.0f);
			std::cout << i / 10 << std::endl;
		}
		// Collectible
		if (terrainArray[i] == 3)
		{
			m_terrainShape[i].setFillColor((sf::Color::Yellow));
			m_terrainShape[i].setPosition(m_terrainSize * (i % 10), i / 10 * m_terrainSize);
			m_terrainShape[i].setSize(sf::Vector2f(m_terrainSize, m_terrainSize));
			m_terrainShape[i].setOrigin(40.0f, 40.0f);
			std::cout << i / 10 << std::endl;
		}
		if (i == 199)
		{
			m_initY = -1 * m_terrainSize - m_terrainSize;
		}
	}

	// Initial pos
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		//m_terrainShape[i].setPosition(0.0f, -10.0f);
	}


	// Setup centre line
	m_centreLineShape.setFillColor(sf::Color::Red);
	m_centreLineShape.setSize(sf::Vector2f(1.0f, 1200.0f));
	m_centreLineShape.setOrigin(0.5f, 400.0f);
	m_centreLineShape.setPosition(500.0f, 0.0F);

	// Score setup
	m_score = 0;
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
	if (sf::Keyboard::Left == t_event.key.code)
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
	if (sf::Keyboard::Right == t_event.key.code)
	{
		b_PlayerMoveLeft = false; // Stops moving left
		b_PlayerMoveRight = true;
	}

	// If the game is over
	if (b_isGamePlaying == false)
	{
		if (sf::Keyboard::R == t_event.key.code)
		{
			// Restart the game
			resetGame();
		}
	}

	// DEBUG
	if (sf::Keyboard::Q == t_event.key.code)
	{
		b_isGameWin = true;
		b_isGamePlaying = false;
	}
	if (sf::Keyboard::T == t_event.key.code)
	{
		m_score += 100;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	// Player Movement
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
	m_playerShape.move(movement * m_playerSpeed * t_deltaTime.asSeconds());

	// Shoot
	if (m_waitToFireCounter == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			for (int i = 0; i < NUM_BULLETS; i++)
			{
				if (m_bulletShape[i].getPosition().x == m_offScreenPos.x)
				{
					// Put bullet back to player's pos
					m_bulletShape[i].setPosition(m_playerShape.getPosition());
				}

				m_waitToFireCounter = m_waitToFireInterval;
				break;
			}
		}
	}
	else
	{
		m_waitToFireCounter--;
	}
	
	// Player Shooting
	for (int i = 0; i < NUM_BULLETS; i++)
	{
		// If that bullet is not already offscreen
		if (m_bulletShape[i].getPosition().x != m_offScreenPos.x)
		{
			m_bulletShape[i].move(0, -m_bulletSpeed * t_deltaTime.asSeconds());
			if (m_bulletShape[i].getPosition().y < 0)
			{
				m_bulletShape[i].setPosition(m_offScreenPos);
			}
		}
	}

	// Enemy and bullet collision
	for (int bulletIndex = 0; bulletIndex < NUM_BULLETS; bulletIndex++)
	{
		for (int i = 0; i < TERRAIN_AMOUNT; i++)
		{
			if (terrainArray[i] == 2)
			{
				if (m_terrainShape[i].getGlobalBounds().intersects(m_bulletShape[bulletIndex].getGlobalBounds()))
				{
					// Put bullet offscreen
					m_bulletShape[bulletIndex].setPosition(m_offScreenPos);
					// Move enemy offscreen
					m_terrainShape[i].setPosition(1000.0f, 1000.0f);
					// Add to score
					m_score += 500;
				}
			}
		}
	}

	// Terrain
	sf::Vector2f terrainMovement(0.f, -m_initY);


	// Move terrain 
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		m_terrainShape[i].move(terrainMovement * m_terrainSpeed * t_deltaTime.asSeconds());
		//m_terrainShape[i].setPosition(0.0f, 0.0f);
	}
	//m_initY--;

	// Player and Terrain collision
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		// Check if it's a 1
		if (terrainArray[i] == 1)
		{
			if (m_playerShape.getGlobalBounds().intersects(m_terrainShape[i].getGlobalBounds()))
			{
				std::cout << "Player collided with terrain!" << std::endl;
				//b_isGameOver = true;
				//b_isGamePlaying = false;
			}
		}
		// Check if it's a 2 for enemy
		if (terrainArray[i] == 2)
		{
			if (m_playerShape.getGlobalBounds().intersects(m_terrainShape[i].getGlobalBounds()))
			{
				std::cout << "Player collided with enemy!" << std::endl;
				//b_isGameOver = true;
				//b_isGamePlaying = false;
			}
		}
		// Check if it's a 3 for collectible
		if (terrainArray[i] == 3)
		{
			if (m_playerShape.getGlobalBounds().intersects(m_terrainShape[i].getGlobalBounds()))
			{
				std::cout << "Player collided with collectible!" << std::endl;
				// Move shape offscreen
				m_terrainShape[i].setPosition(1000.0f, 1000.0f);
				// Add to score
				m_score += 100;
			}
		}
	}

	// Bullet and Terrain collision
	// If 1 (destroy bullet, 0, do nothing, 2 (destroy enemy + add to score), 3 (destroy collectible + add to score)


	// Check if all terrain has left the screen
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		if (m_terrainShape[TERRAIN_AMOUNT].getPosition().y <= SCREEN_HEIGHT)
		{
			//std::cout << "Game Win!" << std::endl;
			//b_isGameWin = true;
			//b_isGamePlaying = false;
		}
	}

	// Score to Score Text
	m_scoreText.setString("Score: " + std::to_string(m_score));
}


void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Player
	m_window.draw(m_playerShape);

	// Bullet
	for (size_t i = 0; i < NUM_BULLETS; i++)
	{
		m_window.draw(m_bulletShape[i]);
	}
	

	// Terain
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		if (terrainArray[i] == 1 || terrainArray[i] == 2 || terrainArray[i] == 3)
		{
			// Don't draw the terrain marked as 0
			m_window.draw(m_terrainShape[i]);
		}

	}

	// Centre line
	m_window.draw(m_centreLineShape);

	// Game Over Screen
	if (b_isGameOver == true)
	{
		m_window.draw(m_gameOverBGShape);
		m_window.draw(m_GameOverText);
		m_window.draw(m_RestartText);
	}

	// Game Win Screen
	if (b_isGameWin == true)
	{
		m_window.draw(m_gameOverBGShape);
		m_window.draw(m_GameWinText);
		m_window.draw(m_RestartText);
	}

	// Score
	m_window.draw(m_scoreText);

	m_window.display();
}

void Game::playerShoot()
{
	// Turn bool off
	b_canPlayerShoot = false;



	// Move bullet
	b_shootBullet = true;

	// Turn bool on
	b_canPlayerShoot = true;
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Game Over Text
	m_GameOverText.setFont(m_ArialBlackfont);
	m_GameOverText.setString("GAME OVER");
	m_GameOverText.setCharacterSize(60);
	m_GameOverText.setFillColor(sf::Color::White);
	m_GameOverText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_GameOverText.setOrigin(30.0f, 10.0f);
	m_GameOverText.setPosition(340.0f, 300.0f);
	m_GameOverText.setOutlineColor(sf::Color::Red);
	m_GameOverText.setOutlineThickness(0.8f);

	// Game Win Text
	m_GameWinText.setFont(m_ArialBlackfont);
	m_GameWinText.setString("YOU WIN!");
	m_GameWinText.setCharacterSize(60);
	m_GameWinText.setFillColor(sf::Color::White);
	m_GameWinText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_GameWinText.setOrigin(30.0f, 10.0f);
	m_GameWinText.setPosition(340.0f, 300.0f);
	m_GameWinText.setOutlineColor(sf::Color::Blue);
	m_GameWinText.setOutlineThickness(0.8f);

	// Restart Game Text
	m_RestartText.setFont(m_ArialBlackfont);
	m_RestartText.setString("Press R to restart game");
	m_RestartText.setCharacterSize(30);
	m_RestartText.setFillColor(sf::Color::White);
	m_RestartText.setOrigin(30.0f, 10.0f);
	m_RestartText.setPosition(320.0f, 400.0f);

	// Game Over Shape
	m_gameOverBGShape.setFillColor(sf::Color::Black);
	m_gameOverBGShape.setSize(sf::Vector2f(1000.0f, 800.0f));
	m_gameOverBGShape.setOrigin(0.0f, 0.0f);
	m_gameOverBGShape.setPosition(0.0f, 0.0F);

	// Score Text
	m_scoreText.setFont(m_ArialBlackfont);
	m_scoreText.setString("0");
	m_scoreText.setCharacterSize(50);
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setStyle(sf::Text::Bold);
	m_scoreText.setPosition(270.0f, 150.0f);
	m_scoreText.setOutlineColor(sf::Color::Red);
	m_scoreText.setOutlineThickness(0.8f);
}

void Game::resetGame()
{
	// Bools setup
	b_isGameOver = false;
	b_isGameWin = false;
	b_isGamePlaying = true;
	b_terrainCanMove = true;
	b_canPlayerShoot = true;

	// Reset player's pos
	m_playerShape.setPosition(500.0f, 600.0f);

	// Reset array
		// Setup Terrain
	// for loop
	for (int i = 0; i < TERRAIN_AMOUNT; i++)
	{
		// Check if it's a 1
		if (terrainArray[i] == 1)
		{
			// i % 10 since there are 10 vertical rows, i / 10 because of sets of 10 ---> 10 by 200 array
			m_terrainShape[i].setPosition(m_terrainSize * (i % 10), i / 10 * m_terrainSize);
			m_terrainShape[i].setSize(sf::Vector2f(m_terrainSize, m_terrainSize));
			m_terrainShape[i].setFillColor((sf::Color::Red));
			m_terrainShape[i].setOrigin(40.0f, 40.0f);
			std::cout << i / 10 << std::endl;
		}
		if (i == 199)
		{
			m_initY = -1 * m_terrainSize - m_terrainSize;
		}
		// Enemy
		if (terrainArray[i] == 2)
		{
			m_terrainShape[i].setFillColor((sf::Color::Magenta));
		}
		// Collectible
		if (terrainArray[i] == 3)
		{
			m_terrainShape[i].setFillColor((sf::Color::Yellow));
		}
	}

}

