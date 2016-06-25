cmake_minimum_required(VERSION 3.5)
project(JNF_NEAT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(SOURCE_FILES
    JNF_NEAT_Examples/body.h
    JNF_NEAT_Examples/gene.cpp
    JNF_NEAT_Examples/gene.h
    JNF_NEAT_Examples/genome.cpp
    JNF_NEAT_Examples/genome.h
    JNF_NEAT_Examples/main.cpp
    JNF_NEAT_Examples/neural_network.cpp
    JNF_NEAT_Examples/neural_network.h
    JNF_NEAT_Examples/neural_network_trainer.cpp
    JNF_NEAT_Examples/neural_network_trainer.h
    JNF_NEAT_Examples/neuron.cpp
    JNF_NEAT_Examples/neuron.h
    JNF_NEAT_Examples/organism.cpp
    JNF_NEAT_Examples/organism.h
    JNF_NEAT_Examples/species.cpp
    JNF_NEAT_Examples/species.h
    JNF_NEAT_Examples/trained_neural_network.cpp
    JNF_NEAT_Examples/trained_neural_network.h
    JNF_NEAT_Examples/training_parameters.h
    README.md)

add_executable(JNF_NEAT ${SOURCE_FILES})
target_link_libraries(JNF_NEAT -lstdc++fs)
