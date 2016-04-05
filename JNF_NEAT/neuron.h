#pragma once
#include "outgoing_connection.h"
#include "connectable_with_neurons.h"
#include <vector>

class Neuron : public ConnectableWithNeurons {
    public:
        Neuron() = delete;
        constexpr Neuron(const std::vector<OutgoingConnection> & connections);
        ~Neuron() = default;
        Neuron(const Neuron & other) = default;

        void FeedConnectedNeurons();

    private:
        constexpr double sigmoid(double d);

        const std::vector<OutgoingConnection> & connections;
};
