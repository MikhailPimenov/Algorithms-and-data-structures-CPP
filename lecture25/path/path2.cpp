#include "path2.h"

void path2(const Lists_t& graph, Path_t& path, Vertex_t start, Vertex_t finish)
{
	Queue_t q;
	q.push(start);
	Distances_t distances;
	distances.insert(std::pair<Vertex_t, int>(start, 0));

	Vertex_t vertex = start;
	while (!q.empty() && vertex != finish) {
		vertex = q.front();
		q.pop();
		for (Vertex_t neighbor : graph.at(vertex)) {
			if (distances.find(neighbor) == distances.cend()) {
				distances.insert(std::pair<Vertex_t, int>(neighbor, distances.at(vertex) + 1));
				if (neighbor == finish) break;
				q.push(neighbor);
			}
		}
	}

	if (distances.find(finish) == distances.cend()) return;

	vertex = finish;
	path.resize(distances.at(finish) + 1);
	int index = distances.at(finish);
	path.at(index) = finish;
	--index;

	while (vertex != start) {
		for (Vertex_t neighbor : graph.at(vertex))
			if (distances.find(neighbor) != distances.cend() &&
				distances.at(neighbor) == distances.at(vertex) - 1) {
				path.at(index) = neighbor;
				--index;
				vertex = neighbor;
				break;
			}
	}
}
