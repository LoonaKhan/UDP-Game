cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

project(bin_data)

add_executable(test_block test_block.cpp block.cpp block.h)
add_executable(test_chunk test_chunk.cpp chunk.h chunk.cpp)
add_executable(test_client test_client.cpp block.h block.cpp chunk.cpp chunk.h)

add_subdirectory(fmt)

target_link_libraries(test_block fmt::fmt)
target_link_libraries(test_chunk fmt::fmt)