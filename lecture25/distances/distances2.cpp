#include "distances2.h"

void distances2(const Lists_t& graph, Distances_t& distances, Vertex_t start)
{
	Queue_t q;
	q.push(start);

	distances.insert(std::pair <Vertex_t, int>(start, 0));

	while (!q.empty()) {
		Vertex_t vertex = q.front();
		q.pop();

		for (Vertex_t neighbor : graph.at(vertex)) {
			if (distances.find(neighbor) == distances.cend()) {
				distances.insert(std::pair<Vertex_t, int>(neighbor,
					distances.at(vertex) + 1));
				q.push(neighbor);
			}
		}
	}
}
