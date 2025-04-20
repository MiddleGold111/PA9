#pragma once
#include "Wall.hpp"
#include "Player.hpp"
#include "GameObject.hpp"

//WallBlock(const sf::Texture& _texture, const sf::Vector2f & _position, const sf::Vector2f& size) : GameObject(_texture, size)
//when created will be at same position
//size will be the size of the screen

class Lava : public GameObject
{
public:
	Lava(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		//this->setTexture(&_texture);

		this->setPosition(_position);
		//this->setSize(size);
	}
	void update(void) override;

private:
	
	float speed;
	

};

void Lava::update(void)
{
	if (this->getPosition().y > 0)
	{
		this->move({ 0, -0.03 });
	}
}