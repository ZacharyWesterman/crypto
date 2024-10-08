# tools

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/analyzer/bin)

add_executable(randomAnalyzer randomAnalyzer.cpp)
add_executable(caesarAnalyzer caesarAnalyzer.cpp)
add_executable(wordSearchAnalyzer wordSearchAnalyzer.cpp)
add_executable(spellCheckAnalyzer spellCheckAnalyzer.cpp)

target_link_libraries(randomAnalyzer PRIVATE helpers ${LIBZED_DIR})
target_link_libraries(caesarAnalyzer PRIVATE ciphers helpers ${LIBZED_DIR})
target_link_libraries(wordSearchAnalyzer PRIVATE helpers ${LIBZED_DIR})
target_link_libraries(spellCheckAnalyzer PRIVATE helpers ${LIBZED_DIR})
