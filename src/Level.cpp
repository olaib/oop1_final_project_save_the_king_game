#include "Level.h"

//--------------------------------------------------------------------------------------------------
//c_tor of Level class

Level::Level(const int& levelNumber,const sf::Vector2u& windowSize)
{
	newLevel(levelNumber,windowSize);
	m_tile.setTexture(Manager::instance().getTexture(14));
}


//--------------------------------------------------------------------------------------------------
//this func updates frame and reads new level

void Level::newLevel(const int& levelNumber , const sf::Vector2u& windowSize) 
{
	read_level(levelNumber);
	initFrame(windowSize);
}


//--------------------------------------------------------------------------------------------------
// this function initFrame and rectangle shape of board

void Level::initFrame(const sf::Vector2u& windowSize) {
	auto boardSize = sf::Vector2f((float)m_width * CELL_SIZE, (float)m_height * CELL_SIZE);
	m_brdFrame.setSize(boardSize);
	m_brdFrame.setOrigin(m_brdFrame.getSize() / 2.f);
	m_brdFrame.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
	m_brdFrame.setFillColor(sf::Color::White - sf::Color(0,0,0,110));
	m_startPos = sf::Vector2f(m_brdFrame.getPosition().x - m_brdFrame.getOrigin().x
		, m_brdFrame.getPosition().y - m_brdFrame.getOrigin().y);
	m_tile.setTexture(Manager::instance().getTexture(TILE));
}
	
//------------------------------------------------------------------------------------------------

void Level::drawFrame(sf::RenderWindow& window)
{
	auto FramePos = sf::Vector2f(m_startPos.x - CELL_SIZE, m_startPos.y - CELL_SIZE);
	auto cols = m_width + 2;
	auto rows = m_height + 2;
	for (size_t i = 0; i < cols; i++)
		for (size_t j = 0; j < rows; j++)
			if (j == 0 || j == rows - 1 || i == 0 || i == cols - 1) {
				m_tile.setPosition(FramePos.x + i * CELL_SIZE, FramePos.y + j * CELL_SIZE);
				window.draw(m_tile);
			}
	window.draw(m_brdFrame);// transperrent rect of board
}

//-----------------------------------------------------------------------------------------------

const float Level::getCurrLvlTime()const
{
	return m_CurrLvlTime;
}

//-------------------------------------------------------------------------------------------------

bool Level::isFileExist(const int& levelNumber) const
{
	const string fileName = "resources/lvl" + std::to_string(levelNumber) + ".txt";
	return exists(fileName);
}

//--------------------------------------------------------------------------------------------------
void Level::read_level( const int levelNumber)
{
	m_board.clear();
	ifstream file;
	open_file(file, levelNumber);

	auto line = string();
	auto time = string();
	std::getline(file, time);
	m_CurrLvlTime = stod(time);
	while (std::getline(file, line)) {
		if (line[0] == '-')
			break;
		m_board.push_back(line);
	}
	std::getline(file, m_telStr);
	m_height = m_board.size();
	m_width = m_board[0].size();
	file.close();
}


// this function returns the board size
sf::Vector2f Level::getBoardSize()
{
	sf::Vector2f boardSize;
	boardSize.x = m_board.size() * CELL_SIZE;
	boardSize.y = m_board[0].size() * CELL_SIZE;
	return boardSize;
}


// this function opens the .txt file to read
void Level::open_file(ifstream& input,const int& levelNumber)
{	
	const string fileName = "resources/lvl" + std::to_string(levelNumber) + ".txt";
	input.open(fileName);
	if (!input.is_open())
	{
		std::cerr << "could not open level's file\n";
		exit(EXIT_FAILURE);
	}
}