#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <array>

const auto  MAX_NUMBER_OF_ITEMS = 3;
const auto NUM_OF_characters = 5;
using string = std::string;

enum class Menu_t :size_t { MENU, PLAY, REPLAY, INTRO, EXIT };

class Menu
{
public:
	Menu(const sf::Vector2u& windowSize, const sf::Font& font);
	void run(sf::RenderWindow& window);
	const Menu_t& menuStatus()const { return m_menuStatus; };
	void gameOver(sf::RenderWindow& window);
private:
	Menu_t m_menuStatus = Menu_t::MENU;
	std::array<sf::Sprite,NUM_OF_characters> m_characters;
	sf::Text m_About;
	sf::RectangleShape m_AboutRect;
	std::array<sf::Text, 2> m_menuTitle;
	sf::Text m_menu[MAX_NUMBER_OF_ITEMS];//main menu
	sf::Text m_gameOverMenu[2];//game over menu
	sf::Sprite m_background;
	int m_selectedItemIndex = 0;
	int m_GameOverItemIndx = 0;
	sf::RectangleShape m_rect;
	void draw2(sf::RenderWindow& window)const;//for game over
	void resetButtons();
	void makeMove(const int& value);
	void initAbout();
	void getAboutText();
	void initCharactersTxtrs();
	void draw(sf::RenderWindow& window);
	void initText(sf::Text& text, const unsigned& charSize, const std::string& str
		, const sf::Font& font, const sf::Color& color, const sf::Vector2f& pos,
		const float thick);
};
