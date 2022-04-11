#include "Objects/MobileObjects/MobileObject.h"

class Theif : public MobileObject {
public:
	using MobileObject::MobileObject;
	using MobileObject::handleCollision;
	bool hasKey() const;
	void setHasKey() { m_hasKey = false; }
	void handleCollision(Object& objct) override;
	void handleCollision(King& king) override;
	void handleCollision(Warrior& war) override;
	void handleCollision(Theif& ) override {};
	void handleCollision(Mage& mage) override;
	void handleCollision(Orc& orc) override;
	void handleCollision(Fire& ) override;
	void handleCollision(Throne& ) override;
	void handleCollision(Teleport& teleport) override;
	void handleCollision(Gate& ) override; 
	void handleCollision(Wall& wall) override;
	void handleCollision(Key& key) override;
	void handleCollision(Dwarf& dwarf) override ;
	void handleCollision(AddTime& ) {};
	void handleCollision(SubTime& ) {};
	void handleCollision(RemoveDwarf& ) {};
private:
	bool m_hasKey = false;
};