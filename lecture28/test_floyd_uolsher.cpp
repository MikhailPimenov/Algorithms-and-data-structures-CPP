#include "test_floyd_uolsher.h"


void test_floyd_uolsher ( void ( *algorithm ) ( const Lists3_t &, All_distances3_t & ),
			  void ( *algorithm_assistant ) ( const Lists3_t &, const Vertex3_t, Distances3_t & ) )
{
	std::cout << "test_floyd_uolsher:\n";
	Lists3_t adjacency_lists;
	All_distances3_t answer;
	All_distances3_t result;

	adjacency_lists = {
		std::make_pair ( 'A', Vertexes3_t {
			std::make_pair ( 'B', 2 ),
			std::make_pair ( 'H', 15 ) } ),
		std::make_pair ( 'B', Vertexes3_t {
			std::make_pair ( 'A', 2 ),
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'D', 5 ) } ),
		std::make_pair ( 'C', Vertexes3_t {
			std::make_pair ( 'B', 1 ),
			std::make_pair ( 'D', 3 ),
			std::make_pair ( 'F', 2 ),
			std::make_pair ( 'G', 1 ) } ),
		std::make_pair ( 'D', Vertexes3_t {
			std::make_pair ( 'B', 5 ),
			std::make_pair ( 'C', 3 ),
			std::make_pair ( 'F', 4 ),
			std::make_pair ( 'E', 6 ) } ),
		std::make_pair ( 'E', Vertexes3_t {
			std::make_pair ( 'D', 6 ),
			std::make_pair ( 'F', 7 ),
			std::make_pair ( 'I', 2 ) } ),
		std::make_pair ( 'F', Vertexes3_t {
			std::make_pair ( 'C', 2 ),
			std::make_pair ( 'D', 4 ),
			std::make_pair ( 'E', 7 ),
			std::make_pair ( 'G', 1 ),
			std::make_pair ( 'H', 3 ) } ),
		std::make_pair ( 'G', Vertexes3_t {
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'F', 1 ) } ),
		std::make_pair ( 'H', Vertexes3_t {
			std::make_pair ( 'A', 15 ),
			std::make_pair ( 'F', 3 ),
			std::make_pair ( 'I', 12 ) } ),
		std::make_pair ( 'I', Vertexes3_t {
			std::make_pair ( 'E', 2 ),
			std::make_pair ( 'H', 12 ), } ),
	};


	for ( const auto &vertex_and_neighbours : adjacency_lists ) {
		Distances3_t distances;
		algorithm_assistant ( adjacency_lists, vertex_and_neighbours.first, distances );
		answer.insert ( std::make_pair ( vertex_and_neighbours.first, distances ) );
	}

	Timer t;
	algorithm ( adjacency_lists, result );
	auto time = t.elapsed();
	std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << "\tt = " << time << '\n';

	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes3_t {
			std::make_pair ( 'B', 2 ),
			std::make_pair ( 'M', 2 ),
			std::make_pair ( 'N', 6 ),
			std::make_pair ( 'O', 10 ),
			std::make_pair ( 'H', 15 ) } ),
		std::make_pair ( 'B', Vertexes3_t {
			std::make_pair ( 'A', 2 ),
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'D', 5 ) } ),
		std::make_pair ( 'C', Vertexes3_t {
			std::make_pair ( 'B', 1 ),
			std::make_pair ( 'D', 3 ),
			std::make_pair ( 'F', 2 ),
			std::make_pair ( 'G', 1 ) } ),
		std::make_pair ( 'D', Vertexes3_t {
			std::make_pair ( 'B', 5 ),
			std::make_pair ( 'M', 4 ),
			std::make_pair ( 'N', 8 ),
			std::make_pair ( 'O', 12 ),
			std::make_pair ( 'C', 3 ),
			std::make_pair ( 'F', 4 ),
			std::make_pair ( 'E', 6 ) } ),
		std::make_pair ( 'E', Vertexes3_t {
			std::make_pair ( 'D', 6 ),
			std::make_pair ( 'J', 1 ),
			std::make_pair ( 'K', 3 ),
			std::make_pair ( 'L', 5 ),
			std::make_pair ( 'F', 7 ),
			std::make_pair ( 'I', 2 ) } ),
		std::make_pair ( 'F', Vertexes3_t {
			std::make_pair ( 'C', 2 ),
			std::make_pair ( 'D', 4 ),
			std::make_pair ( 'E', 7 ),
			std::make_pair ( 'G', 1 ),
			std::make_pair ( 'H', 3 ) } ),
		std::make_pair ( 'G', Vertexes3_t {
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'F', 1 ) } ),
		std::make_pair ( 'H', Vertexes3_t {
			std::make_pair ( 'A', 15 ),
			std::make_pair ( 'F', 3 ),
			std::make_pair ( 'J', 2 ),
			std::make_pair ( 'K', 4 ),
			std::make_pair ( 'L', 6 ),
			std::make_pair ( 'I', 12 ) } ),
		std::make_pair ( 'I', Vertexes3_t {
			std::make_pair ( 'E', 2 ),
			std::make_pair ( 'H', 12 ), } ),
		std::make_pair ( 'J', Vertexes3_t {
			std::make_pair ( 'E', 1 ),
			std::make_pair ( 'H', 2 ), } ),
		std::make_pair ( 'K', Vertexes3_t {
			std::make_pair ( 'E', 3 ),
			std::make_pair ( 'H', 4 ), } ),
		std::make_pair ( 'L', Vertexes3_t {
			std::make_pair ( 'E', 5 ),
			std::make_pair ( 'H', 6 ), } ),
		std::make_pair ( 'M', Vertexes3_t {
			std::make_pair ( 'A', 2 ),
			std::make_pair ( 'D', 4 ), } ),
		std::make_pair ( 'N', Vertexes3_t {
			std::make_pair ( 'A', 6 ),
			std::make_pair ( 'D', 8 ), } ),
		std::make_pair ( 'O', Vertexes3_t {
			std::make_pair ( 'A', 10 ),
			std::make_pair ( 'D', 12 ), } ),
	};

	answer.clear();
	for ( const auto &vertex_and_neighbours : adjacency_lists ) {
		Distances3_t distances;
		algorithm_assistant ( adjacency_lists, vertex_and_neighbours.first, distances );
		answer.insert ( std::make_pair ( vertex_and_neighbours.first, distances ) );
	}

	result.clear();
	t.reset();
	algorithm(adjacency_lists, result);
	time = t.elapsed();
	std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << "\tt = " << time << '\n';

	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes3_t {
			std::make_pair ( 'B', 2 ),
			std::make_pair ( 'H', 15 ) } ),
		std::make_pair ( 'B', Vertexes3_t {
			std::make_pair ( 'A', 2 ),
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'D', 5 ) } ),
		std::make_pair ( 'C', Vertexes3_t {
			std::make_pair ( 'B', 1 ),
			std::make_pair ( 'D', 3 ),
			std::make_pair ( 'F', 2 ),
			std::make_pair ( 'G', 1 ) } ),
		std::make_pair ( 'D', Vertexes3_t {
			std::make_pair ( 'B', 5 ),
			std::make_pair ( 'C', 3 ),
			std::make_pair ( 'F', 4 ),
			std::make_pair ( 'E', 6 ) } ),
		std::make_pair ( 'E', Vertexes3_t {
			std::make_pair ( 'D', 6 ),
			std::make_pair ( 'J', 1 ),
			std::make_pair ( 'K', 3 ),
			std::make_pair ( 'L', 5 ),
			std::make_pair ( 'F', 7 ),
			std::make_pair ( 'I', 2 ) } ),
		std::make_pair ( 'F', Vertexes3_t {
			std::make_pair ( 'C', 2 ),
			std::make_pair ( 'D', 4 ),
			std::make_pair ( 'E', 7 ),
			std::make_pair ( 'G', 1 ),
			std::make_pair ( 'H', 3 ) } ),
		std::make_pair ( 'G', Vertexes3_t {
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'F', 1 ) } ),
		std::make_pair ( 'H', Vertexes3_t {
			std::make_pair ( 'A', 15 ),
			std::make_pair ( 'F', 3 ),
			std::make_pair ( 'J', 2 ),
			std::make_pair ( 'K', 4 ),
			std::make_pair ( 'L', 6 ),
			std::make_pair ( 'I', 12 ) } ),
		std::make_pair ( 'I', Vertexes3_t {
			std::make_pair ( 'E', 2 ),
			std::make_pair ( 'H', 12 ), } ),
		std::make_pair ( 'J', Vertexes3_t {
			std::make_pair ( 'E', 1 ),
			std::make_pair ( 'H', 2 ), } ),
		std::make_pair ( 'K', Vertexes3_t {
			std::make_pair ( 'E', 3 ),
			std::make_pair ( 'H', 4 ), } ),
		std::make_pair ( 'L', Vertexes3_t {
			std::make_pair ( 'E', 5 ),
			std::make_pair ( 'H', 6 ), } ),
	};

	answer.clear();
	for ( const auto &vertex_and_neighbours : adjacency_lists ) {
		Distances3_t distances;
		algorithm_assistant ( adjacency_lists, vertex_and_neighbours.first, distances );
		answer.insert ( std::make_pair ( vertex_and_neighbours.first, distances ) );
	}

	result.clear();
	t.reset();
	algorithm(adjacency_lists, result);
	time = t.elapsed();
	std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << "\tt = " << time << '\n';

	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes3_t {
			std::make_pair ( 'T', 18 ),
			std::make_pair ( 'B', 4 ),
			std::make_pair ( 'C', 1 ),
			std::make_pair ( 'H', 6 ),
			std::make_pair ( 'I', 7 ),
			std::make_pair ( 'N', 1 ) } ),
		std::make_pair ( 'B', Vertexes3_t {
			std::make_pair ( 'A', 4 ),
			std::make_pair ( 'D', 5 ),
			std::make_pair ( 'O', 4 ) } ),
		std::make_pair ( 'C', Vertexes3_t {
			std::make_pair ( 'A', 1 ),
			std::make_pair ( 'D', 5 ),
			std::make_pair ( 'H', 3 ),
			std::make_pair ( 'G', 7 ) } ),
		std::make_pair ( 'D', Vertexes3_t {
			std::make_pair ( 'B', 5 ),
			std::make_pair ( 'O', 8 ),
			std::make_pair ( 'E', 4 ),
			std::make_pair ( 'F', 5 ),
			std::make_pair ( 'C', 5 ) } ),
		std::make_pair ( 'E', Vertexes3_t {
			std::make_pair ( 'O', 8 ),
			std::make_pair ( 'N', 8 ),
			std::make_pair ( 'M', 9 ),
			std::make_pair ( 'F', 3 ),
			std::make_pair ( 'D', 4 ) } ),
		std::make_pair ( 'F', Vertexes3_t {
			std::make_pair ( 'D', 5 ),
			std::make_pair ( 'E', 3 ),
			std::make_pair ( 'M', 6 ),
			std::make_pair ( 'L', 6 ),
			std::make_pair ( 'K', 3 ),
			std::make_pair ( 'G', 2 ) } ),
		std::make_pair ( 'G', Vertexes3_t {
			std::make_pair ( 'C', 7 ),
			std::make_pair ( 'F', 2 ),
			std::make_pair ( 'K', 2 ),
			std::make_pair ( 'H', 4 ) } ),
		std::make_pair ( 'H', Vertexes3_t {
			std::make_pair ( 'A', 6 ),
			std::make_pair ( 'C', 3 ),
			std::make_pair ( 'G', 4 ),
			std::make_pair ( 'J', 2 ) } ),
		std::make_pair ( 'I', Vertexes3_t {
			std::make_pair ( 'A', 7 ),
			std::make_pair ( 'V', 8 ), } ),
		std::make_pair ( 'J', Vertexes3_t {
			std::make_pair ( 'H', 2 ),
			std::make_pair ( 'V', 3 ),
			std::make_pair ( 'S', 4 ) } ),
		std::make_pair ( 'K', Vertexes3_t {
			std::make_pair ( 'G', 2 ),
			std::make_pair ( 'R', 5 ),
			std::make_pair ( 'T', 6 ),
			std::make_pair ( 'F', 3 ) } ),
		std::make_pair ( 'L', Vertexes3_t {
			std::make_pair ( 'F', 6 ),
			std::make_pair ( 'M', 1 ),
			std::make_pair ( 'P', 9 ),
			std::make_pair ( 'R', 4 ) } ),
		std::make_pair ( 'M', Vertexes3_t {
			std::make_pair ( 'N', 8 ),
			std::make_pair ( 'E', 9 ),
			std::make_pair ( 'F', 6 ),
			std::make_pair ( 'L', 1 ),
			std::make_pair ( 'P', 2 ) } ),
		std::make_pair ( 'N', Vertexes3_t {
			std::make_pair ( 'A', 1 ),
			std::make_pair ( 'E', 8 ),
			std::make_pair ( 'M', 8 ) } ),
		std::make_pair ( 'O', Vertexes3_t {
			std::make_pair ( 'B', 4 ),
			std::make_pair ( 'D', 8 ),
			std::make_pair ( 'E', 8 ) } ),
		std::make_pair ( 'P', Vertexes3_t {
			std::make_pair ( 'M', 2 ),
			std::make_pair ( 'L', 9 ),
			std::make_pair ( 'Q', 3 ) } ),
		std::make_pair ( 'Q', Vertexes3_t {
			std::make_pair ( 'P', 3 ),
			std::make_pair ( 'R', 4 ) } ),
		std::make_pair ( 'R', Vertexes3_t {
			std::make_pair ( 'L', 4 ),
			std::make_pair ( 'Q', 4 ),
			std::make_pair ( 'T', 4 ),
			std::make_pair ( 'K', 5 ) } ),
		std::make_pair ( 'S', Vertexes3_t {
			std::make_pair ( 'T', 6 ),
			std::make_pair ( 'J', 4 ) } ),
		std::make_pair ( 'T', Vertexes3_t {
			std::make_pair ( 'R', 4 ),
			std::make_pair ( 'K', 6 ),
			std::make_pair ( 'S', 6 ),
			std::make_pair ( 'A', 18 ) } ),
		std::make_pair ( 'V', Vertexes3_t {
			std::make_pair ( 'I', 8 ),
			std::make_pair ( 'J', 3 ) } ),

	};

	answer.clear();
	for ( const auto &vertex_and_neighbours : adjacency_lists ) {
		Distances3_t distances;
		algorithm_assistant ( adjacency_lists, vertex_and_neighbours.first, distances );
		answer.insert ( std::make_pair ( vertex_and_neighbours.first, distances ) );
	}

	result.clear();
	t.reset();
	algorithm(adjacency_lists, result);
	time = t.elapsed();
	std::cout << "test #4: " << ( ( answer == result ) ? "ok" : "FAILED" ) << "\tt = " << time << '\n';

	/*for ( const auto &vertex_and_distances : answer ) {
		if ( result.at ( vertex_and_distances.first ) != vertex_and_distances.second ) {
			std::cout << vertex_and_distances.first << '\n';

			for ( const auto &vertex_and_distance : vertex_and_distances.second ) {
				if ( vertex_and_distance.second != result.at ( vertex_and_distances.first ).at ( vertex_and_distance.first ) )
					std::cout << '\t' << vertex_and_distance.first << '\n';
			}
		}
	}*/

	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair('A', Vertexes3_t {
			std::make_pair('T', 18),
			std::make_pair('B', 4),
			std::make_pair('C', 1),
			std::make_pair('H', 6),
			std::make_pair('Z', 21),
			std::make_pair('I', 7),
			std::make_pair('N', 1) }),
		std::make_pair('B', Vertexes3_t {
			std::make_pair('A', 4),
			std::make_pair('W', 3),
			std::make_pair('D', 5),
			std::make_pair('O', 4) }),
		std::make_pair('C', Vertexes3_t {
			std::make_pair('A', 1),
			std::make_pair('D', 5),
			std::make_pair('Z', 17),
			std::make_pair('H', 3),
			std::make_pair('G', 7) }),
		std::make_pair('D', Vertexes3_t {
			std::make_pair('B', 5),
			std::make_pair('O', 8),
			std::make_pair('E', 4),
			std::make_pair('Z', 15),
			std::make_pair('Y', 21),
			std::make_pair('F', 5),
			std::make_pair('C', 5) }),
		std::make_pair('E', Vertexes3_t {
			std::make_pair('O', 8),
			std::make_pair('N', 8),
			std::make_pair('M', 9),
			std::make_pair('F', 3),
			std::make_pair('X', 3),
			std::make_pair('D', 4) }),
		std::make_pair('F', Vertexes3_t {
			std::make_pair('D', 5),
			std::make_pair('E', 3),
			std::make_pair('M', 6),
			std::make_pair('W', 18),
			std::make_pair('L', 6),
			std::make_pair('K', 3),
			std::make_pair('G', 2) }),
		std::make_pair('G', Vertexes3_t {
			std::make_pair('C', 7),
			std::make_pair('F', 2),
			std::make_pair('K', 2),
			std::make_pair('H', 4) }),
		std::make_pair('H', Vertexes3_t {
			std::make_pair('A', 6),
			std::make_pair('C', 3),
			std::make_pair('G', 4),
			std::make_pair('J', 2) }),
		std::make_pair('I', Vertexes3_t {
			std::make_pair('A', 7),
			std::make_pair('U', 8),
			std::make_pair('X', 8),
			std::make_pair('Y', 18),
			std::make_pair('V', 8), }),
		std::make_pair('J', Vertexes3_t {
			std::make_pair('H', 2),
			std::make_pair('V', 3),
			std::make_pair('Y', 31),
			std::make_pair('U', 3),
			std::make_pair('S', 4) }),
		std::make_pair('K', Vertexes3_t {
			std::make_pair('G', 2),
			std::make_pair('R', 5),
			std::make_pair('T', 6),
			std::make_pair('Z', 13),
			std::make_pair('F', 3) }),
		std::make_pair('L', Vertexes3_t {
			std::make_pair('F', 6),
			std::make_pair('M', 1),
			std::make_pair('U', 19),
			std::make_pair('P', 9),
			std::make_pair('R', 4) }),
		std::make_pair('M', Vertexes3_t {
			std::make_pair('N', 8),
			std::make_pair('E', 9),
			std::make_pair('F', 6),
			std::make_pair('L', 1),
			std::make_pair('P', 2) }),
		std::make_pair('N', Vertexes3_t {
			std::make_pair('A', 1),
			std::make_pair('E', 8),
			std::make_pair('M', 8) }),
		std::make_pair('O', Vertexes3_t {
			std::make_pair('B', 4),
			std::make_pair('D', 8),
			std::make_pair('X', 14),
			std::make_pair('E', 8) }),
		std::make_pair('P', Vertexes3_t {
			std::make_pair('M', 2),
			std::make_pair('Y', 17),
			std::make_pair('L', 9),
			std::make_pair('Q', 3) }),
		std::make_pair('Q', Vertexes3_t {
			std::make_pair('P', 3),
			std::make_pair('Y', 16),
			std::make_pair('R', 4) }),
		std::make_pair('R', Vertexes3_t {
			std::make_pair('L', 4),
			std::make_pair('Q', 4),
			std::make_pair('X', 6),
			std::make_pair('T', 4),
			std::make_pair('K', 5) }),
		std::make_pair('S', Vertexes3_t {
			std::make_pair('T', 6),
			std::make_pair('J', 4) }),
		std::make_pair('T', Vertexes3_t {
			std::make_pair('R', 4),
			std::make_pair('Y', 9),
			std::make_pair('K', 6),
			std::make_pair('S', 6),
			std::make_pair('A', 18) }),
		std::make_pair('V', Vertexes3_t {
			std::make_pair('I', 8),
			std::make_pair('J', 3) }),
		std::make_pair('U', Vertexes3_t {
			std::make_pair('I', 8),
			std::make_pair('Y', 15),
			std::make_pair('L', 19),
			std::make_pair('J', 3) }),
		std::make_pair('W', Vertexes3_t{
			std::make_pair('F', 18),
			std::make_pair('B', 3) }),
		std::make_pair('X', Vertexes3_t{
			std::make_pair('I', 8),
			std::make_pair('O', 14),
			std::make_pair('R', 6),
			std::make_pair('E', 3) }),
		std::make_pair('Y', Vertexes3_t{
			std::make_pair('Q', 16),
			std::make_pair('P', 17),
			std::make_pair('U', 15),
			std::make_pair('D', 21),
			std::make_pair('Z', 17),
			std::make_pair('T', 9),
			std::make_pair('I', 18),
			std::make_pair('J', 31) }),
		std::make_pair('Z', Vertexes3_t{
			std::make_pair('Y', 17),
			std::make_pair('A', 21),
			std::make_pair('C', 17),
			std::make_pair('D', 15),
			std::make_pair('K', 13) }),
	};

	answer.clear();
	for (const auto& vertex_and_neighbours : adjacency_lists) {
		Distances3_t distances;
		algorithm_assistant(adjacency_lists, vertex_and_neighbours.first, distances);
		answer.insert(std::make_pair(vertex_and_neighbours.first, distances));
	}

	result.clear();
	t.reset();
	algorithm(adjacency_lists, result);
	time = t.elapsed();
	std::cout << "test #5: " << ((answer == result) ? "ok" : "FAILED") << "\tt = " << time << '\n';

}
