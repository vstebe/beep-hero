#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#define LA_REF 440
#include "beeper.h"
#include <string.h>
#include "soundsystem.h"
#include "rendering.h"
#include "sheetparser.h"

using namespace std;


int main(int argc, char ** argv)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "BeepHero", sf::Style::Default);

    SoundSystem sys(&window);

    sf::Event event;

    SheetParser parser("./data/soupe.sheet");

    Sheet sheet = parser.getSheet();

    Rendering rendering(&window, &sheet);

    window.setFramerateLimit(60);
    sf::Clock clock;
    //Render
    while(true) {
        sf::Time elapsed = clock.restart();
        if(window.pollEvent(event)) {
            sys.input(event);
        }
        window.clear();
        rendering.display(elapsed);
        window.display();
    }


    Beeper::get().stopBeep();
    return 0;
}

