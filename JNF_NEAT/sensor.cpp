#include "sensor.h"


void Sensor::SetInput(double input) {
    this->input = input;
}

double Sensor::GetActionPotential() {
    return input;
}



