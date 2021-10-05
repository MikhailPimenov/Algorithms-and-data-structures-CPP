#include "test_get_tangents.h"

void test_get_tangents(std::vector<Tangent>(*algorithm)(const Circle&, const Circle&)) {
	std::cout << "test_get_tangents:\n";

	std::vector<Tangent> tangents_actual;
	std::vector<Tangent> tangents_expected;

	Circle c1(0.0, 0.0, 2.0);
	Circle c2(5.0, 0.0, 2.0);

	
	tangents_expected.emplace_back(Tangent(Point(0.0, -2.0), Point(5.0, -2.0), c1, c2));
	tangents_expected.emplace_back(Tangent(Point(0.0, 2.0), Point(5.0, 2.0), c1, c2));
	tangents_expected.emplace_back(Tangent(Point(0.0, -2.0), Point(5.0, -2.0), c1, c2));
	tangents_expected.emplace_back(Tangent(Point(0.0, -2.0), Point(5.0, -2.0), c1, c2));
	
}
