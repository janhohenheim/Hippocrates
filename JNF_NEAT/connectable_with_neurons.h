#pragma once

class ConnectableWithNeurons {
    public:
        virtual void AddToActionPotential(double additionalActionPotential);
        virtual void Reset();

        virtual double GetActionPotential();

    private:
        double actionPotential = 0.0;
};

