#pragma once
#include "neuron.h"

class Sensor : public ConnectableWithNeurons {
    public:
        void SetInput(double input);
        double GetActionPotential() override;
    private:
        double input;
};

