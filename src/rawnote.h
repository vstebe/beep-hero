#ifndef RAWNOTE_H
#define RAWNOTE_H

#include "config.h"

class RawNote
{
public:
    RawNote(TYPE_NOTE typeNote, int octave);
    RawNote(TYPE_NOTE typeNote);
    RawNote();
    TYPE_NOTE getTypeNote() const;
    int getOctave() const;

protected:
    TYPE_NOTE _typeNote;
    int _octave;
};
#endif // RAWNOTE_H
