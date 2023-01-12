cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

project(CLIENT)
set(TEST_CLIENT test_client)

add_executable(${PROJECT_NAME} main.cpp net/core/core.cpp net/core/core.h net/calls/calls.cpp net/calls/calls.h models/chunk/Chunk.cpp models/chunk/Chunk.h models/block/Block.cpp models/block/Block.h models/player/player.cpp models/player/player.h models/block/BlockSprite.cpp models/block/BlockSprite.h)
add_executable(${TEST_CLIENT} tests/test-requests.cpp net/macros/macros.cpp net/macros/macros.h net/parser/parser.cpp net/parser/parser.h net/calls/calls.cpp net/calls/calls.h models/chunk/Chunk.cpp models/chunk/Chunk.h models/player/player.cpp models/player/player.h models/block/Block.cpp models/block/Block.h)

# other tests
add_executable(test_calls net/calls/tests/test.cpp net/calls/calls.cpp net/calls/calls.h)
add_executable(test_models models/tests/test.cpp models/block/Block.h models/block/Block.cpp models/chunk/Chunk.h models/chunk/Chunk.cpp models/player/player.cpp models/player/player.h)


# libraries
add_subdirectory(fmt)

# linking
target_link_libraries(${TEST_CLIENT} net)
target_link_libraries(${TEST_CLIENT} fmt::fmt)
target_link_libraries(test_calls fmt::fmt)
target_link_libraries(test_models fmt::fmt)
