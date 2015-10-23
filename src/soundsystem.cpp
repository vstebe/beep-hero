#include "soundsystem.h"
#include "beeper.h"

#include <iostream>

SoundSystem::SoundSystem(sf::Window * window) :
    _window(window),
    _currentOctave(3)
{

}

void SoundSystem::setWindow(sf::Window *window) {
    _window = window;
}

RawNote SoundSystem::map(const sf::Keyboard::Key &code) {

    switch (code) {
            case sf::Keyboard::Key::A:
                return RawNote(SOL_D, -1);
        case sf::Keyboard::Key::Q:
            return RawNote(LA, -1);
            case sf::Keyboard::Key::Z:
                return RawNote(LA_D, -1);
        case sf::Keyboard::Key::S:
            return RawNote(SI, -1);

        case sf::Keyboard::Key::D:
            return RawNote(DO, 0);
            case sf::Keyboard::Key::R:
                return RawNote(DO_D, 0);
        case sf::Keyboard::Key::F:
            return RawNote(RE, 0);
            case sf::Keyboard::Key::T:
                return RawNote(RE_D, 0);
        case sf::Keyboard::Key::G:
            return RawNote(MI, 0);
        case sf::Keyboard::Key::H:
            return RawNote(FA, 0);
            case sf::Keyboard::Key::U:
                return RawNote(FA_D, 0);
        case sf::Keyboard::Key::J:
            return RawNote(SOL, 0);
            case sf::Keyboard::Key::I:
                return RawNote(SOL_D, 0);
        case sf::Keyboard::Key::K:
            return RawNote(LA, 0);
            case sf::Keyboard::Key::O:
                return RawNote(LA_D, 0);
        case sf::Keyboard::Key::L:
            return RawNote(SI, 0);

    case sf::Keyboard::Key::M:
        return RawNote(DO, 1);
    //case sf::Keyboard::Key::D:
     //   return RawNote(DO, 0);

        default:
            return RawNote(SILENCE,0);
    }
}

void SoundSystem::setOctaveByKey(const sf::Keyboard::Key &key) {
    switch(key) {
        case sf::Keyboard::F1:
            _currentOctave = 0;
        break;
        case sf::Keyboard::F2:
            _currentOctave = 1;
        break;
        case sf::Keyboard::F3:
            _currentOctave = 2;
        break;
        case sf::Keyboard::F4:
            _currentOctave = 3;
        break;
        case sf::Keyboard::F5:
            _currentOctave = 4;
        break;
        case sf::Keyboard::F6:
            _currentOctave = 5;
        break;
    }
}

void SoundSystem::input(const sf::Event& event) {
    if(event.type == sf::Event::KeyPressed) {

        if(event.key.code >= sf::Keyboard::F1 && event.key.code <= sf::Keyboard::F6) {
            setOctaveByKey(event.key.code);
        } else {
            RawNote note = map(event.key.code);
            if(note.getTypeNote() != SILENCE) {
                //Start the beep
                float octave = _currentOctave + note.getOctave();
                float frequency = getFrequency(note.getTypeNote(), octave);
                Beeper::get().startBeep(frequency);
            }
        }
    } else if(event.type == sf::Event::KeyReleased) {

        RawNote note = map(event.key.code);
        if(note.getTypeNote() != SILENCE) {
            //Stop the beep
            float octave = _currentOctave + note.getOctave();
            float frequency = getFrequency(note.getTypeNote(), octave);
            Beeper::get().stopBeep(frequency);
        }
    }
}

float SoundSystem::getFrequency(TYPE_NOTE note, int octave) {
    int diffHalfTones = note - LA;
    diffHalfTones += octave * 12;

    float freq = LA_REF * pow(2, ((float)diffHalfTones) / 12.f);
    return freq;
}
