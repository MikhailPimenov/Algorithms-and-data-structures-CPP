#include "test_r2.h"

void test_r2(void (*algorithm)(int, const Graph_t&, Graph_t&)) {
	std::cout << "test_r2:\n";

	Graph_t graph;
	Graph_t required_actual;
	Graph_t required_expected;

	int current_vertex;
	int second_vertex1, second_vertex2;
	
	current_vertex = 2;
	second_vertex1 = 1;
	second_vertex2 = 3;

	graph.insert(std::pair<int, Vertexes_t>(second_vertex1, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(second_vertex2, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex1, second_vertex2 }));

	required_expected = graph;

	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #1: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();


	current_vertex = 2;
	second_vertex1 = 1;
	second_vertex2 = 3;

	graph.insert(std::pair<int, Vertexes_t>(second_vertex1, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(second_vertex2, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(4, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(5, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(6, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex1, second_vertex2, 4, 5, 6 }));

	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #2: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();
}