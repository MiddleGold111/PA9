#pragma once
#include <SFML/Graphics.hpp>
//#include "Wall.hpp"
#include "Player.hpp"
#include "ObjectManager.hpp"
#include "Lava.hpp"
#include "Platforms.hpp"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");
    window.setFramerateLimit(120);*/
    //add a background?

    std::srand(std::time(nullptr));
    status meep = status::Run;

    bool menu = true;

    const sf::Font font("theFont.ttf");
    sf::Text text(font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Regular);

  //  sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");

    while (meep != status::End)
    {
        sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");
        window.setFramerateLimit(120);
        ObjectManager O;

        while (window.isOpen())
        {
            if (meep == status::DeathMenu) menu = true;
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) {

                    window.close();
                    exit(1);
                }
            }           

            window.clear();

            if (menu) 
            { // display the menu

                //either open screen or player death
                if (meep == status::Run)
                {
                    text.setString("Welcome to the game\nPress enter to start");
                    text.setPosition({ /*float(500 - ((text.getString().getSize() * 50) / 2))*/ 10 , 450 });
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {
                        meep = status::Run;
                        menu = false;

                    }
                }
                
                if (meep == status::DeathMenu)
                {
                    
                    text.setString("SKILL ISSUE\n score: " + std::to_string(-(int)Player::instance->getPosition().y + 487) + "\nPress escape to leave\nEnter to play again");
                    text.setPosition({ 450, 10 });/*Player::instance->getPosition().y */
                
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    {
                        meep = status::End;
                        window.close(); //?
                        menu = false;

                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {
                        meep = status::Run;
                        O.reset();
                        window.close();
                        menu = true;
                        
                    }




                }
                
            }
            else { // play the game

                meep = O.run(window);                

               if (meep == status::PlayAgain || meep == status::End)
                {
                    window.close();
                }
            }    

            window.display();
        }
    }
    
   
   
    
   //window.close();

    //return 0;
}