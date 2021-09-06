#include "test_r1.h"

void test_r1(void (*algorithm)(int, const Graph_t&, Graph_t&)) {
	std::cout << "test_r1:\n";

	Graph_t graph;
	Graph_t required_actual;
	Graph_t required_expected;

	int current_vertex;
	int second_vertex;
	
	current_vertex = 2;
	second_vertex = 1;

	graph.insert(std::pair<int, Vertexes_t>(second_vertex, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ 3, 4, 5 }));
	graph.insert(std::pair<int, Vertexes_t>(3, Vertexes_t()));
	graph.insert(std::pair<int, Vertexes_t>(4, Vertexes_t()));
	graph.insert(std::pair<int, Vertexes_t>(5, Vertexes_t()));
	
	
	required_expected.insert(std::pair<int, Vertexes_t>(second_vertex, Vertexes_t{ current_vertex }));
	
	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #1: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();


	current_vertex = 2;
	second_vertex = 1;

	graph.insert(std::pair<int, Vertexes_t>(second_vertex, Vertexes_t()));
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(3, Vertexes_t{current_vertex}));
	graph.insert(std::pair<int, Vertexes_t>(4, Vertexes_t{current_vertex}));
	graph.insert(std::pair<int, Vertexes_t>(5, Vertexes_t{current_vertex}));


	required_expected.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex }));

	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #2: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();


	current_vertex = 2;
	second_vertex = 1;

	graph.insert(std::pair<int, Vertexes_t>(second_vertex, Vertexes_t{current_vertex}));
	required_expected.insert(std::pair<int, Vertexes_t>(second_vertex, Vertexes_t{ current_vertex }));

	second_vertex = 3;
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex }));
	required_expected.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex }));



	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #3: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();

	
	current_vertex = 2;
	graph.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ 10, 11, 12 }));
	graph.insert(std::pair<int, Vertexes_t>(110, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(111, Vertexes_t{ current_vertex }));
	graph.insert(std::pair<int, Vertexes_t>(112, Vertexes_t{ current_vertex }));


	algorithm(current_vertex, graph, required_actual);
	std::cout << "test #4: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	graph.clear();
	required_expected.clear();
	required_actual.clear();
	

}