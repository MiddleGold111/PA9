/*****************************************
* Programming Assignment 9
* 04/23/2025
* Programmers: Jayden Claytor, Blaise Banks
*
* Little Lava Lad: a vertical platformer where you run from lava
* SFML 3.0.0
*****************************************/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
using std::vector;


enum class CollisionDirection { None, Top, Bottom, Left, Right };

class GameObject : public sf::RectangleShape
{
public:
	sf::Texture* texture;
	GameObject(const sf::Texture& _texture, const sf::Vector2f& size) : sf::RectangleShape(size)
	{
		texture = new sf::Texture(_texture);
		this->setTexture(texture);
	}
	virtual void update() = 0;

	CollisionDirection collide(GameObject& that);

};



//that should always be a "movable" object like player so it is the one that gets moved in collision
CollisionDirection GameObject::collide(GameObject& that)
{
	//distance between the objects' centers
	float distanceX = this->getGlobalBounds().getCenter().x - that.getGlobalBounds().getCenter().x;
	float distanceY = this->getGlobalBounds().getCenter().y - that.getGlobalBounds().getCenter().y;

	//actual distance between the objects' edges
	float gapX = fabs(distanceX) - (that.getSize().x + this->getSize().x) / 2.0;
	float gapY = fabs(distanceY) - (that.getSize().y + this->getSize().y) / 2.0;

	if (gapX < 0 && gapY < 0)
	{
		if (gapX > gapY) //objects need to be separated horizontally
		{
			if (distanceX < 0) //that is on the right
			{
				that.move({ -gapX, 0.0 });
				return CollisionDirection::Left;
			}
			else //left
			{
				that.move({ gapX, 0.0 });
				return CollisionDirection::Right;
			}
		}
		
		else //separate vertically
		{
			if (distanceY > 0) //that is below
			{
				that.move({ 0.0, gapY });
				return CollisionDirection::Top;
			}
			else //above
			{
				that.move({ 0.0, -gapY });
				return CollisionDirection::Bottom;
			}
		}
		
	}
	return CollisionDirection::None;
}