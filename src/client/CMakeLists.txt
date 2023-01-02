cmake_minimum_required(VERSION 3.22.1)


project(CLIENT)

add_executable(${PROJECT_NAME} main.cpp net/requests/requests.cpp net/requests/requests.h)
add_executable(test_client tests/test-requests.cpp net/macros/macros.cpp net/macros/macros.h)

target_link_libraries(test_client net)