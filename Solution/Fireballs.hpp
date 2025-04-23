#include "GameObject.hpp"
#include "Platforms.hpp"


class FireBalls : public GameObject
{
public:
	//Player(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	FireBalls(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
		velocity = { 0,0 };
		gravity = 0.05f;

		lr = rand() % 2 + 1;
	}

	bool checkCollision()
	{

		bool collided = false;
		for (Platform* platform : Platform::instances)
		{
			CollisionDirection dir = (*platform).collide(*this);
			if (dir == CollisionDirection::Left)
			{
				lr = 2;
			}
			if (dir == CollisionDirection::Right)
			{
				lr = 1;
			}
			/*if (dir == CollisionDirection::Bottom && velocity.y < 0)
			{
				velocity.y = 0;
			}*/
			/*if (dir != CollisionDirection::None)
			{
				collided = true;
			}*/

		}
		/*if (!collided)
		{
			velocity.y += gravity;
		}*/
		return collided;
	}


	void update() override
	{
		checkCollision();
		if (lr == 1)
		{
			this->move({-1, 0});
		}
		else if (lr == 2)
		{
			this->move({ 1, 0 });
		}

		velocity.y += gravity;
		this->move({ 0, velocity.y });

		
	}
	
private:
	sf::Vector2f velocity;
	float gravity;
	int lr;
	//bool grounded;

};

