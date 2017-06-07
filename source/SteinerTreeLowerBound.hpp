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
		// we are just using the bounding box lower bound
		// since all other lower bounds are not helping a lot compared to the needed run time
		Cost const lower_bound_bb = bounding_box(key);
		Cost const lower_bound_mst = 0;//minimum_spanning_tree(key);
//		std::cout << "lower_bound for " << key << " is bb = " << lower_bound_bb << " and mst = " << lower_bound_mst << "\n";
		return std::max(lower_bound_bb, lower_bound_mst / 2);
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

	Cost minimum_spanning_tree(Key const& key) const
	{
		std::vector<Point3d<Coord>> points = {_hanan_grid.point(key.vertex()), _hanan_grid.point(_hanan_grid.vertex(_root_terminal))};

		for (std::size_t i = 0; i < key.terminals().size(); ++i) {
			if (not key.terminals().at(i)) {
				points.push_back(_hanan_grid.point(_hanan_grid.vertex(_other_terminals.at(i))));
			}
		}

		assert(not points.empty());

		std::vector<std::size_t> remaining_points(points.size());
		std::vector<Coord> distances(points.size(), std::numeric_limits<Coord>::max());
		distances.at(distances.size() - 1) = 0;

		for (std::size_t i = 0; i < remaining_points.size(); ++i) {
			remaining_points.at(i) = i;
		}

		assert(points.size() == remaining_points.size());
		assert(points.size() == distances.size());

		auto const compare_function = [&](std::size_t const index_1, std::size_t const index_2) { return distances.at(index_1) > distances.at(index_2); };

		Coord cost = 0;

		while (not remaining_points.empty()) {
			std::size_t current_index = remaining_points.back();
			remaining_points.pop_back();

			cost += distances.at(current_index);
			distances.at(current_index) = -1;

			for (std::size_t i = 0; i < distances.size(); ++i) {
				if (distances.at(i) != -1) {
					Coord const distance = (points.at(current_index) - points.at(i)).norm();
					if (distances.at(i) > distance) {
						distances.at(i) = distance;
					}
				}
			}

			std::sort(remaining_points.begin(), remaining_points.end(), compare_function);
		}

		return cost;
	}

private:
	HananGrid3d<Coord> const& _hanan_grid;
	std::size_t const _root_terminal;
	std::vector<std::size_t> const& _other_terminals;
};

#endif
