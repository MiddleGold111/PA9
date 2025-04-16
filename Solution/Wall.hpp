#include "GameObject.hpp"

class Wall : public GameObject
{
public:
	Wall(const sf::Texture& _texture)
	{
		sf::Sprite(_texture);
	}
	void update() override;
};

void Wall::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->move({2,0});
	}
}