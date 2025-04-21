#pragma once

#include "GameObject.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include <vector>
#include <iostream>

class ObjectManager 
{
public:
	ObjectManager()
	{
		std::cout << "created";
	}
	

	//~ObjectManager(void);

	void start(void);
	void run(void);
	
protected:
	std::vector<GameObject> objects;
	//Wall wall1[17];
	GameObject* top;
};

//void ObjectManager::start(void)
//{
//	sf::Texture testtext("phone.png");
//	sf::Texture* test = &testtext;
//	for (int i = 0; i < 17; i++)
//	{
//		wall1[i].setTexture(test);
//		sf::Vector2f position = {sf::Vector2f( 0, (810 - (50 * i))) };
//		wall1[i].setPosition( position );
//		wall1[i].setSize({ 50,50 });
//
//	}
//}

//this was breaking things

