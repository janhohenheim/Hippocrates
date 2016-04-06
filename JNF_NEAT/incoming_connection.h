#pragma once
#include "connectable_with_neurons.h"

struct IncomingConnection {
    ConnectableWithNeurons * connection;
    float weight = 1.0f;
};