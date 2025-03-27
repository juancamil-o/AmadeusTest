#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

class JSONParser {
public:
    static std::vector<std::map<std::string, std::string> > parseFromFile(const std::string& filename);
};

#endif // JSON_PARSER_H
