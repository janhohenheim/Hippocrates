#pragma once
namespace Hippocrates::Utility {
 
class Interface {
public:
	Interface() = default;
	virtual ~Interface() = 0;
	Interface(const Interface&) = default;
	Interface(Interface&&) = default;

	Interface& operator=(const Interface &) = default;
	Interface& operator=(Interface &&) = default;
};

inline Interface::~Interface() {}

}