#include "test_get_graph.h"


void test_get_graph(Graph_t(*algorithm)(const Point&, const Point&, const std::vector<Circle>&)) {
	std::cout << "test_get_graph:\n";
	Graph_t expected;
	Graph_t actual;
	std::vector<Circle> circles;
	Points_t points;
/*
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
	*/

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
	//auto difference = expected - actual;
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
	

}
