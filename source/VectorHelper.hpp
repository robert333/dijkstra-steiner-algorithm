// VectorHelper.hpp
#ifndef VECTORHELPER_HPP
#define VECTORHELPER_HPP

#include <vector>
#include <algorithm>

template<typename T>
void sort(std::vector<T>& vector)
{
	std::sort(vector.begin(), vector.end());
}

template<typename T>
void sort_and_unique_and_erase(std::vector<T>& vector)
{
	sort(vector);
	vector.erase(std::unique(vector.begin(), vector.end()), vector.end());
}

template<typename T>
void append(std::vector<T>& vector_destination, std::vector<T> const& vector_append)
{
	vector_destination.insert(vector_destination.end(), vector_append.begin(), vector_append.end());
}

#endif
