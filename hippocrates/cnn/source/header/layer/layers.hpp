#pragma once
#include "ilayer.hpp"
#include <memory>
#include <vector>

namespace Convolutional::Layer {

	class Layers : public ILayer {

	public:
		using Layer_t = std::unique_ptr<ILayer>;

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

		explicit Layers(std::vector<Layer_t> layers)
		: layers{std::move(layers)}
		{ }

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

		auto ProcessMultiMatrix(const MultiMatrix& multiMatrix) -> MultiMatrix override {
			auto mm = multiMatrix;
			for (const auto &layer : layers)
				mm = layer->ProcessMultiMatrix(mm);

			return mm;
		}

		virtual auto GetDimensionalityAfterProcessing(MultiMatrix::Dimensionality dimensionality) const noexcept -> MultiMatrix::Dimensionality override {
			for (const auto &layer : layers)
				dimensionality = layer->GetDimensionalityAfterProcessing(dimensionality);

			return dimensionality;
		}

		auto Clone() const noexcept -> std::unique_ptr<ILayer> override { return std::make_unique<Layers>(*this); }

		auto& operator[](std::size_t i){return layers[i]; }
		const auto& operator[](std::size_t i) const {return layers[i]; }

		auto begin() { return layers.begin(); }
		const auto begin() const { return layers.begin(); }
		auto end() { return layers.end(); }
		const auto end() const { return layers.end(); }

		auto& front() {return layers.front(); }
		const auto& front() const {return layers.front(); }
		auto& back() {return layers.back(); }
		const auto& back() const {return layers.back(); }

		auto size() const {return layers.size(); }

	private:
		std::vector<Layer_t> layers;

	};

}
