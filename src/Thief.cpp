#pragma once
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Mage.h"
#include "Objects/StaticObjects/Teleport.h"
#include "Objects/MobileObjects/Dwarf.h"


bool Theif::hasKey() const
{
	return m_hasKey;
}

 
void Theif::handleCollision(Object& objct)
{
	if (&objct == this)
		return;
	objct.handleCollision(*this);
}

//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Warrior& objct)
{
	objct.stopMove();
}
//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Mage& objct)
{
	objct.stopMove();
}

//------------------------------------------------------------------------------------------------
void Theif::handleCollision(King& objct)
{
	objct.stopMove();
}
//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Orc& )
{
	m_sprite.move(-m_wantedPos);
}

//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Wall& )
{
	m_sprite.move(-m_wantedPos);
}

//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Key& ) 
{
	if (!m_hasKey) {
		Manager::instance().play_stop(Got_Obj, PLAY);
		m_hasKey = true;
	}
}

//------------------------------------------------------------------------------------------------
void Theif::handleCollision(Fire&) 
{
	m_sprite.move(-m_wantedPos);
}


void Theif::handleCollision(Throne&) 
{
	m_sprite.move(-m_wantedPos);
}

void Theif::handleCollision(Teleport& teleport)
{
	if (!m_transferred)
	{
		m_transferred = true;
		m_sprite.setPosition(teleport.getTwinLoc());
	}
}

void Theif::handleCollision(Gate&)
{
	if (m_hasKey)
		m_hasKey = false;
	else
		m_sprite.move(-m_wantedPos);
	
}
void Theif::handleCollision(Dwarf& dwarf)
{
	dwarf.stopMove();
	m_sprite.move(-m_wantedPos);
}
