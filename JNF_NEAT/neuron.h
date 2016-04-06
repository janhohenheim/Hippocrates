#pragma once
#include "incoming_connection.h"
#include "connectable_with_neurons.h"
#include <vector>

class Neuron : public ConnectableWithNeurons {
    public:
        Neuron() = default;
        Neuron(const std::vector<IncomingConnection> & connections);
        ~Neuron() = default;
        Neuron(const Neuron & other) = default;

		inline void AddConnection(IncomingConnection connection);
		inline void AddConnections(std::vector<IncomingConnection> & connections);
		float RequestDataAndGetActionPotential() override;

    private:
		float sigmoid(float d) const;

        std::vector<IncomingConnection> connections;
};