#pragma once
#include "connectable_with_neurons.h"

struct IncomingConnection {
    ConnectableWithNeurons * connection;
    double weight = 1.0;
};