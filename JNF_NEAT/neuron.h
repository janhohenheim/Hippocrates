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

        double RequestDataAndGetActionPotential() override;

    private:
        double sigmoid(double d) const;

        const std::vector<IncomingConnection> & connections;
};