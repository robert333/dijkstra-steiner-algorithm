// test_dijkstra_steiner_algorithm.cpp
#include "catch/catch.hpp"

#include "../source/dijkstra_steiner_algorithm.hpp"

TEST_CASE("Computing Minimum Steiner Tree (Test 0)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "0\n";
//	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 1)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "1\n"
			 << "0 0 0\n";
//	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 2)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "2\n"
			 << "0 0 0\n"
			 << "1 1 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 3)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "3\n"
			 << "0 0 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 4)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "4\n"
			 << "0 0 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "0 2 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 5)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "5\n"
			 << "0 0 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "0 2 0\n"
			 << "1 3 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 6)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "6\n"
			 << "0 0 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "0 2 0\n"
			 << "1 3 0\n"
			 << "4 5 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 7)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "7\n"
			 << "0 0 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "0 2 0\n"
			 << "1 3 0\n"
			 << "4 5 0\n"
			 << "6 2 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Computing Minimum Steiner Tree (Test 10)", "[dijkstra_steiner_algorithm]" )
{
	std::stringstream instance;
	instance << "10\n"
			 << "0 4 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "0 2 0\n"
			 << "1 3 0\n"
			 << "4 5 0\n"
			 << "6 2 0\n"
			 << "1 8 0\n"
			 << "6 0 0\n"
			 << "9 2 0\n";
	dijkstra_steiner_algorithm(instance);
}

TEST_CASE("Same Steiner Tree length for different root terminals", "[dijkstra_steiner_algorithm]" )
{
	std::size_t const num_terminals = 5;

	std::stringstream instance;
	instance << num_terminals << "\n"
			 << "0 3 0\n"
			 << "1 1 0\n"
			 << "2 0 0\n"
			 << "6 0 0\n"
			 << "9 1 0\n";

	std::cout << "instance:\n" << instance.str() << "\n";

	std::vector<SteinerTree3d<int>> minimum_steiner_trees;

	for (std::size_t root_terminal = 0; root_terminal < num_terminals; ++root_terminal) {
		instance.clear();
		instance.seekg (0, std::ios::beg);
		minimum_steiner_trees.push_back(dijkstra_steiner_algorithm(instance, root_terminal));
	}

	for (std::size_t root_terminal = 1; root_terminal < num_terminals; ++root_terminal) {
		CHECK(minimum_steiner_trees.at(root_terminal).cost() == minimum_steiner_trees.at(0).cost());
		if (minimum_steiner_trees.at(root_terminal).cost() != minimum_steiner_trees.at(0).cost()) {
			minimum_steiner_trees.at(0).gnuplot_2d_data(std::cout);
			minimum_steiner_trees.at(root_terminal).gnuplot_2d_data(std::cout);
		}
	}
}
