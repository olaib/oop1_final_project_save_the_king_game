#include "Board.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
const auto FLY_TEXT = 30.f;

Board::Board(const sf::Vector2u& windowSize) : m_level(1, windowSize) {
	initText(m_hasKeyText, 35, Manager::instance().getFont(Fonts::font5)
		, "Has key:n", 1, { 650.f, 5.f });
	initText(m_giftsText, 30, Manager::instance().getFont(Fonts::font5)
		, "", 0, { 0.f, 0.f });
}


void Board::NewLevel(const sf::Vector2u& windowSize)
{
	m_levelNumber++;
	m_levelWin = false;
	m_level.newLevel(m_levelNumber, windowSize);
	m_CurrLvlTime = m_level.getCurrLvlTime();
	addToBoard();
}

void Board::restartLvl()
{
	m_levelWin = false;
	addToBoard();
}

bool Board::isFileExist(const int& levelNumber) const
{
	return m_level.isFileExist(levelNumber);
}

void Board::NewGame(const sf::Vector2u& windowSize)
{
	m_levelWin = false;
	m_levelNumber = 0;
	NewLevel(windowSize);
}

void Board::initText(sf::Text& text, const unsigned& size, const sf::Font& font, const string& msg, const float& thick, const sf::Vector2f& pos)
{
	text.setFont(font);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(thick);
	text.setCharacterSize(size);
	text.setString(msg);
	auto textRec = sf::FloatRect(text.getLocalBounds());
	text.setOrigin(textRec.width / 2.f, textRec.height / 2.f);//place it in center
	text.setPosition(pos);
}

void Board::initLocVec()
{
	auto colOfTel = size_t();
	auto rowOfTel = size_t();
	std::stringstream str(m_level.getTelVec());
	while (str >> rowOfTel) {
		str >> colOfTel;
		m_teleleportsLoc.push_back(getWantedPos(rowOfTel, colOfTel));
	}
}

void Board::initTeleportsLoc()
{
	initLocVec();
	auto i = size_t(0);
	Teleport* telPtr;
	StaticObject* staticPtr;

	for (auto& staticObj : m_staticObj) {
		staticPtr = staticObj.get();
		telPtr = dynamic_cast<Teleport*>(staticPtr);
		if (telPtr) {
			for (i = 0; i < m_teleleportsLoc.size(); i++) {
				if ((telPtr->getPos() == m_teleleportsLoc[i])) {
					telPtr->setTwinLoc((i % 2 == 0) ? m_teleleportsLoc[i + 1] : m_teleleportsLoc[i - 1]);
				}
			}
		}
	}
}

void Board::addToBoard()
{
	//empty
	m_players = {};
	m_staticObj.clear();
	m_dwarfs.clear();

	auto board = m_level.getBoard();
	for (auto i = size_t(0); i < board.size(); i++)
		for (auto j = size_t(0); j < board[0].size(); j++)
			initObjects(static_cast<InpChar>(board[i][j]), i, j);
	initTeleportsLoc();//connect between teleports
}


const sf::Vector2f Board::getWantedPos(const size_t& row, const size_t& col)
{
	auto x = (float)m_level.getStartPos().x + col * CELL_SIZE;
	auto y = (float)m_level.getStartPos().y + row * CELL_SIZE;
	return sf::Vector2f(x, y);
}


