#include "kosaraju2.h"

namespace Kosaraju2 {
	void depth_first_search_forward(const Lists_t& graph, Vertex_t vertex, Vertexes_t& used, Stack_t& stack)
	{
		used.insert(vertex);

		for (Vertex_t neighbor : graph.at(vertex))
			if (used.find(neighbor) == used.cend())
				depth_first_search_forward(graph, neighbor, used, stack);

		stack.push(vertex);
	}

	void depth_first_search_backward(const Lists_t& graph, Vertex_t vertex, Vertexes_t& used, Vertexes_t& component)
	{
		used.insert(vertex);
		component.insert(vertex);

		for (Vertex_t neighbor : graph.at(vertex))
			if (used.find(neighbor) == used.cend())
				depth_first_search_backward(graph, neighbor, used, component);
	}

	void reverse_graph(const Lists_t& graph, Lists_t& reversed_graph)
	{
		for (const auto& vertex_and_neighbours : graph)
			reversed_graph.insert(std::pair<Vertex_t, Vertexes_t>(vertex_and_neighbours.first, Vertexes_t()));

		for (const auto& vertex_and_neighbours : graph)
			for (Vertex_t vertex : vertex_and_neighbours.second)
				reversed_graph.at(vertex).insert(vertex_and_neighbours.first);

	}
}
int kosaraju_adapted2(const Lists_t& graph)
{
	Components_t components;
	return kosaraju2(graph, components);

}

int kosaraju2(const Lists_t& graph, Components_t& components_out)
{
	Vertexes_t used;
	Stack_t stack;

	for (const auto& vertex_and_neighbours : graph) {
		if (used.find(vertex_and_neighbours.first) == used.cend()) {
			Kosaraju2::depth_first_search_forward(graph, vertex_and_neighbours.first,
				used, stack);
		}
	}

	Lists_t reversed_graph;
	Kosaraju2::reverse_graph(graph, reversed_graph);
	used.clear();

	while (!stack.empty()) {
		Vertex_t vertex = stack.top();
		stack.pop();

		if (used.find(vertex) == used.cend()) {
			Vertexes_t component;
			Kosaraju2::depth_first_search_backward(reversed_graph, vertex, used, component);
			components_out.push_back(component);
		}

	}

	return static_cast<int>(components_out.size());
}
