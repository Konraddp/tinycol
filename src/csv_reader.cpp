#include <tinycol/csv_reader.hpp>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {

// Splits a line at every occurrence of sep.
// An empty field at the end ("a,b,") is kept as an empty string.
std::vector<std::string> split(const std::string& line, char sep) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, sep)) {
        fields.push_back(field);
    }
    // getline drops a trailing empty field, so add it back explicitly
    if (!line.empty() && line.back() == sep) {
        fields.push_back("");
    }
    return fields;
}

// Removes a trailing '\r' (files created on Windows end lines with "\r\n").
void strip_cr(std::string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

}  // namespace

namespace tinycol {

Table read_csv(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    // Header line: column names
    std::string line;
    if (!std::getline(file, line)) {
        throw std::runtime_error("File is empty: " + path);
    }
    strip_cr(line);
    std::vector<std::string> names = split(line, ',');

    // Collect all values as text, one vector per column
    std::vector<std::vector<std::string>> raw(names.size());

    std::size_t line_no = 1;  // header is line 1
    while (std::getline(file, line)) {
        ++line_no;
        strip_cr(line);
        if (line.empty()) {
            continue;  // skip empty lines, e.g. at the end of the file
        }

        std::vector<std::string> fields = split(line, ',');
        if (fields.size() != names.size()) {
            throw std::runtime_error(
                path + ":" + std::to_string(line_no) + ": row has " +
                std::to_string(fields.size()) + " fields, expected " +
                std::to_string(names.size()));
        }
        for (std::size_t i = 0; i < fields.size(); ++i) {
            raw[i].push_back(std::move(fields[i]));
        }
    }

    // Temporary test output, remove later
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << names[i] << ": " << raw[i].size() << " values\n";
    }

    return Table{};
}

}  // namespace tinycol