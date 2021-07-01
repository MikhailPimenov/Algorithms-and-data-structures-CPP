#include <iostream>

#include "lecture24/connected_components/count_connected_components4.h"
#include "lecture24/connected_components/test_connected_components.h"
#include "lecture24/Types_for_graph.h"

#include <unordered_set>
#include <numeric>


template<typename T>
struct hash_on_sum: private std::hash<typename T::value_type>
{
	using count_type = typename T::value_type;
	using base = typename std::hash<count_type>;
	std::size_t operator()(T const& obj) const
	{
		return base::operator()(
			std::accumulate(
				obj.cbegin(), 
				obj.cend(), 
				0,
				[](std::size_t sum, const count_type& next) {
					return sum + std::hash<count_type>{}(next);
				}
			)
		);
	}
};

using inner_type = std::unordered_set<Vertex_t>;
using set_of_unique_sets = std::unordered_set<inner_type, hash_on_sum<inner_type>>;

int main()
{
	inner_type inner_set1;
	inner_set1.insert('A');
	inner_set1.insert('B');
	inner_set1.insert('C');
	inner_set1.insert('D');
	
	inner_type inner_set2;
	inner_set2.insert('A');
	inner_set2.insert('a');
	inner_set2.insert('b');
	inner_set2.insert('c');
	inner_set2.insert('C');
	inner_set2.insert('D');
	inner_set2.insert('e');
	inner_set2.insert('B');
	inner_set2.erase('a');
	inner_set2.erase('b');
	inner_set2.erase('c');
	//inner_set2.erase('e');

	set_of_unique_sets set;
	set.insert(inner_set1);
	set.insert(inner_set2);

	std::cout << "size: " << set.size() << '\n';
	inner_set2.erase('e');
	
	std::cout << "size: " << set.size() << '\n';
	

	std::unordered_set<int> set1;
	set1.insert(1);
	set1.insert(2);
	set1.insert(3);
	set1.insert(4);

	std::cout << "sum: " << 
		std::accumulate(set1.cbegin(), set1.cend(), 0) << '\n';
	std::cout << "multiplication: " << 
		std::accumulate(set1.cbegin(), set1.cend(), 1, std::multiplies<int>()) << '\n';

	std::cout << "sum of squares: " <<
		std::accumulate(set1.cbegin(), set1.cend(), 0, [](int sum, int next) {
		return sum + next * next;
			}) << '\n';

	return 0;
}
