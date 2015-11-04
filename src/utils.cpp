#include "utils.h"

#include <string>
#include <sstream>

std::vector<std::string> Utils::split(const std::string& s, char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


float Utils::getLength(const Note &note, float tempo) {
    float duration = 60000.f / tempo;

    switch(note.getLength())
            {
                case WHOLE:
                    duration = duration * 4;
                    break;
                case HALF:
                    duration = duration * 2;
                    break;
                case QUARTER:
                    duration = duration;
                    break;
                case EIGHTH:
                    duration = duration / 2.f;
                    break;
                case SIXTEENTH:
                    duration = duration / 4.f;
                    break;
                case THIRTYSECOND:
                    duration = duration / 8.f;
                    break;
                case WHOLE_POINT:
                    duration = duration * 6;
                    break;
                case HALF_POINT:
                    duration = duration * 3;
                    break;
                case QUARTER_POINT:
                    duration = duration * 1.5f;
                    break;
                case EIGHTH_POINT:
                    duration = (duration * 1.5f) / 2.f;
                    break;
                case SIXTEENTH_POINT:
                    duration = (duration * 1.5f) / 4.f;
                    break;
                case THIRTYSECOND_POINT:
                    duration = (duration * 1.5f) / 8.f;
                    break;
            }
    return duration;
}