void Board::initObjects(InpChar _ch, const size_t& row, const size_t& col)
{
	switch (_ch) {
	case InpChar::KING:
		m_players[0] = make_unique<King>(getWantedPos(row, col), Manager::instance().getTexture(KING));
		m_players[0]->setColor(sf::Color::Cyan);
		break;
	case InpChar::WARRIOR:
		m_players[1] = make_unique<Warrior>(getWantedPos(row, col), Manager::instance().getTexture(WARRIOR));
		break;
	case InpChar::MAGE:
		m_players[2] = make_unique<Mage>(getWantedPos(row, col), Manager::instance().getTexture(MAGE));
		break;
	case InpChar::THIEF:
		m_players[3] = make_unique<Theif>(getWantedPos(row, col), Manager::instance().getTexture(THIEF));
		break;
	case InpChar::DWARF: 
		m_dwarfs.push_back(make_unique<Dwarf>(getWantedPos(row, col), Manager::instance().getTexture(DWARF1)));
		break;
	case InpChar::KEY:
		m_staticObj.push_back(make_unique<Key>(getWantedPos(row, col), Manager::instance().getTexture(KEY)));
		break;
	case InpChar::WALL:
		m_staticObj.push_back(make_unique<Wall>(getWantedPos(row, col), Manager::instance().getTexture(WALL)));
		break;
	case InpChar::GATE:
		m_staticObj.push_back(make_unique<Gate>(getWantedPos(row, col), Manager::instance().getTexture(GATE)));
		break;
	case InpChar::FIRE:
		m_staticObj.push_back(make_unique<Fire>(getWantedPos(row, col), Manager::instance().getTexture(FIRE)));
		m_staticObj[m_staticObj.size() - 1]->initSpriteSheet();//for sprite sheet
		break;
	case InpChar::THRONE:
		m_staticObj.push_back(make_unique<Throne>(getWantedPos(row, col), Manager::instance().getTexture(THRONE)));
		break;
	case InpChar::TELEPORT:
		m_staticObj.push_back(make_unique<Teleport>(getWantedPos(row, col), Manager::instance().getTexture(TELEPORT)));
		break;
	case InpChar::ORC:
		m_staticObj.push_back(make_unique<Orc>(getWantedPos(row, col), Manager::instance().getTexture(ORC)));
		break;
	case InpChar::ADD:
		initGiftType(InpChar::ADD, row, col);
		break;
	case InpChar::REDUCE:
		initGiftType(InpChar::REDUCE, row, col);
		break;
	case InpChar::REMOVE:
		m_staticObj.push_back(make_unique<RemoveDwarf>(getWantedPos(row, col), Manager::instance().getTexture(GIFTS)));
		break;
	default:
		break;
	}
}

void Board::initGiftType(InpChar _ch, const size_t& row, const size_t& col)
{
	m_staticObj.push_back(make_unique<GiftTime>(getWantedPos(row, col), Manager::instance().getTexture(GIFTS)));
	GiftTime* giftTime = dynamic_cast<GiftTime*>(m_staticObj[m_staticObj.size() - 1].get());
	_ch == InpChar::ADD ?
		giftTime->setGiftType(ADD_TIME_FACTOR, ADD_TIME_TYPE) :
		giftTime->setGiftType(REDUCE_TIME_FACTOR, REDUCE_TIME_TYPE);
}

void Board::draw(sf::RenderWindow& window)
{
		m_level.drawFrame(window);
		for (auto& object : m_staticObj)
			object->draw(window);

		for (auto& dwarf : m_dwarfs)
			dwarf->draw(window);

		for (auto& player : m_players)
			player->draw(window);

		if (m_giftsText.getPosition().y > (float)0) 
			window.draw(m_giftsText);

		window.draw(m_hasKeyText);
}


const float Board::getLvlTime() const
{
	return m_level.getCurrLvlTime();
}

MobileObject* Board::getPlayer(const size_t& indx)
{
	return m_players[indx].get();
}

StaticObject* Board::getObject(const size_t& indx)const
{
	return m_staticObj[indx].get();
}

