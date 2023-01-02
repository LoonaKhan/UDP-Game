cmake_minimum_required(VERSION 3.22.1)
project(net)
add_library(${PROJECT_NAME} core.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER core.h)
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/
        )