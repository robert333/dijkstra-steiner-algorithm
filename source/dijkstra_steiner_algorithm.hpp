// dijkstra_steiner_algorithm.hpp
#include "Point3d.hpp"
#include "HananGrid3d.hpp"
#include "SteinerTree3d.hpp"

Point3d<int>::Vector parse_input(std::istream& instance);
SteinerTree3d<int> dijkstra_steiner_algorithm(std::istream& instance, std::size_t root_terminal = 0);
