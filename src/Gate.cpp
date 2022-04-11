#include "Objects/StaticObjects/Gate.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"



//--------------------------------------------------------------------------------------------------
void Gate::handleCollision(King& king)
{
    king.handleCollision(*this);
}

//--------------------------------------------------------------------------------------------------
void Gate::handleCollision(Warrior& war)
{
    war.handleCollision(*this);
}

//--------------------------------------------------------------------------------------------------
void Gate::handleCollision(Theif& thief)
{
    if (!thief.hasKey())
        thief.handleCollision(*this);// can not pass
    else {
        Manager::instance().play_stop(DOOR, PLAY);
        m_disposed = true;
        thief.setHasKey();// set to false
    }
}

//----------------------------------------------------------------------------------------------------
void Gate::handleCollision(Mage& mage)
{
    mage.handleCollision(*this);
}