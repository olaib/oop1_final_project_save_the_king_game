#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <fstream>
#include "Manager.h"
#include <SFML/Graphics.hpp>
#include <filesystem>

const auto CELL_SIZE = 41.f;
const auto NUM_OF_PLAYERS = 4;
using std::vector;
using std::string;
using std::array;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;
using std::filesystem::exists;

enum class InpChar :char {
	KING = 'K',
	MAGE = 'M',
	THIEF = 'T',
	WARRIOR = 'W',
	KEY = 'F',
	ORC = '!',
	WALL = '=',
	GATE = '#',
	FIRE = '*',
	THRONE = '@',
	TELEPORT = 'X',
	DWARF = '^',
	ADD = '+',
	REDUCE = '-',
	REMOVE = '?'
};

class Level {
public:
	Level(const int& levelNumber, const sf::Vector2u& windowSize);
	sf::Vector2f getBoardSize();
	sf::FloatRect getFrameBound()const { return m_brdFrame.getGlobalBounds(); }
	vector<string> getBoard()const { return m_board; }
	const sf::Vector2f& getStartPos()const   {return m_startPos;}
	const string& getTelVec()const { return m_telStr; }
	void drawFrame(sf::RenderWindow& window);
	const float getCurrLvlTime()const;
	void newLevel(const int& levelNumber, const sf::Vector2u& windowSize);
	bool isFileExist(const int& levelNumber) const;
private:
	sf::Sprite m_tile;
	sf::Vector2f m_startPos;
	sf::RectangleShape m_brdFrame;
	size_t m_width;
	size_t m_height;
	float m_CurrLvlTime = 0;
	vector<string> m_board;
	string m_telStr;
	void initFrame(const sf::Vector2u& windowSize);
	void open_file(ifstream& input, const int& levelNumber);
	void read_level( const int levelNumber);
};

