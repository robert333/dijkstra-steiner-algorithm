// SteinerTreesManager.hpp
#ifndef STEINERTREESMANAGER_HPP
#define STEINERTREESMANAGER_HPP

#include <limits>
#include <queue>
#include <array>
#include <functional>

#include "SteinerTreeLabelTable.hpp"
#include "SteinerTreeLabelQueue.hpp"

template<std::size_t num_terminals>
class SteinerTreesManager {
public:
	using Key = SteinerTreeKey<num_terminals>;
	using Label = SteinerTreeLabel<num_terminals>;
	using Cost = typename Label::Cost;
	using Backtrack = typename Label::Backtrack;

public:
	SteinerTreesManager(typename Label::Key::Vertex const& root_terminal) :
		_root_terminal(root_terminal)
	{}

	bool next(Label& label)
	{
		assert(not _steiner_tree_label_queue.is_empty());

//		std::cout << "\n\n";

		do {
			label = _steiner_tree_label_queue.top_and_pop();
//			std::cout << "check label " << label << "\n";
		} while (_steiner_tree_label_table.is_processed(label.key()));

//		std::cout << "\nprocess label " << label << "\n";

		// mark label as processed
		_steiner_tree_label_table.set_label_information(label.key(), label.cost(), label.backtrack());

		return label.key().vertex() != _root_terminal or label.key().terminals().num_ones() != label.key().terminals().size();
	}

	bool is_processed(Key const& key) const
	{
		return _steiner_tree_label_table.is_processed(key);
	}

	bool update(Label const& label)
	{
		if (not is_processed(label.key())) {
			_steiner_tree_label_queue.insert(label);
		}

		return false;
	}

	Cost get_minimum_cost(Key const& key) const
	{
		assert(_steiner_tree_label_table.get_label_information(key).initialised);
		return _steiner_tree_label_table.get_label_information(key).minimum_cost;
	}

	Backtrack get_backtrack(Key const& key) const
	{
		assert(_steiner_tree_label_table.get_label_information(key).initialised);
		return _steiner_tree_label_table.get_label_information(key).backtrack;
	}

private:
	typename Label::Key::Vertex _root_terminal;

	SteinerTreeLabelTable<num_terminals> _steiner_tree_label_table;
	SteinerTreeLabelQueue<num_terminals> _steiner_tree_label_queue;
};

#endif
