// test_dijkstra_steiner_algorithm.cpp
#include "catch/catch.hpp"

#include "../source/dijkstra_steiner_algorithm.hpp"

#include <fstream>

TEST_CASE("Test Minimum Steiner Tree Instances", "[instances]" )
{
	struct Instance {
		std::string name;
		std::size_t minimum_cost;
	};

	std::vector<Instance> instances = {
		{"i02.sdtg", 971},
		{"i03.sdtg", 1932},
		{"i04.sdtg", 1645},
		{"i05.sdtg", 2235},
		{"i10.sdtg", 3504},
//		{"i20.sdtg", 5826}
	};

	std::string const instances_path = "../instances/";

	for (Instance const& instance : instances) {
		std::cout << "Compute instance " << instance.name << "...\n";

		std::ifstream file(instances_path + instance.name);

		assert(file.is_open());

		SteinerTree3d<int> const steiner_tree = dijkstra_steiner_algorithm(file);

		CHECK(steiner_tree.cost() == instance.minimum_cost);
	}
}
