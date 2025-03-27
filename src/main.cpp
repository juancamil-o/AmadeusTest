#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "json_parser.h"
#include "xml_parser.h"

// Función auxiliar para obtener la extensión del archivo
std::string getFileExtension(const std::string& filename) {
    size_t dotPos = filename.rfind('.');
    return (dotPos != std::string::npos) ? filename.substr(dotPos + 1) : "";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo.json/xml>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string extension = getFileExtension(filename);
    
    std::vector<std::map<std::string, std::string>> employees;

    if (extension == "json") {
        employees = JSONParser::parseFromFile(filename);
    } else if (extension == "xml") {
        employees = XMLParser::parseFromFile(filename);
    } else {
        std::cerr << "Error: Formato de archivo no soportado. Use JSON o XML." << std::endl;
        return 1;
    }

    if (employees.empty()) {
        std::cout << "No se encontraron empleados en el archivo " << filename << std::endl;
        return 1;
    }

    // Imprimir la lista de empleados
    std::cout << "Lista de empleados en " << filename << ":" << std::endl;
    for (const auto& emp : employees) {
        std::cout << "-------------------------" << std::endl;
        for (const auto& [key, value] : emp) {
            std::cout << key << ": " << value << std::endl;
        }
    }

    return 0;
}
