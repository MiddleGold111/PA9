#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GameObject : public sf::RectangleShape
{
public:
	sf::Texture* texture;
	GameObject(const sf::Texture& _texture, const sf::Vector2f &size) : sf::RectangleShape(size) 
	{ 
		texture = new sf::Texture(_texture);
		this->setTexture(texture); 
	}
	virtual void update() = 0;
};