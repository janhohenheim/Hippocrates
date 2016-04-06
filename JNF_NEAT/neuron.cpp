#include <cmath>
#include "neuron.h"

constexpr Neuron::Neuron(const std::vector<IncomingConnection> & connections) :
connections(connections) {

}

float Neuron::sigmoid(float d) const {
    return tanh(d);
}

float Neuron::RequestDataAndGetActionPotential() {
    float actionPotential = 0.0;
    for (auto & in : connections){
        actionPotential += sigmoid(in.connection->RequestDataAndGetActionPotential() * in.weight);
    }
    return actionPotential;
}