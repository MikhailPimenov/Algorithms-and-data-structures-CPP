#include "dijkstra3.h"

namespace Dijkstra3 {
	int get_unreachable_maximum(const Lists3_t& g) {
		int maximum = 0;

		for (const auto& vn : g)
			for (const auto& vd : vn.second)
				maximum += vd.second;

		return maximum * 20;
	}
}

void dijkstra3(const Lists3_t& g, Vertex3_t start, Distances3_t &d)
{
	Queue3_t q;
	q.push(start);

	int maximum = Dijkstra3::get_unreachable_maximum(g);

	for (const auto& vn : g)
		d.insert(std::pair<Vertex3_t, int>(vn.first, maximum));

	d.at(start) = 0;

	while (!q.empty()) {
		Vertex3_t vertex = q.front();
		q.pop();

		for (const auto& nd : g.at(vertex)) {
			const int& edge = g.at(vertex).at(nd.first);
			int& n_d = d.at(nd.first);
			const int& vertex_d = d.at(vertex);
			if (n_d > vertex_d + edge) {
				n_d = vertex_d + edge;
				q.push(nd.first);
			}
		}	
	}
}
