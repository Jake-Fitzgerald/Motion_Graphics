/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	// Setup Text
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

	// Ghost
	m_GhostShape.setFillColor(sf::Color::Red);
	m_GhostShape.setSize(sf::Vector2f(100.0f, 100.0f));
	m_GhostShape.setOrigin(50.0f, 50.0f);
	// Set Ghost Speed
	m_GhostSpeed = 1.0f;
	m_ghostXPos = 0.0f;

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

	m_CurrentPellotAmount = 0;

	// Reset 
	resetGhostPos();
}




/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Pacman - Jake Fitzgerald - C00288105" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 

	m_screenWidth = m_window.getSize().x;
	m_screenHeight = m_window.getSize().y;
	
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
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
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
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


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
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
	
	// Pellot Collision
	pellotCollision();
	// Ghost Movement
	ghostMovement();
	// Ghost Collision
	ghostCollision();



	// Update Personal Best Counter (move this to it's own func!)
	m_PersonalBestAmount = m_CurrentPellotAmount;

	// Update counter text
	m_TextPellotCounter.setString("Pellots: " + std::to_string(m_CurrentPellotAmount));

	// Update personal best text
	m_TextPersonalBest.setString("PB: " + std::to_string(m_CurrentPellotAmount));

	// Check if all the pellots have been eaten + large pellot
	if (m_CurrentPellotAmount >= m_TOTAL_PELLOT_AMOUNT + 1)
	{
		std::cout << "All pellots eaten ---> Reset pellots!" << std::endl;
		// Turn pellot reset to true
		b_ResetPellots = true;
	}

	// Pellot reset function
	if (b_ResetPellots == true)
	{
		// Reset pellots

		// Set resetpellots to false
		b_ResetPellots = false;
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
			// Move Pellot off-screen
			m_PellotShape[i].setPosition(1000.0f, 1000.0f);
		}
	}
	// Collision for large pellot
	if (m_PacmanShape.getGlobalBounds().intersects(m_LargePellotShape.getGlobalBounds()))
	{
		// Add to pellot counter
		m_CurrentPellotAmount += 1;
		// Move Pellot off-screen
		m_LargePellotShape.setPosition(1000.0f, 1000.0f);
		// Make Ghost vulnerable by Pacman powering up
		b_IsPacmanPoweredUp = true;
		// Turn Pacman a different colour
		m_PacmanShape.setFillColor(sf::Color::White);
	}
}

void Game::ghostMovement()
{
	// Ghost movement
	sf::Vector2f ghostMovement(0.0f, 0.0f);
	if (b_GhostSwitchDirection == false)
	{
		m_ghostXPos += m_GhostSpeed;
	}
	else
	{
		m_ghostXPos -= m_GhostSpeed;
	}
	// Move Ghost
	m_GhostShape.setPosition(m_ghostXPos, 400.0f);

	// Ghost Switch Directions
	if (m_ghostXPos >= 700.0f)
	{
		b_GhostSwitchDirection = true;
	}

	if (m_ghostXPos <= 100.0f)
	{
		b_GhostSwitchDirection = false;
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
	}

	// Check is Ghost alive
	if (b_IsGhostAlive == false)
	{
		m_GhostShape.setPosition(1000.0f, 1000.0f);
	}
}

void Game::resetGhostPos()
{
	m_GhostShape.setPosition(300.0f, 440.0f);
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
	m_window.draw(m_GhostShape);

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




