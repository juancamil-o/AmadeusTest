#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "json_parser.h"
#include "xml_parser.h"

// aux func to get the file extension
std::string getFileExtension(const std::string& filename) {
    size_t dotPos = filename.rfind('.');
    return (dotPos != std::string::npos) ? filename.substr(dotPos + 1) : "";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Use: " << argv[0] << " <file1.json/xml> <file2.json/xml> ..." << std::endl;
        return 1;
    }

    std::vector<std::map<std::string, std::string>> allEmployees;
    int highestSalary = 0;
    std::map<std::string, std::string> valuesHighestSalary;
    int totalSalary = 0;
    int salariesNumber = 0;
    // Iterar sobre cada archivo pasado como argumento
    for (int i = 1; i < argc; ++i) {
        std::string filename = argv[i];
        std::string extension = getFileExtension(filename);
        std::vector<std::map<std::string, std::string>> employees;
        

        if (extension == "json") {
            employees = JSONParser::parseFromFile(filename);
        } else if (extension == "xml") {
            employees = XMLParser::parseFromFile(filename);
        } else {
            std::cerr << "Error: file extension no supported (" << filename << "). Use JSON or XML." << std::endl;
            continue;
        }

        if (!employees.empty()) {
            allEmployees.insert(allEmployees.end(), employees.begin(), employees.end());
        }
    }

    if (allEmployees.empty()) {
        std::cout << "Not employees found in the file(s)." << std::endl;
        return 1;
    }

    for (const auto& emp : allEmployees) {
    
    for (const auto& [key, value] : emp) {
        if (key == "salary") { 
            int salary = std::stoi(value);
            totalSalary += salary;
            salariesNumber++;

            if (salary > highestSalary) {
                highestSalary = salary;
                valuesHighestSalary = emp;  
            }
        }
    }
}

    std::cout << "-------------------------" << std::endl;
    std::cout << "Salary Average:" << std::endl;
    std::cout << totalSalary/salariesNumber << std::endl;
    std::cout << "-------------------------" << std::endl;

    std::cout << "-------------------------" << std::endl;
    std::cout << "Employee with the highest Salary:" << std::endl;
    std::cout << "-------------------------" << std::endl;
    for (const auto& [key, value] : valuesHighestSalary) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
    std::cout << "-------------------------" << std::endl;

    std::vector<std::map<std::string, std::string>> sortedEmployees = allEmployees;

    // ordering employees by id in ascending order
    std::sort(sortedEmployees.begin(), sortedEmployees.end(), 
    [](const std::map<std::string, std::string>& a, 
       const std::map<std::string, std::string>& b) {
        return std::stoi(a.at("id")) < std::stoi(b.at("id"));
});

    std::cout << "Sorted Employees List:" << std::endl;
    for (const auto& emp : sortedEmployees) {
        std::cout << "-------------------------" << std::endl;
        for (const auto& [key, value] : emp) {
            std::cout << key << ": " << value << std::endl;
        }
    }

    return 0;
}
