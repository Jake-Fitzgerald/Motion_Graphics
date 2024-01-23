// Student Name : Jake Fitzgerald
// Student No. : C00288105

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Title Text
	m_TextPacman.setFont(m_ArialBlackfont);
	m_TextPacman.setString("P A C M A N");
	m_TextPacman.setCharacterSize(60);
	m_TextPacman.setFillColor(sf::Color::White);
	m_TextPacman.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_TextPacman.setOrigin(30.0f, 10.0f);
	m_TextPacman.setPosition(230.0f, 60.0f);
	m_TextPacman.setOutlineColor(sf::Color::Yellow);
	m_TextPacman.setOutlineThickness(0.8f);

	// Pellot Counter Text
	m_TextPellotCounter.setFont(m_ArialBlackfont);
	m_TextPellotCounter.setString("0");
	m_TextPellotCounter.setCharacterSize(50);
	m_TextPellotCounter.setFillColor(sf::Color::White);
	m_TextPellotCounter.setStyle(sf::Text::Bold);
	m_TextPellotCounter.setPosition(270.0f, 150.0f);
	m_TextPellotCounter.setOutlineColor(sf::Color::Red);
	m_TextPellotCounter.setOutlineThickness(0.8f);

	// Personal Best Text
	m_TextPersonalBest.setFont(m_ArialBlackfont);
	m_TextPersonalBest.setString("0");
	m_TextPersonalBest.setCharacterSize(50);
	m_TextPersonalBest.setFillColor(sf::Color::White);
	m_TextPersonalBest.setStyle(sf::Text::Bold);
	m_TextPersonalBest.setPosition(330.0f, 220.0f);
	m_TextPersonalBest.setOutlineColor(sf::Color::Green);
	m_TextPersonalBest.setOutlineThickness(0.8f);

	// Shapes setup
	// Pacman
	m_PacmanShape.setRadius(40.0f);
	m_PacmanShape.setOrigin(20.0f, 20.0f);
	m_PacmanShape.setPosition(60.0f, 424.0f);
	m_PacmanShape.setFillColor(sf::Color::Yellow);

	// Ghost
	m_GhostShape.setFillColor(sf::Color::Red);
	m_GhostShape.setSize(sf::Vector2f(100.0f, 100.0f));
	m_GhostShape.setOrigin(50.0f, 50.0f);
	// Set Ghost Speed
	m_GhostSpeed = 1.0f;
	m_ghostXPos = 400.0f;

	// Environment
	// Top Blue Bar
	m_TopBlueBar.setPosition(0.0f, 380.0f);
	m_TopBlueBar.setOrigin(800.0f, 2.0f);
	m_TopBlueBar.setSize(sf::Vector2f(1600.0f, 4.0f));
	m_TopBlueBar.setFillColor(sf::Color::Blue);
	// Bottom Blue Bar
	m_BottomBlueBar.setPosition(0.0f, 500.0f);
	m_BottomBlueBar.setOrigin(800.0f, 2.0f);
	m_BottomBlueBar.setSize(sf::Vector2f(1600.0f, 4.0f));
	m_BottomBlueBar.setFillColor(sf::Color::Blue);
	// Green Centre Line
	m_GreenCentreLine.setPosition(0.0f, 443.0f);
	m_BottomBlueBar.setOrigin(400.0f, 1.0f);
	m_GreenCentreLine.setSize(sf::Vector2f(800.0f, 2.0f));
	m_GreenCentreLine.setFillColor(sf::Color::Green);

	// Personal Best counter
	m_PersonalBestAmount = 0;

	// Reset Functions
	resetPellots();
	resetGhostPos();
	resetPacman();
	resetScores();

}


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Pacman - Jake Fitzgerald - C00288105" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

	m_screenWidth = m_window.getSize().x;
	m_screenHeight = m_window.getSize().y;
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
	if (sf::Keyboard::D == t_event.key.code)
	{
		b_PacmanMoveLeft = false; // Stops moving left
		b_PacmanMoveRight = true;
	}

	// Move Left
	if (sf::Keyboard::A == t_event.key.code)
	{
		b_PacmanMoveRight = false; // Stops moving right
		b_PacmanMoveLeft = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	//-----------------------------------------------------------------
	// Pacman Movement

	// Movement Vector to move Pacman
	sf::Vector2f movement(0.f, 0.f);

	// Check if D has been pressed
	if (b_PacmanMoveRight == true && b_PacmanMoveLeft == false)
	{
		movement.x += 100.0f;
	}

	// Check if A has been pressed
	if (b_PacmanMoveLeft == true && b_PacmanMoveRight == false)
	{
		movement.x -= 100.0f;
	}

	// Movement by Delta time (last frame)  
	m_PacmanShape.move(movement * t_deltaTime.asSeconds());
	
	// Pacaman boundary check
	checkBoundaries();
	//-----------------------------------------------------------------

	// Pellot Collision
	pellotCollision();
	// Pellot Collection
	checkPellotsCollected();
	// Ghost Movement
	ghostMovement();
	// Ghost Collision
	ghostCollision();

	// Pacman Powerup
	checkPacmanPowerUp();


	// Update Personal Best Counter (move this to it's own func!)
	//m_PersonalBestAmount = m_CurrentPellotAmount;

	// Update counter text
	m_TextPellotCounter.setString("Pellots: " + std::to_string(m_CurrentPellotAmount));

	// Update personal best text
	m_TextPersonalBest.setString("PB: " + std::to_string(m_PersonalBestAmount));

	// Pellot reset function
	if (b_ResetPellots == true)
	{
		// Reset pellots
		resetPellots();
	}
}

