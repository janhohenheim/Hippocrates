#pragma once
#include "neuron.h"

class Sensor : public ConnectableWithNeurons {
    public:
        void SetInput(float input);
		float RequestDataAndGetActionPotential() override;
    private:
        float input;
};