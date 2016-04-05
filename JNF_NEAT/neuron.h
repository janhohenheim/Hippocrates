#pragma once
#include "incoming_connection.h"
#include "connectable_with_neurons.h"
#include <vector>

class Neuron : public ConnectableWithNeurons {
    public:
        Neuron() = delete;
        constexpr Neuron(const std::vector<IncomingConnection> & connections);
        ~Neuron() = default;
        Neuron(const Neuron & other) = default;

        double GetActionPotential() override;

    private:
        constexpr double sigmoid(double d);

        const std::vector<IncomingConnection> & connections;
};
