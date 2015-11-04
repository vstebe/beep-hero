#ifndef RENDERING_H
#define RENDERING_H

#include <SFML/Graphics.hpp>
#include "sheet.h"

/**
 * @brief Rendering class used to display sheet
 */
class Rendering
{
public:
    /**
     * @brief Constructs the rendering and set the window
     * @param window
     */
    Rendering(sf::RenderWindow *window, Sheet * sheet);

    /**
     * @brief Handles the given event
     * @param event the event to handle
     */
    void input(const sf::Event& event);

    /**
     * @brief Do the actual rendering
     * @param time time since the last frame
     */
    void display(const sf::Time &time);

private:
    sf::RenderWindow * _window;
    Sheet * _sheet;
    sf::Time _time;
    sf::View _view;
    sf::RectangleShape _bar;

    std::vector<sf::RectangleShape> _rects;
};

#endif // RENDERING_H
