#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.hpp"
#include "Player.hpp"
#include "ObjectManager.hpp"
#include "Lava.hpp"
#include "Platforms.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "SFML works!");
    //add a background?

    sf::Texture testtext("Play.png");
    sf::Texture lavatext("Lava3.png");
    sf::Texture platText("Platform.png");
    sf::Texture wally("goldblock.png");
    Wall firstWall(21, wally, { 1000,1000 }, 70);
    
     
     Lava l(lavatext, { 70,990 }, { 930,1000 });
     AllPlatforms plat(1, 25, { 1000,1000 }, platText);
     Player p(testtext, { 400,875 }, { 100,100 }, plat.getVec());

    //ObjectManager O;
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        firstWall.update(p, window); 
       
        p.update();
        l.update();
        window.clear();

        
       
        window.draw(l);
        firstWall.draw(window);
        plat.draw(window);
     
        window.draw(p);
       
        window.display();

    }
}