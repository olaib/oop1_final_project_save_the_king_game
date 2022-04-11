#pragma once
#include "Objects/StaticObjects/StaticObject.h"

class Throne : public StaticObject {
public:
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
	void handleCollision(King& king) override;
	void handleCollision(Warrior& war) override;
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& mage) override;
	const bool& isEndLvl()const { return m_endLevel; }
private:
	bool m_endLevel = false;
};