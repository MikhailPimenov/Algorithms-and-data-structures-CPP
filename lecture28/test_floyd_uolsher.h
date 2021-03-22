#ifndef TEST_FLOYD_UOLSHER_H
#define TEST_FLOYD_UOLSHER_H


#include <iostream>

#include "Types_for_graph.h"

void test_floyd_uolsher(void (*algorithm) (const Lists3_t&, All_distances3_t&),
	void (*algorithm_assistant) (const Lists3_t&, const Vertex3_t, Distances3_t&));

#endif // TEST_FLOYD_UOLSHER_H
