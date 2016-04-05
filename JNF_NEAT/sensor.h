#pragma once
#include "neuron.h"

class Sensor : public ConnectableWithNeurons {
    public:
        void SetInput(double input);
        double RequestDataAndGetActionPotential() override;
    private:
        double input;
};

