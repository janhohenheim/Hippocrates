#pragma once
#include "connectable_with_neurons.h"

struct OutgoingConnection {
    ConnectableWithNeurons * connection;
    double weight = 1.0;
};