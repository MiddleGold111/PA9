#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
//#include "Wall.hpp"
#include <vector>
#include <iostream>
#include "Lava.hpp"
#include <cstdlib>
#include <string>

using std::rand;

enum class status {Menu, Run, DeathMenu, End, PlayAgain };
//enum class status { Run, End};

class ObjectManager
{
public:
	
	ObjectManager();


	~ObjectManager(void)
	{
		for (size_t i = 0; i < objects.size();i++)
		{
			delete(objects[i]);
		}
		Platform::instances.clear();
		Platform::top = 0;
		Player::instance = nullptr;
		Lava::instance = nullptr;
	}

	void reset(void)
	{
		
		
		Platform::instances.clear();
		Player::instance = nullptr;
		/*if (Player::instance) {
			delete Player::instance;
		}*/
		
		
	}

	status run(sf::RenderWindow& window);
	
protected:
	std::vector<GameObject*> objects;
	sf::Texture playerTexture;
	sf::Texture platformTexture;
	sf::Texture lavaTexture;
	sf::Texture goldblockTexture;
	const sf::Font font;
	sf::Text scoreboard;
	bool endScreen;


	sf::SoundBuffer buffer;
	sf::Sound sound;
	
	int nextPlatform;

};



ObjectManager::ObjectManager() : font("theFont.ttf"), scoreboard(font), sound(buffer)
{

	if (!playerTexture.loadFromFile("Play.png")) std::cout << "Failed to load Play.png\n";
	if (!platformTexture.loadFromFile("Platform.png")) std::cout << "Failed to load Platform.png\n";
	if (!lavaTexture.loadFromFile("Lava3.png")) std::cout << "Failed to load Lava3.png\n";
	if (!goldblockTexture.loadFromFile("goldblock.png")) std::cout << "Failed to load goldblock.png\n";

	objects.push_back(new Player(playerTexture, { 400, 300 }, { 100,100 }));
	objects.push_back(new Platform(platformTexture, { 0, 500 }, { 1000, 1000 }));
	objects.push_back(new Lava(lavaTexture, { 0,1000 }, { 1000, 1000 }));

	nextPlatform = rand() % 4 + 9;
	//add starting objects
	for (int i = 0; i < 1070; i += 70)
	{
		objects.push_back(new Platform(goldblockTexture, { 0,(float)i }, { 70, 70 }));
		objects.push_back(new Platform(goldblockTexture, { 930,(float)i }, { 70, 70 }));
		/*if(nextPlatform == 0)
		{
			objects.push_back(new Platform(platformTexture, { 70, (float)i }, {50, 150}));
			nextPlatform = rand() % 4 + 9;
		}
		nextPlatform--;*/
	}
	endScreen = false;
	scoreboard.setStyle(sf::Text::Regular);
	scoreboard.setOutlineThickness(3.0f);



	
	buffer.loadFromFile("clang.mp3");
	sound.setBuffer(buffer);
	
	
}

status ObjectManager::run(sf::RenderWindow& window)
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
			window.draw(*current);

			if (current != Player::instance && current->getPosition().y > Lava::instance->getPosition().y)
			{
				//delete objects below lava
				delete(current);
				objects.erase(objects.begin() + i);

			}
			else
			{
				i++;
			}
		}

		//create new objects based on top platform
		//generate new platforms (and walls)
		if (Platform::top > Player::instance->getPosition().y - 700)
		{
			//walls
			objects.push_back(new Platform(goldblockTexture, { 0, Platform::top - 70 }, { 70, 70 }));
			objects.push_back(new Platform(goldblockTexture, { 930, Platform::top }, { 70, 70 }));

			//platforms
			if (nextPlatform == 0)
			{
				float platWidth;
				float platPos;
				int numPlats = rand() % 2 + 1;
				switch (numPlats)
				{
				case 1:
				{
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (860 - (int)platWidth) + 70);
					objects.push_back(new Platform(platformTexture, { platPos , Platform::top }, { platWidth, 50 }));
					break;
				}
				case 2:
				{
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (430 - (int)platWidth) + 70);
					objects.push_back(new Platform(platformTexture, { platPos , Platform::top }, { platWidth, 50 }));
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (430 - (int)platWidth) + 500); 
					objects.push_back(new Platform(platformTexture, {platPos , Platform::top}, {platWidth, 50}));
					break;
				}
				/*case 3:
				{
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (287 - (int)platWidth) + 70);
					objects.push_back(new Platform(platformTexture, { platPos , Platform::top }, { platWidth, 50 }));
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (287 - (int)platWidth) + 357);
					objects.push_back(new Platform(platformTexture, {platPos , Platform::top}, {platWidth, 50}));
					platWidth = (float)(rand() % 100 + 150);
					platPos = (float)(rand() % (287 - (int)platWidth) + 644);
					objects.push_back(new Platform(platformTexture, {platPos , Platform::top}, {platWidth, 50}));
					break;
				}*/
				}
				nextPlatform = rand() % 3 + 4;

			}
			nextPlatform--;
		}
		if (Player::instance->getPosition().y > Lava::instance->getPosition().y)
		{
			endScreen = true;
		}
		//update score color and lavaspeed
		if (Player::instance->getPosition().y < -40000 && Lava::instance->getSpeed()>-4.0f)
		{
			Lava::instance->setSpeed(-3.5f);
			scoreboard.setOutlineColor(sf::Color::Red);
			scoreboard.setFillColor(sf::Color::Black);
		}
		else if (Player::instance->getPosition().y < -25000 && Lava::instance->getSpeed()>-3.5f)
		{
			Lava::instance->setSpeed(-3.5f);
			scoreboard.setOutlineColor(sf::Color::Cyan);
			scoreboard.setFillColor(sf::Color::White);
		}
		else if (Player::instance->getPosition().y < -12500 && Lava::instance->getSpeed()>-3.0f)
		{
			Lava::instance->setSpeed(-3.0f);
			scoreboard.setOutlineColor(sf::Color::Magenta);
			scoreboard.setFillColor(sf::Color::Blue);
		}
		else if (Player::instance->getPosition().y < -5000 && Lava::instance->getSpeed()>-2.5f)
		{
			Lava::instance->setSpeed(-2.5f);

			scoreboard.setOutlineColor(sf::Color::Yellow);
			scoreboard.setFillColor(sf::Color::Green);
		}
		return status::Run;
	}
	else
	{
		//sound.play();



		return status:: DeathMenu;
		//
		//sf::Text text(font);
		//text.setCharacterSize(50);
		//text.setStyle(sf::Text::Regular);
		//text.setString("SKILL ISSUE\n score: " + std::to_string(-(int)Player::instance->getPosition().y + 487) + "\nPress escape to leave\nEnter to play again");
		//text.setPosition({ 450, Player::instance->getPosition().y });
		//window.draw(text);


		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		//{
		//	//window.close();
		//	return status::End;
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		//{
		//	
		//	return status::PlayAgain;
		//}
		////figure out replay

	}

}


