// main.cpp
#include <fstream>
#include "dijkstra_steiner_algorithm.hpp"

int main(int argc, char* argv[])
{
	assert(argc > 0);

	if (argc < 2) {
		std::cerr << "argument needed: " << argv[0] << " instance_filepath\n";
		return 1;
	}

	std::string const instance_filepath = argv[1];

	std::ifstream instance_file(instance_filepath);

	if (not instance_file.is_open()) {
		std::cerr << "ERROR: cannot open instance file " << instance_filepath << "\n";
		return 1;
	}

	SteinerTree3d<int> steiner_tree({}, {}, 0);

	try{
		// compute a optimum steiner tree with the Dijkstra-Steiner algorithm
		// if there is something wrong with the instance a exception will be thrown
		steiner_tree = dijkstra_steiner_algorithm(instance_file);
	} catch(...) {
		std::cerr << "ERROR: cannot parse instance file " << instance_filepath << "\n";
		return 1;
	}

	std::cout << steiner_tree.cost() << "\n";

	// create a gnuplot file of the computed steiner tree if it is demanded
	bool gnuplot = false;

	if (argc > 2) {
		if (std::string(argv[2]) == "gnuplot") {
			gnuplot = true;
		}
	}

	if (gnuplot) {
		std::ofstream gnuplot_2d_data_file(instance_filepath + "_gnuplot_2d_data.dat");
		std::ofstream gnuplot_3d_data_file(instance_filepath + "_gnuplot_3d_data.dat");

		assert(gnuplot_2d_data_file.is_open());
		assert(gnuplot_3d_data_file.is_open());

		steiner_tree.gnuplot_2d_data(gnuplot_2d_data_file);
		steiner_tree.gnuplot_3d_data(gnuplot_3d_data_file);

		gnuplot_2d_data_file.close();
		gnuplot_3d_data_file.close();

		std::string const command_2d = "gnuplot -persistent -e \"data_filepath='" + instance_filepath + "_gnuplot_2d_data.dat'\" gnuplot/plot_2d_steiner_tree";
		std::string const command_3d = "gnuplot -persistent -e \"data_filepath='" + instance_filepath + "_gnuplot_3d_data.dat'\" gnuplot/plot_3d_steiner_tree";

#ifndef NDEBUG
		int status_1 = system(command_2d.c_str());
		int status_2 = system(command_3d.c_str());

		assert(not status_1);
		assert(not status_2);

		std::cout << "Enter to exit the program...";
		std::cin.ignore().get();
#else
		std::cout << "for gnuplot use the following commands:\n"
				  << command_2d << "\n"
				  << command_3d << "\n";
#endif
	}

	return 0;
}
