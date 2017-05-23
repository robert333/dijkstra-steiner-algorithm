// debug.hpp
#ifndef DEBUG_HPP
#define DEBUG_HPP

//#define NDEBUG

#include <cassert>
#include <iostream>
#include <vector>
#include <deque>

//#define DEBUG

template<typename T>
void output(T const& object, std::string const& name = "")
{
	if (not name.empty()) {
		std::cout << name << " = ";
	}

	std::cout << object << "\n";
}

template<typename T>
void output(std::vector<T> const& vector, std::string const& name = "")
{
	if (not name.empty()) {
		std::cout << name << " = ";
	}

	std::cout << "{";

	if (not vector.empty()) {
		std::cout << vector[0];

		for (std::size_t i = 1; i < vector.size(); ++i) {
			std::cout << ", " << vector[i];
		}
	}

	std::cout << "}\n";
}

template<typename T>
void output(std::deque<T> const& vector, std::string const& name = "")
{
	if (not name.empty()) {
		std::cout << name << " = ";
	}

	std::cout << "{";

	if (not vector.empty()) {
		std::cout << vector[0];

		for (std::size_t i = 1; i < vector.size(); ++i) {
			std::cout << ", " << vector[i];
		}
	}

	std::cout << "}\n";
}

#endif
