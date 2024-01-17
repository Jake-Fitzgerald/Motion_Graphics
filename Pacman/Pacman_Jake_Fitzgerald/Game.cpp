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
	m_TextPacman.setFont(m_ArialBlackfont);
	m_TextPacman.setString("P A C M A N");
	m_TextPacman.setCharacterSize(60);
	m_TextPacman.setFillColor(sf::Color::White);
	m_TextPacman.setStyle(sf::Text::Bold | sf::Text::Underlined);
	m_TextPacman.setOrigin(30.0f, 10.0f);
	m_TextPacman.setPosition(230.0f, 60.0f);
	m_TextPacman.setOutlineColor(sf::Color::Yellow);
	m_TextPacman.setOutlineThickness(0.8f);


	// Shapes setup
	// Pacman
	m_PacmanShape.setRadius(40.0f);
	m_PacmanShape.setPosition(100.0f, 400.0f);
	m_PacmanShape.setFillColor(sf::Color::Yellow);

	// Pellots
	m_PellotShape.setRadius(10.0f);
	m_PellotShape.setPosition(200.0f, 434.0f);
	m_PellotShape.setFillColor(sf::Color::Yellow);

	// Environment
	// Top Blue Bar
	m_TopBlueBar.setPosition(0.0f, 380.0f);
	m_TopBlueBar.setSize(sf::Vector2f(800.0f, 4.0f));
	m_TopBlueBar.setFillColor(sf::Color::Blue);
	// Bottom Blue Bar
	m_BottomBlueBar.setPosition(0.0f, 500.0f);
	m_BottomBlueBar.setSize(sf::Vector2f(800.0f, 4.0f));
	m_BottomBlueBar.setFillColor(sf::Color::Blue);
	// Green Centre Line
	m_GreenCentreLine.setPosition(0.0f, 443.0f);
	m_GreenCentreLine.setSize(sf::Vector2f(800.0f, 2.0f));
	m_GreenCentreLine.setFillColor(sf::Color::Green);

	m_CurrentPellotAmount = 0;


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


	
	if (m_PacmanShape.getGlobalBounds().intersects(m_PellotShape.getGlobalBounds()))
	{
		// Add to pellot counter
		m_CurrentPellotAmount += 1;
		// Move Pellot off-screen
		m_PellotShape.setPosition(1000.0f, 1000.0f);

	}
}
	

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Pacman
	m_window.draw(m_PacmanShape);
	// Pellots
	m_window.draw(m_PellotShape);

	// Environment
	m_window.draw(m_TopBlueBar);
	m_window.draw(m_BottomBlueBar);
	m_window.draw(m_GreenCentreLine);

	// Text 
	m_window.draw(m_TextPacman);

	m_window.display();
}




