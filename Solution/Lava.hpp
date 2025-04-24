/*****************************************
* Programming Assignment 9
* 04/23/2025
* Programmers: Jayden Claytor, Blaise Banks
*
* Little Lava Lad: a vertical platformer where you run from lava
* SFML 3.0.0
*****************************************/
#pragma once
#include "Player.hpp"
#include "GameObject.hpp"

class Lava : public GameObject
{
public:
	static Lava* instance;
	Lava(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		speed = -1.5f; 
		this->setPosition(_position);
		if (instance == nullptr) instance = this;
	}
	void update(void) override;
	void setSpeed(float _speed) { speed = _speed; }
	float getSpeed() { return speed; }
private:
	float speed;

};
Lava* Lava::instance = nullptr;

void Lava::update(void)
{
	this->move({ 0, speed });

	//never fall too far behind the player
	if (Player::instance->getPosition().y < this->getPosition().y - 2500)
	{
		this->setPosition({ 0, Player::instance->getPosition().y + 2500 });
	}
	
}