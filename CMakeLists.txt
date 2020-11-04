cmake_minimum_required(VERSION 3.10)
project(LoggerScorpio LANGUAGES CXX)

add_compile_options(-Wall)
add_compile_options(-pedantic)

set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(spdlog REQUIRED)

set (
    SOURCES
    src/SPDLogWrapper.cpp
)

add_library (
    scorpio_log
    SHARED
    ${SOURCES} 
)

set_target_properties(scorpio_log PROPERTIES PUBLIC_HEADER include/ScorpioLog.hpp) 

target_link_libraries(scorpio_log PRIVATE spdlog::spdlog_header_only)

include (GNUInstallDirs)

install (
    TARGETS scorpio_log
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scorpio_log
)

install (
    DIRECTORY "${CMAKE_SOURCE_DIR}/src"
    DESTINATION "include/scorpio_log"
    FILES_MATCHING
    PATTERN "*.hpp"
)