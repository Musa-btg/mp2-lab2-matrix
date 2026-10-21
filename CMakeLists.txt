cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME matrix_lab)
project(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(MP2_LIBRARY "${PROJECT_NAME}")
set(MP2_TESTS   "test_${PROJECT_NAME}")
set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Заголовочная библиотека (tmatrix.h - только заголовок)
add_library(${MP2_LIBRARY} INTERFACE)
target_include_directories(${MP2_LIBRARY} INTERFACE ${MP2_INCLUDE})

add_subdirectory(gtest)
add_subdirectory(samples)
add_subdirectory(test)

message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}")
message(STATUS "=====================================")
message(STATUS "")
message(STATUS "  Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "")