#include "test_there_is_collision_between_tangent_and_circle.h"

void test_there_is_collision_between_tangent_and_circle(
	bool (*algorithm)(const Tangent&, const Circle&)
) {
	std::cout << "test_there_is_collision_between_tangent_and_circle:\n";

	Circle dummy(Point(0.0, 0.0), 1.0);
	bool result_expected = true;
	bool result_actual = false;


	Tangent t1(
		Point(1.0, 1.0),
		Point(2.0, 2.0),
		dummy,
		dummy
	);
	Circle c1(Point(5.0, 5.0), 1.0);
	result_expected = false;

	result_actual = algorithm(t1, c1);

	std::cout << "test  #1: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t2(t1);
	Circle c2(Point(2.0, 5.0), 1.0);
	result_expected = false;

	result_actual = algorithm(t2, c2);

	std::cout << "test  #2: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t3(t1);
	Circle c3(Point(0.0, 3.0), 1.0);
	result_expected = false;

	result_actual = algorithm(t3, c3);

	std::cout << "test  #3: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t4(t1);
	Circle c4(Point(-2.0, 5.0), 4.0);
	result_expected = false;

	result_actual = algorithm(t4, c4);

	std::cout << "test  #4: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t5(t1);
	Circle c5(Point(-2.0, 2.0), 5.0);
	result_expected = true;

	result_actual = algorithm(t5, c5);

	std::cout << "test  #5: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t6(t1);
	Circle c6(Point(-0.5, 2.0), 2.0);
	result_expected = true;

	result_actual = algorithm(t6, c6);

	std::cout << "test  #6: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t7(t1);
	Circle c7(Point(0.0, 2.0), 2.0);
	result_expected = true;

	result_actual = algorithm(t7, c7);

	std::cout << "test  #7: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t8(t1);
	Circle c8(Point(-1.0, 1.0), 2.0);
	result_expected = true;

	result_actual = algorithm(t8, c8);

	std::cout << "test  #8: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t9(Point(-2.0, -2.0), Point(3.0, 1.0), dummy, dummy);
	Circle c9(c8);
	result_expected = false;

	result_actual = algorithm(t9, c9);

	std::cout << "test  #9: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t10(t9);
	Circle c10(Point(1.0, 2.0), 2.0);
	result_expected = true;

	result_actual = algorithm(t10, c10);

	std::cout << "test #10: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t11(Point(-2.0, -2.0), Point(-2.0, 4.0), dummy, dummy);
	Circle c11(c10);
	result_expected = false;

	result_actual = algorithm(t11, c11);

	std::cout << "test #11: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Tangent t12(t11);
	Circle c12(Point(0.0, 2.0), 2.0);
	result_expected = true;

	result_actual = algorithm(t12, c12);

	std::cout << "test #12: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';
}