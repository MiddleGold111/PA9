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
#include <vector>
#include "Player.hpp"
 

class Platform : public GameObject
{
public:
	static vector<Platform*> instances;
	static float top;

	Platform(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
		instances.push_back(this);
		top = this->getPosition().y;
	}

	~Platform(void)
	{
		Platform& temp = *this;
		instances.erase(std::find(instances.begin(), instances.end(), this));
	}

	void update(void) override;

	
private:

};

//instantiate static objects
vector<Platform*> Platform::instances = vector<Platform*>();
float Platform::top = 0; 

void Platform::update(void){}
