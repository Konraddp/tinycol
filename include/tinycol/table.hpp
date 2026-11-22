#pragma once
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace tinycol {

enum class ColumnType { Int64, String };

struct Column {
    std::string name;
    ColumnType type;
    // The values: either all int64 or all strings
    std::variant<std::vector<int64_t>, std::vector<std::string>> values;

    std::size_t size() const {
        return std::visit([](const auto& v) { return v.size(); }, values);
    }
};

struct Table {
    std::vector<Column> columns;

    // All columns have the same length (enforced by add_column).
    std::size_t num_rows() const {
        if (columns.empty()) return 0;
        return columns[0].size();
    }

    std::size_t num_columns() const {
        return columns.size();
    }

    bool has_column(const std::string& name) const {
        for (const auto& col : columns) {
            if (col.name == name) {
                return true;
            }
        }
        return false;
    }

    const Column& column(const std::string& name) const {
        for (const auto& col : columns) {
            if (col.name == name) {
                return col;
            }
        }
        throw std::runtime_error("Column not found: " + name);
    }

    void add_column(Column col) {
        if (has_column(col.name)) {
            throw std::runtime_error("Duplicate column: " + col.name);
        }
        if (!columns.empty() && col.size() != num_rows()) {
            throw std::runtime_error(
                "Column '" + col.name + "' has " + std::to_string(col.size()) +
                " rows, expected " + std::to_string(num_rows()));
        }
        columns.push_back(std::move(col));
    }
};

}  // namespace tinycol