#pragma once
#include "incomming_connection.h"
#include "connectable_with_neurons.h"
#include <vector>

class Neuron : public ConnectableWithNeurons {
    public:
        Neuron() = default;
        Neuron(const std::vector<IncommingConnection> & connections);
        ~Neuron() = default;
        Neuron(const Neuron & other) = default;

		inline void AddConnection(IncommingConnection connection);
		inline void AddConnections(std::vector<IncommingConnection> & connections);
		float RequestDataAndGetActionPotential() override;

    private:
		float sigmoid(float d) const;

        std::vector<IncommingConnection> connections;
};