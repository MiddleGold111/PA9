#pragma once
#include "GameObject.hpp"
#include "Platforms.hpp"
#include <SFML/Graphics.hpp>



class Player : public GameObject
{
public:
	static Player* instance; 

	Player(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
		velocity = { 0.0,0.0 };
		gravity = 0.2f;
		jumpStrength = -10.0;
		groundY = 875;
		grounded = true;

		maxJumpHeight = 300;
		jumpStart = 0.0;
		jumping = false;
		jumpKeyHeld = 0;
		
		if(instance == nullptr)
		{
			instance = this;
		}
	}

	void update() override;

	bool checkCollision()
	{

		//sf::FloatRect playerBounds = this->getGlobalBounds();
		bool collided = true;
		for (Platform* platform : Platform::instances)
		{
			CollisionDirection dir = (*platform).collide(*this);
			if (dir == CollisionDirection::Top)
			{
				grounded = true;
				velocity.y = 0;
				jumping = false;
			}
		}
		if (!collided)
		{
			grounded = false;
			collided = false;
		}
		return collided;
	}


private:
	sf::Vector2f velocity;
	float gravity;
	float jumpStrength;
	float groundY;
	bool grounded;
	//bool grounded2;
	float maxJumpHeight;
	float jumpStart;
	bool jumping;
	int jumpKeyHeld;

	//temporary

	//bool moveleft;
	//bool moveright;
	
};

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (this->getPosition().x > 70) //based on walls check for left wall so cant go further
		{
			this->move({ -0.9,0 });
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (this->getPosition().x < 1000 - 70 - getSize().x) //based on walls based on right wall so can't go further
		{
			this->move({ 0.9,0 });
		}
	}

	bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	if (jumpPressed && (jumpKeyHeld<20 || grounded))
	{
		velocity.y = jumpStrength;
		grounded = false;
		jumping = true;
		jumpStart = this->getPosition().y;

	}

	if (jumpPressed)
	{
		jumpKeyHeld++;
	}
	else
	{
		jumpKeyHeld = 0;
	}

	if (jumping)
	{
		if (this->getPosition().y <= jumpStart - maxJumpHeight)
		{
			velocity.y = 0.0;
			jumping = false;
		}
	}
	//else if (grounded) //can remove but changes things
	//{

	/*if (!grounded && !wee)
	{
		velocity.y += gravity;
	}*/
		
	
	if (!grounded)
	{
		velocity.y += gravity;
	}
	this->move({ 0, velocity.y });

	checkCollision();
	if (this->getPosition().y >= groundY) //&& this->getPosition().y <= 0  which is check for ceiling collision, unneccessary...
	{
		this->setPosition({ this->getPosition().x, groundY });
		velocity.y = 0;
		grounded = true;
		jumping = false;
	}
	if (this->getPosition().y < 0)
	{
		this->setPosition({ this->getPosition().x, 0 });
		velocity.y = 0;
		
	}
}

