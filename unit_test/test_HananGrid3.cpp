// test_HananGrid3.cpp
#include "catch/catch.hpp"

#include "../source/HananGrid3d.hpp"

TEST_CASE("Computing HananGrid3d (Test 1)", "[hanan_grid_3]" )
{
	Point3d<int>::Vector terminal_points {
		{0, 0, 0},
		{1, 2, 3},
		{4, 3, 1},
		{1, 1, 1},
		{4, 2, 0}
	};

	HananGrid3d<int> hanan_grid_3(terminal_points);

	CHECK(hanan_grid_3.num_terminals() == 5);
	CHECK(hanan_grid_3.num_x_coords() == 3);
	CHECK(hanan_grid_3.num_y_coords() == 4);
	CHECK(hanan_grid_3.num_z_coords() == 3);

	CHECK(hanan_grid_3.vertex(terminal_points.at(0)) == 0);
	CHECK(hanan_grid_3.vertex(terminal_points.at(1)) == 31);
	CHECK(hanan_grid_3.vertex(terminal_points.at(2)) == 23);
	CHECK(hanan_grid_3.vertex(terminal_points.at(3)) == 16);
	CHECK(hanan_grid_3.vertex(terminal_points.at(4)) == 8);

	std::map<Direction3d, std::vector<HananGrid3d<int>::Vertex>> has_no_neighbour;
	has_no_neighbour.insert({EAST, {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35}});
	has_no_neighbour.insert({WEST, {0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33}});
	has_no_neighbour.insert({NORTH, {9, 10, 11, 21, 22, 23, 33, 34, 35}});
	has_no_neighbour.insert({SOUTH, {0, 1, 2, 12, 13, 14, 24, 25, 26}});
	has_no_neighbour.insert({UP, {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35}});
	has_no_neighbour.insert({DOWN, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}});

	for (auto const& pair : has_no_neighbour) {
		for (HananGrid3d<int>::Vertex vertex_index : pair.second) {
			assert(not hanan_grid_3.has_neighbour(vertex_index, pair.first));
			CHECK(not hanan_grid_3.has_neighbour(vertex_index, pair.first));
		}
	}

	CHECK(hanan_grid_3.get_neighbour(16, EAST) == 17);
	CHECK(hanan_grid_3.get_neighbour(16, WEST) == 15);
	CHECK(hanan_grid_3.get_neighbour(16, NORTH) == 19);
	CHECK(hanan_grid_3.get_neighbour(16, SOUTH) == 13);
	CHECK(hanan_grid_3.get_neighbour(16, UP) == 28);
	CHECK(hanan_grid_3.get_neighbour(16, DOWN) == 4);
}
