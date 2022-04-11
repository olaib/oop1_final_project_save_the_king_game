#include "Objects/Object.h"
#include<iostream>


//---------------------------------------------------------------------------------------------------
//c_tor of object class
Object::Object(const sf::Vector2f& pos, const sf::Texture& txtr)
{
	m_sprite.setTexture(txtr);
	m_sprite.setPosition(pos);

}


//---------------------------------------------------------------------------------------------------
void Object::draw(RenderWindow& window)
{
	window.draw(m_sprite);
}


//---------------------------------------------------------------------------------------------------
//this func changes the color of sprite
void Object::setColor(const sf::Color& color)
{
	m_sprite.setColor(color);
}


//----------------------------------------------------------------------------------------------------
//this function checks if there is a collision between 2 objects
bool Object::checkCollision(const Object& objct) const
{
	return m_sprite.getGlobalBounds().intersects(objct.m_sprite.getGlobalBounds());
}