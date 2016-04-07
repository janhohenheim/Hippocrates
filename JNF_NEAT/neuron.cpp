#include "neuron.h"
#include <cmath>

Neuron::Neuron(const Connections & connections) :
connections(connections) {

}

void Neuron::AddConnection(Neuron::IncomingConnection connection)
{
	connections.push_back(connection);
}

float Neuron::RequestDataAndGetActionPotential() {
    float actionPotential = 0.0;
    for (auto & in : connections){
        actionPotential += in.incoming->RequestDataAndGetActionPotential() * in.weight;
    }
    return sigmoid(actionPotential);
}

float Neuron::sigmoid(float d) {
    return (float)tanh(d);
}