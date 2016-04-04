#include "connectable_with_neurons.h"

constexpr void ConnectableWithNeurons::AddToActionPotential(double additionalActionPotential) {
    actionPotential += additionalActionPotential;
}

constexpr void ConnectableWithNeurons::Reset() {
    actionPotential = 0;
}


constexpr double ConnectableWithNeurons::GetActionPotential() {
    return actionPotential;
}

constexpr void ConnectableWithNeurons::AddToActionPotential(double additionalActionPotential) {

}

