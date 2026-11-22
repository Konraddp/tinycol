#pragma once
#include <string>
#include <tinycol/table.hpp>

namespace tinycol {

Table read_csv(const std::string& path);

}  // namespace tinycol