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

# i tak jest tam wszystko, wiec osobny header tylko by imo zasmiecal
# chcociaz jak teraz mysle, to jednak chyba potem go dodam
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${source_dir}/Log.hpp) 

target_include_directories(${PROJECT_NAME} PRIVATE ${source_dir} ${vendor_dir}/spdlog/include)

install (
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/scorpio
)