# root

# Top level stuff
cmake_minimum_required(VERSION 3.15...3.30)

project(crypto VERSION 1.0
               DESCRIPTION "A cryptography program"
               LANGUAGES CXX)

# My stuff

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)     # For binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)   # For shared libraries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)   # For static libraries

add_library(ciphers
    src/ciphers/caesar.cpp src/ciphers/caesar.h
    src/ciphers/substitution.cpp src/ciphers/substitution.h
)

add_library(helpers
    src/helpers/dictionary.cpp src/helpers/dictionary.h
    src/helpers/parser.cpp src/helpers/parser.h
)

set(LIBZED_DIR "${CMAKE_SOURCE_DIR}/libs/libzed/libzed.a")

add_subdirectory(tools/analyzer)
add_subdirectory(tests)

add_executable(crypto crypto.cpp)

add_custom_target(test
    COMMAND ./tests/bin/run_tests
)

add_custom_target(install_libzed
    COMMAND cd libs && git clone https://github.com/ZacharyWesterman/libzed.git && cd libzed && make -j32 static
)

add_custom_target(update_libzed
    COMMAND cd libs/libzed/ && make clean && git pull && make -j32 static
)

target_link_libraries(crypto PRIVATE ciphers helpers ${LIBZED_DIR})
