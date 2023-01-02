cmake_minimum_required(VERSION 3.22.1)


project(CLIENT)

add_executable(${PROJECT_NAME} main.cpp net/requests.cpp net/requests.h)
add_executable(test_client tests/test-requests.cpp)

target_link_libraries(test_client net)