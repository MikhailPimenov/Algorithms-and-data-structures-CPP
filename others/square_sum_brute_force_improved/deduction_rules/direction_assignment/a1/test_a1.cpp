#include "test_a1.h"

void test_a1(void (*algorithm)(int, Graph_t&)) {
	std::cout << "test_a1:\n";

	Graph_t required_expected;
	Graph_t required_actual;

	int current_vertex;
	int second_vertex1;
	int second_vertex2;

	current_vertex = 2;
	second_vertex1 = 1;
	second_vertex2 = 3;

	required_actual.insert(std::pair<int, Vertexes_t>(second_vertex1, Vertexes_t{ current_vertex }));
	required_actual.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex2 }));
	required_actual.insert(std::pair<int, Vertexes_t>(second_vertex2, Vertexes_t{ current_vertex }));
	
	required_expected.insert(std::pair<int, Vertexes_t>(second_vertex1, Vertexes_t{ current_vertex }));
	required_expected.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex2 }));
	

	algorithm(current_vertex, required_actual);
	std::cout << "test #1: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	required_expected.clear();
	required_actual.clear();


	current_vertex = 2;
	second_vertex1 = 1;
	second_vertex2 = 3;

	required_actual.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex1, second_vertex2 }));
	required_actual.insert(std::pair<int, Vertexes_t>(second_vertex2, Vertexes_t{ current_vertex }));

	required_expected.insert(std::pair<int, Vertexes_t>(current_vertex, Vertexes_t{ second_vertex1 }));
	required_expected.insert(std::pair<int, Vertexes_t>(second_vertex2, Vertexes_t{ current_vertex }));


	algorithm(current_vertex, required_actual);
	std::cout << "test #2: " << (required_actual == required_expected ? "ok" : "FAILED") << '\n';
	required_expected.clear();
	required_actual.clear();

}