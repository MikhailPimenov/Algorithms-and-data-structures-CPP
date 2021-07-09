#pragma once

#include <vector>

void adjacency_lists_compact_storage4(
	const std::vector < char >& vertexes,
	const std::vector < std::vector < char > >& lists,
	std::vector < char >& vertexes_out,
	std::vector < char >& compact_lists_out,
	std::vector < int >& indexes_out
);
