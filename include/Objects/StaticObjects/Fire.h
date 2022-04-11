#pragma once
#include "StaticObject.h"

class Fire : public StaticObject {

public:
	void initSpriteSheet();
	void animated(const sf::Time& delta);
	using StaticObject::StaticObject;
	using StaticObject::handleCollision;
	void handleCollision(King& king) override;
	void handleCollision(Warrior& war) override;
	void handleCollision(Theif& thief) override;
	void handleCollision(Mage& mage) override;
private:
	static sf::Time m_time;
	static sf::IntRect m_rectSourceSprite;
	
};

