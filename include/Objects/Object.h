#pragma once
#include <SFML/Graphics.hpp>
#include "Manager.h"

using Sprite = sf::Sprite;
using RenderWindow = sf::RenderWindow;
class Orc;
class King;
class Warrior;
class Mage;
class Theif;
class Fire;
class Throne;
class Teleport;
class Gate;
class Wall;
class Key;
class Dwarf;
class AddTime;
class SubTime;
class RemoveDwarf;

const auto CELLSIZE = 41;

class Object {
public:
	Object(const sf::Vector2f& pos, const sf::Texture& txtr);
	virtual ~Object() = default;
	void draw(RenderWindow& window);
	const sf::Vector2f& getPos() const{return m_sprite.getPosition();}
	virtual void setColor(const sf::Color& color);
	bool checkCollision(const Object& objct)const;
	virtual void handleCollision(Object& objct) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Warrior& war) = 0;
	virtual void handleCollision(Theif& thief) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Orc& objct) = 0;
	virtual void handleCollision(Fire& objct) = 0;
	virtual void handleCollision(Throne& objct) = 0;
	virtual void handleCollision(Teleport& objct) = 0;
	virtual void handleCollision(Gate& objct) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Key& key) = 0;
	virtual void handleCollision(Dwarf& gameObject) = 0;
	virtual void handleCollision(AddTime& objct) = 0;
	virtual void handleCollision(SubTime& objct) = 0;
	virtual void handleCollision(RemoveDwarf& objct) = 0;
protected:
	Sprite m_sprite;
};