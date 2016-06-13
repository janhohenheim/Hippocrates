#include "neuron.h"
#include <cmath>
#include <stdexcept>

using namespace JNF_NEAT;
using namespace std;

Neuron::Neuron(const Connections& connections) :
connections(connections) {
}

void Neuron::AddConnection(IncomingConnection connection) {
    if (connection.neuron == this || connection.neuron == nullptr) {
        throw invalid_argument("Invalid incomming connection");
    }
    connections.push_back(move(connection));
}

float Neuron::RequestDataAndGetActionPotential() {
    float incomingPotentials = 0.0f;
    for (auto& in : connections){
        incomingPotentials += in.neuron->lastActionPotential * in.weight;
    }
    lastActionPotential = sigmoid(incomingPotentials);
    return lastActionPotential;
}

float Neuron::sigmoid(float d) {
    return (float)tanh(d);
}

void Neuron::SetInput(float input) {
    lastActionPotential = input;
}

void Neuron::SetLayer(size_t layer) {
    if(layer > this->layer){
        this->layer = layer;
    }
}