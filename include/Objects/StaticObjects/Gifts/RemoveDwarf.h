#pragma once
#include "Gift.h"

class RemoveDwarf : public Gift {
public:
	using Gift::Gift;
	using Gift::handleCollision;
	void handleCollision(King& ) override;
	void handleCollision(Warrior& ) override;
	void handleCollision(Theif& ) override;
	void handleCollision(Mage& ) override;
};

