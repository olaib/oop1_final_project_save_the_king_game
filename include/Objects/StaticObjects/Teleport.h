#pragma once
#include "StaticObject.h"
#include <iostream>
class Teleport : public StaticObject {
public:
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
	void setTwinLoc(const sf::Vector2f& pos) {
		m_TwinLoc = pos;
	}
	const sf::Vector2f& getTwinLoc()const {
		return m_TwinLoc;
	}
	void handleCollision(King& king) override;
	void handleCollision(Warrior& war) override;
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& ) override {};
private:
	sf::Vector2f m_TwinLoc;
};