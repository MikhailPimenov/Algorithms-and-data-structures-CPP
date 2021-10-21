#include "test_get_graph.h"

void show_difference(const Graph_t& left, const Graph_t& right) {
	const auto hash_function_right = right.hash_function();
	const auto hash_function_left = left.hash_function();
	
	std::cout << "left:\n";
	for (const auto& [vertex, _] : left) {
		std::cout << "Point(" << vertex.m_x << ", " << vertex.m_y << "): " <<
			hash_function_left(vertex) << '\n';
	}

	std::cout << "right:\n";
	for (const auto& [vertex, _] : right) {
		std::cout << "Point(" << vertex.m_x << ", " << vertex.m_y << "): " <<
			hash_function_left(vertex) << '\n';
	}


	if (left.size() != right.size()) {
		std::cout << "There is a different amount of vertices in the graph!\n";
		return;
	}
	for (const auto& [vertex, _] : left) {
		std::cout << "left: " << hash_function_left(vertex) << '\n';
		
		if (right.find(vertex) == right.cend()) {
			std::cout << "right: " << hash_function_right(vertex) << '\n';
			std::cout << "There is no vertex Point(" << vertex.m_x << ", " <<
				vertex.m_y << ") in right!\n";
			return;
		}
	}


	for (const auto& [vertex, left_vertices] : left) {
		if (left_vertices.size() != right.at(vertex).size()) {
			std::cout << "For vertex Point(" << vertex.m_x << ", " <<
				vertex.m_y << ") there is a different amount of neighbors!\n";
			return;
		}

		for (const auto& [neighbor, _] : left_vertices) {
			if (right.at(vertex).find(neighbor) == right.at(vertex).cend()) {
				std::cout << "For vertex Point(" << vertex.m_x << ", " <<
					vertex.m_y << ") there is no neighbor Point(" << neighbor.m_x << ", " <<
					neighbor.m_y << ") in right!\n";
			}
		}


		if (left_vertices != right.at(vertex)) {
			for (const auto& [neighbor, _] : left_vertices) {
				const auto left_range = left_vertices.equal_range(neighbor);
				std::unordered_multiset<Length_t, Length_t_hash> left_distances;
				for (auto iterator = left_range.first; iterator != left_range.second; ++iterator) {
					left_distances.emplace(iterator->second);
				}
				
				const auto right_range = right.at(vertex).equal_range(neighbor);
				std::unordered_multiset<Length_t, Length_t_hash> right_distances;
				for (auto iterator = right_range.first; iterator != right_range.second; ++iterator) {
					right_distances.emplace(iterator->second);
				}

				if (left_distances != right_distances) {
					if (left_distances.size() != right_distances.size()) {
						std::cout << "For vertex Point(" << vertex.m_x << ", " <<
							vertex.m_y << ") for neighbor Point(" << neighbor.m_x << ", " <<
							neighbor.m_y << ") there is a different amount of edges!\n";
					}
					for (const auto& distance : left_distances) {
						if (right_distances.find(distance) == right_distances.cend()) {
							std::cout << "For vertex Point(" << vertex.m_x << ", " <<
								vertex.m_y << ") for neighbor Point(" << neighbor.m_x << ", " <<
								neighbor.m_y << ") there is no edge " << distance << "!\n";
						}
					}
				}
			}
		}



		// A : { B: 10, B: 20, C: 5, C: 25, D: 41, E: 5}
		// B : { A: 10, A: 20, C: 23, C: 7, D: 21}
		// ...

		// Vertices_t:  B: 10, B: 20

		//const auto left_range = left_vertices.equal_range(vertex);
		//		
		//
		//const Vertices_t right_vertices = right.at(vertex);
		//const auto right_range = right_vertices.equal_range(vertex);
		//for (auto it = right_range.first; it != right_range.second; ++it) {
		//	//right_vertices.emplace(it->second);
		//}

		//if (left_vertices != right_vertices) {
		//	if (left_vertices.size() != right_vertices.size()) {
		//		std::cout << "At vertex " << "Point(" << vertex.m_x << ", " <<
		//			vertex.m_y << ") " << "there is a different amount of neighbors!\n";
		//		return;
		//	}

		//	std::cout << "Point(" << vertex.m_x << ", " << vertex.m_y << "): ";
		//	for (const auto& neighbor : left_vertices) {
		//		std::cout << "Point(" << neighbor.first.m_x << "), " <<
		//			neighbor.first.m_y << "), distance = " << 
		//			neighbor.second.m_value << '\n';
 	//		}
		//}
	}

}
void test_get_graph(Graph_t(*algorithm)(const Point&, const Point&, const std::vector<Circle>&)) {
	std::cout << "test_get_graph:\n";
	Graph_t expected;
	Graph_t actual;
	std::vector<Circle> circles;
	Points_t points;

	Point a1(-1.0, 0.0);
	Point b1(1.0, 0.0);
	expected.emplace(
		std::pair<Vertex_t, Vertices_t>(
			a1, Vertices_t{ std::pair<Vertex_t, double>(b1, 2.0) }));
	expected.emplace(
		std::pair<Vertex_t, Vertices_t>(
			b1, Vertices_t{ std::pair<Vertex_t, double>(a1, 2.0) }));

	actual = algorithm(a1, b1, circles);

	std::cout << "test  #1: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	expected.clear();
	actual.clear();
	circles.clear();


	Point a2(0.0, 0.0);
	Point b2(2.0, 2.0);
	
	circles.emplace_back(Point(1.0, 1.0), 1.0);
	expected.emplace(std::pair<Vertex_t, Vertices_t>(a2, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 1.0)
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(b2, Vertices_t{ 
		std::pair<Vertex_t, double>(Point(1.0, 2.0), 1.0), 
		std::pair<Vertex_t, double>(Point(2.0, 1.0), 1.0) 
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(a2, 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(2.0, 1.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(2.0, 1.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0, 2.0), g_pi),
		std::pair<Vertex_t, double>(Point(1.0, 2.0), g_pi),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(a2, 1.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0, 2.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0, 2.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(2.0, 1.0), g_pi),
		std::pair<Vertex_t, double>(Point(2.0, 1.0), g_pi),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(b2, 1.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0, 2.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0, 2.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b2, 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(2.0, 1.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(2.0, 1.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi),

		}));


	actual = algorithm(a2, b2, circles);

	std::cout << "test  #2: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	expected.clear();
	actual.clear();
	circles.clear();
	

	Point a3(0.0, 0.0);
	Point b3(1.0, 1.0 - std::sqrt(2.0));

	circles.emplace_back(Point(1.0, 1.0), 1.0);
	expected.emplace(std::pair<Vertex_t, Vertices_t>(a3, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 1.0),
		std::pair<Vertex_t, double>(b3, std::sqrt(4.0 - 2.0 * std::sqrt(2.0)))
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(b3, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 1.0),
		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 1.0),
		std::pair<Vertex_t, double>(a3, std::sqrt(4.0 - 2.0 * std::sqrt(2.0)))
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(a3, 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 7.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 7.0 * g_pi / 4.0),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(a3, 1.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 3.0 * g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 7.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 5.0 * g_pi / 4.0),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b3, 1.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 7.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 5.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 2.0),

	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b3, 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 7.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 4.0),
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 7.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 2.0),
		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 2.0),

	}));


	actual = algorithm(a3, b3, circles);

	std::cout << "test  #3: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	expected.clear();
	actual.clear();
	circles.clear();
	

	Point a4(0.0, 0.0);
	Point b4(3.0, 3.0);

	circles.emplace_back(Point(1.0, 1.0), 1.0);
	circles.emplace_back(Point(2.0, 2.0), 1.0);
	expected.emplace(std::pair<Vertex_t, Vertices_t>(a4, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(b4, Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), 1.0),
		std::pair<Vertex_t, double>(Point(2.0, 3.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(a4, 1.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0)
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(a4, 1.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0)
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), std::sqrt(2.0)),
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), std::sqrt(2.0)),
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0, 3.0), Vertices_t{
		std::pair<Vertex_t, double>(b4, 1.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(3.0, 2.0), g_pi / 2.0)
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(3.0, 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b4, 1.0),

		std::pair<Vertex_t, double>(Point(2.0, 3.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0)
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0, 3.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), g_pi),
		
		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), std::sqrt(2.0))
	}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(2.0, 3.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(3.0, 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), std::sqrt(2.0))
	}));
	
	actual = algorithm(a4, b4, circles);

	std::cout << "test  #4: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	
	expected.clear();
	actual.clear();
	circles.clear();


	Point a5(0.0, 0.0);
	Point b5(3.0, 3.0);

	circles.emplace_back(Point(1.0, 1.0), 1.0);
	circles.emplace_back(Point(2.0, 2.0), 1.0);
	circles.emplace_back(Point(1.5, 1.5), 0.5);
	expected.emplace(std::pair<Vertex_t, Vertices_t>(a5, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(b5, Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), 1.0),
		std::pair<Vertex_t, double>(Point(2.0, 3.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(a5, 1.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(a5, 1.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), std::sqrt(2.0)),
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), std::sqrt(2.0)),
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0, 3.0), Vertices_t{
		std::pair<Vertex_t, double>(b5, 1.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(3.0, 2.0), g_pi / 2.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(3.0, 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b5, 1.0),

		std::pair<Vertex_t, double>(Point(2.0, 3.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), g_pi / 4.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0, 3.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(1.0 + std::sqrt(2.0) / 2.0, 1.0 - std::sqrt(2.0) / 2.0), std::sqrt(2.0))
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0 - std::sqrt(2.0) / 2.0, 2.0 + std::sqrt(2.0) / 2.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(2.0, 3.0), g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(3.0, 2.0), 3.0 * g_pi / 4.0),

		std::pair<Vertex_t, double>(Point(2.0 + std::sqrt(2.0) / 2.0, 2.0 - std::sqrt(2.0) / 2.0), g_pi),

		std::pair<Vertex_t, double>(Point(1.0 - std::sqrt(2.0) / 2.0, 1.0 + std::sqrt(2.0) / 2.0), std::sqrt(2.0))
		}));

	actual = algorithm(a5, b5, circles);

	std::cout << "test  #5: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	expected.clear();
	actual.clear();
	circles.clear();
	


	Point a6(0.0, 0.0);
	Point b6(3.0, 3.0);

	circles.emplace_back(Point(1.0, 1.0), 1.0);
	circles.emplace_back(Point(2.0, 2.0), 1.0);
	circles.emplace_back(Point(1.5, 1.5), 1.5);
	expected.emplace(std::pair<Vertex_t, Vertices_t>(a6, Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 1.0),
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(b6, Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), 1.0),
		std::pair<Vertex_t, double>(Point(2.0, 3.0), 1.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.0, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(a6, 1.0),

		std::pair<Vertex_t, double>(Point(0.0, 1.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.5, 0.0), 0.5),
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.0), Vertices_t{
		std::pair<Vertex_t, double>(a6, 1.0),

		std::pair<Vertex_t, double>(Point(1.0, 0.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.5, 0.0), 0.5)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.5, 0.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(1.0, 0.0), 0.5),

		std::pair<Vertex_t, double>(Point(3.0, 1.5), 1.5 * g_pi / 2.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(0.0, 1.5), Vertices_t{
		std::pair<Vertex_t, double>(Point(0.0, 1.0), 0.5),

		std::pair<Vertex_t, double>(Point(1.5, 3.0), 1.5 * g_pi / 2.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(2.0, 3.0), Vertices_t{
		std::pair<Vertex_t, double>(b6, 1.0),

		std::pair<Vertex_t, double>(Point(3.0, 2.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(1.5, 3.0), 0.5)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(3.0, 2.0), Vertices_t{
		std::pair<Vertex_t, double>(b6, 1.0),

		std::pair<Vertex_t, double>(Point(2.0, 3.0), g_pi / 2.0),

		std::pair<Vertex_t, double>(Point(3.0, 1.5), 0.5)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(3.0, 1.5), Vertices_t{
		std::pair<Vertex_t, double>(Point(3.0, 2.0), 0.5),

		std::pair<Vertex_t, double>(Point(1.5, 0.0), 3.0 * g_pi / 2.0)
		}));
	expected.emplace(std::pair<Vertex_t, Vertices_t>(Point(1.5, 3.0), Vertices_t{
		std::pair<Vertex_t, double>(Point(2.0, 3.0), 0.5),

		std::pair<Vertex_t, double>(Point(0.0, 1.5), 3.0 * g_pi / 2.0)
		}));


	actual = algorithm(a6, b6, circles);

	std::cout << "test  #6: " << ((actual == expected) ? "ok" : "FAILED") << '\n';
	if (actual != expected)
		show_difference(actual, expected);
	
	expected.clear();
	actual.clear();
	circles.clear();
}
