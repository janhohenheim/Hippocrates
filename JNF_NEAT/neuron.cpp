#include <cmath>
#include "neuron.h"

constexpr Neuron::Neuron(const std::vector<IncomingConnection> & connections) :
connections(connections) {

}

double Neuron::sigmoid(double d) const {
    return tanh(d);
}

double Neuron::RequestDataAndGetActionPotential() {
    double actionPotential = 0.0;
    for (auto & in : connections){
        actionPotential += sigmoid(in.connection->RequestDataAndGetActionPotential() * in.weight);
    }
    return actionPotential;
}