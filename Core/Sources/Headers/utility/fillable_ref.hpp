#pragma once
#include <optional>

namespace Hippocrates::Utility {
	
	template<typename T>
	class MaybeShared {
		public:
			MaybeShared(T&&);

			auto IsShared() { return; }
			auto& Get() {}
			const auto& Get() const {}
	private:
		std::
	};

}