cmake_minimum_required(VERSION 3.0.0)
project(CppBasicTechnique LANGUAGES CXX VERSION 0.1.0)

# sub dir
add_subdirectory(c-pointer)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)