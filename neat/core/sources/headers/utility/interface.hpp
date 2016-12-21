#pragma once
namespace Hippocrates::Utility {
 
class Interface {
public:
	Interface() = default;
	virtual ~Interface() = 0;
	Interface(const Interface&) = default;
	Interface(Interface&&) = default;

	virtual Interface& operator=(const Interface &)& = default;
	virtual Interface& operator=(Interface &&)& = default;
};

inline Interface::~Interface() {}

}