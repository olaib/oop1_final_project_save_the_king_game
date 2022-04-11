#pragma once
#include "StaticObject.h"

class Key : public StaticObject {

public:
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
	void handleCollision(King& ) override {};
	void handleCollision(Warrior& ) override {};
	void handleCollision(Theif& ) override;
	void handleCollision(Mage& ) override {};
};
