#include <cmath>
#include "neuron.h"

constexpr Neuron::Neuron(const std::vector<OutgoingConnection> & connections) :
connections(connections) {

}

void Neuron::FeedConnectedNeurons() {
    for(auto & connection : connections) {
        double output = sigmoid(GetActionPotential()) * connection.weight;
        connection.connection->AddToActionPotential(output);
    };
}

constexpr double Neuron::sigmoid(double d) {
    return tanh(d);
}






