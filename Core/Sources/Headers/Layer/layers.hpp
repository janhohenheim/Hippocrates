#pragma once
#include "ilayer.hpp"

// Umbrella header part
#include "filters.hpp"
#include "fully_connected_neural_network.hpp"
#include "Pooler/max_pooler.hpp"
#include "relu.hpp"

#include <memory>
#include <vector>

namespace Convolutional::Layer {

	class Layers {

	public:
		template <typename ... Ts>
		explicit Layers(Ts&&... params) {
			// C++1z
			// static_assert((std::is_base_of<ILayer, Ts>::value && ...), "");

			layers.reserve(sizeof...(params));

			// See http://stackoverflow.com/questions/40300977/pass-a-list-of-deriveds-for-storage-as-member
			[[maybe_unused]]
			volatile int dummy[] =
			{ 0, (layers.emplace_back(std::make_unique<Ts>(std::forward<Ts>(params))), 0)... };
			// C++1z
			// layers.emplace_back(std::make_unique<Ts>(std::forward<Ts>(params))) && ...;
		}

		Layers(const Layers& other) {
			layers.reserve(other.layers.size());
			for (const auto& layer : other.layers) {
				layers.push_back(layer->Clone());
			}
		}

		Layers(Layers&& other) = default;

		Layers& operator=(const Layers& other) {
			layers.clear();
			layers.reserve(other.layers.size());
			for (const auto& layer : other.layers) {
				layers.push_back(layer->Clone());
			}
			return *this;
		}

		Layers& operator=(Layers&& other) = default;

		auto begin() { return layers.begin(); }
		const auto begin() const { return layers.begin(); }
		auto end() { return layers.end(); }
		const auto end() const { return layers.end(); }

		using Layer_t = std::unique_ptr<ILayer>;

	private:
		std::vector<Layer_t> layers;

	};

}