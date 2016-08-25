#pragma once
#include <vector>

namespace JNF_NEAT {

	class IBody	{
		public:
			IBody() = default;
			IBody(const IBody&) = default;
			IBody(IBody&&) = default;
			virtual ~IBody() = default;

            virtual auto operator=(const IBody&)& ->IBody& = default;
            virtual auto operator=(IBody&&)& -> IBody& = default;

			virtual auto Reset() -> void = 0;
			virtual auto Update(const std::vector<float>& networkOutputs) -> void = 0;
			virtual auto GetFitness() const -> double = 0;

			virtual auto ProvideNetworkWithInputs() const -> std::vector<float> = 0;
	};

}