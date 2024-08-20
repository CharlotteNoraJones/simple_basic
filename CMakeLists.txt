cmake_minimum_required(VERSION 3.10)

project(SimpleBasic)

find_package(raylib CONFIG REQUIRED)

add_executable(SimpleBasic src/main.cpp)

if (MSVC)
    target_compile_options(SimpleBasic PRIVATE /W4 /WX)
else()
    target_compile_options(SimpleBasic PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set_target_properties(SimpleBasic PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

target_link_libraries(SimpleBasic PRIVATE raylib)
