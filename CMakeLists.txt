cmake_minimum_required(VERSION 3.10)

project(LoggerScorpio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)

add_compile_options(-Wall)
add_compile_options(-pedantic)

set(source_dir ${PROJECT_NAME}/src)
set(vendor_dir ${PROJECT_NAME}/vendor)

set (
    SOURCES
    ${source_dir}/Log.cpp
)
    

add_library (
    ${PROJECT_NAME} SHARED
    ${SOURCES} 
)
    
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${PROJECT_NAME}/include/ScorpioLog.hpp) 
    
target_include_directories(${PROJECT_NAME} PRIVATE ${source_dir} ${vendor_dir}/spdlog/include)

install (
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scorpio
)
install (
    DIRECTORY "${source_dir}"
    DESTINATION "include/scorpio"
    FILES_MATCHING
    PATTERN "*.hpp"
)