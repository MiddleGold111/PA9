#pragma once
#include "GameObject.hpp"
#include <vector>
#include "Player.hpp"
 

class Platform : public GameObject
{
public:
	static vector<Platform*> instances;

	//WallBlock(const sf::Texture& _texture, const sf::Vector2f & _position, const sf::Vector2f& size) : GameObject(_texture, size)
	Platform(const sf::Texture& _texture, const sf::Vector2f& _position, const sf::Vector2f& size) : GameObject(_texture, size)
	{
		this->setPosition(_position);
		instances.push_back(this);
	}

	void update(void) override;

	
private:

};

vector<Platform*> Platform::instances = vector<Platform*>();


void Platform::update(void)
{
	int i = 0;
}



//class AllPlatforms
//{
//public:
//	AllPlatforms(int numPlatforms, float distance, sf::Vector2f winposition, const sf::Texture& newText) :  winpos(winposition), text(newText)
//	{
//		num = numPlatforms;
//		int originalX = 70;
//		int originalY = 900;
//
//		for (int i = 0; i < numPlatforms; i++)
//		{
//			if (i == 0)
//			{
//				Platform newPlatform(text, { 70,900 }, { 200,50 });
//				platforms.push_back(newPlatform);
//			}
//			else
//			{
//				sf::Vector2f priorpos = platforms[i - 1].getPosition();
//				float newsizeX = 200 + priorpos.x + 100;
//				float newsizeY = 50 + priorpos.y - 100;
//				Platform newPlatform(text, { newsizeX, newsizeY }, { 200,50 });
//				platforms.push_back(newPlatform);
//			}
//			
//		}
//	}
//	int getNum(void)
//	{
//		return num;
//	}
//	std::vector<Platform>& getVec(void)
//	{
//		return platforms;
//	}
//
//	void update(void)
//	{
//		int i = 0;
//	}
//
//	void draw(sf::RenderWindow& window);
//
//	
//private:
//	std::vector<Platform> platforms;
//	const sf::Texture& text;
//	sf::Vector2f winpos;
//	int num;
//};
//
//
//void AllPlatforms::draw(sf::RenderWindow& window)
//{
//	for (int i = 0; i < num; i++)
//	{
//		window.draw(platforms[i]);
//	}
//}