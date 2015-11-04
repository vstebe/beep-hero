#include "rendering.h"
#include "utils.h"

#include <iostream>

#define NOTE_WIDTH 20

Rendering::Rendering(sf::RenderWindow *window, Sheet * sheet) :
    _bar(sf::Vector2f(window->getSize().x, 10.f))
{
    _window = window;
    _sheet = sheet;

    float time = 0.f;
    std::vector<Note> notes = sheet->getNotes();
    for(std::vector<Note>::const_iterator it = notes.begin(); it != notes.end(); it++) {
        float duration = Utils::getLength(*it, sheet->getTempo());

        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(NOTE_WIDTH, duration));
        rect.setPosition(NOTE_WIDTH * (it->getOctave()*12 + it->getTypeNote() - 12), -time-duration);
        rect.setFillColor(sf::Color(it->getOctave() *80, 50, 50));
        time += duration;

        _rects.push_back(rect);

        std::cout << it->getTypeNote() << " " << rect.getPosition().x << " " << rect.getPosition().y <<  " " << rect.getSize().x << " " << rect.getSize().y <<  std::endl;
    }
    _view.move(0, _window->getDefaultView().getSize().y * -1);
    _bar.setPosition(0, window->getSize().y/2-_bar.getSize().y/2);
}

void Rendering::display(const sf::Time &time) {
    _window->setView(_view);
    _time += time;

    _view.move(sf::Vector2f(0, -time.asMilliseconds()));

    for(std::vector<sf::RectangleShape>::iterator it = _rects.begin(); it != _rects.end(); it++) {
        _window->draw(*it);
    }

    _window->setView(_window->getDefaultView());
    _window->draw(_bar);
}
