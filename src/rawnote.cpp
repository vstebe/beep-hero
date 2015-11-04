#include "rawnote.h"


RawNote::RawNote(TYPE_NOTE typeNote, int octave) : _typeNote(typeNote), _octave(octave) {}

RawNote::RawNote(TYPE_NOTE typeNote) : _typeNote(typeNote){}


RawNote::RawNote() :  _typeNote(LA), _octave(3) {}



TYPE_NOTE RawNote::getTypeNote() const
{
    return _typeNote;
}

int RawNote::getOctave() const
{
    return _octave;
}
