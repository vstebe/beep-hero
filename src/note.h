#ifndef NOTE_H
#define NOTE_H

#include "rawnote.h"

class Note : public RawNote
{
public:
    Note(LENGTH length, TYPE_NOTE typeNote, int octave);
    Note(LENGTH length, TYPE_NOTE typeNote);
    Note();
    LENGTH getLength() const;

private:
    LENGTH _length;
};

#endif // NOTE_H
