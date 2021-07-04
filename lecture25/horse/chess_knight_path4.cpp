#include "chess_knight_path4.h"

namespace Chess_knight_path4 {
	void create_vertex(Vertex2_t& vertex, int i, int j) {
		const static std::string letters("abcdefgh");
		const static std::string numbers("12345678");

		vertex.resize(2);
		vertex.at(0) = letters.at(i);
		vertex.at(1) = numbers.at(j);
	}

	void add_vertex(Lists2_t& G, int i, int j) {
		Vertex2_t vertex;
		create_vertex(vertex, i, j);

		if (G.find(vertex) == G.cend()) {
G.insert(std::pair<Vertex2_t, Vertexes2_t>(vertex, Vertexes2_t()));
		}
	}

	void add_edge(Lists2_t& G, int i1, int j1, int i2, int j2) {
		Vertex2_t v1, v2;
		create_vertex(v1, i1, j1);
		create_vertex(v2, i2, j2);

		if (G.find(v1) != G.cend()) {
			G.at(v1).insert(v2);
		}
	}

	void create_graph(Lists2_t& G) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				add_vertex(G, i, j);
			}
		}

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (i + 2 < 8 && j + 1 < 8) {
					add_edge(G, i + 2, j + 1, i, j);
					add_edge(G, i, j, i + 2, j + 1);
				}
				if (i + 1 < 8 && j + 2 < 8) {
					add_edge(G, i + 1, j + 2, i, j);
					add_edge(G, i, j, i + 1, j + 2);
				}
				if (i - 2 >= 0 && j - 1 >= 0) {
					add_edge(G, i - 2, j - 1, i, j);
					add_edge(G, i, j, i - 2, j - 1);
				}
				if (i - 1 >= 0 && j - 2 >= 0) {
					add_edge(G, i - 1, j - 2, i, j);
					add_edge(G, i, j, i - 1, j - 2);
				}
				if (i + 2 < 8 && j - 1 >= 0) {
					add_edge(G, i + 2, j - 1, i, j);
					add_edge(G, i, j, i + 2, j - 1);
				}
				if (i + 1 < 8 && j - 2 >= 0) {
					add_edge(G, i + 1, j - 2, i, j);
					add_edge(G, i, j, i + 1, j - 2);
				}
				if (i - 2 >= 0 && j + 1 < 8) {
					add_edge(G, i - 2, j + 1, i, j);
					add_edge(G, i, j, i - 2, j + 1);
				}
				if (i - 1 >= 0 && j + 2 < 8) {
					add_edge(G, i - 1, j + 2, i, j);
					add_edge(G, i, j, i - 1, j + 2);
				}
			}
		}
	}
}

void chess_knight_path4(Path2_t& path_out, const Vertex2_t& start, const Vertex2_t& finish) {
	Queue2_t q;
	Distances2_t d;
	Lists2_t G;
	Chess_knight_path4::create_graph(G);

	q.push(start);
	d.insert(std::pair<Vertex2_t, int>(start, 0));
	bool found = false;

	while (!q.empty() && !found) {
		const Vertex2_t& vertex = q.front();

		for (const auto& n : G.at(vertex)) {
			if (d.find(n) == d.cend()) {
				d.insert(std::pair<Vertex2_t, int>(n, d.at(vertex) + 1));

				if (n == finish) {
					found = true;
					break;
				}
				q.push(n);
			}
		}

		q.pop();
	}

	if (!found) {
		path_out.clear();
		return;
	}

	path_out.resize(d.at(finish) + 1);
	path_out.at(d.at(finish)) = finish;

	std::size_t k = d.at(finish) - 1;
	Vertex2_t vertex = finish;
	while (vertex != start) {
		for (const auto& n : G.at(vertex)) {
			if (d.find(n) != d.cend() && d.at(n) == d.at(vertex) - 1){
				path_out.at(k) = n;
				
				if (n == start) {
					return;
				}
				--k;
				vertex = n;
				break;
			}
		}
	}
}
