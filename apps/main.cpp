#include <tinycol/csv_reader.hpp>
#include <exception>
#include <iostream>

int main() {
    try {
        tinycol::read_csv("tests/data/sample.csv");
    } catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}