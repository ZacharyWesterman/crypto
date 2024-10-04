# tools

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/analyzer/bin)

add_executable(randomAnalyzer randomAnalyzer.cpp)
add_executable(caesarAnalyzer caesarAnalyzer.cpp)
add_executable(wikiAnalyzer wikiAnalyzer.cpp)

target_link_libraries(randomAnalyzer PRIVATE helpers ${LIBZED_DIR})
target_link_libraries(caesarAnalyzer PRIVATE ciphers helpers ${LIBZED_DIR})
target_link_libraries(wikiAnalyzer PRIVATE helpers ${LIBZED_DIR})
