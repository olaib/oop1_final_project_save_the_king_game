#include "Objects/MobileObjects/Dwarf.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"

constexpr auto DWARF_SPEED = 70.f;
constexpr auto NUM_OF_DIR = 5;
#include <iostream>


sf::Vector2f toVector(Direction dir)
{
    switch (dir)
    {
    case Direction::Up:
        return { 0, -1 };
    case Direction::Down:
        return { 0, 1 };
    case Direction::Right:
        return { 1, 0 };
    case Direction::Left:
        return { -1, 0 };
    case Direction::Stay:
        return { 0, 0 };
    default:
        return { 0,0 };
    }
}

//--------------------------------------------------------------------------------------------------

bool Dwarf::allowed() const
{
    return m_allowed;
}

//-------------------------------------------------------------------------------------------------

void Dwarf::setAllowed()
{
    m_allowed = true;
}

//--------------------------------------------------------------------------------------------------

void Dwarf::move(const sf::Time& delta, const sf::FloatRect& boardRec)
{
    if (!m_allowed) //do not move
        return;
    m_time += delta;
    if (m_time.asSeconds() >= 3)
    {
        m_time -= m_time; //restart time(other options did not work ;) , we tried)
        m_dir = static_cast<Direction>(rand() % NUM_OF_DIR);
    }
    m_wantedPos = toVector(m_dir) * delta.asSeconds() * DWARF_SPEED;
    m_sprite.move(m_wantedPos);
    if (!isInRange(boardRec))
        m_sprite.move(-m_wantedPos);
}


//--------------------------------------------------------------------------------------------
void Dwarf::handleCollision(Object& objct)
{
    if (&objct == this)
        return;
    objct.handleCollision(*this);
}

//---------------------------------------------------------------------------------------------

void Dwarf::handleCollision(King& king)
{

    m_allowed = false;
    king.handleCollision(*this);

}

//--------------------------------------------------------------------------------------------------

void Dwarf::handleCollision(Mage& mage)
{

    m_allowed = false;
    mage.handleCollision(*this);

}

//--------------------------------------------------------------------------------------------------

void Dwarf::handleCollision(Theif& theif)
{

    m_allowed = false;
    theif.handleCollision(*this);

}

//--------------------------------------------------------------------------------------------------
void Dwarf::handleCollision(Warrior& warrior)
{
    m_allowed = false;
    warrior.handleCollision(*this);

}