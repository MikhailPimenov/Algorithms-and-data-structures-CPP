#ifndef TEST_TARJAN_H
#define TEST_TARJAN_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "../Types_for_graph.h"

void test_is_sorted_graph(bool (*algorithm) (const Lists_t& adjacency_lists,
	const Numbers_t& numbers));

void test_tarjan(bool (*algorithm) (const Lists_t&, Numbers_t&),
	bool (*is_sorted_graph) (const Lists_t& adjacency_lists,
		const Numbers_t& result));

#endif // TEST_TARJAN_H
