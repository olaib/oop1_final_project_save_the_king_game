#include "Objects/StaticObjects/Throne.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"
#include <iostream>

void Throne::handleCollision(King&)
{
	Manager::instance().play_stop(WIN_LVL, PLAY);
	m_endLevel = true;
}

void Throne::handleCollision(Warrior& war)
{
	war.handleCollision(*this);
}

void Throne::handleCollision(Theif& thief)
{
	thief.handleCollision(*this);
}


void Throne::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}
