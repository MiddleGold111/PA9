#pragma once
#include "GameObject.hpp"


class Player : public GameObject
{
public:
	Player(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
	}

	void update() override;
private:

	int jumptime;
	bool jumpdown;
	int jumpdowncount;
};

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->move({ -1,0 });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->move({ 1,0 });
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		if (jumptime > 100)
		{	
			jumpdown = true;
			
						
		}
		else 
		{
			this->move({ 0,-1 });
			jumptime++;
			
		}
		
		
	}
	else
	{
		jumptime = 0;
	}

	if (jumpdown = true)
	{
		if (jumptime > jumpdowncount)
		{
			this->move({ 0,1 });
		}
		jumpdowncount++;
		
		
	}
	
	
}