#include "Menu.h"
#include <iostream>
#include "Manager.h"
#include <fstream>

const auto FILE_NAME = "resources/About_text.txt";
const auto MOVE_UP = MAX_NUMBER_OF_ITEMS - 1;// value for move up
const auto MOVE_DOWN = 1; //value for move down

//------------------------------------------------------------------------------------------------
//c_tor of Menu
Menu::Menu(const sf::Vector2u& windowSize, const sf::Font& font)
{
	const auto pos = sf::Vector2f(windowSize);
	m_background.setTexture(Manager::instance().getTexture(Textures::BACKGROUND));
	initAbout();
	//Main Menu
	initText(m_menuTitle[0], 50, "Main Menu", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f - 100, 0 }, 2.f);
	initText(m_menu[0], 30, "Play", font, sf::Color::White,
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) }, 3.f);
	initText(m_menu[1], 30, "About", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) * 2 }, 3.f);
	initText(m_menu[2], 30, "Exit", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f, pos.y / (MAX_NUMBER_OF_ITEMS + 1) * 3 }, 3.f);
	//GameOver menu
	initText(m_menuTitle[1], 50, "Game Over", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f - 100, 0 }, 2.f);
	initText(m_gameOverMenu[0], 30, "Play Again", font, sf::Color::White,
		{ pos.x / 2.f, pos.y / 3 }, 3.f);
	initText(m_gameOverMenu[1], 30, "Return to Main Menu", font, sf::Color(214, 203, 129),
		{ pos.x / 2.f, pos.y / 3 * 2 }, 3.f);
}
//------------------------------------------------------------------------------------------------
void Menu::initText( sf::Text& text, const unsigned& charSize, const std::string& str
	, const sf::Font& font, const sf::Color& color, const sf::Vector2f& pos, const float thick) {
	text.setFont(font);
	text.setFillColor(color);
	text.setString(str);
	text.setOutlineThickness(thick);
	text.setCharacterSize(charSize);
	text.setPosition(pos);
}

//------------------------------------------------------------------------------------------------
//this func is main menu
void Menu::run(sf::RenderWindow& window )
{
	m_menuStatus = Menu_t::MENU;
	resetButtons();
	while (window.isOpen())
	{
		draw(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					if(m_menuStatus==Menu_t::MENU)
						makeMove(MOVE_UP);
					break;

				case sf::Keyboard::Down:
					if (m_menuStatus == Menu_t::MENU)
						makeMove(MOVE_DOWN);
					break;
				case sf::Keyboard::Backspace:
					if (m_menuStatus == Menu_t::INTRO)
						m_menuStatus = Menu_t::MENU;//return to menu
						resetButtons();
					break;
				case sf::Keyboard::Return:
					if (m_menuStatus==Menu_t::MENU)
						Manager::instance().play_stop(SELECTED, PLAY);//button pressed sound
					switch (m_selectedItemIndex)
					{
					case 0://Play selected
						m_menuStatus = Menu_t::PLAY;
						return;
					case 1://Intro selected
						m_menuStatus = Menu_t::INTRO;
						break;
					case 2://Exit selected
						m_menuStatus = Menu_t::EXIT;
						return;
					}
					break;
				}
				break;
			}	
		}
	}
}

void Menu::gameOver(sf::RenderWindow& window)
{
	m_selectedItemIndex = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					Manager::instance().play_stop(CLICK, PLAY);
					m_selectedItemIndex = (m_selectedItemIndex + 1) % 2;
					break;
				case sf::Keyboard::Down:
					Manager::instance().play_stop(CLICK, PLAY);
					m_selectedItemIndex = (m_selectedItemIndex + 1) % 2;
					break;
				case sf::Keyboard::Return:
					Manager::instance().play_stop(SELECTED, PLAY);;//button pressed sound
					switch (m_selectedItemIndex)
					{
					case 0://play selected
						return;
					case 1:
						run(window);//return to main menu
						break;
					}
					break;
				}
				break;
			}
		}
		draw2(window);
		//update buttons
		m_gameOverMenu[m_selectedItemIndex].setFillColor(sf::Color::White);
		m_gameOverMenu[(m_selectedItemIndex + 1) % 2].setFillColor(sf::Color(214, 203, 129));
	}
}
//------------------------------------------------------------------------------------------------
//this func draws gameover menu
void Menu::draw2( sf::RenderWindow& window)const {
	window.clear();
	window.draw(m_background);
	window.draw(m_menuTitle[1]);//game over
	for (auto button : m_gameOverMenu)
		window.draw(button);
	window.display();
}

