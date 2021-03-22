#include "test_tarjan.h"

void test_is_sorted_graph ( bool ( *algorithm ) ( const Lists_t &adjacency_lists,
			    const Numbers_t &numbers ) )
{
	std::cout << "test_is_sorted_graph:\n";

	Lists_t adjacency_lists {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'D', 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t{} ),
	};
	Numbers_t numbers {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 3 ),
	};

	bool result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #1: " << ( ( result ) ? "ok" : "FAILED" ) << '\n';


	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 1 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 3 ),
	};
	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #2: " << ( ( ! result ) ? "ok" : "FAILED" ) << '\n';


	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 1 ),
		std::make_pair ( 'B', 0 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 3 ),
	};
	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #3: " << ( ( ! result ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C', 'D' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'F' } ),
		std::make_pair ( 'D', Vertexes_t { 'E' } ),
		std::make_pair ( 'E', Vertexes_t { 'G' } ),
		std::make_pair ( 'F', Vertexes_t { 'G' } ),
		std::make_pair ( 'G', Vertexes_t{} ),
	};
	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 3 ),
		std::make_pair ( 'C', 4 ),
		std::make_pair ( 'D', 1 ),
		std::make_pair ( 'E', 2 ),
		std::make_pair ( 'F', 5 ),
		std::make_pair ( 'G', 6 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #4: " << ( ( result ) ? "ok" : "FAILED" ) << '\n';

	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 3 ),
		std::make_pair ( 'D', 2 ),
		std::make_pair ( 'E', 4 ),
		std::make_pair ( 'F', 5 ),
		std::make_pair ( 'G', 6 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #5: " << ( ( result ) ? "ok" : "FAILED" ) << '\n';


	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 4 ),
		std::make_pair ( 'E', 5 ),
		std::make_pair ( 'F', 3 ),
		std::make_pair ( 'G', 6 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #6: " << ( ( result ) ? "ok" : "FAILED" ) << '\n';

	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 1 ),
		std::make_pair ( 'E', 2 ),
		std::make_pair ( 'F', 4 ),
		std::make_pair ( 'G', 6 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #7: " << ( ( ! result ) ? "ok" : "FAILED" ) << '\n';

	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 0 ),
		std::make_pair ( 'B', 1 ),
		std::make_pair ( 'C', 2 ),
		std::make_pair ( 'D', 4 ),
		std::make_pair ( 'E', 5 ),
		std::make_pair ( 'F', 3 ),
		std::make_pair ( 'G', 16 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #8: " << ( ( ! result ) ? "ok" : "FAILED" ) << '\n';

	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'D', 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t{} ),
	};
	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 1 ),
		std::make_pair ( 'B', 2 ),
		std::make_pair ( 'C', 3 ),
		std::make_pair ( 'D', 4 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #9: " << ( ( result ) ? "ok" : "FAILED" ) << '\n';

	numbers.clear();
	numbers = {
		std::make_pair ( 'A', 21 ),
		std::make_pair ( 'B', 22 ),
		std::make_pair ( 'C', 23 ),
		std::make_pair ( 'D', 24 ),
	};

	result = algorithm ( adjacency_lists, numbers );
	std::cout << "test #10: " << ( ( ! result ) ? "ok" : "FAILED" ) << '\n';
}


