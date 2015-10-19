#include "sheet.h"

Sheet::Sheet(const std::vector<Note> &notes, int tempo)
{
    _notes = notes;
    _tempo = tempo;
}

std::vector<Note> Sheet::getNotes()
{
    return _notes;
}

int Sheet::getTempo()
{
    return _tempo;
}
