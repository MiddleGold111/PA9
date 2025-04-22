#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
//#include "Wall.hpp"
#include <vector>
#include <iostream>
#include "Lava.hpp"

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
	objects.push_back(new Lava(sf::Texture("Lava3.png"), { 0,1000 }, { 1000, 1000 }));


	//add starting objects(
	for (int i = 0; i < 1070; i += 70)
	{
		objects.push_back(new Platform(sf::Texture("goldblock.png"), { 0,(float)i }, { 70, 70 }));
		objects.push_back(new Platform(sf::Texture("goldblock.png"), { 930,(float)i }, { 70, 70 }));
	}

}

void ObjectManager::run(sf::RenderWindow& window)
{
	for (GameObject* current : objects)
	{
		sf::View view = window.getView();
		view.setCenter({ 500, Player::instance->getPosition().y });
		window.setView(view);
		
		current->update();
		window.draw(*current);
	}
	//create new objects based on top platform
	//delete objects below lava

	//generate new platforms (and walls)
	if (Platform::top > Player::instance->getPosition().y - 700)
	{
		objects.push_back(new Platform(sf::Texture("goldblock.png"), { 0, Platform::top-70}, { 70, 70 }));
		objects.push_back(new Platform(sf::Texture("goldblock.png"), { 930, Platform::top}, { 70, 70 }));

	}
}


