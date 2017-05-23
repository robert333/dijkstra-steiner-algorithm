// SteinerTree3d.hpp
#ifndef STEINERTREE3D_HPP
#define STEINERTREE3D_HPP

#include "Point3d.hpp"

template<typename Coord>
class SteinerTree3d {
public:
	using Vertex = Point3d<Coord>;
	using Edge = std::pair<Vertex, Vertex>;

public:
	SteinerTree3d(std::vector<Vertex> const& terminals, std::vector<Edge> const& edges, Coord const& cost);

	Coord const& cost() const;

	void gnuplot_2d_data(std::ostream& ostream) const;
	void gnuplot_3d_data(std::ostream& ostream) const;

private:
	std::vector<Vertex> _terminals;
	std::vector<Edge> _edges;
	Coord _cost;
};

template<typename Coord>
SteinerTree3d<Coord>::SteinerTree3d(std::vector<Vertex> const& terminals, std::vector<Edge> const& edges, Coord const& cost) :
	_terminals(terminals),
	_edges(edges),
	_cost(cost)
{}

template<typename Coord>
Coord const& SteinerTree3d<Coord>::cost() const
{
	return _cost;
}

template<typename Coord>
void SteinerTree3d<Coord>::gnuplot_2d_data(std::ostream& ostream) const
{
	ostream << "# edges {(x_1, y_1), (x_2, y_2)}\n";

	for (Edge const& edges : _edges) {
		ostream << edges.first.x() << " " << edges.first.y() << "\n"
				<< edges.second.x() << " " << edges.second.y() << "\n\n";
	}

	ostream << "\n"
			<< "# terminals (x, y)\n";

	for (Vertex const& terminal : _terminals) {
		ostream << terminal.x() << " " << terminal.y() << "\n";
	}
}

template<typename Coord>
void SteinerTree3d<Coord>::gnuplot_3d_data(std::ostream& ostream) const
{
	ostream << "# edges {(x_1, y_1, z_1), (x_2, y_2, z_2)}\n";

	if (not _edges.empty()) {
		ostream << _edges.front().first.x() << " " << _edges.front().first.y() << " " << _edges.front().first.z() << "\n";
	}

	for (Edge const& edges : _edges) {
		ostream << edges.first.x() << " " << edges.first.y() << " " << edges.first.z() << "\n"
				<< edges.second.x() << " " << edges.second.y() << " " << edges.second.z() << "\n\n";
	}

	ostream << "\n"
			<< "# terminals (x, y, z)\n";

	for (Vertex const& terminal : _terminals) {
		ostream << terminal.x() << " " << terminal.y() << " " << terminal.z()<< "\n";
	}
}

#endif
