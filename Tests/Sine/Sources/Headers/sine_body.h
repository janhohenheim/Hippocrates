// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/body.h"

namespace Hippocrates {
namespace Tests {
namespace Sine {

class SineBody: public IBody {
public:
	auto Reset() -> void override;
	auto Update(const std::vector<float>& networkOutputs) -> void override;
	auto HasFinishedTask() const -> bool override { return datasetsTested == 200; };
	auto GetFitness() const -> double override { return fitness; };

	auto ProvideNetworkWithInputs() const -> std::vector<float> override;

	auto GetInputCount() const -> std::size_t override { return 1; };
	auto GetOutputCount() const -> std::size_t override { return 1; };

	auto GetMaximumFitness() const -> double override { return 18000; }; // 10% error rate expected

private:
	std::size_t datasetsTested = 0;
	mutable float currentDataSet;
	double fitness = 0;
};

}
}
}
