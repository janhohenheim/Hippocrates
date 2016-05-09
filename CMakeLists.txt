cmake_minimum_required(VERSION 3.5)
project(JNF_NEAT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    JNF_NEAT/main.cpp
    JNF_NEAT/gene.h
    JNF_NEAT/gene.cpp
    JNF_NEAT/neural_network.h
    JNF_NEAT/neural_network.cpp
    JNF_NEAT/neural_network_trainer.h
    JNF_NEAT/neural_network_trainer.cpp
    JNF_NEAT/neuron.h
    JNF_NEAT/neuron.cpp
    JNF_NEAT/trainable.h
    JNF_NEAT/xor_solver.h
    JNF_NEAT/xor_solver.cpp
    JNF_NEAT/organism.h
    JNF_NEAT/organism.cpp
    JNF_NEAT/species.h
    JNF_NEAT/species.cpp
    JNF_NEAT/genome.h
    JNF_NEAT/genome.cpp)

add_definitions(-std=c++14)
add_executable(JNF_NEAT ${SOURCE_FILES})