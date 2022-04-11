#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"
#include "Objects/StaticObjects/Teleport.h"
#include "Objects/MobileObjects/Dwarf.h"


void Warrior::handleCollision(Object& objct)
{
	if (&objct == this)
		return;
	objct.handleCollision(*this);
}

void Warrior::handleCollision(Mage& objct)
{
	objct.stopMove();
}

void Warrior::handleCollision(Theif& objct)
{
	objct.stopMove();
}

void Warrior::handleCollision(King& objct)
{
	objct.stopMove();
}


void Warrior::handleCollision(Wall& ) {

	m_sprite.move(-m_wantedPos);
}


void Warrior::handleCollision(Fire& ) {

	m_sprite.move(-m_wantedPos);
}

void Warrior::handleCollision(Throne& ) {

	m_sprite.move(-m_wantedPos);
}

void Warrior::handleCollision(Teleport& teleport)
{
	if (!m_transferred)
	{
		m_transferred = true;
		m_sprite.setPosition(teleport.getTwinLoc());
	}
}

void Warrior::handleCollision(Gate& )
{
	m_sprite.move(-m_wantedPos);
}


void Warrior::handleCollision(Dwarf& dwarf)
{
	dwarf.stopMove();
	m_sprite.move(-m_wantedPos);
}