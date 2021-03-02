cmake_minimum_required(VERSION 3.0.0)
project(CppBasicTechnique LANGUAGES CXX VERSION 0.1.0)

# C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")

# sub dir
add_subdirectory(c-pointer)
add_subdirectory(orient_object)
add_subdirectory(ndim_array)
add_subdirectory(heap_ndim_array)
add_subdirectory(iterator)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)