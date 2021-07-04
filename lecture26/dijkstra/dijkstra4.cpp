#include "dijkstra4.h"

namespace Dijkstra4 {
	int get_unreachable_maximum(const Lists3_t& G) {
		int maximum = 0;
		for (const auto& vn : G) {
			for (const auto& nd : vn.second) {
				maximum += nd.second;
			}
		}

		return maximum * 10;
	}
}

void dijkstra4(const Lists3_t& G, Vertex3_t start, Distances3_t& d_out) {
	Queue3_t q;
	q.push(start);

	int maximum = Dijkstra4::get_unreachable_maximum(G);
	for (const auto& vn : G) {
		d_out.insert(std::pair<Vertex3_t, int>(vn.first, maximum));
	}
	d_out.at(start) = 0;

	while (!q.empty()) {


		/*
		Taking vertex from the front of the queue
		*/
		Vertex3_t v = q.front();


		/*
		Removing vertex from the front of the queue
		*/
		q.pop();


		/*
		Iterating on all neighbors of the vertex
		*/
		for (const auto& nd : G.at(v)) {
			

			/*
			Old distance to the neighbor of the vertex
			*/
			int& old_d = d_out.at(nd.first);


			/*
			New distance to the neighbor of the vertex. New distance equals to 
			distance to the vertex plus weight of the edge between the vertex and this neighbor
			*/
			int new_d = d_out.at(v) + nd.second;


			/*
			If new distance is "better", than the old one, updating distance and 
			adding neighbor to the end of the queue
			*/
			if (new_d < old_d) {
				old_d = new_d;
				q.push(nd.first);
			}
		}
	}
}
