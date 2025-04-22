#pragma once
#include <SFML/Graphics.hpp>
//#include "Wall.hpp"
#include "Player.hpp"
#include "ObjectManager.hpp"
#include "Lava.hpp"
#include "Platforms.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");
    window.setFramerateLimit(120);
    //add a background?

    //sf::Texture testtext("Play.png");
    //sf::Texture lavatext("Lava3.png");
    //sf::Texture platText("Platform.png");
    //sf::Texture wally("goldblock.png");
    ObjectManager O;
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        
        window.clear();
        O.run(window);
        window.display();

    }
    
}