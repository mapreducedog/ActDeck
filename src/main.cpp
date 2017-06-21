#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>//for sf::VideoMode
#include <SFML/Window.hpp> //for sf::RenderWindow
#include "cards.h"
#include <SFML/Graphics/Text.hpp>



int main(int argc, char **argv) {
    cards::initialize();
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop.width / 2, desktop.height / 2), "SFML works!");
    std::cout << desktop.width << " " << desktop.height << std::endl;
    std::string filename = "../data/1.json";
    cards::CardSprite a(cards::getJSON(filename));
    //sf::Text b = cards::create_text();
    sf::Event event;
    window.pollEvent(event);
    while (!(event.KeyPressed && event.key.code == sf::Keyboard::Q))
    {
        window.clear(sf::Color::White);
        window.pollEvent(event);
        a.draw(window);
        //window.draw(b);
        window.display();
    }
    //*/
    
    return 0;
    
}
