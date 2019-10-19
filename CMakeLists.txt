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


# CLANG-TIDY
if(ENABLE_CLANG_TIDY)

    find_program(CLANG_TIDY_BIN clang-tidy)

    if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
        message(FATAL_ERROR "unable to locate clang-tidy")
    endif()

    list(APPEND CLANG_TIDY_BIN
        -clang-tidy-binary ${CLANG_TIDY_BIN}
        -header-filter=.*
    )

    add_custom_target(
        tidy
        COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
        COMMENT "running clang tidy"
    )

endif()
# END OF CLANG-TIDY


include_directories(src tests)
add_library(bip39 src/mnemonic.hpp src/dictionary.hpp src/mnemonic.cpp)
add_executable(testsuite src/dictionary.hpp tests/utilstest.cpp tests/catch.hpp tests/tests-main.cpp)
target_link_libraries(testsuite bip39)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
