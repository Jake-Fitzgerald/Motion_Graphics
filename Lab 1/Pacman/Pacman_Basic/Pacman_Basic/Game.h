
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	bool m_exitGame; // control exiting game

	// Pacman
	sf::RectangleShape m_pacmanShape;
	//sf::Vector2f(200.0f, 200.0f);
	int m_pacmanSpeed = 100.0f;
	bool b_pacmanFaceRight;

	// Ghost
	sf::RectangleShape m_ghostShape;
	int m_ghostSpeed = 50.0f;

	// Pellots
	const int TOTAL_PELLOT_AMOUNT = 10;
	sf::CircleShape m_pellotShape[10];
	sf::CircleShape m_bigPellot;
	int m_pellotCounter;
	sf::Text m_pellotCounterText;
	int m_PB;
	sf::Text m_PBText;
	int m_pellotResetCounter;

	bool b_playerCanMove;
	bool b_ghostCanMove;

};

#endif // !GAME_HPP

