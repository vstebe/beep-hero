#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "rawnote.h"

class SoundSystem
{
public:


    /**
     * @brief Constructs the SoundSystem
     * @param window the SFML window to use for events
     */
    SoundSystem(sf::Window * window = NULL);

    /**
     * @brief Set to window to use for inputs
     */
    void setWindow(sf::Window * window);

    /**
     * @brief Start the SoundSystem by starting the internal thread
     */
    void start();

    /**
     * @brief Main loop of the Sound System. Handle events
     */
    void mainLoop();

    /**
     * @brief Map the key code to note type (ex key E -> Do)
     * @param code key code
     * @return note type (DO, RE etc) with octave offset
     */
    RawNote map(const sf::Keyboard::Key& code);

    /**
     * @brief Compute the frequency with the note and octave
     * @param note the given note
     * @param octave the given octave
     * @return associated frequency
     */
    float getFrequency(TYPE_NOTE note, int octave);

private:
    sf::Window * _window;
    sf::Thread _thread;
    int _currentOctave;
};

#endif // SOUNDSYSTEM_H
