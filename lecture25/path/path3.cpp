#include "path3.h"

void path3(const Lists_t& g, Path_t& p, Vertex_t start, Vertex_t finish)
{
	Queue_t q;
	q.push(start);

	Distances_t d;
	d.insert(std::pair<Vertex_t, int>(start, 0));

	Vertex_t vertex = start;
	while (!q.empty() && vertex != finish) {
		vertex = q.front();
		q.pop();

		for (Vertex_t neighbor : g.at(vertex)) {
			if (d.find(neighbor) == d.cend()) {
				d.insert(std::pair<Vertex_t, int>(neighbor, 1 + d.at(vertex)));
				q.push(neighbor);
				if (neighbor == finish) {
					vertex = finish;
					break;
				}
			}
		}
	}

	if (vertex != finish) return;

	vertex = finish;
	p.resize(d.at(finish) + 1);
	int i = d.at(finish);
	p[i] = finish;
	--i;

	while (vertex != start) {
		for (Vertex_t neighbor : g.at(vertex)) {
			if (d.find(neighbor) != d.cend() && d.at(neighbor) == d.at(vertex) - 1) {
				p[i] = neighbor;
				--i;
				vertex = neighbor;
				break;
			}
		}
	}
}
