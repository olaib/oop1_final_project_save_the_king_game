#include "Objects/StaticObjects/Teleport.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"

//------------------------------------------------------------------------------------------------
void Teleport::handleCollision(King& king)
{
	Manager::instance().play_stop(Tel_sound, PLAY);
	king.handleCollision(*this);
}

//------------------------------------------------------------------------------------------------
void Teleport::handleCollision(Warrior& war)
{
	Manager::instance().play_stop(Tel_sound, PLAY);
	war.handleCollision(*this);
}

//------------------------------------------------------------------------------------------------
void Teleport::handleCollision(Theif& thief)
{
	Manager::instance().play_stop(Tel_sound, PLAY);
	thief.handleCollision(*this);
}

