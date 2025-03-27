#include "json_parser.h"
#include <sstream>
#include <algorithm>

// Función para eliminar espacios en los bordes de un string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

// Función para extraer valores entre comillas (ej: "nombre": "John Doe")
std::string extractValue(const std::string& line) {
    size_t first = line.find("\"");
    size_t last = line.rfind("\"");
    if (first != std::string::npos && last != std::string::npos && first != last) {
        return line.substr(first + 1, last - first - 1);
    }
    return "";
}

// Parseador manual de JSON usando solo STL
std::vector<std::map<std::string, std::string>> JSONParser::parseFromFile(const std::string& filename) {
    std::vector<std::map<std::string, std::string>> employees;
    std::ifstream file(filename);
    
    if (!file) {
        std::cerr << "Error: No se pudo abrir el archivo JSON." << std::endl;
        return employees;
    }

    std::string line;
    std::map<std::string, std::string> employee;
    bool inEmployeeBlock = false;

    while (std::getline(file, line)) {
        line = trim(line);

        if (line == "\"employees\": [") {
            continue;
        }

        if (line == "{") {
            inEmployeeBlock = true;
            employee.clear();
            continue;
        }

        if (line == "},") {
            employees.push_back(employee);
            inEmployeeBlock = false;
            continue;
        }

        if (line == "}") {
            if (!employee.empty()) employees.push_back(employee);
            break; 
        }

        if (inEmployeeBlock) {
            size_t colonPos = line.find(":");
            if (colonPos != std::string::npos) {
                std::string key = extractValue(line.substr(0, colonPos));
                std::string value = extractValue(line.substr(colonPos + 1));

                // Si es un número, mantenerlo como string
                if (value.empty()) {
                    value = trim(line.substr(colonPos + 1));
                    if (value.back() == ',') value.pop_back(); // Remover coma final
                }

                employee[key] = value;
            }
        }
    }

    return employees;
}
