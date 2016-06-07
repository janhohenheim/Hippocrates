#include "neural_network_streamer.h"

std::string NeuralNetworkStreamer::GetString(const NeuralNetwork & net)
{
	std::string genomeString;
	for (auto& gene : net.GetGenome()) {
		genomeString +=
			"Gene with marking #" + std::to_string(gene.historicalMarking) + ":\n"
			+ "\t	from: " + std::to_string(gene.from) + "\n"
			+ "\t	to: " + std::to_string(gene.to) + "\n"
			+ "\t	weight: " + std::to_string(gene.weight) + "\n"
			+ "\t	is enabled: " + std::to_string(gene.isEnabled) + "\n\n";
	}
	return genomeString;
}
