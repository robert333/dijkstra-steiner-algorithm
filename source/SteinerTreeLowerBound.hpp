// SteinerTreeLowerBound.hpp
#ifndef STEINERTREELOWERBOUND_HPP
#define STEINERTREELOWERBOUND_HPP

#include "SteinerTreeLabel.hpp"
#include "HananGrid3d.hpp"

template<typename Coord, std::size_t num_terminals>
class SteinerTreeLowerBound {
public:
	using Key = SteinerTreeKey<num_terminals>;
	using Label = SteinerTreeLabel<num_terminals>;
	using Vertex = typename Key::Vertex;
	using Terminals = typename Key::Terminals;
	using Cost = typename Label::Cost;

public:
	SteinerTreeLowerBound(HananGrid3d<Coord> const& hanan_grid,
						  std::size_t const root_terminal,
						  std::vector<std::size_t> const& other_terminals) :
		_hanan_grid(hanan_grid),
		_root_terminal(root_terminal),
		_other_terminals(other_terminals)
	{}

	Cost lower_bound(Key const& key) const
	{
//		return 0;
		Cost const lower_bound = bounding_box(key);
//		std::cout << "lower_bound for " << key << " is " << lower_bound << "\n";
		return lower_bound;
	}

private:
	Cost bounding_box(Key const& key) const
	{
		Point3d<Coord> min_point = _hanan_grid.point(key.vertex());
		Point3d<Coord> max_point = min_point;

		for (std::size_t i = 0; i < key.terminals().size(); ++i) {
			if (not key.terminals().at(i)) {
				Point3d<Coord> terminal_point = _hanan_grid.point(_hanan_grid.vertex(_other_terminals.at(i)));

				if (terminal_point.x() < min_point.x()) {
					min_point.set_x(terminal_point.x());
				} else if (terminal_point.x() > max_point.x()) {
					max_point.set_x(terminal_point.x());
				}

				if (terminal_point.y() < min_point.y()) {
					min_point.set_y(terminal_point.y());
				} else if (terminal_point.y() > max_point.y()) {
					max_point.set_y(terminal_point.y());
				}

				if (terminal_point.z() < min_point.z()) {
					min_point.set_z(terminal_point.z());
				} else if (terminal_point.z() > max_point.z()) {
					max_point.set_z(terminal_point.z());
				}
			}
		}

		Point3d<Coord> terminal_point = _hanan_grid.point(_hanan_grid.vertex(_root_terminal));

		if (terminal_point.x() < min_point.x()) {
			min_point.set_x(terminal_point.x());
		} else if (terminal_point.x() > max_point.x()) {
			max_point.set_x(terminal_point.x());
		}

		if (terminal_point.y() < min_point.y()) {
			min_point.set_y(terminal_point.y());
		} else if (terminal_point.y() > max_point.y()) {
			max_point.set_y(terminal_point.y());
		}

		if (terminal_point.z() < min_point.z()) {
			min_point.set_z(terminal_point.z());
		} else if (terminal_point.z() > max_point.z()) {
			max_point.set_z(terminal_point.z());
		}

		return (max_point - min_point).norm();
	}

private:
	HananGrid3d<Coord> const& _hanan_grid;
	std::size_t const _root_terminal;
	std::vector<std::size_t> const& _other_terminals;
};

#endif
