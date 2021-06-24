#include "distances3.h"

void distances3(const Lists_t& g, Distances_t& d, Vertex_t start)
{
	Queue_t q;
	q.push(start);

	d.insert(std::pair<Vertex_t, int>(start, 0));

	while (!q.empty()) {
		Vertex_t vertex = q.front();
		q.pop();

		for (Vertex_t neighbor : g.at(vertex)) {
			if (d.find(neighbor) == d.cend()) {
				d.insert(std::pair<Vertex_t, int>(neighbor, 1 + d.at(vertex)));
				q.push(neighbor);
			}
		}
	}
}
