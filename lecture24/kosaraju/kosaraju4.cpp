#include "kosaraju4.h"

namespace Kosaraju4 {
	void reverse_graph(const Lists_t& G, Lists_t& Gr_out) {
		for (const auto& vn : G) {
			Gr_out.insert(std::pair<Vertex_t, Vertexes_t>(vn.first, Vertexes_t()));
		}

		for (const auto& vn : G) {
			for (Vertex_t neighbor : vn.second) {
				Gr_out.at(neighbor).insert(vn.first);
			}
		}
	}

	void depth_first_search_forward(Vertex_t start, const Lists_t& G, Vertexes_t& used, Stack_t& stack) {
		used.insert(start);

		for (Vertex_t neighbor : G.at(start)) {
			if (used.find(neighbor) == used.cend()) {
				depth_first_search_forward(neighbor, G, used, stack);
			}
		}

		stack.push(start);
	}

	void depth_first_search_backward(Vertex_t start, const Lists_t& Gr, Vertexes_t& used, Component_t &component) {
		used.insert(start);
		component.insert(start);

		for (Vertex_t neighbor : Gr.at(start)) {
			if (used.find(neighbor) == used.cend()) {
				depth_first_search_backward(neighbor, Gr, used, component);
			}
		}
	}

}

int kosaraju4(const Lists_t& G, Components_t& components_out) {
	Vertexes_t used;
	Stack_t stack;

	for (const auto& vn : G) {
		if (used.find(vn.first) == used.cend()) {
			Kosaraju4::depth_first_search_forward(vn.first, G, used, stack);
		}
	}

	used.clear();
	Lists_t Gr;
	Kosaraju4::reverse_graph(G, Gr);
	components_out.clear();

	while ( !stack.empty() ) {
		Vertex_t vertex = stack.top();
		stack.pop();

		if (used.find(vertex) == used.cend()) {
			Component_t component;
			Kosaraju4::depth_first_search_backward(vertex, Gr, used, component);
			components_out.insert(component);
		}
	}

	return components_out.size();
}
