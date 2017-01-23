#pragma once

#ifdef __has_include
	#if __has_include(<optional>)
		#include <optional>
		#define OPTIONAL std::optional
	#elif __has_include(<experimental/optional>)
		#include <experimental/optional>
		#define OPTIONAL std::experimental::optional
	#endif
#else
	#include <optional>
	#define OPTIONAL std::optional
#endif

#include <stdexcept>

namespace Hippocrates::Utility {

	class const_error : public std::logic_error {
		using std::logic_error::logic_error;
	};

	template<typename T>
	class FillableRef {
	public:
		FillableRef(const T& ref) : asConstPointer {&ref} {}
		FillableRef(T& ref) : asPointer{ &ref } {}
		FillableRef(T&& value) : asValue( std::move(value) ) {}
		FillableRef(const T&& value) = delete;

		FillableRef& operator=(const FillableRef&)& = default;
		FillableRef& operator= (FillableRef&&)& = default;
		FillableRef& operator= (const FillableRef&&)& = delete;

		const auto& operator*() const { return Get(); }
		auto& operator*() { return Get(); }

		const auto& Get() const {
			if (asConstPointer)
			    return *asConstPointer;
			return const_cast<FillableRef*>(this)->Get();
		}
		auto& Get() { 
            if (asValue)
                return asValue.value();
            if (asPointer)
                return *asPointer;
            if (asConstPointer)
			    throw const_error("Tried to get non const reference from FillableRef containing a const value");
            throw std::runtime_error("Tried to get value out of empty FillableRef");
		}

	private:
		OPTIONAL<T> asValue;
		T* asPointer = nullptr;
		const T* asConstPointer = nullptr;
	};

}

#undef OPTIONAL