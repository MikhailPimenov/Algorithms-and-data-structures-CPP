#include "horse_path2.h"

void set_vertex(Vertex2_t& vertex, int letter_index, int number_index)
{
	static std::string letters("abcdefgh");
	static std::string numbers("12345678");
	vertex.resize(2);

	vertex.at(0) = letters.at(static_cast<std::size_t>(letter_index));
	vertex.at(1) = numbers.at(static_cast<std::size_t>(number_index));
}
void add_vertex(Lists2_t& graph, int letter_index, int number_index)
{
	Vertex2_t vertex;
	set_vertex(vertex, letter_index, number_index);
	graph.insert(std::pair < Vertex2_t, Vertexes2_t>(vertex, Vertexes2_t()));
}
void add_edge(Lists2_t& graph, int letter_index1, int number_index1,
	int letter_index2, int number_index2)
{
	Vertex2_t vertex1;
	Vertex2_t vertex2;

	set_vertex(vertex1, letter_index1, number_index1);
	set_vertex(vertex2, letter_index2, number_index2);

	graph.at(vertex1).insert(vertex2);
	graph.at(vertex2).insert(vertex1);
}

void create_graph(Lists2_t& graph)
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			add_vertex(graph, i, j);

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (i + 2 < 8 && j + 1 < 8)
				add_edge(graph, i + 2, j + 1, i, j);
			if (i + 1 < 8 && j + 2 < 8)
				add_edge(graph, i + 1, j + 2, i, j);
			if (i - 2 >= 0 && j - 1 >= 0)
				add_edge(graph, i - 2, j - 1, i, j);
			if (i - 1 >= 0 && j - 2 >= 0)
				add_edge(graph, i - 1, j - 2, i, j);
			if (i - 2 >= 0 && j + 1 < 8)
				add_edge(graph, i - 2, j + 1, i, j);
			if (i - 1 >= 0 && j + 2 < 8)
				add_edge(graph, i - 1, j + 2, i, j);
			if (i + 2 < 8 && j - 1 >= 0)
				add_edge(graph, i + 2, j - 1, i, j);
			if (i + 1 < 8 && j - 2 >= 0)
				add_edge(graph, i + 1, j - 2, i, j);
		}
	}
}

void horse_path2(Path2_t& path, const Vertex2_t& start, const Vertex2_t& finish)
{
	Lists2_t graph;
	create_graph(graph);

	Queue2_t q;
	q.push(start);
	Vertex2_t vertex = start;
	Distances2_t distances;
	distances.insert(std::pair<Vertex2_t, int>(start, 0));

	bool stop = false;
	while (!q.empty() && !stop) {
		vertex = q.front();
		q.pop();

		for (const auto& neighbor : graph.at(vertex)) {
			if (distances.find(neighbor) == distances.cend()) {
				distances.insert(std::pair<Vertex2_t, int>(neighbor, distances.at(vertex) + 1));
				if (neighbor == finish) {
					stop = true;
					break;
				}
				q.push(neighbor);
			}
		}
	}

	if (distances.find(finish) == distances.cend()) return;

	path.resize(distances.at(finish) + 1);
	std::size_t index = distances.at(finish);
	path.at(index) = finish;
	--index;
	vertex = finish;

	while (vertex != start) {
		for (const auto& neighbor : graph.at(vertex)) {
			if (distances.find(neighbor) != distances.cend() &&
				distances.at(neighbor) == distances.at(vertex) - 1) {
				path.at(index) = neighbor;
				--index;
				vertex = neighbor;
				break;
			}
		}
	}
}
