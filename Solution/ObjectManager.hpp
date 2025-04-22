#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
//#include "Wall.hpp"
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
		sf::View view = window.getView();
		current->update();
		window.draw(*current);
	}
	//create new objects based on top platform
	//delete objects below lava

}


