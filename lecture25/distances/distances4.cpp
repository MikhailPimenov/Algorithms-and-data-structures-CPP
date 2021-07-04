#include "distances4.h"

void distances4(const Lists_t& G, Distances_t& distances_out, Vertex_t start) {
	Queue_t queue;
	queue.push(start);
	distances_out.insert(std::pair<Vertex_t, int>(start, 0));

	while (! queue.empty()) {
		Vertex_t vertex = queue.front();
		queue.pop(); // does it pop from front?

		for (Vertex_t neighbor : G.at(vertex)) {
			if (distances_out.find(neighbor) == distances_out.cend()) {
				distances_out.insert(
					std::pair<Vertex_t, int>(
						neighbor, 1 + distances_out.at(vertex)));
				queue.push(neighbor);
			}
		}
	}
}
