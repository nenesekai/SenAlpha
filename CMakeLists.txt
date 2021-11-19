cmake_minimum_required(VERSION 3.0)

project(SenAlpha)

include(FetchContent)

find_package(date CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(xlnt CONFIG REQUIRED)

add_subdirectory(src)