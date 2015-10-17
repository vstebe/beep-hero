#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define LA_REF 440
#include "beep.h"

using namespace std;

int charToFreq(char c) {

    char azerty[] = {'a','z','e','r','t','y','u','i','o','p','q','s','d','f','g','h','j','k','l','m','w','x','c','v','b','n'};
    int index = 0;
    int octave = 0;
    for(int i=0; i<26; i++) {
        if(azerty[i] == c) {
            index = i;
            break;
        }
        if(azerty[i]-32 == c) {
            index = i;
            octave++;
            break;
        }
    }
    return LA_REF * pow(2, ((float)index+12*octave) / 12.f);

}

int main(int argc, char ** argv)
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML window with OpenGL", sf::Style::Default);

    bool native = false;
    if(argc == 2 && strcmp(argv[1], "native"))
        native = true;

    sf::Font font;
    font.loadFromFile("Niconne-Regular.ttf");
    sf::Text text("abc", font);
    text.setPosition(0,0);
    while(window.isOpen()) {
        window.clear(sf::Color::Black);
        sf::Event event;

        while (window.pollEvent(event))
               {
                   // Close window: exit
                   if (event.type == sf::Event::Closed)
                       window.close();

                   // Escape key: exit
                   if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                       window.close();

                   if(event.type == sf::Event::TextEntered) {
                       int freq;
                       if(native)
                        freq = ((char)event.text.unicode)*10;
                       else
                        freq = charToFreq((char)event.text.unicode);
                       startBeep(freq);
                       text.setString(std::to_string(freq) + "Hz");
                   }

                   if(event.type == sf::Event::KeyReleased) {
                       stopBeep();
                   }

               }
        window.draw(text);
        window.display();
    }

    stopBeep();
    return 0;
}

