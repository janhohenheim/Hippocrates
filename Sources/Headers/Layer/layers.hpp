#pragma once
#include "ilayer.hpp"
#include <memory>
#include <vector>

namespace Convolutional::Layer {

	class Layers {
	public:
		template <typename ... Ts>
		explicit Layers(Ts&&... params) {
			layers.reserve(sizeof...(params));

			// See http://stackoverflow.com/questions/40300977/pass-a-list-of-deriveds-for-storage-as-member
			[[maybe_unused]]
			volatile int dummy[] =
			{ 0, (layers.emplace_back(std::make_unique<Ts>(std::forward<Ts>(params))), 0)... };

		}

		auto begin() { return layers.begin(); }
		const auto begin() const { return layers.begin(); }
		auto end() { return layers.end(); }
		const auto end() const { return layers.end(); }

		using Layer_t = std::unique_ptr<ILayer>;
	private:
		std::vector<Layer_t> layers;
	};

}