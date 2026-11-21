cmake_minimum_required(VERSION 3.20)
project(tinycol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tinycol_lib
    src/placeholder.cpp
)
target_include_directories(tinycol_lib PUBLIC include)
target_compile_options(tinycol_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(tinycol apps/main.cpp)
target_link_libraries(tinycol PRIVATE tinycol_lib)