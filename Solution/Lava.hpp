#pragma once
//#include "Wall.hpp"
#include "Player.hpp"
#include "GameObject.hpp"

//WallBlock(const sf::Texture& _texture, const sf::Vector2f & _position, const sf::Vector2f& size) : GameObject(_texture, size)
//when created will be at same position
//size will be the size of the screen

class Lava : public GameObject
{
public:
	static Lava* instance;
	Lava(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		//this->setTexture(&_texture);
		speed = -1.5f; 
		this->setPosition(_position);
		//this->setSize(size);
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

	if (Player::instance->getPosition().y < this->getPosition().y - 2500)
	{
		this->setPosition({ 0, Player::instance->getPosition().y + 2500 });
	}
	
}