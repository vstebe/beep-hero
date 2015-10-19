#ifndef SHEET_H
#define SHEET_H

#include <vector>
#include "note.h"

class Sheet
{
public:
    Sheet(const std::vector<Note>& notes, int tempo);
    int getTempo();
    std::vector<Note> getNotes();

private:
    std::vector<Note> _notes;
    int _tempo;
};

#endif // SHEET_H