void Game::pellotCollision()
{
	// Collision for small pellot
	for (int i = 0; i < m_TOTAL_PELLOT_AMOUNT; i++)
	{
		if (m_PacmanShape.getGlobalBounds().intersects(m_PellotShape[i].getGlobalBounds()))
		{
			// Add to pellot counter
			m_CurrentPellotAmount += 1;
			// Add to PB
			m_PersonalBestAmount += 1;
			// Move Pellot off-screen
			m_PellotShape[i].setPosition(1000.0f, 1000.0f);
		}
	}
	// Collision for large pellot
	if (m_PacmanShape.getGlobalBounds().intersects(m_LargePellotShape.getGlobalBounds()))
	{
		// Add to pellot counter
		m_CurrentPellotAmount += 1;
		// Add to PB
		m_PersonalBestAmount += 1;
		// Move Pellot off-screen
		m_LargePellotShape.setPosition(1000.0f, 1000.0f);
		// Make Ghost vulnerable by Pacman powering up
		b_IsPacmanPoweredUp = true;
	}
}

void Game::checkPellotsCollected()
{
	// Check if all the pellots have been eaten + large pellot
	if (m_CurrentPellotAmount >= m_TOTAL_PELLOT_AMOUNT + 1)
	{
		std::cout << "All pellots eaten ---> Reset pellots!" << std::endl;
		// Turn pellot reset to true
		b_ResetPellots = true;
		// Reset Pellot Counter
		m_CurrentPellotAmount = 0;	
		// Turn off powerup (Makes it harder next round?)
		b_IsPacmanPoweredUp = false;
		// Turn Ghost back on
		b_IsGhostAlive = true;
	}
}

void Game::ghostMovement()
{
	
	// Ghost movement
	//sf::Vector2f ghostMovement(0.0f, 0.0f);
	if (b_GhostSwitchDirection == false)
	{
		m_ghostXPos += m_GhostSpeed;
	}
	else
	{
		m_ghostXPos -= m_GhostSpeed;
	}


	// Ghost Switch Directions
	if (m_ghostXPos >= 700.0f)
	{
		b_GhostSwitchDirection = true;
	}

	if (m_ghostXPos <= 100.0f)
	{
		b_GhostSwitchDirection = false;
	}
	
	if (b_IsGhostAlive == false)
	{
		srand((unsigned)time(0));
		int xRandomPos;
		xRandomPos = (rand() % 500) + 1;
		m_GhostShape.setPosition(xRandomPos, 1000.0f);
		//b_IsGhostAlive = true;
	}
	else
	{
		// Initial Ghost Pos
		m_GhostShape.setPosition(m_ghostXPos, 440.0f);
	}

}

