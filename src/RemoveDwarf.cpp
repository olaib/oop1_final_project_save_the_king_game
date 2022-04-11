#include "Objects/StaticObjects/Gifts/RemoveDwarf.h"
 
void RemoveDwarf::handleCollision(King& ) {
	m_disposed = true;
}

void RemoveDwarf::handleCollision(Mage& ) {
	m_disposed = true;
}

void RemoveDwarf::handleCollision(Warrior& ) {
	m_disposed = true;
}

void RemoveDwarf::handleCollision(Theif& ) {
	m_disposed = true;
}