#pragma once
#include "GameObject.hpp"

class Wall : public GameObject
{
public:
	Wall(const sf::Texture& _texture, const sf::Vector2f & _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
	}
	void update() override;
};

void Wall::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->move({0,1});
	}
}
