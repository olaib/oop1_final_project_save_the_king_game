#include "Objects/StaticObjects/Orc.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"


void Orc::handleCollision(King& king)
{
	king.handleCollision(*this);
}



void Orc::handleCollision(Warrior& war)
{
	m_disposed = true;
	war.handleCollision(*this);
}


void Orc::handleCollision(Theif& thief)
{
	thief.handleCollision(*this);
}


void Orc::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}




