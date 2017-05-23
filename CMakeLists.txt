cmake_minimum_required(VERSION 3.7)
project(Dijkstra-Steiner-Algorithm)

set(CMAKE_CXX_STANDARD 14)

set(WARNING_FLAGS "-Wall -Wextra -pedantic -Werror")

set(CMAKE_CXX_FLAGS "${WARNING_FLAGS}")

set(MAIN_FILE source/main.cpp)

set(SOURCE_FILES
        source/debug.hpp
        source/Output.hpp
        source/Output.cpp
        source/Point3d.hpp
        source/HananGrid3d.hpp
        source/dijkstra_steiner_algorithm.hpp
        source/dijkstra_steiner_algorithm.cpp
        source/DijkstraSteinerAlgorithm.hpp
        source/VectorHelper.hpp
        source/BitSet.hpp
        source/BitSetTable.hpp
        source/BitSetEnumerator.hpp
        source/Direction3d.hpp
        source/SteinerTreeKey.hpp
        source/SteinerTreeLabel.hpp
        source/SteinerTreeLabelTable.hpp
        source/SteinerTreeLabelQueue.hpp
        source/SteinerTreeLowerBound.hpp
        source/SteinerTreesManager.hpp
        source/SteinerTree3d.hpp source/BinaryHeap.hpp)

set(UNIT_TEST_FILES
        unit_test/unit_tests.cpp
        unit_test/test_instances.cpp
        unit_test/test_BitSetEnumerator.cpp
        unit_test/test_dijkstra_steiner_algorithm.cpp
        unit_test/test_HananGrid3.cpp)

add_executable(dijkstra_steiner_algorithm ${MAIN_FILE} ${SOURCE_FILES})
add_executable(dijkstra_steiner_algorithm_unit_tests ${SOURCE_FILES} ${UNIT_TEST_FILES})