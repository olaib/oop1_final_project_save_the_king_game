#pragma once
#include "Objects/MobileObjects/MobileObject.h"

class King : public MobileObject {
public:
	using MobileObject::MobileObject;
	using MobileObject::handleCollision;
	 void handleCollision(Object& objct) override;
	 void handleCollision(King& ) override {};
	 void handleCollision(Warrior& war) override;
	 void handleCollision(Theif& thief) override;
	 void handleCollision(Mage& mage) override; 
	 void handleCollision(Orc& orc) override;
	 void handleCollision(Fire& ) override;
	 void handleCollision(Throne& ) override {};
	 void handleCollision(Teleport& teleport) override;
	 void handleCollision(Gate& gate) override;
     void handleCollision(Wall& wall) override;
	 void handleCollision(Key& ) override {};
	 void handleCollision(Dwarf& dwarf) override;
	 void handleCollision(AddTime& ) {};
	 void handleCollision(SubTime& ) {};
	 void handleCollision(RemoveDwarf& ) {};
};