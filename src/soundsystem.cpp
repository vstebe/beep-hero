#include "soundsystem.h"
#include "beeper.h"

#include <iostream>

SoundSystem::SoundSystem(sf::Window * window) :
    _window(window),
    _thread(&SoundSystem::mainLoop, this),
    _currentOctave(3)
{

}


void SoundSystem::start() {
    _thread.launch();
}

SimpleNote SoundSystem::map(const sf::Keyboard::Key &code) {

    switch (code) {
            case sf::Keyboard::Key::A:
                return SimpleNote(SOL_D, -1);
        case sf::Keyboard::Key::Q:
            return SimpleNote(LA, -1);
            case sf::Keyboard::Key::Z:
                return SimpleNote(LA_D, -1);
        case sf::Keyboard::Key::S:
            return SimpleNote(SI, -1);

        case sf::Keyboard::Key::D:
            return SimpleNote(DO, 0);
            case sf::Keyboard::Key::R:
                return SimpleNote(DO_D, 0);
        case sf::Keyboard::Key::F:
            return SimpleNote(RE, 0);
            case sf::Keyboard::Key::T:
                return SimpleNote(RE_D, 0);
        case sf::Keyboard::Key::G:
            return SimpleNote(MI, 0);
        case sf::Keyboard::Key::H:
            return SimpleNote(FA, 0);
            case sf::Keyboard::Key::U:
                return SimpleNote(FA_D, 0);
        case sf::Keyboard::Key::J:
            return SimpleNote(SOL, 0);
            case sf::Keyboard::Key::I:
                return SimpleNote(SOL_D, 0);
        case sf::Keyboard::Key::K:
            return SimpleNote(LA, 0);
            case sf::Keyboard::Key::O:
                return SimpleNote(LA_D, 0);
        case sf::Keyboard::Key::L:
            return SimpleNote(SI, 0);

    case sf::Keyboard::Key::M:
        return SimpleNote(DO, 1);
    //case sf::Keyboard::Key::D:
     //   return SimpleNote(DO, 0);

        default:
            return SimpleNote(SILENCE,0);
    }
}

void SoundSystem::mainLoop() {
    sf::Event event;

    //For each event
    while(_window->waitEvent(event)) {
        if(event.type == sf::Event::KeyPressed) {
            SimpleNote note = map(event.key.code);
            float frequency = _currentOctave + note.offsetOctave;
            Beeper::get().startBeep(frequency);
        } else if(event.type == sf::Event::KeyReleased) {
            SimpleNote note = map(event.key.code);
            float frequency = _currentOctave + note.offsetOctave;
            Beeper::get().stopBeep(frequency);
        }
    }
}

float SoundSystem::getFrequency(TYPE_NOTE note, int octave) {
    int diffOctave =  octave - OCTAVE_REF;
    int diffHalfTones = note - LA;
    diffHalfTones += diffOctave * 12;

    float freq = LA_REF * pow(2, ((float)diffHalfTones) / 12.f);
    return freq;
}