//--------------------------------------------------------------------------------------------------
//manage all logics of movement
void Board::move(const sf::Time& deltaTime)
{
	for (auto& object : m_staticObj) {
		if (object->disposed() && typeid(*object) == typeid(Orc)) {// change from orc to key
			Manager::instance().play_stop(Sounds::FIGHTING, PLAY);
			m_staticObj.push_back(std::make_unique<Key>(object->getPos(), Manager::instance().getTexture(KEY)));
		}

		if (typeid(*object) == typeid(GiftTime) && object->disposed()) {
			GiftTime* giftTime = dynamic_cast<GiftTime*>(object.get());
			giftTime->getMyType() == REDUCE_TIME_TYPE?
				resetGiftText(sf::Color::Red, (size_t)Gifts_type::Reduce_time): //fly text of reduce time
				resetGiftText(sf::Color::Green, (size_t)Gifts_type::Add_time);  //fly text of add time
		}


		if (object->disposed() && typeid(*object) == typeid(RemoveDwarf))// remove dwarf vector
			m_dwarfs.clear();

		Throne* ThronePtr = dynamic_cast<Throne*>(object.get());
		if (typeid(*object) == typeid(Throne)) {
			m_levelWin = ThronePtr->isEndLvl();
		}

		if (typeid(*object) == typeid(Fire)) {
			object->animated(deltaTime);
		}
		Teleport* telPtr = dynamic_cast<Teleport*>(object.get());
		if (telPtr) {
			if (telPtr->checkCollision(*m_players[m_currPlayerIndx]))
				telPtr->handleCollision(*m_players[m_currPlayerIndx]);
		}
	}
	//update m_hasKey text
	Theif* theif = dynamic_cast<Theif*> (m_players[3].get());
	m_hasKeyText.setString((const string& )"has key: " + (theif->hasKey() ? "y" : "n"));

	std::erase_if(m_staticObj, [](auto& objct) {return objct->disposed(); });

	m_players[m_currPlayerIndx]->move(deltaTime, m_level.getFrameBound());

	for (auto& dwarf : m_dwarfs)
	{
		if (!dwarf->allowed()) {
			for (auto& player : m_players)
				if (dwarf->checkCollision(*player))
					return;
			dwarf->setAllowed();
		}
		dwarf->move(deltaTime, m_level.getFrameBound());
	}

	m_GiftTextTime += deltaTime; // fly to void
	if (m_GiftTextTime.asSeconds()>0.3&& m_giftsText.getPosition().y!=0) {
		m_giftsText.setPosition(m_giftsText.getPosition() - sf::Vector2f(0, FLY_TEXT));
		m_GiftTextTime -= m_GiftTextTime;
	}
}

void Board::resetGiftText(const sf::Color& color, size_t giftType)
{
	m_GiftTextTime -= m_GiftTextTime;
	m_giftsText.setFillColor(color);
	m_giftsText.setString(m_GiftStr[giftType]);
	m_giftsText.setPosition(m_players[m_currPlayerIndx]->getPos());
}

//----------------------------------------------------------------------------------------
const size_t& Board::getCurrIndx() const
{
	return m_currPlayerIndx;
}

//--------------------------------------------------------------------------------------------
//this func updates collor of curr player
void Board::updateCurrIndx()
{
	m_currPlayerIndx = (m_currPlayerIndx + 1) % NUM_OF_PLAYERS;
	
	for (auto i = size_t(0); i < NUM_OF_PLAYERS; i++)
		m_players[i]->setColor((i != m_currPlayerIndx) ? 
						sf::Color::White : sf::Color::Cyan);
}
//------------------------------------------------------------------------------------------------
//this func manages dwarf collissions

void Board::dwarfCollision()
{
	for (auto& dwarf : m_dwarfs)
		handleCollisions(*dwarf);
}

//------------------------------------------------------------------------------------------------
//this func manages collissions
void Board::handleCollisions(MobileObject& objct)
{
	bool collision = false;

	for (auto& object : m_staticObj)
	{
		if (objct.checkCollision(*object))
		{
			collision = true;
			objct.handleCollision(*object);
		}
	}
	if (!collision)
		objct.setTransferred();
	for (auto& player : m_players)
	{
		if (objct.checkCollision(*player))
		{
			objct.handleCollision(*player);
		}
	}

}

