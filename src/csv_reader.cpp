#include <tinycol/csv_reader.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace {

std::vector<std::string> split(const std::string& line, char sep) {
    std::vector<std::string> fields;  
    std::stringstream ss(line);        
    std::string field;
    while (std::getline(ss, field, sep)) {
        fields.push_back(field);
    }
    return fields;
}

} 

namespace tinycol {

Table read_csv(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    std::string line;
    if (!std::getline(file, line)) {
        throw std::runtime_error("File is empty: " + path);
    }
    std::vector<std::string> names = split(line, ',');

    for (const auto& name : names) {
        std::cout << name << "\n"; 
    }

    return Table{};
}

}  // namespace tinycol