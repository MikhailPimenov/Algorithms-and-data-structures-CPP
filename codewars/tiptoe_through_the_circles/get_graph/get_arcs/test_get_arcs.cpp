#include "test_get_arcs.h"

void test_get_arcs(Arcs_t(*algorithm)(const Points_t&, const Circle&)) {
	std::cout << "test_get_arcs:\n";
	Arcs_t arcs_expected;
	Arcs_t arcs_actual;

	Circle c1(0.0, 0.0, 2.0);
	Points_t points1;
	
	points1.emplace(2.0, 0.0);
	points1.emplace(0.0, 2.0);
	arcs_expected.emplace(Point(2.0, 0.0), Point(0.0, 2.0), c1);
	arcs_expected.emplace(Point(0.0, 2.0), Point(2.0, 0.0), c1);

	arcs_actual = algorithm(points1, c1);

	std::cout << "test  #1: " <<
		(arcs_actual == arcs_expected ? "ok" : "FAILED") << '\n';
	arcs_actual.clear();
	arcs_expected.clear();


	Circle c2(c1);
	Points_t points2;

	points2.emplace(2.0, 0.0);
	points2.emplace(0.0, 2.0);
	points2.emplace(-2.0, 0.0);
	arcs_expected.emplace(Point(2.0, 0.0), Point(0.0, 2.0), c2);
	arcs_expected.emplace(Point(0.0, 2.0), Point(2.0, 0.0), c2);
	arcs_expected.emplace(Point(-2.0, 0.0), Point(0.0, 2.0), c2);
	arcs_expected.emplace(Point(0.0, 2.0), Point(-2.0, 0.0), c2);
	arcs_expected.emplace(Point(2.0, 0.0), Point(-2.0, 0.0), c2);
	arcs_expected.emplace(Point(-2.0, 0.0), Point(2.0, 0.0), c2);

	arcs_actual = algorithm(points2, c2);

	std::cout << "test  #2: " <<
		(arcs_actual == arcs_expected ? "ok" : "FAILED") << '\n';
	arcs_actual.clear();
	arcs_expected.clear();


	Circle c3(1.0, 1.0, 2.0);
	Points_t points3;

	points3.emplace(3.0, 1.0);
	points3.emplace(1.0, 3.0);
	points3.emplace(-1.0, 1.0);
	arcs_expected.emplace(Point(3.0, 1.0), Point(1.0, 3.0), c3);
	arcs_expected.emplace(Point(1.0, 3.0), Point(3.0, 1.0), c3);
	arcs_expected.emplace(Point(-1.0, 1.0), Point(1.0, 3.0), c3);
	arcs_expected.emplace(Point(1.0, 3.0), Point(-1.0, 1.0), c3);
	arcs_expected.emplace(Point(3.0, 1.0), Point(-1.0, 1.0), c3);
	arcs_expected.emplace(Point(-1.0, 1.0), Point(3.0, 1.0), c3);

	arcs_actual = algorithm(points3, c3);

	std::cout << "test  #3: " <<
		(arcs_actual == arcs_expected ? "ok" : "FAILED") << '\n';
	arcs_actual.clear();
	arcs_expected.clear();


	Circle c4(1.0, 1.0, 1.0);
	Points_t points4;

	points4.emplace(2.0, 1.0);
	points4.emplace(1.0, 2.0);
	points4.emplace(0.0, 1.0);
	arcs_expected.emplace(Point(0.0, 1.0), Point(2.0, 1.0), c4);
	arcs_expected.emplace(Point(2.0, 1.0), Point(0.0, 1.0), c4);
	arcs_expected.emplace(Point(2.0, 1.0), Point(1.0, 2.0), c4);
	arcs_expected.emplace(Point(1.0, 2.0), Point(2.0, 1.0), c4);
	arcs_expected.emplace(Point(0.0, 1.0), Point(1.0, 2.0), c4);
	arcs_expected.emplace(Point(1.0, 2.0), Point(0.0, 1.0), c4);
	
	arcs_actual = algorithm(points4, c4);

	std::cout << "test  #4: " <<
		(arcs_actual == arcs_expected ? "ok" : "FAILED") << '\n';
	arcs_actual.clear();
	arcs_expected.clear();


	Circle c5(1.0, 1.0, 1.0);
	Points_t points5;

	points5.emplace(1.0, 2.0);
	points5.emplace(1.0, 0.0);
	arcs_expected.emplace(Point(1.0, 0.0), Point(1.0, 2.0), c5);
	arcs_expected.emplace(Point(1.0, 2.0), Point(1.0, 0.0), c5);

	arcs_actual = algorithm(points5, c5);

	std::cout << "test  #5: " <<
		(arcs_actual == arcs_expected ? "ok" : "FAILED") << '\n';
	arcs_actual.clear();
	arcs_expected.clear();

}
