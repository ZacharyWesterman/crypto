# tests

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests/bin)

add_executable(run_tests src/main.cpp src/ciphers.cpp src/dictionary.cpp)

target_link_libraries(run_tests PRIVATE gcov dl ciphers helpers ${LIBZED_DIR})
