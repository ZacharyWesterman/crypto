# tools

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools/update_dict/bin)

add_executable(update_dict update_dict.cpp)

target_link_libraries(update_dict PRIVATE helpers ${LIBZED_DIR})
