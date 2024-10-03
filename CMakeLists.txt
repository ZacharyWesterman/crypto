# CMake minimum version required
cmake_minimum_required(VERSION 3.10)

# Project name and C++ standard
project(crypto)
set(CMAKE_CXX_STANDARD 17)

# Enable coverage flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi -fPIC --coverage")

# Specify the main source file
set(MAIN_SOURCE "crypto.cpp")

# Find other source files
file(GLOB_RECURSE OTHER_SRCS 
    "src/*.cpp"
    "src/ciphers/*.cpp"
    "src/helpers/*.cpp"
)

# Add the executable including the main source
add_executable(crypto ${MAIN_SOURCE} ${OTHER_SRCS})

# Link libraries, including gcov explicitly
target_link_libraries(crypto PRIVATE dl zed gcov)

# Custom command to clone or update the libzed repository
add_custom_target(
    fetch ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Fetching libzed..."
    COMMAND git -C ext/libzed pull || git clone https://github.com/ZacharyWesterman/libzed.git ext/libzed
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Custom command to build the libzed library
add_custom_target(
    build_libzed ALL DEPENDS fetch
    COMMAND make static dynamic -C ext/libzed -j32
)

# Custom command to install libzed
add_custom_target(
    install_libzed DEPENDS build_libzed
    COMMAND make install -C ext/libzed
)

# Custom target for cleaning up
add_custom_target(
    clean_crypto
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning project..."
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/crypto
    COMMAND ${CMAKE_COMMAND} -E remove -f ${CMAKE_BINARY_DIR}/*.o
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/src/* 
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/src/ciphers/* 
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/src/helpers/* 
    COMMAND ${CMAKE_COMMAND} -E echo "Cleaning tests..."
    COMMAND make clean -C tests
    COMMAND make clean -C tools
)

# Custom target to count files and lines of code
add_custom_target(
    count_files
    COMMAND ${CMAKE_COMMAND} -E echo "Analyzing files not in ./ext or ./tests/bin"
    COMMAND ${CMAKE_COMMAND} -E echo "Total File Count"
    COMMAND find . -type f -not -path "*/.git/*" | wc -l | sed 's/^/  /'
    COMMAND ${CMAKE_COMMAND} -E echo "Lines of Code (cpp, h, py)"
    COMMAND find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.py" \) ! -path "./ext/*" ! -path "./tests/bin" ! -name pugixml.cpp -exec wc -l {} +
)

# Custom command to build the tests
set(TESTS_DIR "${CMAKE_SOURCE_DIR}/tests")
add_custom_target(
    build_tests ALL
    COMMAND ${CMAKE_COMMAND} -E echo "Building tests..."
    COMMAND make -C ${TESTS_DIR}
)

# Custom command to run tests after they are built
add_custom_target(
    run_tests DEPENDS build_tests
    COMMAND ${CMAKE_COMMAND} -E echo "Running tests..."
    COMMAND ${CMAKE_COMMAND} -E execute_process(
        COMMAND ${TESTS_DIR}/bin/run_tests
        WORKING_DIRECTORY ${TESTS_DIR}/bin
    )
)

# Custom command to build tools
add_custom_target(
    build_tools ALL
    DEPENDS crypto
    COMMAND ${CMAKE_COMMAND} -E echo "Building tools..."
    COMMAND make -C tools
)

# Add the analyzer target for the tools
set(TOOLS_DIR "${CMAKE_SOURCE_DIR}/tools")
add_executable(wikiAnalyzer
    ${TOOLS_DIR}/analyzer/wikiAnalyzer.cpp
    ${OTHER_SRCS} # Include necessary source files for the analyzer
)
add_executable(randomAnalyzer
    ${TOOLS_DIR}/analyzer/randomAnalyzer.cpp
    ${OTHER_SRCS} # Include necessary source files for the analyzer
)
add_executable(caesarAnalyzer
    ${TOOLS_DIR}/analyzer/caesarAnalyzer.cpp
    ${OTHER_SRCS} # Include necessary source files for the analyzer
)

# Link necessary libraries for the analyzer, including gcov
target_link_libraries(wikiAnalyzer PRIVATE dl zed gcov)
target_link_libraries(randomAnalyzer PRIVATE dl zed gcov)
target_link_libraries(caesarAnalyzer PRIVATE dl zed gcov)
