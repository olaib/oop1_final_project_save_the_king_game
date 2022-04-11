#pragma once
#include "Menu.h"
#include "Board.h"
#include "Manager.h"
#include "LevelTimer.h"

using string = std::string;

enum class GameStatus :unsigned
{
	MENU, 
	START_GAME,
	GAME_OVER,
	RESTART_LEVEL,
	LEVEL_UP,PLAYING,
	END_GAME, EXIT
};

enum  Msg : size_t {
	LVL_UP_MSG,
	END_GAME_MSG,
	GETREADY_MSG,
	PRESS_KEY,
	RESTART_MSG
};

class Controller {
public:
	Controller();
	void run();
private:
	Menu m_menu;
	Board m_board;
	sf::Text m_numOfLevel;
	GameStatus m_gameStatus = GameStatus::MENU;
	std::array<sf::Text, 5> m_gameMsgs;
	std::array<string, 2>m_messages;
	sf::RectangleShape m_msgFrame;//for end game messages
	sf::RenderWindow m_window;
	Sprite m_background;
	void draw(sf::Clock& gameClock);
	void drawEndMsg(sf::Clock& gameClock);
	void drawGetReady(sf::Clock& gameClock);
	void handleEvents();
	void updateGameObjects(sf::Clock& gameClock);
	void lvlUp();
	void playing(const sf::Time& deltaTime);
	void readMessages();
	void initTexts();
	void initMsgFrame();
};