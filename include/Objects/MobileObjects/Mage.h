#include "Objects/MobileObjects/MobileObject.h"

class Mage : public MobileObject {
public:
	using MobileObject::MobileObject;
	using MobileObject::handleCollision;
	void handleCollision(Object& objct) override;
	void handleCollision(King& king) override;
	void handleCollision(Warrior& war) override;
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& ) override {};
	void handleCollision(Orc& ) override;
	void handleCollision(Fire& ) override {};
	void handleCollision(Throne& ) override;
	void handleCollision(Teleport&) override {};
	void handleCollision(Gate& ) override;
	void handleCollision(Wall& ) override;
	void handleCollision(Key& ) override {};
	void handleCollision(Dwarf& dwarf) override;
	void handleCollision(AddTime&) {};
	void handleCollision(SubTime&) {};
	void handleCollision(RemoveDwarf&) {};
};