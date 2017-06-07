// debug.hpp
#ifndef DEBUG_HPP
#define DEBUG_HPP

#define NDEBUG

#include <cassert>
#include <iostream>
#include <vector>
#include <deque>

#ifdef NDEBUG
inline void debug_output(std::string const&)
{}
#else
inline void debug_output(std::string const& text)
{
	std::cout << text;
}
#endif

inline void output(std::string const& text)
{
	std::cout << text;
}

template<typename T>
void output(T const& object, std::string const& name = "")
{
	if (not name.empty()) {
		output(name + " = ");
	}

	std::cout << object << "\n";
}

template<typename T>
void output(std::vector<T> const& vector, std::string const& name = "")
{
	if (not name.empty()) {
		output(name + " = ");
	}

	output("{");

	if (not vector.empty()) {
		std::cout << vector[0];

		for (std::size_t i = 1; i < vector.size(); ++i) {
			std::cout << ", " << vector[i];
		}
	}

	output("}\n");
}

template<typename T>
void output(std::deque<T> const& vector, std::string const& name = "")
{
	if (not name.empty()) {
		output(name + " = ");
	}

	output("{");

	if (not vector.empty()) {
		std::cout << vector[0];

		for (std::size_t i = 1; i < vector.size(); ++i) {
			std::cout << ", " << vector[i];
		}
	}

	output("}\n");
}

#endif
