#pragma once
#include <string>
#include <vector>

namespace tinycol {
    std::vector<std::vector<std::string>> read_csv(const std::string& path);
}