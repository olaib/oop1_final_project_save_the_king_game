#include "Objects/StaticObjects/Wall.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"

void Wall::handleCollision(King& king)
{
	king.handleCollision(*this);
}

void Wall::handleCollision(Warrior& war)
{
	war.handleCollision(*this);
}

void Wall::handleCollision(Theif& thief)
{
	
	thief.handleCollision(*this);
}

void Wall::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

