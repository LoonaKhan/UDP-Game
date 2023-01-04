cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

project(CLIENT)
set(TEST_CLIENT test_client)

add_executable(${PROJECT_NAME} main.cpp net/core/core.cpp net/core/core.h)
add_executable(${TEST_CLIENT} tests/test-requests.cpp net/macros/macros.cpp net/macros/macros.h net/parser/parser.cpp net/parser/parser.h)


# libraries
add_subdirectory(fmt)

target_link_libraries(${TEST_CLIENT} net)
target_link_libraries(${TEST_CLIENT} fmt::fmt)
