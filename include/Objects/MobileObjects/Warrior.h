#pragma once
#include "Objects/MobileObjects/MobileObject.h"

class Warrior : public MobileObject {
public:
	using MobileObject::MobileObject;
	using MobileObject::handleCollision;
	void handleCollision(Object&) override;
	void handleCollision(King& king) override;
	void handleCollision(Warrior& ) override {};
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Orc& ) override {};
	void handleCollision(Fire& ) override;
	void handleCollision(Throne& ) override;
	void handleCollision(Teleport& teleport) override;
	void handleCollision(Gate& gate) override;
	void handleCollision(Wall& wall) override;
	void handleCollision(Key& ) override {};
	void handleCollision(Dwarf& dwarf) override ;
	virtual void handleCollision(AddTime& ) override {};
	void handleCollision(SubTime& ) {};
	void handleCollision(RemoveDwarf& ) {};
};