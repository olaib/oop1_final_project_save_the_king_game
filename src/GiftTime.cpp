#include "Objects/StaticObjects/Gifts/GiftTime.h"

void GiftTime::handleCollision(King&)
{
	updateDuration();
}

void GiftTime::handleCollision(Warrior&)
{
	updateDuration();
}

void GiftTime::handleCollision(Theif&)
{
	updateDuration();
}

void GiftTime::handleCollision(Mage&)
{
	updateDuration();
}

void GiftTime::setGiftType(const float& factor, const std::string& type)
{
	m_factor = sf::seconds(factor);	
	m_myType = type;
}

void GiftTime::updateDuration()
{
	m_disposed = true;
	if (m_factor == sf::seconds(ADD_TIME_FACTOR))
		Manager::instance().play_stop(Got_Obj, PLAY);
	LevelTimer::instance().updateDuration(m_factor);
}