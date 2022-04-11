#pragma once 
#include "Gift.h"
#include "LevelTimer.h";
const auto ADD_TIME_FACTOR = 60.f;
const auto REDUCE_TIME_FACTOR = -1 * ADD_TIME_FACTOR;
const auto ADD_TIME_TYPE = std::string("add time");
const auto REDUCE_TIME_TYPE = std::string("reduce time");

class GiftTime :public Gift{
public:
	using Gift::Gift;
	using Gift::handleCollision;
	void handleCollision(King&) override;
	void handleCollision(Warrior&) override;
	void handleCollision(Theif&) override;
	void handleCollision(Mage&) override;
	void setGiftType(const float& factor, const std::string& type);
	const std::string& getMyType() { return m_myType; }
private:
	sf::Time m_factor = sf::seconds(0);
	std::string m_myType;
	void updateDuration();
};