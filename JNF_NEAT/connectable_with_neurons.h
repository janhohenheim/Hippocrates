#pragma once

// TODO jnf
// Think about if we even want to use a template
// Complaint: This interface is too specific
// Alternative: Use Templates
class ConnectableWithNeurons {
    public:
		// TODO jnf
		// Maybe split this function
		// It does a tad too much
		virtual float RequestDataAndGetActionPotential() = 0;
};