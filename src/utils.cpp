#include "utils.h"


std::vector<std::string> Utils::split(const std::string& constStr, const std::string& delimiter)
{
    std::string s = constStr;
    std::vector<std::string> res;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    return res;
}
