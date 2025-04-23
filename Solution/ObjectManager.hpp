#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
//#include "Wall.hpp"
#include <vector>
#include <iostream>
#include "Lava.hpp"
#include <cstdlib>
#include <string>
#include "Fireballs.hpp"

using std::rand;

class ObjectManager 
{
public:
	ObjectManager();
	

	//~ObjectManager(void);
	void run(sf::RenderWindow& window);
	
protected:
	std::vector<GameObject*> objects;
	sf::Texture playerTexture;
	sf::Texture platformTexture;
	sf::Texture lavaTexture;
	sf::Texture goldblockTexture;
	const sf::Font font;
	sf::Text scoreboard;
	bool endScreen;
};

ObjectManager::ObjectManager() : font("theFont.ttf"), scoreboard(font)
{

	if (!playerTexture.loadFromFile("Play.png")) std::cout << "Failed to load Play.png\n";
	if (!platformTexture.loadFromFile("Platform.png")) std::cout << "Failed to load Platform.png\n";
	if (!lavaTexture.loadFromFile("Lava3.png")) std::cout << "Failed to load Lava3.png\n";
	if (!goldblockTexture.loadFromFile("goldblock.png")) std::cout << "Failed to load goldblock.png\n";
	//if (!goldblockTexture.loadFromFile("wall.png")) std::cout << "Failed to load goldblock.png\n";

	objects.push_back(new Player(playerTexture, { 400, 300 }, { 100,100 }));
	objects.push_back(new Platform(platformTexture, { 0, 500 }, { 1000, 1000 }));
	objects.push_back(new Lava(lavaTexture, { 0,1000 }, { 1000, 1000 }));


	/*objects.push_back(new Player(sf::Texture("Play.png"), { 400, 300 }, { 100,100 }));
	objects.push_back(new Platform(sf::Texture("Platform.png"), { 0, 500 }, { 1000, 1000 }));
	objects.push_back(new Lava(sf::Texture("Lava3.png"), { 0,1000 }, { 1000, 1000 }));*/


	//add starting objects(
	for (int i = 0; i < 1070; i += 70)
	{
		objects.push_back(new Platform(goldblockTexture, { 0,(float)i }, { 70, 70 }));
		objects.push_back(new Platform(goldblockTexture, { 930,(float)i }, { 70, 70 }));
	}
	endScreen = false;
	scoreboard.setStyle(sf::Text::Regular);
}

void ObjectManager::run(sf::RenderWindow& window)
{
	if (!endScreen)
	{

		sf::View view = window.getView();
		view.setCenter({ 500, Player::instance->getPosition().y });
		window.setView(view);

		//update scoreboard position
		scoreboard.setPosition({ 100, view.getCenter().y - (window.getSize().y / 2) + 10 });
		scoreboard.setString(std::to_string(-(int)Player::instance->getPosition().y +400));
		window.draw(scoreboard);

		//for (GameObject* current : objects)
		for (size_t i = 0; i < objects.size();)
		{
			GameObject* current = objects[i];


			current->update();
			if (i >= 3)
			{
				window.draw(*current);
			}
			

			if (current != Player::instance && current->getPosition().y > Lava::instance->getPosition().y)
			{
				delete(current);
				objects.erase(objects.begin() + i);
			}
			else
			{
				i++;
			}
		}
		for (int i = 0; i < 3; i++)
		{
			window.draw(*objects[i]);
		}
		//create new objects based on top platform
		//delete objects below lava

		//generate new platforms (and walls)
		if (Platform::top > Player::instance->getPosition().y - 700)
		{
			objects.push_back(new Platform(goldblockTexture, { 0, Platform::top - 70 }, { 70, 70 }));
			objects.push_back(new Platform(goldblockTexture, { 930, Platform::top }, { 70, 70 }));
			if ((int)Platform::top % 12 == 0)
			{
				//objects.push_back(new Platform(platformTexture, { (float)(rand() % 930 + 20), Platform::top }, { (float)(rand() % 50 + 200), 50 })); 
				
				////float width = (float)(rand() % 50 + 200);
				////float x = (float)(rand() % (int)(1000 - 70 * 2 - width) + 70); // between 70 and 930 - width

				////objects.push_back(new Platform(platformTexture, { x, Platform::top }, { width, 50 }));



				float width = static_cast<float>(rand() % 50 + 200); // 200 to 249 wide
				float minX = 100.0f;  // leave ~100px from left wall
				float maxX = 1000.0f - 100.0f - width; // leave ~100px from right wall based on width

				float x = static_cast<float>(rand() % static_cast<int>(maxX - minX)) + minX;

				objects.push_back(new Platform(platformTexture, { x, Platform::top }, { width, 50 }));

				objects.push_back(new FireBalls(lavaTexture, { (float)(rand()%500 +200), view.getCenter().y - 510}, {40,40}));
			}
		}

		

		if (Player::instance->getPosition().y > Lava::instance->getPosition().y)
		{
			endScreen = true;
		}
	}
	else
	{
		
		sf::Text text(font);
		text.setCharacterSize(50);
		text.setStyle(sf::Text::Regular);
		text.setString("SKILL ISSUE\n score: " + std::to_string(-(int)Player::instance->getPosition().y + 487));
		text.setPosition({ 450, Player::instance->getPosition().y });
		window.draw(text);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			window.close();
		}


	}

}


