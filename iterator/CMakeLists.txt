cmake_minimum_required(VERSION 3.0.0)

set(TARGET_NAME iterator)

add_executable(${TARGET_NAME} 
    main_iterator.cpp
    iterator.hpp
    iterator.cpp
)

# コンパイラオプション
# https://cmake.org/cmake/help/latest/command/target_compile_options.html?highlight=target_compile_options
target_compile_options(${TARGET_NAME} PRIVATE
    # gcc
    $<$<CXX_COMPILER_ID:GNU>:-Wall -pedantic --pedantic-errors>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:-O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-O3>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:MinSizeRel>>:-Os>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:RelWithDebgInfo>>:-O2 -g>
    # clang & apple clang
    $<$<CXX_COMPILER_ID:Clang,AppleClang>:-Wall --pedantic-errors>
    $<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:Debug>>:-O0 -g>
    $<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:Release>>:-O3>
    $<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:MinSizeRel>>:-Os>
    $<$<AND:$<CXX_COMPILER_ID:Clang,AppleClang>,$<CONFIG:RelWithDebgInfo>>:-O2 -g>
    # msvc
    $<$<CXX_COMPILER_ID:MSVC>:/GR /EHsc /W4 /utf-8 /Zc:__cplusplus /bigobj> # /GR /EHsc /utf-8 /Zc:__cplusplus /bigobj
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/Ob0 /Od /MDd /Zi /RTC1>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/Ob2 /O2 /MD>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MinSizeRel>>:/O1 /MD>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebgInfo>>:/Od /MDd /Zi /RTC1>
)

# 定義済みマクロ
# https://cmake.org/cmake/help/latest/command/target_compile_definitions.html?highlight=target_compile_definitions
target_compile_definitions(${TARGET_NAME} PRIVATE
    # gcc
    $<$<CXX_COMPILER_ID:GNU>:>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Debug>>:>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:MinSizeRel>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:RelWithDebgInfo>>:>
    # clang & apple clang
    $<$<CXX_COMPILER_ID:Clang>:>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Debug>>:>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:Release>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:MinSizeRel>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:Clang>,$<CONFIG:RelWithDebgInfo>>:>
    # msvc
    $<$<CXX_COMPILER_ID:MSVC>:WIN32 _WINDOWS>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:MinSizeRel>>:NDEBUG>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebgInfo>>:>
)

# コンパイラ機能(指定した機能に対応するC++バージョンが自動で選ばれる)
# https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html
# https://cmake.org/cmake/help/latest/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html#prop_gbl:CMAKE_CXX_KNOWN_FEATURES
target_compile_features(${TARGET_NAME} PRIVATE
    # gcc
    $<$<CXX_COMPILER_ID:GNU>:cxx_std_20>
    # clang & apple clang
    $<$<CXX_COMPILER_ID:Clang,AppleClang>:cxx_std_20>
    # msvc
    $<$<CXX_COMPILER_ID:MSVC>:cxx_std_20>
)