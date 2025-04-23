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
		grounded = false;
		jumping = false;
		jumpKeyHeld = 0;
		jumpsleft = 2;
		
		if(instance == nullptr)
		{ 
			instance = this;
		}
	}

	void update() override;

	bool checkCollision()
	{

		//sf::FloatRect playerBounds = this->getGlobalBounds();
		bool collided = false;
		for (Platform* platform : Platform::instances)
		{
			CollisionDirection dir = (*platform).collide(*this);
			if (dir == CollisionDirection::Top)
			{
				grounded = true;
				velocity.y = 0;
				jumping = false;
				jumpsleft = 2;
			}
			if (dir == CollisionDirection::Bottom && velocity.y < 0)
			{
				velocity.y = 0;
			}
			if (dir!=CollisionDirection::None)
			{
				collided = true;
			}
			
		}
		if (!collided)
		{
			grounded = false;
		}
		return collided;
	}


private:
	sf::Vector2f velocity;
	float gravity;
	float jumpStrength;
	bool grounded;
	//bool grounded2;
	bool jumping;
	int jumpKeyHeld;

	int jumpsleft;

	//temporary

	//bool moveleft;
	//bool moveright;
	
};
Player* Player::instance = nullptr;


void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		if (this->getPosition().x > 70) //based on walls check for left wall so cant go further
		{
			this->move({ -3.5,0 });
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		if (this->getPosition().x < 1000 - 70 - getSize().x) //based on walls based on right wall so can't go further
		{
			this->move({ 3.5,0 });
		}
	}

	bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	if (jumpPressed && jumpKeyHeld<20 && jumpsleft>0) //fix double jump with &&
	{
		velocity.y = jumpStrength;
		grounded = false;
		jumping = true;
		if(jumpKeyHeld == 0) jumpsleft--;
	}

	if (jumpPressed)
	{
		jumpKeyHeld++;
	}
	else
	{
		jumpKeyHeld = 0;
	}
	if (!grounded)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			velocity.y += (3 * gravity);
		}
		else velocity.y += gravity;
	}
	this->move({ 0, velocity.y });

	checkCollision();


	//if (jumping)
	//{
	//	if (this->getPosition().y <= jumpStart - maxJumpHeight)
	//	{
	//		velocity.y = 0.0;
	//		jumping = false;
	//	}
	//}

	//if (this->getPosition().y >= groundY) //&& this->getPosition().y <= 0  which is check for ceiling collision, unneccessary...
	//{
	//	this->setPosition({ this->getPosition().x, groundY });
	//	velocity.y = 0;
	//	grounded = true;
	//	jumping = false;
	//}
	/*if (this->getPosition().y < 0)
	{
		this->setPosition({ this->getPosition().x, 0 });
		velocity.y = 0;
		
	}*/
}

