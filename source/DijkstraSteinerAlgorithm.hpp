// DijkstraSteinerAlgorithm.hpp
#ifndef DIJKSTRASTEINERALGORITHM_HPP
#define DIJKSTRASTEINERALGORITHM_HPP

#include <bitset>
#include <set>
#include <queue>
#include "HananGrid3d.hpp"
#include "BitSet.hpp"
#include "SteinerTreeLabel.hpp"
#include "SteinerTreesManager.hpp"
#include "VectorHelper.hpp"
#include "BitSetEnumerator.hpp"
#include "SteinerTreeLowerBound.hpp"

template<typename Coord, std::size_t num_terminals>
class DijkstraSteinerAlgorithm {
public:
	using Key = SteinerTreeKey<num_terminals>;
	using Label = SteinerTreeLabel<num_terminals>;
	using Value = int;
	using TerminalIndex = std::size_t;
	using TerminalSet = std::size_t;

	using Vertex = std::size_t;
	using Edge = std::pair<Vertex, Vertex>;

public:
	DijkstraSteinerAlgorithm(HananGrid3d<Coord> const& hanan_grid, TerminalIndex const& root_terminal) :
		_hanan_grid(hanan_grid),
		_root_terminal(root_terminal),
		_steiner_trees_manager(_hanan_grid.vertex(root_terminal))
	{
		assert(_hanan_grid.num_terminals() >= 0);
	}

	void preparation()
	{
		for (TerminalIndex terminal_index = 0; terminal_index < _hanan_grid.num_terminals(); ++terminal_index) {
			if (_root_terminal == terminal_index) {
				continue;
			}

			_other_terminals.push_back(terminal_index);
			_terminal_index_to_other_terminals.push_back(terminal_index);
		}

		for (TerminalIndex terminal_index = 0; terminal_index < _other_terminals.size(); ++terminal_index) {
			typename Key::Vertex const vertex = _hanan_grid.vertex(_terminal_index_to_other_terminals.at(terminal_index));
			typename Key::Terminals terminals(_other_terminals.size());
			terminals.reset();
			assert(terminals.none());
			terminals.set(terminal_index, true);

			Key const steiner_tree_key(vertex, terminals);
			Label const terminal_label(steiner_tree_key, 0, 0, {Key::invalid(), Key::invalid()});

			debug_output("terminal_label = " + terminal_label.to_string() + "\n");

			_steiner_trees_manager.update(terminal_label);
		}
	}

	Value run()
	{
		SteinerTreeLowerBound<Coord, num_terminals> const steiner_tree_lower_bound(_hanan_grid, _root_terminal, _other_terminals);

		SteinerTreeLabel<num_terminals> label;

		while (_steiner_trees_manager.next(label)) {
			typename SteinerTreeLabel<num_terminals>::Cost const label_cost = label.cost();

			// check for the current vertex each direction and so each neighbour
			// and update it with the new cost
			for (Direction3d const& direction : directions_3d()) {
				typename HananGrid3d<Coord>::Vertex neighbour;
				typename HananGrid3d<Coord>::Value distance;

				if (_hanan_grid.get_neighbour(label.key().vertex(), direction, neighbour, distance)) {
					Key const neighbour_key(neighbour, label.key().terminals());
					Label const neighbour_label(neighbour_key,
												label_cost + distance,
												steiner_tree_lower_bound.lower_bound(neighbour_key),
												{label.key(), Key::invalid()});

					_steiner_trees_manager.update(neighbour_label);
				}
			}

			BitSetEnumerator<num_terminals> const bitset_enumerator(label.key().terminals());
			Key other_key(label.key().vertex(), typename Key::Terminals(label.key().terminals().size()));

			assert(other_key.terminals().none());

			// using the bitset enumerator we check each appropriate label as required by the algorithm
			// and update it with the new cost
			while (bitset_enumerator.next(other_key.non_const_terminals())) {
				assert(other_key.terminals().any());

				if (_steiner_trees_manager.is_processed(other_key)) {
					Key const union_key(label.key().vertex(), other_key.terminals(), label.key().terminals());
					Label const union_label(union_key,
											label_cost + _steiner_trees_manager.get_minimum_cost(other_key),
											steiner_tree_lower_bound.lower_bound(union_key),
											{label.key(), other_key});

					_steiner_trees_manager.update(union_label);
				}
			}
		}

		return _steiner_trees_manager.get_minimum_cost(label.key());
	}

	std::vector<Edge> backtrack(Key const& key)
	{
		assert(not key.is_invalid());

		typename Label::Backtrack const& backtrack_item = _steiner_trees_manager.get_backtrack(key);

		debug_output("backtrack key " + key.to_string() + " with cost " + std::to_string(_steiner_trees_manager.get_minimum_cost(key))
					 + " and backtrack {" + backtrack_item.first.to_string() + ", " + backtrack_item.second.to_string() + "}\n");

		if (backtrack_item.first.is_invalid() and backtrack_item.second.is_invalid()) {
			return {};
		} else if (backtrack_item.second.is_invalid()) {
			std::vector<Edge> edges = backtrack(backtrack_item.first);
			edges.push_back({key.vertex(), backtrack_item.first.vertex()});
			return edges;
		} else {
			std::vector<Edge> edges_1 = backtrack(backtrack_item.first);
			std::vector<Edge> edges_2 = backtrack(backtrack_item.second);
			append(edges_1, edges_2);
			return edges_1;
		}
	}

private:
	HananGrid3d<Coord> const _hanan_grid;
	TerminalIndex const _root_terminal;

	std::vector<TerminalIndex> _other_terminals;
	std::vector<TerminalIndex> _terminal_index_to_other_terminals;

	SteinerTreesManager<num_terminals> _steiner_trees_manager;
};

#endif
