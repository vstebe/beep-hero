#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define LA_REF 440
#include "beeper.h"
#include <string.h>
#include "soundsystem.h"

using namespace std;


int main(int argc, char ** argv)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "BeepHero", sf::Style::Default);

    SoundSystem sys(&window);

    sf::Event event;

    window.setFramerateLimit(60);
    //Render
    while(true) {
        if(window.pollEvent(event)) {
            sys.input(event);
            window.clear();
            window.display();
        }
    }


    Beeper::get().stopBeep();
    return 0;
}

