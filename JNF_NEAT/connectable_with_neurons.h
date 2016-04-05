#pragma once

class ConnectableWithNeurons {
    public:
        virtual double RequestDataAndGetActionPotential() = 0;
};

