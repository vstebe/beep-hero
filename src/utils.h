#ifndef UTILS_H
#define UTILS_H
#include<string>
#include<vector>

#include "note.h"

class Utils
{
public :
    static std::vector<std::string> split(const std::string& s, char delim);
    static float getLength(const Note& note, float tempo);
};

#endif // UTILS_H
