#include "xml_parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::map<std::string, std::string>> XMLParser::parseFromFile(const std::string& filename) {
    std::vector<std::map<std::string, std::string>> employees;
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Error opening XML file." << std::endl;
        return employees;
    }

    std::string line;
    std::map<std::string, std::string> employee;
    bool inEmployeeBlock = false;
    
    while (std::getline(file, line)) {
        // Deleting spaces in the beggining and end of the line
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);
        
        if (line == "<employee>") {
            inEmployeeBlock = true;
            employee.clear();
        } else if (line == "</employee>") {
            inEmployeeBlock = false;
            employees.push_back(employee);
        } else if (inEmployeeBlock) {
            // Get data between tags
            size_t startTagPos = line.find('<');
            size_t endTagPos = line.find('>');
            size_t closeTagPos = line.rfind('<');

            if (startTagPos != std::string::npos && endTagPos != std::string::npos && closeTagPos != std::string::npos) {
                std::string key = line.substr(startTagPos + 1, endTagPos - startTagPos - 1);
                std::string value = line.substr(endTagPos + 1, closeTagPos - endTagPos - 1);
                employee[key] = value;
            }
        }
    }

    return employees;
}
