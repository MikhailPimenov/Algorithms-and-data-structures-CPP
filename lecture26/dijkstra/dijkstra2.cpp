#include "dijkstra2.h"


int calculate_maximum(const Lists3_t& graph)
{
	int maximum = 0;
	for (const auto& vertex_and_neighbours : graph)
		for (const auto& neighbor_and_cost : vertex_and_neighbours.second)
			maximum += neighbor_and_cost.second;

	return 5 * maximum;
}
void dijkstra2(const Lists3_t& graph, Vertex3_t start, Distances3_t& distances)
{
	Queue3_t q;
	q.push(start);

	int maximum = calculate_maximum(graph);

	for (const auto& vertex_and_neighbours : graph)
		distances.insert(std::pair < Vertex3_t, int>(vertex_and_neighbours.first, maximum));

	distances.at(start) = 0;


	while (!q.empty()) {
		Vertex3_t vertex = q.front();
		q.pop();
		for (const auto& neighbor_and_cost : graph.at(vertex)) {
			const int& edge = neighbor_and_cost.second;
			int& distance_neighbor = distances.at(neighbor_and_cost.first);
			int& distance_vertex = distances.at(vertex);

			if (distance_vertex + edge < distance_neighbor) {
				distance_neighbor = distance_vertex + edge;
				q.push(neighbor_and_cost.first);
			}
		}
	}
}
