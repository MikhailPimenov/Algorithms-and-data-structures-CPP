#include "test_get_distance_from_line.h"


void test_get_distance_from_line(double (*algorithm)(const Circle&, const Tangent&)) {
	std::cout << "test_get_distance_from_line:\n";

	double length_expected = 0.0;
	double length_actual = -1.0;

	Circle c1(0.0, 0.0, 2.0);
	Tangent t1(
		Point(10.0, 0.0),
		Point(10.0, 10.0),
		Circle(11.0, 0.0, 1.0),
		Circle(11.0, 10.0, 1.0)
		);
	length_expected = 10.0;

	length_actual = algorithm(c1, t1);
	std::cout << "test  #1: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';

	Circle c2(c1);
	Tangent t2(
		Point(0.0, 100.0),
		Point(100.0, 100.0),
		Circle(0.0, 99.0, 1.0),
		Circle(100.0, 101.0, 1.0)
	);
	length_expected = 100.0;

	length_actual = algorithm(c2, t2);
	std::cout << "test  #2: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';

	Circle c3(c1);
	Tangent t3(
		Point(10.0, 0.0),
		Point(0.0, 10.0),
		Circle(12.0, 2.0, 2.0 * std::sqrt(2.0)),
		Circle(2.0, 12.0, 2.0 * std::sqrt(2.0))
	);
	length_expected = 5.0 * std::sqrt(2.0);

	length_actual = algorithm(c3, t3);
	std::cout << "test  #3: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


}