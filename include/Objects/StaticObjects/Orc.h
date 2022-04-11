#pragma once
#include "StaticObject.h"

class Orc : public StaticObject {

public:
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
	void handleCollision(King& king) override;
    void handleCollision(Warrior& war) override;
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& mage) override;
};
