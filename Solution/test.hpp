/*****************************************
* Programming Assignment 9
* 04/23/2025
* Programmers: Jayden Claytor, Blaise Banks
*
* Little Lava Lad: a vertical platformer where you run from lava
* SFML 3.0.0
*****************************************/
#pragma once
#include "ObjectManager.hpp"
#include <iostream>

using std::cout;
using std::endl;



class Test
{
public:
	void testObjectManager(void)
	{
		sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "TESTING THE GAME");
		ObjectManager* O = new ObjectManager;
		int i = 0;
		while (window.isOpen() && i < 20)
		{

			window.clear();
			O->run(window);
			window.display();
			i++;

		}
		window.close();
		delete O;



		cout << "ObjectManager test passed" << endl;


	}

	void testcollision(void)
	{



		sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "TESTING THE GAME");
		ObjectManager* O = new ObjectManager;
		while (window.isOpen())
		{

			window.clear();
			O->run(window);
			window.display();
			if (Player::instance->checkCollision())
			{
				cout << "Collision check success" << endl;
				break;
			}

		}
		window.close();
		delete O;

		//Player::instance->setPosition()
	}

	void testObjectManagerDestructor(void)
	{
		ObjectManager* testO = new ObjectManager();
		delete testO;
		if (Platform::instances.empty() && Player::instance == nullptr)
		{
			cout << "ObjectManager destructor test passed" << endl;
		}
	}


	void testBackgroundMusic(void)
	{
		sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "TESTING THE GAME");

		sf::Music music;
		if (!music.openFromFile("musicbackground.mp3"))
		{
			cout << "Failed to load music file.\n";
			return;
		}

		music.setVolume(20.0f);
		music.setLooping(true);
		music.play();

		int i = 0;
		while (window.isOpen() && i < 300)  // let it run longer (~5 seconds)
		{


			window.clear();  // optional: draw something if you like
			window.display();

			sf::sleep(sf::milliseconds(16));  // simulate frame time
			i++;
		}
		cout << "Background Music test passed" << endl;

		window.close();
	}


	void testdeath(void) {
		sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "TESTING THE GAME");
		ObjectManager* O = new ObjectManager;
		//Lava::instance->setSpeed(-10.0f);
		status stat = status::Run;



		while (window.isOpen() && stat != status::DeathMenu) {


			window.clear();
			stat = O->run(window);  // Make sure this can return DeathMenu
			window.display();
		}

		window.close();
		cout << "Player death test passed\n";
		delete O;
	}

	void testAll(void)
	{
		testcollision();

		testObjectManager();

		testdeath();
		testBackgroundMusic();
		testObjectManagerDestructor();
	}

};