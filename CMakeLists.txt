cmake_minimum_required(VERSION 3.5)
project(JNF_NEAT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(LIBRARY_NAME JNF_NEAT)
set(SOURCE_FILES
    JNF_NEAT/body.h
    JNF_NEAT/gene.cpp
    JNF_NEAT/gene.h
    JNF_NEAT/genome.cpp
    JNF_NEAT/genome.h
    JNF_NEAT/neural_network.cpp
    JNF_NEAT/neural_network.h
    JNF_NEAT/neural_network_trainer.cpp
    JNF_NEAT/neural_network_trainer.h
    JNF_NEAT/neuron.cpp
    JNF_NEAT/neuron.h
    JNF_NEAT/organism.cpp
    JNF_NEAT/organism.h
    JNF_NEAT/species.cpp
    JNF_NEAT/species.h
    JNF_NEAT/trained_neural_network.cpp
    JNF_NEAT/trained_neural_network.h
	JNF_NEAT/logger.cpp
	JNF_NEAT/logger.h
    JNF_NEAT/training_parameters.h
    )

add_library(${LIBRARY_NAME}
STATIC
${SOURCE_FILES})
target_link_libraries(JNF_NEAT -lstdc++fs)
