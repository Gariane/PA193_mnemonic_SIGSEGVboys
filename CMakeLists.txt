cmake_minimum_required(VERSION 3.0)
project(PA193_mnenomic_SIGSEGVboys)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # using regular Clang or AppleClang or GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast")
    set(CMAKE_EXPORT_COMPILE_COMMANDS on)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # using Visual Studio C++
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /W4 /permissive-")
    add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

if (ENABLE_VALGRIND)
    find_program(VALGRIND_BIN valgrind)

    if(VALGRIND_BIN STREQUAL "VALGRIND_BIN-NOTFOUND")
        message(FATAL_ERROR "Valgrind is not installed!")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
endif()

if (ENABLE_COVERAGE) 
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
endif()

set(testBin "testsuite")
set(testSources "tests/test-main.cpp" "tests/test-utils.cpp" "tests/test-mnemonic.cpp" "tests/test-mnemonic-invalid.cpp" "tests/test-mnemonic-advanced.cpp")

set(libName "bip39")
set(libSources "src/mnemonic.cpp" "src/dictionary.cpp")

set(cliBin "cli")
set(cliSources "src/CLI.cpp")

find_package(OpenSSL REQUIRED)
include_directories(src tests)
add_library(${libName} ${libSources})
target_link_libraries(${libName} OpenSSL::SSL)

add_executable(${testBin} ${testSources})
target_link_libraries(${testBin} ${libName})

add_executable(${cliBin} ${cliSources})
target_link_libraries(${cliBin} ${libName})

add_custom_target(
    runtest
    COMMAND "./${testBin}"
    COMMENT "Running testsuite"
    DEPENDS "./${testBin}" 
  )



