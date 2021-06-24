#include "horse_path3.h"

namespace Horse_path3 {
	void set_vertex(Vertex2_t& vertex, int i, int j) {
		static const std::string letters("abcdefgh");
		static const std::string numbers("12345678");
		vertex.resize(2);
		vertex[0] = letters[static_cast<std::size_t>(i)];
		vertex[1] = numbers[static_cast<std::size_t>(j)];
	}
	void add_vertex(Lists2_t& g, int i, int j) {
		Vertex2_t v1;
		set_vertex(v1, i, j);
		g.insert(std::pair<Vertex2_t, Vertexes2_t>(v1, Vertexes2_t()));
	}
	void add_edge(Lists2_t& g, int i1, int j1, int i2, int j2) {
		Vertex2_t v1;
		set_vertex(v1, i1, j1);
		Vertex2_t v2;
		set_vertex(v2, i2, j2);

		g.at(v1).insert(v2);
		g.at(v2).insert(v1);
	}
	void create_graph(Lists2_t& g) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				add_vertex(g, i, j);
			}
		}

		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (i + 2 < 8 && j + 1 < 8)
					add_edge(g, i, j, i + 2, j + 1);
				if (i + 1 < 8 && j + 2 < 8)
					add_edge(g, i, j, i + 1, j + 2);
				if (i - 2 >= 0 && j - 1 >= 0)
					add_edge(g, i, j, i - 2, j - 1);
				if (i - 1 >= 0 && j - 2 >= 0)
					add_edge(g, i, j, i - 1, j - 2);
				if (i - 2 >= 0 && j + 1 < 8)
					add_edge(g, i, j, i - 2, j + 1);
				if (i - 1 >= 0 && j + 2 < 8)
					add_edge(g, i, j, i - 1, j + 2);
				if (i + 2 < 8 && j - 1 >= 0)
					add_edge(g, i, j, i + 2, j - 1);
				if (i + 1 < 8 && j - 2 >= 0)
					add_edge(g, i, j, i + 1, j - 2);
			}
		}
	}
}

void horse_path3(Path2_t& path, const Vertex2_t& start, const Vertex2_t& finish)
{
	Lists2_t g;
	Horse_path3::create_graph(g);
	
	Queue2_t q;
	q.push(start);
	
	Distances2_t d;
	d.insert(std::pair<Vertex2_t, int>(start, 0));

	bool finish_is_found = false;
	while (!q.empty() && !finish_is_found) {
		const Vertex2_t vertex = q.front();
		q.pop();

		for (const auto& neighbor : g.at(vertex)) {
			if (d.find(neighbor) == d.cend()) {
				d.insert(std::pair<Vertex2_t, int>(neighbor, 1 + d.at(vertex)));
				q.push(neighbor);
				if (neighbor == finish) {
					finish_is_found = true;
					break;
				}
			}
		}
	}

	if (!finish_is_found) return;

	path.resize(d.at(finish) + 1);
	int i = d.at(finish);
	path[i] = finish;
	--i;

	Vertex2_t vertex = finish;
	while (vertex != start) {
		for (const auto& neighbor : g.at(vertex)) {
			if (d.find(neighbor) != d.cend() && d.at(neighbor) == d.at(vertex) - 1) {
				path[i] = neighbor;
				--i;
				vertex = neighbor;
				break;
			}
		}
	}
}
