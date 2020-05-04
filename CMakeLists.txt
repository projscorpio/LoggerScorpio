cmake_minimum_required(VERSION 3.10)

project(LoggerScorpio LANGUAGES CXX)
set(PROJECT_NAME LoggerScorpio)

set(source_dir ${PROJECT_NAME}/src)
set(vendor_dir ${PROJECT_NAME}/vendor)

file(GLOB source_files "${source_dir}/*.cpp")
file(GLOB header_files "${source_dir}/*.hpp")

include_directories(${vendor_dir}/spdlog/include)

add_executable(${PROJECT_NAME} ${source_files} ${header_files})