void test_tarjan ( bool ( *algorithm ) ( const Lists_t &adjacency_lists,
                   Numbers_t &numbersOut ),
                   bool ( *is_sorted_graph ) ( const Lists_t &adjacency_lists,
                           const Numbers_t &result ) )
{
        std::cout << "test_tarjan:\n";

	Lists_t adjacency_lists {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'D', 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t{} ),
	};
	Numbers_t result;
	bool success;
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #1:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C', 'D' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'F' } ),
		std::make_pair ( 'D', Vertexes_t { 'E' } ),
		std::make_pair ( 'E', Vertexes_t { 'G' } ),
		std::make_pair ( 'F', Vertexes_t { 'G' } ),
		std::make_pair ( 'G', Vertexes_t{} ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #2:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'F' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'E' } ),
		std::make_pair ( 'C', Vertexes_t { 'J', 'D' } ),
		std::make_pair ( 'D', Vertexes_t { 'I', 'L', 'M' } ),
		std::make_pair ( 'E', Vertexes_t { 'J', 'G' } ),
		std::make_pair ( 'F', Vertexes_t { 'H' } ),
		std::make_pair ( 'G', Vertexes_t { 'I' } ),
		std::make_pair ( 'H', Vertexes_t { 'O', 'G' } ),
		std::make_pair ( 'I', Vertexes_t { 'P', 'R', 'S', 'N' } ),
		std::make_pair ( 'J', Vertexes_t { 'K' } ),
		std::make_pair ( 'K', Vertexes_t { 'G', 'I' } ),
		std::make_pair ( 'L', Vertexes_t { 'N' } ),
		std::make_pair ( 'M', Vertexes_t { 'T' } ),
		std::make_pair ( 'N', Vertexes_t { 'T' } ),
		std::make_pair ( 'O', Vertexes_t { 'Q', 'P' } ),
		std::make_pair ( 'P', Vertexes_t { 'R' } ),
		std::make_pair ( 'Q', Vertexes_t { 'V' } ),
		std::make_pair ( 'R', Vertexes_t { 'S' } ),
		std::make_pair ( 'S', Vertexes_t { 'T' } ),
		std::make_pair ( 'T', Vertexes_t{} ),
		std::make_pair ( 'V', Vertexes_t { 'R' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #3:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'D', 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t { 'A' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #4:  " << ( ( !success && !is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'F' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'E' } ),
		std::make_pair ( 'C', Vertexes_t { 'J', 'D' } ),
		std::make_pair ( 'D', Vertexes_t { 'I', 'L', 'M' } ),
		std::make_pair ( 'E', Vertexes_t { 'J', 'G' } ),
		std::make_pair ( 'F', Vertexes_t { 'H' } ),
		std::make_pair ( 'G', Vertexes_t { 'I' } ),
		std::make_pair ( 'H', Vertexes_t { 'O', 'G' } ),
		std::make_pair ( 'I', Vertexes_t { 'P', 'R', 'S', 'N' } ),
		std::make_pair ( 'J', Vertexes_t { 'K' } ),
		std::make_pair ( 'K', Vertexes_t { 'G', 'I' } ),
		std::make_pair ( 'L', Vertexes_t { 'N' } ),
		std::make_pair ( 'M', Vertexes_t { 'T' } ),
		std::make_pair ( 'N', Vertexes_t { 'T' } ),
		std::make_pair ( 'O', Vertexes_t { 'Q', 'P' } ),
		std::make_pair ( 'P', Vertexes_t { 'R' } ),
		std::make_pair ( 'Q', Vertexes_t { 'V' } ),
		std::make_pair ( 'R', Vertexes_t { 'S' } ),
		std::make_pair ( 'S', Vertexes_t { 'T' } ),
		std::make_pair ( 'T', Vertexes_t { 'A' } ),
		std::make_pair ( 'V', Vertexes_t { 'R' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #5:  " << ( ( !success && !is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'D', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'D' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t{} ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #6:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
		std::make_pair ( 'C', Vertexes_t {} ),
		std::make_pair ( 'D', Vertexes_t { 'E', 'C' } ),
		std::make_pair ( 'E', Vertexes_t { 'C' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #7:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
		std::make_pair ( 'C', Vertexes_t {} ),
		std::make_pair ( 'D', Vertexes_t { 'E', 'C' } ),
		std::make_pair ( 'E', Vertexes_t { 'C', 'A' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #8:  " << ( ( ! success && ! is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'E', 'F', 'D' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t {} ),
		std::make_pair ( 'D', Vertexes_t { 'F', 'C' } ),
		std::make_pair ( 'E', Vertexes_t { 'B', 'C', 'F' } ),
		std::make_pair ( 'F', Vertexes_t { 'C' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #9:  " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
		std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
		std::make_pair ( 'D', Vertexes_t { 'E' } ),
		std::make_pair ( 'E', Vertexes_t {} ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #10: " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B' } ),
		std::make_pair ( 'B', Vertexes_t { 'C', 'D' } ),
		std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
		std::make_pair ( 'D', Vertexes_t { 'E' } ),
		std::make_pair ( 'E', Vertexes_t { 'C' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #11: " << ( ( ! success && ! is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'A' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #12: " << ( ( ! success && ! is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D' } ),
		std::make_pair ( 'D', Vertexes_t { 'A' } ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #13: " << ( ( ! success && ! is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'B', 'D', 'F' } ),
		std::make_pair ( 'B', Vertexes_t { 'C' } ),
		std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
		std::make_pair ( 'D', Vertexes_t { 'E' } ),
		std::make_pair ( 'E', Vertexes_t { 'F' } ),
		std::make_pair ( 'F', Vertexes_t {} ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #14: " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';


	adjacency_lists.clear();
	adjacency_lists = {
		std::make_pair ( 'A', Vertexes_t { 'C' } ),
		std::make_pair ( 'B', Vertexes_t { 'E' } ),
		std::make_pair ( 'C', Vertexes_t { 'D', 'E' } ),
		std::make_pair ( 'D', Vertexes_t {} ),
		std::make_pair ( 'E', Vertexes_t {} ),
	};
	result.clear();
	success = algorithm ( adjacency_lists, result );
	std::cout << "test #15: " << ( ( success && is_sorted_graph ( adjacency_lists, result ) ) ? "ok" : "FAILED" ) << '\n';

}
