#pragma once
#include "Objects/Object.h"
const auto SPEED = 50.f;

class MobileObject : public Object {
public:
	using Object::Object;
	using Object::handleCollision;
	virtual void move(const sf::Time& delta, const sf::FloatRect& boardRec);
	sf::Vector2f dirFromKey();
	void stopMove();
	void setTransferred() { m_transferred = false; }
protected:
	bool isInRange(const sf::FloatRect& boardRec)const;
	sf::Vector2f m_wantedPos;
	bool m_transferred = false;
};