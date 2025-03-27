#include <iostream>
#include "json_parser.h"

int main() {
    auto employees = JSONParser::parseFromFile("../employees.json");

    std::cout << "Número de empleados: " << employees.size() << std::endl;
    for (const auto& emp : employees) {
        std::cout << "Empleado:\n";
        for (const auto& [key, value] : emp) {
            std::cout << "  " << key << ": " << value << std::endl;
        }
        std::cout << "-----------------\n";
    }

    return 0;
}
