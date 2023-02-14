cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 17)

# executables
project(CLIENT)
set(TEST_CLIENT test_client)

# sources
# makes it easier to write down sources
set(GLOBVARS_PKG globvars/globvars.cpp globvars/globvars.h)
set(MODELS_PKG models/block/Block.h models/block/Block.cpp models/chunk/Chunk.cpp models/chunk/Chunk.h models/player/player.cpp models/player/player.h models/particle/Particle.h models/particle/Particle.cpp)
set(NET_PKG net/calls/calls.cpp net/calls/calls.h net/core/core.cpp net/core/core.h net/macros/macros.cpp net/macros/macros.h net/parser/parser.h net/parser/parser.cpp)
set(SOURCES ${GLOBVARS_PKG} ${MODELS_PKG} ${NET_PKG})



# executables
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} models/particle/Particle.cpp models/particle/Particle.h) # project
add_executable(${TEST_CLIENT} tests/test-requests.cpp ${SOURCES}) # main test client

# other tests
add_executable(test_calls net/calls/tests/test.cpp ${NET_PKG})
add_executable(test_models models/tests/block_chunk_test.cpp models/block/Block.h models/block/Block.cpp models/chunk/Chunk.h models/chunk/Chunk.cpp models/player/player.cpp models/player/player.h)
# perlin noise gen
add_executable(noise_gen tests/noise_gen/noise_gen.cpp ${SOURCES})
# chunk rendering
add_executable(chunk_rendering tests/chunk_rendering.cpp ${SOURCES})
#sfml shapes
add_executable(gui_test tests/sfml-test.cpp ${SOURCES})
add_executable(particle_test models/tests/particle_test.cpp models/particle/Particle.cpp models/particle/Particle.h models/particle/ParticleStream.cpp models/particle/ParticleStream.h)




# libraries
add_subdirectory(fmt)

# aliasing
set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)
set(ALL_LIBS fmt::fmt net ${SFML_LIBS})

# linking
target_link_libraries(${TEST_CLIENT} ${ALL_LIBS})
target_link_libraries(test_calls fmt::fmt)
target_link_libraries(test_models fmt::fmt ${SFML_LIBS})
target_link_libraries(noise_gen ${ALL_LIBS})
target_link_libraries(gui_test ${ALL_LIBS})
target_link_libraries(particle_test ${ALL_LIBS})
target_link_libraries(chunk_rendering ${ALL_LIBS})