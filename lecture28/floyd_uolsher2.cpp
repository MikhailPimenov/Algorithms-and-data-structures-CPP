#include "floyd_uolsher2.h"

namespace Floyd_uolsher2 {

	int calculate_maximum(const Lists3_t& graph)
	{
		int maximum = 0;
		for (const auto& vertex_and_neighbours : graph)
			for (const auto& neighbor_and_cost : vertex_and_neighbours.second)
				maximum += neighbor_and_cost.second;
		return maximum;
	}

	int minimum(int a, int b) {
		return (a < b) ? a : b;
	}
}


void floyd_uolsher2(const Lists3_t& graph, All_distances3_t& distances)
{
	int maximum = Floyd_uolsher2::calculate_maximum(graph);

	std::size_t index = 0;
	std::vector < Vertex3_t> vector;
	vector.resize(graph.size());

	for (const auto& vertex_and_neighbours : graph) {
		vector.at(index) = vertex_and_neighbours.first;
		++index;
	}

	std::array<All_distances3_t, 2> f;
	Distances3_t d;

	for (const auto& vertex_and_neighbour : graph)
		d.insert(std::pair<Vertex3_t, int>(vertex_and_neighbour.first, 0));
	for (auto& one_f : f)
		for (const auto& vertex_and_neighbours : graph)
			one_f.insert(std::pair<Vertex3_t, Distances3_t>(vertex_and_neighbours.first, d));


	std::size_t index1 = 0;
	std::size_t index2 = 0;

	for (const auto& vns1 : graph) {
		for (const auto& vns2 : graph) {
			if (vns1.second.find(vns2.first) != vns1.second.cend())
				f[0].at(vector.at(index1)).at(vector.at(index2)) = vns1.second.at(vns2.first);
			else
				f[0].at(vector.at(index1)).at(vector.at(index2)) = maximum;

			++index2;
		}
		++index1;
		index2 = 0;
	}

	for (std::size_t i = 0; i < graph.size(); ++i)
		f[0].at(vector.at(i)).at(vector.at(i)) = 0;

	f[1] = f[0];
	for (std::size_t k = 0; k < graph.size(); ++k) {
		for (std::size_t i = 0; i < graph.size(); ++i) {
			for (std::size_t j = 0; j < graph.size(); ++j) {
				f[k % 2].at(vector[i]).at(vector[j]) = Floyd_uolsher2::minimum(f[(k - 1) % 2].at(vector[i]).at(vector[j]),
					f[(k - 1) % 2].at(vector[i]).at(vector[k]) + f[(k - 1) % 2].at(vector[k]).at(vector[j]));
			}
		}
	}

	distances = f[(graph.size() + 1) % 2];
}
