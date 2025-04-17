#include <SFML/Graphics.hpp>

class GameObject : public sf::Sprite
{
public:
	GameObject();
	virtual void update() = 0;
};