void Game::ghostCollision()
{
	// Ghost Collision
	if (m_PacmanShape.getGlobalBounds().intersects(m_GhostShape.getGlobalBounds()))
	{
		if (b_IsPacmanPoweredUp == true)
		{
			b_IsGhostAlive = false;
			m_PacmanShape.setFillColor(sf::Color::Yellow);
			
		}
		else
		{
			// Kill the player by reseting the game
			//resetGame();
			//resetPellots();
			//resetScores();
			//m_CurrentPellotAmount = 0;
			resetPacman();
			if (m_PersonalBestAmount > 1)
			{
				m_PersonalBestAmount = m_PersonalBestAmount - 1;
				std::cout << "Take damage!" << std::endl;
			}	
		}
	}

	// Check is Ghost alive
	if (b_IsGhostAlive == false)
	{
		// Turn powerup off
		b_IsPacmanPoweredUp = false;
	}
}

void Game::checkPacmanPowerUp()
{
	if (b_IsPacmanPoweredUp == true)
	{
		// Turn Pacman a different colour
		m_PacmanShape.setFillColor(sf::Color::White);
	}
	else if (b_IsPacmanPoweredUp == false)
	{
		// Turn Pacman yellow
		m_PacmanShape.setFillColor(sf::Color::Yellow);
	}
}

void Game::resetPellots()
{
	// Pellot
	// Loop to create the place array of pellots
	for (int i = 0; i < m_TOTAL_PELLOT_AMOUNT; i++)
	{
		m_PellotShape[i].setFillColor(sf::Color::Yellow);
		m_PellotShape[i].setRadius(10.0f);
		m_PellotShape[i].setOrigin(5.0f, 5.0f);
		m_PellotShape[i].setPosition(80.0f * i, 440.0f);
	}

	// Large Pellot
	m_LargePellotShape.setRadius(20.0f);
	m_LargePellotShape.setOrigin(10.0f, 10.0f);
	m_LargePellotShape.setPosition(400.0f, 435.0f);
	m_LargePellotShape.setFillColor(sf::Color::Yellow);
	m_LargePellotShape.setOutlineColor(sf::Color::Red);
	m_LargePellotShape.setOutlineThickness(2.0f);
	
	// Set resetpellots to false
	b_ResetPellots = false;

}

void Game::resetScores()
{
	// Turn score counter to 0
	m_CurrentPellotAmount = 0;
}

void Game::resetGhostPos()
{
	if (b_IsGhostAlive == false)
	{
		m_GhostShape.setPosition((m_ghostXPos + 10000.0f), 440.0f);
		b_IsGhostAlive = true;
		b_IsGhostAlive = true;
	}
	else
	{
		m_GhostShape.setPosition(m_ghostXPos, 440.0f);
	}
}

void Game::resetPacman()
{
	// Turn Pacman back to yellow with bool
	b_IsPacmanPoweredUp = false;
	checkPacmanPowerUp();
	m_PacmanShape.setPosition(60.0f, 424.0f);
}

void Game::resetGame()
{
	resetPacman(); // Powerup turn off
	//resetScores(); // Reset score to 0
	resetPellots();
	resetGhostPos();
	b_IsGhostAlive = true;

}

void Game::checkBoundaries()
{
	// Check boundaries
	float xPos = m_PacmanShape.getPosition().x;
	if (xPos <= -25 || xPos >= 825)
	{
		if (xPos <= -25)
		{
			// Move Pacman back to right spawn
			m_PacmanShape.setPosition(824U, 424U);
		}
		else
		{
			// Move Pacman back to left spawn
			m_PacmanShape.setPosition(-24, 424U);
		}
	}
}
	

void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Pacman
	m_window.draw(m_PacmanShape);
	// Pellots
	for (int i = 0; i < m_TOTAL_PELLOT_AMOUNT; i++)
	{
		m_window.draw(m_PellotShape[i]);
	}
	
	// Large Pellot
	m_window.draw(m_LargePellotShape);

	// Ghost
	if (b_IsGhostAlive == true)
	{
		m_window.draw(m_GhostShape);
	}
	
	// Environment
	m_window.draw(m_TopBlueBar);
	m_window.draw(m_BottomBlueBar);
	m_window.draw(m_GreenCentreLine);

	// Text 
	m_window.draw(m_TextPacman);
	m_window.draw(m_TextPellotCounter);
	m_window.draw(m_TextPersonalBest);

	m_window.display();
}




