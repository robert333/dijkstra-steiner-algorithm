// HananGrid3d.hpp
#ifndef HANANGRID3D_HPP
#define HANANGRID3D_HPP

#include <map>
#include "Point3d.hpp"
#include "VectorHelper.hpp"
#include "Direction3d.hpp"

template<typename Coord>
class HananGrid3d {
public:
	using Vertex = std::size_t;
	using Index = std::size_t;
	using Value = int;

public:
	HananGrid3d(std::vector<Point3d<Coord>> const& terminal_points);

	Vertex num_terminals() const;

	Vertex num_x_coords() const;
	Vertex num_y_coords() const;
	Vertex num_z_coords() const;

	Vertex vertex(Index const& terminal) const;
	Vertex vertex(Point3d<Coord> const& point) const;

	Point3d<Coord> point(Vertex const vertex) const;

	Value distance_to_neighbour(Vertex const vertex, Direction3d const direction) const;
	Value distance_to_neighbour(Vertex const vertex, Direction3d const direction, Vertex const neighbour) const;

	bool has_neighbour(Vertex const vertex_index, Direction3d const direction) const;
	Vertex get_neighbour(Vertex const vertex_index, Direction3d const direction) const;
	bool get_neighbour(Vertex const vertex_index, Direction3d const direction, Vertex& neighbour, Value& distance) const;

private:
	void compute();

	Index compute_x_index(Vertex const vertex) const;
	Index compute_y_index(Vertex const vertex) const;
	Index compute_z_index(Vertex const vertex) const;

	Coord compute_x_coord(Vertex const vertex) const;
	Coord compute_y_coord(Vertex const vertex) const;
	Coord compute_z_coord(Vertex const vertex) const;

private:
	std::vector<Point3d<Coord>> _terminal_points;

	std::vector<Vertex> _terminal_to_vertex;

	std::vector<Coord> _x_coords;
	std::vector<Coord> _y_coords;
	std::vector<Coord> _z_coords;

	std::map<Coord, Index> _x_coord_to_index;
	std::map<Coord, Index> _y_coord_to_index;
	std::map<Coord, Index> _z_coord_to_index;
};

