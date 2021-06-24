#include <iostream>
#include <vector>

#include "common_tests/test_sort/test_sort.h"

#include "lecture6/bubble_sort/bubble_sort3.h"
#include "lecture6/insert_sort/insert_sort3.h"
#include "lecture6/select_sort/select_sort3.h"
#include "lecture19/heap_sort/heap_sort3.h"

#include "lecture9/hoar_sort/hoar_sort3.h"
#include "lecture9/merge_sort/merge_sort3.h"

#include "lecture12/knuth_morris_pratt/p_function3.h"
#include "lecture12/knuth_morris_pratt/test_p_function.h"

#include "lecture12/knuth_morris_pratt/knuth_morris_pratt3.h"
#include "lecture12/knuth_morris_pratt/test_find_substring.h"

#include "lecture11/longest_increasing_subsequence/longest_increasing_subsequence3.h"
#include "lecture11/longest_increasing_subsequence/test_longest_increasing_subsequence.h"

#include "lecture12/levenstein/levenstein3.h"
#include "lecture12/levenstein/test_levenstein.h"

#include "lecture17/discrete_bag/discrete_bag3.h"
#include "lecture17/discrete_bag/test_discrete_bag.h"

#include "lecture11/longest_common_subsequence/longest_common_subsequence3.h"
#include "lecture11/longest_common_subsequence/test_longest_common_subsequence.h"
#include "lecture13/brace_sequence/brace_sequence3.h"
#include "lecture13/brace_sequence/test_brace_sequence.h"

#include "lecture13/reversed_polish_notation/reversed_polish_notation3.h"
#include "lecture13/reversed_polish_notation/test_reversed_polish_notation.h"

#include "lecture11/chess_queen/chess_queen3.h"
#include "lecture11/chess_queen/test_chess_queen.h"

#include "lecture26/dijkstra/dijkstra2.h"
#include "lecture26/dijkstra/dijkstra.h"

#include "lecture28/test_floyd_uolsher.h"
#include "lecture28/floyd_uolsher/floyd_uolsher3.h"

#include "lecture26/dijkstra/dijkstra3.h"
#include "lecture26/dijkstra/test_dijkstra.h"

#include "lecture24/kosaraju/kosaraju3.h"
#include "lecture24/kosaraju/test_kosaraju.h"

#include "lecture24/tarjan/tarjan3.h"
#include "lecture24/tarjan/test_tarjan.h"
#include "lecture24/tarjan/is_sorted_graph.h"

#include "lecture24/connected_components/count_connected_components3.h"
#include "lecture24/connected_components/test_connected_components.h"

#include "lecture25/distances/distances3.h"
#include "lecture25/distances/test_distances.h"

#include "lecture25/path/path3.h"
#include "lecture25/path/test_path.h"

#include "lecture25/horse/horse_path3.h"
#include "lecture25/horse/test_horse.h"

#include "lecture23/adjacency_matrix/adjacency_matrix3.h"
#include "lecture23/adjacency_matrix/test_adjacency_matrix.h"

int main()
{
	std::cout << "\nlecture 6: bubble sort\n";
	test_sort(bubble_sort3);

	std::cout << "\nlecture 6: insert sort\n";
	test_sort(insert_sort3);

	std::cout << "\nlecture 6: select sort\n";
	test_sort(select_sort3);

	std::cout << "\nlecture 19: heap sort\n";
	test_sort(heap_sort3);

	std::cout << "\nlecture 9: hoar sort\n";
	test_sort(hoar_sort3);

	std::cout << "\nlecture 9: merge sort\n";
	test_sort(merge_sort3);

	std::cout << "\nlecture 12: p-function\n";
	test_p_function(p_function3);

	std::cout << "\nlecture 12: Knuth-Morris-Pratt\n";
	test_find_substring(knuth_morris_pratt3);

	std::cout << "\nlecture 11: longest increasing subsequence\n";
	test_longest_increasing_subsequence(longest_increasing_subsequence3);

	std::cout << "\nlecture 12: levenstein\n";
	test_levenstein(levenstein3);

	std::cout << "\nlecture 17: discrete bag\n";
	test_discrete_bag(discrete_bag_adapted3);

	std::cout << "\nlecture 11: longest common subsequence\n";
	test_longest_common_subsequence(longest_common_subsequence3);

	std::cout << "\nlecture 13: brace sequence\n";
	test_brace_sequence(brace_sequence3);

	std::cout << "\nlecture 13: reversed polish notation\n";
	test_reversed_polish_notation(reversed_polish_notation3);

	std::cout << "\nlecture 11: chess queen\n";
	test_chess_queen(chess_queen3);

	std::cout << "\nlecture 28: floyd uolsher\n";
	test_floyd_uolsher(floyd_uolsher3, dijkstra);

	std::cout << "\nlecture 26: dijkstra\n";
	test_dijkstra(dijkstra3);

	std::cout << "\nlecture 24: kosaraju\n";
	test_kosaraju(kosaraju_adapted3);

	std::cout << "\nlecture 24: tarjan\n";
	test_tarjan(tarjan3, is_sorted_graph);

	std::cout << "\nlecture 24: connected components\n";
	test_connected_components(count_connected_components3);

	std::cout << "\nlecture 25: distances\n";
	test_distances(distances3);

	std::cout << "\nlecture 25: path\n";
	test_path(path3);

	std::cout << "\nlecture 25: horse path\n";
	test_horse(horse_path3);

	std::cout << "\nlecture 23: adjacency matrix\n";
	test_adjacency_matrix(adjacency_matrix3);



	return 0;
}
