#include "Objects/StaticObjects/Fire.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"

sf::Time Fire::m_time;
sf::IntRect Fire::m_rectSourceSprite;


//---------------------------------------------------------------------------------------------
//this function initialize IntRect for animation

void Fire::initSpriteSheet()
{
    m_isAnimated = true;
    m_rectSourceSprite = sf::IntRect(0, 0,CELLSIZE , CELLSIZE);
    m_sprite.setTextureRect(m_rectSourceSprite);
}


//------------------------------------------------------------------------------------------------
//this func updates a sprite sheet based on time

void Fire::animated(const sf::Time& delta)
{
    m_time += delta;
    if (m_time.asSeconds() > 0.3f) {
        m_rectSourceSprite.left =((int)(m_rectSourceSprite.left + CELLSIZE) % ((int)CELLSIZE*6)); //update to next sprite
        m_sprite.setTextureRect(m_rectSourceSprite);//update sprite
        m_time -= m_time;//set to zero ,again :)
    }
}

//-----------------------------------------------------------------------------------------------------

void Fire::handleCollision(Mage& )
{
    m_disposed = true;
}

//-----------------------------------------------------------------------------------------------------

void Fire::handleCollision(Theif& thief)
{
    thief.handleCollision(*this);
}

//------------------------------------------------------------------------------------------------------

void Fire::handleCollision(King& king)
{
    king.handleCollision(*this);
}

//----------------------------------------------------------------------------------------------------

void Fire::handleCollision(Warrior& war)
{
    war.handleCollision(*this);
}

