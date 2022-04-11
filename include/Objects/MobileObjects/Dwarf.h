#pragma once
#include "Objects/MobileObjects/MobileObject.h"

enum class Direction : size_t { Up, Down, Right, Left, Stay };

class Dwarf : public MobileObject {
public:
	using MobileObject::MobileObject;
	using MobileObject::handleCollision;
	bool allowed() const;
	void setAllowed();
	void move(const sf::Time& delta, const sf::FloatRect& boardRec) override;
	void handleCollision(Object& object) override ;
	void handleCollision(King& king) override;
	void handleCollision(Theif& theif) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Orc&) override {};
	void handleCollision(Fire&) override {};
	void handleCollision(Throne&) override {};
	void handleCollision(Teleport&) override {};
	void handleCollision(Gate&) override {};
	void handleCollision(Wall&) override {};
	void handleCollision(Key&) override {};
	void handleCollision(Dwarf&) override {};
	void handleCollision(AddTime&) {};
	void handleCollision(SubTime&) {};
	void handleCollision(RemoveDwarf&) {};
private:
	sf::Time m_time;
	Direction m_dir = Direction::Right;
	bool m_allowed = true;
};