#include "neuron.h"
#include <cmath>

Neuron::Neuron(const Connections& connections) :
connections(connections) {

}

void Neuron::AddConnection(const Neuron::IncomingConnection& connection)
{
	connections.push_back(connection);
}

void Neuron::AddConnection(Neuron::IncomingConnection&& connection)
{
	connections.push_back(connection);
}

float Neuron::RequestDataAndGetActionPotential() {
    if (isSensor){
        return lastActionPotential;
    }

    float incomingPotentials = 0.0f;
    for (auto& in : connections){
        incomingPotentials += in.incoming->RequestDataAndGetActionPotential() * in.weight;
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