cmake_minimum_required(VERSION 3.0)
project(PA193_mnenomic_SIGSEGVboys)



if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # using regular Clang or AppleClang or GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast")
    set(CMAKE_EXPORT_COMPILE_COMMANDS on)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # using Visual Studio C++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4 /permissive-")
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()


include_directories(src tests)
add_library(bip39 src/mnemonic.hpp src/dictionary.hpp src/mnemonic.cpp)
add_executable(utilstest src/dictionary.hpp tests/utilstest.cpp tests/catch.hpp tests/tests-main.cpp)
target_link_libraries(utilstest bip39)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
