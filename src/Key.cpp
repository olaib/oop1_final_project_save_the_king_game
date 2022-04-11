#include "Objects/StaticObjects/Key.h"
#include "Objects/MobileObjects/Theif.h"


void Key::handleCollision(Theif& thief)
{
	m_disposed = !thief.hasKey();// thief has only one key
	
	thief.handleCollision(*this);
}

