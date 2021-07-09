#include <iostream>

#include "lecture5/shift_array/shift_array4.h"
#include "lecture5/shift_array/test_shift_array.h"

#include "lecture5/eratosthenes_sieve/eratosthenes_sieve4.h"
#include "lecture5/eratosthenes_sieve/test_eratosthenes_sieve.h"

#include "lecture7/grand_common_divisor/grand_common_divisor4.h"
#include "lecture7/grand_common_divisor/test_grand_common_divisor.h"

#include "lecture7/power_fast/power_fast4.h"
#include "lecture7/power_fast/test_power_fast.h"

#include "lecture8/generate_permutations/generate_permutations4.h"
#include "lecture8/generate_permutations/test_generate_permutations.h"

#include "lecture9/binary_search/binary_search4.h"
#include "lecture9/binary_search/test_binary_search.h"

#include "lecture10/fibonacci/fibonacci4.h"
#include "lecture10/fibonacci/test_fibonacci.h"

#include "lecture17/fibonacci_recursive_cash/fibonacci_recursive_cache4.h"
#include "lecture17/fibonacci_recursive_cash/test_fibonacci_recursive_cash.h"

#include "lecture13/brace_sequence/brace_sequence4.h"
#include "lecture13/brace_sequence/test_brace_sequence.h"

#include "lecture13/reversed_polish_notation/reversed_polish_notation4.h"
#include "lecture13/reversed_polish_notation/test_reversed_polish_notation.h"

#include "lecture23/adjacency_matrix/adjacency_matrix4.h"
#include "lecture23/adjacency_matrix/test_adjacency_matrix.h"

#include "lecture23/adjacency_lists/adjacency_lists4.h"
#include "lecture23/adjacency_lists/test_adjacency_lists.h"

#include "lecture23/adjacency_lists_compact_storage/adjacency_lists_compact_storage4.h"
#include "lecture23/adjacency_lists_compact_storage/test_adjacency_lists_compact_storage.h"

#include "lecture11/chess_queen/chess_queen4.h"
#include "lecture11/chess_queen/test_chess_queen.h"

#include "lecture10/trajectory_tracing/trajectory_tracing4.h"
#include "lecture10/trajectory_tracing/test_trajectory_tracing.h"

int main()
{
	std::cout << "\nlecture5: shift_array\n";
	test_shift_array(shift_array4);

	std::cout << "\nlecture5: eratosthenes_sieve\n";
	test_eratosthenes_sieve(eratosthenes_sieve4);

	std::cout << "\nlecture7: grand_common_divisor\n";
	test_grand_common_divisor(grand_common_divisor4);

	std::cout << "\nlecture7: power_fast\n";
	test_power_fast(power_fast4);

	std::cout << "\nlecture8: generate_permutations\n";
	test_generate_permutations(generate_permutations4);

	std::cout << "\nlecture9: binary_search\n";
	test_binary_search(binary_search4);

	std::cout << "\nlecture10: fibonacci\n";
	test_fibonacci(fibonacci4);

	std::cout << "\nlecture17: fibonacci_recursive_cache\n";
	Fibonacci_recursive_cache4::initialize_cache();
	test_fibonacci_recursive_cash(fibonacci_recursive_cache4);

	std::cout << "\nlecture13: brace_sequence\n";
	test_brace_sequence(brace_sequence4);

	std::cout << "\nlecture13: reversed_polish_notation\n";
	test_reversed_polish_notation(reversed_polish_notation4);

	std::cout << "\nlecture23: adjacency_matrix\n";
	test_adjacency_matrix(adjacency_matrix4);

	std::cout << "\nlecture23: adjacency_lists\n";
	test_adjacency_lists(adjacency_lists4);

	std::cout << "\nlecture23: adjacency_lists_compact_storage\n";
	test_adjacency_lists_compact_storage(adjacency_lists_compact_storage4);

	std::cout << "\nlecture11: chess_queen\n";
	test_chess_queen(chess_queen4);

	std::cout << "\nlecture10: trajectory_tracing\n";
	test_trajectory_tracing(trajectory_tracing4);

	return 0;
}
