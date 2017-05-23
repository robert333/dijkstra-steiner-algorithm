// Direction3d.hpp
#ifndef DIRECTION3D_HPP
#define DIRECTION3D_HPP

#include <array>

enum Direction3d {
	MIN_3D_DIRECTION = 0,
	EAST = 0,
	WEST,
	NORTH,
	SOUTH,
	UP,
	DOWN,
	NUM_3D_DIRECTIONS
};

inline std::array<Direction3d, NUM_3D_DIRECTIONS> directions_3d()
{
	return {EAST, WEST, NORTH, SOUTH, UP, DOWN};
}

#endif
