#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

namespace tinycol {

enum class ColumnType { Int64, String };

struct Column {
    std::string name;
    ColumnType type;
    // The values: either all int64 or all strings
    std::variant<std::vector<int64_t>, std::vector<std::string>> values;
};

struct Table {
    std::vector<Column> columns;
    int64_t num_rows() const {
        if (columns.empty()) return 0;
        return std::visit([](const auto& v) { return static_cast<int64_t>(v.size()); }, columns[0].values);
    }
};

}