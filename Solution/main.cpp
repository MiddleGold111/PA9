#include <SFML/Graphics.hpp>
#include "Wall.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 800 }), "SFML works!");
    sf::Texture testtext("phone.png");
    Wall test(testtext, { 0,-2000 }, {200,200});
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        test.update();
        window.clear();
        window.draw(test);
        window.display();

    }
}