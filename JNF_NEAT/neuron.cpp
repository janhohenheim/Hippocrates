#include "neuron.h"
#include <cmath>
#include <stdexcept>

Neuron::Neuron(const Connections& connections) :
connections(connections) {
}

void Neuron::AddConnection(IncommingConnection&& connection)
{
    if (connection.neuron == this || connection.neuron == nullptr) {
        throw std::invalid_argument("Invalid incomming connection");
    }
    connections.push_back(std::move(connection));
}

float Neuron::RequestDataAndGetActionPotential() {
    if (isSensor){
        return lastActionPotential;
    }

    float incomingPotentials = 0.0f;
    for (auto& in : connections){
        incomingPotentials += in.neuron->RequestDataAndGetActionPotential() * in.weight;
    }
    lastActionPotential = sigmoid(incomingPotentials);
    return lastActionPotential;
}

float Neuron::sigmoid(float d) {
    return (float)tanh(d);
}

void Neuron::SetInput(float input) {
    isSensor = true;
    lastActionPotential = input;
}

void Neuron::SetLayer(size_t layer) {
    if(layer > this->layer){
        this->layer = layer;
    }
}



