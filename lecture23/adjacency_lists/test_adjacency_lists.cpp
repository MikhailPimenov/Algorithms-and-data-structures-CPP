#include "test_adjacency_lists.h"

void test_adjacency_lists(void (*algorithm) (std::unordered_map < char, std::unordered_set < char > >& lists))
{
	std::cout << "test_adjacency_lists:\n";

	//         4 5
	//         A B
	//         B C
	//         C D
	//         D B
	//         A D
	std::unordered_map < char, std::unordered_set < char > > answer
	{
		 std::make_pair('A',  std::unordered_set < char > { 'B', 'D' }) ,
		 std::make_pair('B',  std::unordered_set < char > { 'A', 'D', 'C' }) ,
		 std::make_pair('C',  std::unordered_set < char > { 'B', 'D' }) ,
		 std::make_pair('D',  std::unordered_set < char > { 'A', 'B', 'C' }) ,
	};
	std::unordered_map < char, std::unordered_set < char > > result;

	algorithm(result);

	std::cout << "test #1: " << ((answer == result) ? "ok" : "FAILED") << '\n';
}
