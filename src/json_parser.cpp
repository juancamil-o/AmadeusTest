#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>


class JSONParser {
public:
    static std::vector<std::map<std::string, std::string>> parseFromFile(const std::string& filename) {
        std::ifstream file(filename);  

        if (!file.is_open()) {
            throw std::runtime_error("Error opening JSON " + filename);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();  // Cargar todo el archivo en un string
        file.close();

        return parseJSON(buffer.str());
    }

private:
    static std::vector<std::map<std::string, std::string>> parseJSON(const std::string& jsonStr) {
        std::vector<std::map<std::string, std::string>> data;
        std::map<std::string, std::string> obj;
        std::string key, value;

        bool inQuotes = false;
        bool readingKey = true;

        for (size_t i = 0; i < jsonStr.length(); i++) {
            char c = jsonStr[i];

            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (!inQuotes && (c == '{' || c == '[')) {
                obj.clear();
            } else if (!inQuotes && (c == '}' || c == ']')) {
                if (!obj.empty()) {
                    data.push_back(obj);
                }
            } else if (!inQuotes && c == ':') {
                readingKey = false;
            } else if (!inQuotes && (c == ',' || c == '\n')) {
                readingKey = true;
            } else {
                if (inQuotes) {
                    if (readingKey) {
                        key += c;
                    } else {
                        value += c;
                    }
                }
            }

            if (!readingKey && !inQuotes && (c == ',' || c == '}' || c == ']')) {
                obj[key] = value;
                key.clear();
                value.clear();
            }
        }

        return data;
    }

    
};



#endif // JSON_PARSER_H
