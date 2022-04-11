#include "Objects/MobileObjects/King.h"
#include "Objects/MobileObjects/Warrior.h"
#include "Objects/MobileObjects/Theif.h"
#include "Objects/MobileObjects/Mage.h"
#include "Objects/MobileObjects/dwarf.h"
#include "Objects/StaticObjects/Teleport.h"

//-----------------------------------------------------------------------------------------------------

void King::handleCollision(Object& objct) 
{
	if (&objct == this)
		return;
	objct.handleCollision(*this);
}

//--------------------------------------------------------------------------------------------------

void King::handleCollision(Warrior& objct)
{
	objct.stopMove();
}

//--------------------------------------------------------------------------------------------------
void King::handleCollision(Theif& objct)
{
	objct.stopMove();
}

//--------------------------------------------------------------------------------------------------
void King::handleCollision(Mage& objct)
{
	objct.stopMove();
}

//--------------------------------------------------------------------------------------------------
void King::handleCollision(Wall& ) 
{
	m_sprite.move(-m_wantedPos);
}

//--------------------------------------------------------------------------------------------------
void King::handleCollision(Dwarf& dwarf)
{
	dwarf.stopMove();
	m_sprite.move(-m_wantedPos);
}


//--------------------------------------------------------------------------------------------------
 void King::handleCollision(Orc& ) 
 {

	m_sprite.move(-m_wantedPos);
 }
 
 //--------------------------------------------------------------------------------------------------
 void King::handleCollision(Fire& ) 
 {

	 m_sprite.move(-m_wantedPos);
 }

 //--------------------------------------------------------------------------------------------------
 void King::handleCollision(Teleport& teleport)
 {
	 if (!m_transferred) // did not passed a teleport now
	 {
		 m_transferred = true;
		 m_sprite.setPosition(teleport.getTwinLoc()); // go to twinport
	 }
 }

 //--------------------------------------------------------------------------------------------------
 void King::handleCollision(Gate&)
 {
	 m_sprite.move(-m_wantedPos);
 }


 

