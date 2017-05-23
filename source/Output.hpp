// Output.hpp
#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

class Output {
public:

public:
	Output();

	virtual std::string to_string() const = 0;

private:

private:
	
};

std::ostream& operator<<(std::ostream& ostream, Output const& output);

#endif