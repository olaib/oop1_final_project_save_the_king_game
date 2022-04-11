#include "Objects/MobileObjects/MobileObject.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"


//----------------------------------------------------------------------------------------------------
//this function makes a move with a player if inrange

void MobileObject::move(const sf::Time& delta, const sf::FloatRect& boardRec)
{
    m_wantedPos = sf::Vector2f(dirFromKey() * SPEED * delta.asSeconds());
    m_sprite.move(m_wantedPos);
    if (!isInRange(boardRec)) 
        m_sprite.move(-m_wantedPos);
}


//---------------------------------------------------------------------------------
//this function returns wanted dirction (depending on key pressed)

sf::Vector2f MobileObject:: dirFromKey()
{
    static const
        std::initializer_list<std::pair<sf::Keyboard::Key, sf::Vector2f>>
        keyToVectorMapping =
    {
        { sf::Keyboard::Right, { 1, 0 } },
        { sf::Keyboard::Left , { -1, 0 } },
        { sf::Keyboard::Up   , { 0, -1 } },
        { sf::Keyboard::Down , { 0, 1 } },
    };

    for (const auto& pair : keyToVectorMapping)
        if (sf::Keyboard::isKeyPressed(pair.first))
            return pair.second;

    return { 0, 0 }; // no movement
}

//---------------------------------------------------------------------------------------------------
//this function stops move of a player out of it's class
//needed in handlecollission when 2 players colliding

void MobileObject::stopMove()
{
    if (!m_transferred)
        m_sprite.move(-m_wantedPos);
}

//----------------------------------------------------------------------------------------------------
bool MobileObject::isInRange(const sf::FloatRect& boardRec) const
{
    return (boardRec.contains(m_sprite.getPosition() - m_sprite.getOrigin()) &&
        boardRec.contains(m_sprite.getPosition() - m_sprite.getOrigin() + sf::Vector2f(CELLSIZE, CELLSIZE)));
}