template<typename Coord>
HananGrid3d<Coord>::HananGrid3d(std::vector<Point3d<Coord>> const& terminal_points) :
	_terminal_points(terminal_points),
	_terminal_to_vertex(terminal_points.size()),
	_x_coords(terminal_points.size()),
	_y_coords(terminal_points.size()),
	_z_coords(terminal_points.size())
{
	compute();
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::num_terminals() const
{
	return _terminal_points.size();
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::num_x_coords() const
{
	return _x_coords.size();
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::num_y_coords() const
{
	return _y_coords.size();
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::num_z_coords() const
{
	return _z_coords.size();
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::vertex(Index const& terminal) const
{
	return _terminal_to_vertex.at(terminal);
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::vertex(Point3d<Coord> const& point) const
{
	return _x_coord_to_index.at(point.x())
		   + _y_coord_to_index.at(point.y()) * num_x_coords()
		   + _z_coord_to_index.at(point.z()) * (num_x_coords() * num_y_coords());
}

template<typename Coord>
Point3d<Coord> HananGrid3d<Coord>::point(Vertex const vertex) const
{
	return Point3d<Coord>(compute_x_coord(vertex), compute_y_coord(vertex), compute_z_coord(vertex));
}

template<typename Coord>
typename HananGrid3d<Coord>::Value HananGrid3d<Coord>::distance_to_neighbour(Vertex const vertex, Direction3d const direction) const
{
	if (has_neighbour(vertex, direction)) {
		Vertex const neighbour = get_neighbour(vertex, direction);
		return distance_to_neighbour(vertex, direction, neighbour);
	} else {
		return std::numeric_limits<Value>::max();
	}
}

template<typename Coord>
typename HananGrid3d<Coord>::Value HananGrid3d<Coord>::distance_to_neighbour(Vertex const vertex, Direction3d const direction, Vertex const neighbour) const
{
	switch (direction) {
		case EAST : return compute_x_coord(neighbour) - compute_x_coord(vertex);
		case WEST : return compute_x_coord(vertex) - compute_x_coord(neighbour);
		case NORTH : return compute_y_coord(neighbour) - compute_y_coord(vertex);
		case SOUTH : return compute_y_coord(vertex) - compute_y_coord(neighbour);
		case UP : return compute_z_coord(neighbour) - compute_z_coord(vertex);
		case DOWN : return compute_z_coord(vertex) - compute_z_coord(neighbour);
		default: assert(false);
	}
}

template<typename Coord>
bool HananGrid3d<Coord>::has_neighbour(Vertex const vertex, Direction3d const direction) const
{
	switch (direction) {
		case EAST : return compute_x_index(vertex) + 1 < num_x_coords();
		case WEST : return compute_x_index(vertex) > 0;
		case NORTH : return compute_y_index(vertex) + 1 < num_y_coords();
		case SOUTH : return compute_y_index(vertex) > 0;
		case UP : return compute_z_index(vertex) + 1 < num_z_coords();
		case DOWN : return compute_z_index(vertex) > 0;
		default: assert(false);
	}
}

template<typename Coord>
typename HananGrid3d<Coord>::Vertex HananGrid3d<Coord>::get_neighbour(Vertex const vertex_index, Direction3d const direction) const
{
	switch (direction) {
		case EAST : return vertex_index + 1;
		case WEST : return vertex_index - 1;
		case NORTH : return vertex_index + num_x_coords();
		case SOUTH : return vertex_index - num_x_coords();
		case UP : return vertex_index + (num_x_coords() * num_y_coords());
		case DOWN : return vertex_index - (num_x_coords() * num_y_coords());
		default: assert(false);
	}
}

template<typename Coord>
bool HananGrid3d<Coord>::get_neighbour(Vertex const vertex_index, Direction3d const direction, Vertex& neighbour, Value& distance) const
{
	if (has_neighbour(vertex_index, direction)) {
		neighbour = get_neighbour(vertex_index, direction);
		distance = distance_to_neighbour(vertex_index, direction, neighbour);
		return true;
	} else {
		return false;
	}
}

template<typename Coord>
void HananGrid3d<Coord>::compute()
{
	for (Vertex i = 0; i < num_terminals(); ++i) {
		Point3d<Coord> const& terminal = _terminal_points.at(i);
		_x_coords.at(i) = terminal.x();
		_y_coords.at(i) = terminal.y();
		_z_coords.at(i) = terminal.z();
	}

	sort_and_unique_and_erase(_x_coords);
	sort_and_unique_and_erase(_y_coords);
	sort_and_unique_and_erase(_z_coords);

	for (Vertex i = 0; i < _x_coords.size(); ++i) {
		_x_coord_to_index.insert({_x_coords.at(i), i});
	}

	for (Vertex i = 0; i < _y_coords.size(); ++i) {
		_y_coord_to_index.insert({_y_coords.at(i), i});
	}

	for (Vertex i = 0; i < _z_coords.size(); ++i) {
		_z_coord_to_index.insert({_z_coords.at(i), i});
	}

	for (Index terminal_index = 0; terminal_index < num_terminals(); ++terminal_index) {
		Point3d<Coord> const& terminal_point = _terminal_points.at(terminal_index);
		_terminal_to_vertex.at(terminal_index) = vertex(terminal_point);
	}
}

template<typename Coord>
typename HananGrid3d<Coord>::Index HananGrid3d<Coord>::compute_x_index(Vertex const vertex) const
{
	return vertex % num_x_coords();
}

template<typename Coord>
typename HananGrid3d<Coord>::Index HananGrid3d<Coord>::compute_y_index(Vertex const vertex) const
{
	return (vertex / num_x_coords()) % num_y_coords();
}

template<typename Coord>
typename HananGrid3d<Coord>::Index HananGrid3d<Coord>::compute_z_index(Vertex const vertex) const
{
	return (vertex / (num_x_coords() * num_y_coords())) % num_z_coords();
}

template<typename Coord>
Coord HananGrid3d<Coord>::compute_x_coord(Vertex const vertex) const
{
	return _x_coords.at(compute_x_index(vertex));
}

template<typename Coord>
Coord HananGrid3d<Coord>::compute_y_coord(Vertex const vertex) const
{
	return _y_coords.at(compute_y_index(vertex));
}

template<typename Coord>
Coord HananGrid3d<Coord>::compute_z_coord(Vertex const vertex) const
{
	return _z_coords.at(compute_z_index(vertex));
}

#endif
