#include <iostream>

#include "lecture24/connected_components/count_connected_components4.h"
#include "lecture24/connected_components/test_connected_components.h"

#include "lecture24/tarjan/tarjan4.h"
#include "lecture24/tarjan/test_tarjan.h"
#include "lecture24/tarjan/is_sorted_graph.h"

#include "lecture24/kosaraju/kosaraju4.h"
#include "lecture24/kosaraju/test_kosaraju.h"

#include "lecture25/distances/distances4.h"
#include "lecture25/distances/test_distances.h"

#include "lecture25/path/path4.h"
#include "lecture25/path/test_path.h"

#include "lecture26/dijkstra/dijkstra4.h"
#include "lecture26/dijkstra/test_dijkstra.h"

#include "lecture25/horse/chess_knight_path4.h"
#include "lecture25/horse/test_horse.h"


int main()
{
	std::cout << "\nlecture24: count_connected_components\n";
	test_connected_components(count_connected_components4);
	
	std::cout << "\nlecture24: kosaraju\n";
	test_kosaraju(kosaraju4);

	std::cout << "\nlecture24: tarjan\n";
	test_tarjan(tarjan4, is_sorted_graph);
	
	std::cout << "\nlecture25: distances\n";
	test_distances(distances4);

	std::cout << "\nlecture25: path\n";
	test_path(path4);

	std::cout << "\nlecture26: dijkstra\n";
	test_dijkstra(dijkstra4);

	std::cout << "\nlecture25: chess_knight_path\n";
	test_horse(chess_knight_path4);

	return 0;
}
