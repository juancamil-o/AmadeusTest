#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <vector>
#include <map>
#include <string>

class XMLParser {
public:
    static std::vector<std::map<std::string, std::string>> parseFromFile(const std::string& filename);
};

#endif // XML_PARSER_H
