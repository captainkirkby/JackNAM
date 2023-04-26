cmake_minimum_required(VERSION 3.10)

project(JackNAM VERSION 0.0.1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

include_directories(SYSTEM deps/eigen)
include_directories(SYSTEM deps/NeuralAmpModelerCore/NAM)
include_directories(SYSTEM deps/NeuralAmpModelerCore/NAM)
include_directories(SYSTEM deps/json)
include_directories(SYSTEM deps/denormal)

add_executable(jack_nam src/main.cpp)

set(NAM_SOURCES ../deps/NeuralAmpModelerCore/NAM/activations.h
        ../deps/NeuralAmpModelerCore/NAM/activations.cpp
        ../deps/NeuralAmpModelerCore/NAM/version.h
        ../deps/NeuralAmpModelerCore/NAM/lstm.h
        ../deps/NeuralAmpModelerCore/NAM/lstm.cpp
        ../deps/NeuralAmpModelerCore/NAM/dsp.h
        ../deps/NeuralAmpModelerCore/NAM/dsp.cpp
        ../deps/NeuralAmpModelerCore/NAM/get_dsp.cpp
        ../deps/NeuralAmpModelerCore/NAM/util.cpp
        ../deps/NeuralAmpModelerCore/NAM/util.h
        ../deps/NeuralAmpModelerCore/NAM/wavenet.cpp
        ../deps/NeuralAmpModelerCore/NAM/wavenet.h
        ../deps/NeuralAmpModelerCore/NAM/convnet.cpp
        ../deps/NeuralAmpModelerCore/NAM/convnet.h)

add_library(neural_amp_modeler ${NAM_SOURCES})

source_group(NAM ${CMAKE_CURRENT_SOURCE_DIR} FILES ${NAM_SOURCES})

target_link_libraries(jack_nam PUBLIC neural_amp_modeler -ljack)
