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
    //sf::Texture testtext("Play.png");
    sf::Texture testtext("Play.png");
    sf::Texture lavatext("Lava3.png");
    sf::Texture platText("Platform.png");
    Wall firstWall(21, testtext, { 1000,1000 }, 70);
    
     
     Lava l(lavatext, { 70,990 }, { 930,1000 });
     AllPlatforms plat(1, 25, { 1000,1000 }, platText);
     Player p(testtext, { 400,875 }, { 100,100 }, plat);

    //ObjectManager O;
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        firstWall.update(p, window); 
       // wall2.update();
        p.update();
        l.update();
        window.clear();

        //O.start();
        /*for (int i = 0; i < 17; i++)
        {
            window.draw(O.getwall()[i]);
        }*/
        window.draw(l);
        firstWall.draw(window);
        plat.draw(window);
      //window.draw(firstWall);
     // window.draw(wall2);
        window.draw(p);
       // window.draw(l);
        window.display();

    }
}