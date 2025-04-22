#pragma once

#include "GameObject.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include <vector>
#include <iostream>

class ObjectManager 
{
public:
	ObjectManager();
	

	//~ObjectManager(void);
	void run(sf::RenderWindow& window);
	
protected:
	std::vector<GameObject*> objects;
};

ObjectManager::ObjectManager()
{
	objects.push_back(new Player(sf::Texture("Play.png"), { 400, 300 }, { 100,100 }));
	objects.push_back(new Platform(sf::Texture("Platform.png"), { 0, 500 }, { 1000, 1000 }));
	//add starting objects

}

void ObjectManager::run(sf::RenderWindow& window)
{
	for (GameObject* current : objects)
	{
		current->update();
		window.draw(*current);
	}
	//create new objects based on top platform
	//delete objects below lava

}

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

