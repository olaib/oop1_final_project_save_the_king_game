#pragma once
#include "Level.h"
#include "Menu.h"
#include "Objects/StaticObjects/Gifts/Gift.h"
#include "Objects/StaticObjects/StaticObject.h"
#include "Objects/MobileObjects/Dwarf.h"
#include "Objects/Objects.hpp"
using std::vector;
const auto NUM_OF_GIFTS = 3;//num of gift's type

class Board {
public:
	Board(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window);
	const float getLvlTime()const;
	MobileObject* getPlayer(const size_t& indx);
	StaticObject* getObject(const size_t& indx)const;
	void move( const sf::Time& deltaTime);
	const size_t& getCurrIndx() const;
	void updateCurrIndx();
	unsigned getLvlNum()const { return m_levelNumber; }
	void handleCollisions(MobileObject& objct);
	void dwarfCollision();
	void NewLevel(const sf::Vector2u& windowSize);
	void restartLvl();
	bool isLvlWin()const {return m_levelWin; };
	bool isFileExist(const int& levelNumber) const;
	void NewGame(const sf::Vector2u& windowSize);
	void initText(sf::Text& text, const unsigned& size, const sf::Font& font,
		const string& msg, const float& thick, const sf::Vector2f& pos);
private:
	Level m_level;
	array <string, NUM_OF_GIFTS> m_GiftStr{"Time-- ):","Time++ (:","kill (:"};
	sf::Time m_GiftTextTime;//for gift type drawing
	bool m_levelWin=false;
	sf::Text m_giftsText;
	sf::Text m_hasKeyText;
	int m_levelNumber= 1;
	float m_CurrLvlTime = 0;
	size_t m_currPlayerIndx = 0;
	vector <unique_ptr <Dwarf>> m_dwarfs;
	vector <unique_ptr <StaticObject>> m_staticObj;
	array <unique_ptr <MobileObject>, NUM_OF_PLAYERS> m_players;
	vector<sf::Vector2f> m_teleleportsLoc;
	void initTeleportsLoc();
	void addToBoard();
	void initLocVec();
	enum class Gifts_type :size_t {
		Reduce_time,
		Add_time
	};
	void resetGiftText(const sf::Color& color, size_t giftType);
	const sf::Vector2f getWantedPos(const size_t& row, const size_t& col);
	void initObjects(InpChar _ch, const size_t& row, const size_t& col);
	void initGiftType(InpChar _ch, const size_t& row, const size_t& col);
};