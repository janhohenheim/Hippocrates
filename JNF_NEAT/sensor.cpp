#include "sensor.h"


void Sensor::SetInput(float input) {
    this->input = input;
}

float Sensor::RequestDataAndGetActionPotential() {
    return input;
}



