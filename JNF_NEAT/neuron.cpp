#include <cmath>
#include "neuron.h"

Neuron::Neuron(const std::vector<IncommingConnection> & connections) :
connections(connections) {

}

float Neuron::sigmoid(float d) const {
    return (float)tanh(d);
}

float Neuron::RequestDataAndGetActionPotential() {
    float actionPotential = 0.0;
    for (auto & in : connections){
        actionPotential += sigmoid(in.connection->RequestDataAndGetActionPotential() * in.weight);
    }
    return actionPotential;
}

void Neuron::AddConnection(IncommingConnection connection) {
    connections.push_back(connection);
}

void Neuron::AddConnections(std::vector<IncommingConnection> & connections) {
    connections.insert( connections.end(), connections.begin(), connections.end() );
}