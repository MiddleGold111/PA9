#pragma once
#include <SFML/Graphics.hpp>
//#include "Wall.hpp"
#include "Player.hpp"
#include "ObjectManager.hpp"
#include "Lava.hpp"
#include "Platforms.hpp"
#include <SFML/Audio.hpp>

int main()
{
    
    //add a background?

    int highscore = 0;


    std::srand(std::time(nullptr));
    status meep = status::Run;

    bool menu = true;

    const sf::Font font("theFont.ttf");
    sf::Text text(font);
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Regular);

   /* sf::Texture t;
    t.loadFromFile("goldblock.png");
    sf::Sprite s(t);*/

    
    //sound.play();

   






    sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");
    
    window.setFramerateLimit(120);
    ObjectManager* O = new ObjectManager;
    while (meep != status::End)
    {
        //sf::RenderWindow window(sf::VideoMode({ 1000, 1000 }), "THE GAME");
       // window.setFramerateLimit(120);
       // ObjectManager* O = new ObjectManager;

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
                    text.setPosition({ /*float(500 - ((text.getString().getSize() * 50) / 2))*/ 50 , window.getView().getCenter().y - 100 });
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {
                        meep = status::Run;
                        menu = false;

                    }
                }

                if (meep == status::DeathMenu)
                {

                    int score = -(int)Player::instance->getPosition().y + 487;
                    if (score > highscore)
                    {
                        highscore = score;
                    }
                    window.clear();
                    text.setString("SKILL ISSUE\nScore: " + std::to_string(score) + "\nHigh Score: " + std::to_string(highscore) + "\nPress escape to leave\nEnter to play again");

                   
                    text.setPosition({ 350, window.getView().getCenter().y -200 });/*Player::instance->getPosition().y */
                
                    window.draw(text);

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                    {
                        meep = status::End;
                        window.close(); //?
                        menu = false;

                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                    {
                        
                        delete O;

                        O = new ObjectManager();

                        meep = status::Run;
                   
                        menu = true;
                        
                    }





                }
                
            }
            else { // play the game

                //window.draw(s); //bs background

                meep = O->run(window);                

               if (meep == status::PlayAgain || meep == status::End)
                {
                   /*delete O;
                    window.close();*/
                   menu = true;
                }
            }    

            window.display();
        }
    }
    delete O;
    return 0;
   
    
   //window.close();

    //return 0;
}