//------------------------------------------------------------------------------------------------
// this func is about About
void Menu::initAbout()
{
	getAboutText();
	m_About.setFont(Manager::instance().getFont(1));
	m_About.setCharacterSize(24);
	m_About.setOutlineColor(sf::Color::White);
	auto textRec = sf::FloatRect(m_About.getLocalBounds());
	m_About.setOrigin(textRec.width / 2.f, textRec.height / 2.f);
	m_About.setPosition(sf::Vector2f(400.f, 300.f));
	m_About.setFillColor(sf::Color::Black);
	//init rectangle frame of About
	m_rect.setFillColor(sf::Color::White - sf::Color(0, 0, 0, 100));
	m_rect.setOutlineColor(sf::Color::Black);
	m_rect.setOutlineThickness(1.f);
	m_rect.setOrigin(m_About.getOrigin());
	m_rect.setPosition(m_About.getPosition());
	m_rect.setSize(sf::Vector2f(m_About.getGlobalBounds().width,
		m_About.getGlobalBounds().height));
	initCharactersTxtrs();//for sprites
}

//------------------------------------------------------------------------------------------------
// reads from file about msg
void Menu::getAboutText()
{
	auto inpFile = std::ifstream(FILE_NAME);
	if (!inpFile) {
		std::cerr << "Error in opening file!" << std::endl;
		return;
	}
	auto line = string();
	auto msg = string();
	//reading whole input file
	while (std::getline(inpFile, line)) {
		 msg += line;
		 msg += "\n";
	}
	inpFile.close();
	m_About.setString(msg);
}
//------------------------------------------------------------------------------------------------
//init of sprites
void Menu::initCharactersTxtrs()
{
		m_characters[KING].setTexture(Manager::instance().getTexture(KING));
		m_characters[KING].setPosition(sf::Vector2f(60.f,30 ));

		m_characters[WARRIOR].setTexture(Manager::instance().getTexture(WARRIOR));
		m_characters[WARRIOR].setPosition(sf::Vector2f(60.f, 190));

		m_characters[MAGE].setTexture(Manager::instance().getTexture(MAGE));
		m_characters[MAGE].setPosition(sf::Vector2f(60.f, 320));

		m_characters[THIEF].setTexture(Manager::instance().getTexture(THIEF));
		m_characters[THIEF].setPosition(sf::Vector2f(60.f, 380));

	m_characters[NUM_OF_characters-1].setTexture(Manager::instance().getTexture(NUM_OF_TEXTURES-1));
	m_characters[NUM_OF_characters-1].setPosition(sf::Vector2f(750.f,550.f));
}



void Menu::draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_background);
	if (m_menuStatus==Menu_t::INTRO)
	{
		window.draw(m_rect);
		window.draw(m_About);
		for (auto sprite : m_characters)
			window.draw(sprite);
	}
	
	else {//if we still in menu
		window.draw(m_menuTitle[0]);
		for (auto button : m_menu)
			window.draw(button);
	}
	window.display();
}
//------------------------------------------------------------------------------------------------

void Menu::resetButtons()
{
	m_selectedItemIndex = 0;
	m_menu[0].setFillColor(sf::Color::White);
	const auto color =sf::Color(214, 203, 129);
	m_menu[1].setFillColor(color);
	m_menu[2].setFillColor(color);
}
//------------------------------------------------------------------------------------------------
void Menu::makeMove(const int& value)
{
	Manager::instance().play_stop(CLICK, PLAY);
	m_menu[m_selectedItemIndex].setFillColor(sf::Color(214, 203, 129));
	m_selectedItemIndex = (m_selectedItemIndex + value) % MAX_NUMBER_OF_ITEMS;
	m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
}
