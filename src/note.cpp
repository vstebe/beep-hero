#include "note.h"

Note::Note(LENGTH length, TYPE_NOTE typeNote, int octave) : RawNote(typeNote, octave), _length(length) {}

Note::Note(LENGTH length, TYPE_NOTE typeNote) : RawNote(typeNote), _length(length) {}


Note::Note() :  RawNote(), _length(QUARTER) {}

LENGTH Note::getLength() const
{
    return _length;
}
