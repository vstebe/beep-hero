#ifndef SHEETPARSER_H
#define SHEETPARSER_H

#include <string>
#include <iostream>
#include <vector>
#include "sheet.h"

class SheetParser
{
private:
    std::string _fileName;
    Sheet * _sh;
    std::iostream * _file;
    Note getNote(std::string ligne);
    int numLigne;

public:
    SheetParser();
    SheetParser(std::string fileName);
    Sheet getSheet();


};


#endif // SHEETPARSER_H
