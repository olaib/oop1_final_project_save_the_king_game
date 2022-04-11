#include "Objects/MobileObjects/Mage.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/StaticObjects/Teleport.h"
#include "Objects/MobileObjects/Dwarf.h"


void Mage::handleCollision(Object& objct) {

	if (&objct == this)
		return;
	objct.handleCollision(*this);
}

void Mage::handleCollision(Warrior& objct)
{
	objct.stopMove();
}

void Mage::handleCollision(Theif& objct)
{
	objct.stopMove();
}

void Mage::handleCollision(King& objct)
{
	objct.stopMove();
}

void Mage::handleCollision(Dwarf& dwarf)
{
	dwarf.stopMove();
	m_sprite.move(-m_wantedPos);
}



void Mage::handleCollision(Wall& ) {

	m_sprite.move(-m_wantedPos);
}


void Mage::handleCollision(Orc& ) {

	m_sprite.move(-m_wantedPos);
}


void Mage::handleCollision(Throne& )
{
	m_sprite.move(-m_wantedPos);
}


void Mage::handleCollision(Gate& )
{
	m_sprite.move(-m_wantedPos);
}