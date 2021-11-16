cmake_minimum_required(VERSION 3.0)

project(SenAlpha)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(xlnt CONFIG REQUIRED)
find_package(date CONFIG REQUIRED)

add_subdirectory(src)