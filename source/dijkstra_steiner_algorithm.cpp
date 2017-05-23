// dijkstra_steiner_algorithm.cpp
#include "dijkstra_steiner_algorithm.hpp"

#include "DijkstraSteinerAlgorithm.hpp"

Point3d<int>::Vector parse_input(std::istream& instance)
{
	std::string line;
	std::stringstream stringstream;

	std::getline(instance, line);

	int n = std::stoi(line);

	assert(n >= 0);

	int x;
	int y;
	int z;

	Point3d<int>::Vector terminal_points;

	while (std::getline(instance, line)) {
		stringstream.clear();
		stringstream.str(line);

		stringstream >> x;
		stringstream >> y;
		stringstream >> z;

		terminal_points.emplace_back(x, y, z);
	}

	assert(static_cast<std::size_t>(n) == terminal_points.size());

	return terminal_points;
}

SteinerTree3d<int> dijkstra_steiner_algorithm(std::istream& instance, std::size_t root_terminal)
{
	std::cout << "\n== Dijkstra-Steiner Algorithm ==\n\n";

	Point3d<int>::Vector const terminal_points = parse_input(instance);

	std::cout << "Terminals\n";

	for (Point3d<int> const& terminal_point : terminal_points) {
		std::cout << "\t" << terminal_point << "\n";
	}

	std::cout << "\nHananGrid3\n";

	HananGrid3d<int> const hanan_grid(terminal_points);
	DijkstraSteinerAlgorithm<int, 20>::TerminalIndex const real_root_terminal = root_terminal % hanan_grid.num_terminals();

	std::cout << "\nDijkstraSteinerAlgorithm\n";

	DijkstraSteinerAlgorithm<int, 20> dijkstra_steiner_algorithm(terminal_points, real_root_terminal);

	std::cout << "\nPreparation\n";

	dijkstra_steiner_algorithm.preparation();

	std::cout << "\nRun\n";

	int const minimum_cost = dijkstra_steiner_algorithm.run();

	std::cout << "\nBacktrack\n";

	SteinerTreeKey<20> const root_terminal_key(hanan_grid.vertex(real_root_terminal), BitSet<20>(terminal_points.size() - 1).flip());

	std::vector<std::pair<std::size_t, std::size_t>> const edges_ids = dijkstra_steiner_algorithm.backtrack(root_terminal_key);

	std::vector<SteinerTree3d<int>::Edge> edges;

	for (std::pair<std::size_t, std::size_t> const& edge_id : edges_ids) {
		edges.push_back({hanan_grid.point(edge_id.first), hanan_grid.point(edge_id.second)});
	}

	SteinerTree3d<int> const steiner_tree(terminal_points, edges, minimum_cost);

	std::cout << "\n================================\n";

	return steiner_tree;
}
