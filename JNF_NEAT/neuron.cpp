#include <cmath>
#include "neuron.h"

constexpr Neuron::Neuron(const std::vector<IncomingConnection> & connections) :
connections(connections) {

}

constexpr double Neuron::sigmoid(double d) {
    return tanh(d);
}

double Neuron::GetActionPotential() {
    double actionPotential = 0.0;
    for (auto & in : connections){
        actionPotential += sigmoid(in.connection->GetActionPotential() * in.weight);
    }
    return actionPotential;
}