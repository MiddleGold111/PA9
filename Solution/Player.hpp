/*****************************************
* Programming Assignment 9
* 04/23/2025
* Programmers: Jayden Claytor, Blaise Banks
*
* Little Lava Lad: a vertical platformer where you run from lava
* SFML 3.0.0
*****************************************/
#pragma once
#include "GameObject.hpp"
#include "Platforms.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class Player : public GameObject
{
public:
	static Player* instance; 

	Player(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size), jumpSound(jumpBuffer), bonkSound(bonkBuffer), jumpSound2(jumpBuffer2)
	{
		this->setPosition(_position);
		velocity = { 0.0,0.0 };
		gravity = 0.2f;
		jumpStrength = -10.0;
		grounded = false;
		jumping = false;
		jumpsleft = 2;
		jumpBuffered = false;

		
		
		if(instance == nullptr)
		{ 
			instance = this;
		}
		
		jumpBuffer.loadFromFile("dirt_jump.mp3");
		jumpSound.setBuffer(jumpBuffer);
		jumpBuffer2.loadFromFile("swish.mp3");
		jumpSound2.setBuffer(jumpBuffer2);
		bonkBuffer.loadFromFile("bonk.mp3");
		bonkSound.setBuffer(bonkBuffer);
		jumpSound.setVolume(50.0f);
	}

	void update() override;
	bool checkCollision();

private:
	sf::Vector2f velocity;
	float gravity;
	float jumpStrength;
	bool grounded;
	bool jumping;
	bool jumpBuffered;
	int jumpsleft;
	
	sf::SoundBuffer jumpBuffer;
	sf::SoundBuffer jumpBuffer2;
	sf::SoundBuffer bonkBuffer;
	sf::Sound jumpSound;
	sf::Sound bonkSound;
	sf::Sound jumpSound2;

};
//instantiate singleton
Player* Player::instance = nullptr;


bool Player::checkCollision()
{
	bool collided = false;
	//check every platform
	for (Platform* platform : Platform::instances)
	{
		CollisionDirection dir = (*platform).collide(*this);
		//landed on a platform
		if (dir == CollisionDirection::Top)
		{
			grounded = true;
			if (velocity.y > 0) velocity.y = 0;
			jumping = false;
			jumpsleft = 2;

		}
		//hit under a platform
		if (dir == CollisionDirection::Bottom && velocity.y < 0)
		{
			if (velocity.y < -5.0f) bonkSound.play();
			velocity.y = 0;
		}
		if (dir != CollisionDirection::None)
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
	if (jumpPressed && !jumpBuffered && jumpsleft > 0)
	{
		velocity.y = jumpStrength;
		
		jumping = true;

		jumpsleft--;
		if (jumpsleft == 1)
			jumpSound.play();
		else jumpSound2.play();
	
		grounded = false;

	}

	jumpBuffered = jumpPressed; // set to true if the key is still held

	if (!grounded)
	{
		if (velocity.y < 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			velocity.y += gravity * 0.7f;  // lighter gravity on way up
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			velocity.y += (3 * gravity);
		}
		else velocity.y += gravity;
		
	}
	this->move({ 0, velocity.y });

	checkCollision();



}

