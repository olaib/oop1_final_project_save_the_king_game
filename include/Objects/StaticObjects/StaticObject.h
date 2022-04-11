#pragma once
#include "Objects/Object.h"

class StaticObject : public Object {
public:
	using Object::Object;
	bool isAnimated()const { return m_isAnimated; }
	bool disposed()const { return m_disposed; }
	virtual void initSpriteSheet() {};
	virtual void animated(const sf::Time&) {};
	//defines collisions of the objects
	using Object::handleCollision;
	virtual void handleCollision(Object& ) override {};
	virtual void handleCollision(Orc&) override {};
	virtual void handleCollision(Fire&)  {};
	virtual void handleCollision(Throne& ) override {};
	virtual void handleCollision(Teleport& ) override {};
	virtual void handleCollision(Gate& ) override {};
	virtual void handleCollision(Wall& ) override {};
	virtual void handleCollision(Key& ) override {};
	virtual void handleCollision(Dwarf&) override {};
	virtual void handleCollision(AddTime&) override {};
	virtual void handleCollision(SubTime&) override {};
	virtual void handleCollision(RemoveDwarf&) override {};
protected:
	bool m_isAnimated = false; // check if curr objct is an animation
	bool m_disposed = false; // delete mark
};