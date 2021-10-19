#include "test_there_is_collision_between_arc_and_circle.h"


void test_there_is_collision_between_arc_and_circle(
	bool (*algorithm)(const Arc&, const Circle&)
) {
	std::cout << "test_there_is_collision_between_arc_and_circle:\n";

	Circle owner(Point(0.0, 0.0), 2.0);
	bool result_expected = true;
	bool result_actual = false;


	Arc a1(
		Point(0.0, 2.0),
		Point(2.0, 0.0),
		owner
	);
	Circle c1(Point(4.0, 4.0), 2.0);
	result_expected = false;

	result_actual = algorithm(a1, c1);

	std::cout << "test  #1: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a2(a1);
	Circle c2(Point(1.0, 1.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a2, c2);

	std::cout << "test  #2: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a3(a1);
	Circle c3(Point(0.0, 0.0), 1.5);
	result_expected = false;

	result_actual = algorithm(a3, c3);

	std::cout << "test  #3: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a4(a1);
	Circle c4(Point(-1.0, 1.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a4, c4);

	std::cout << "test  #4: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a5(a1);
	Circle c5(Point(-1.0, -1.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a5, c5);

	std::cout << "test  #5: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a6(a1);
	Circle c6(Point(-3.0, 0.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a6, c6);

	std::cout << "test  #6: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a7(a1);
	Circle c7(Point(0.0, 3.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a7, c7);

	std::cout << "test  #7: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a8(a1);
	Circle c8(Point(3.0, 0.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a8, c8);

	std::cout << "test  #8: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a9(a1);
	Circle c9(Point(0.0, 3.0), 1.0);
	result_expected = true;

	result_actual = algorithm(a9, c9);

	std::cout << "test  #9: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a10(a1);
	Circle c10(Point(3.0, 3.0), 3.0 * std::sqrt(2.0) - 2.0);
	result_expected = true;

	result_actual = algorithm(a10, c10);

	std::cout << "test #10: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a11(a1);
	Circle c11(Point(3.0, 3.0), 3.0);
	result_expected = true;

	result_actual = algorithm(a11, c11);

	std::cout << "test #11: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a12(a1);
	Circle c12(Point(1.0, 1.0), 3.0);
	result_expected = true;

	result_actual = algorithm(a12, c12);

	std::cout << "test #12: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a13(a1);
	Circle c13(Point(2.0, 0.0), 2.0);
	result_expected = true;

	result_actual = algorithm(a13, c13);

	std::cout << "test #13: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a14(a1);
	Circle c14(Point(0.0, -1.0), 2.0);
	result_expected = false;

	result_actual = algorithm(a14, c14);

	std::cout << "test #14: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a15(a1);
	Circle c15(Point(-1.0, 1.0), 2.0);
	result_expected = true;

	result_actual = algorithm(a15, c15);

	std::cout << "test #15: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a16(a1);
	Circle c16(Point(-2.0, 3.0), 2.0);
	result_expected = false;

	result_actual = algorithm(a16, c16);

	std::cout << "test #16: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a17(a1);
	Circle c17(Point(-1.0, 3.0), 2.0);
	result_expected = true;

	result_actual = algorithm(a17, c17);

	std::cout << "test #17: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a18(a1);
	Circle c18(Point(1.0, 3.0), 0.5);
	result_expected = false;

	result_actual = algorithm(a18, c18);

	std::cout << "test #18: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a19(a1);
	Circle c19(Point(-1.0, 0.0), 2.0);
	result_expected = false;

	result_actual = algorithm(a19, c19);

	std::cout << "test #19: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a20(
		Point(-2.0, 0.0),
		Point(0.0, -2.0),
		owner
	);
	Circle c20(Point(2.0, 2.0), 1.0);
	result_expected = true;

	result_actual = algorithm(a20, c20);

	std::cout << "test #20: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a21(
		Point(0.0, -2.0),
		Point(-2.0, 0.0),
		owner
	);
	Circle c21(Point(2.0, 2.0), 1.0);
	result_expected = false;

	result_actual = algorithm(a21, c21);

	std::cout << "test #21: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a22(
		Point(0.0, 2.0),
		Point(-2.0, 0.0),
		owner
	);
	Circle c22(Point(-2.0, -2.0), 1.0);
	result_expected = true;

	result_actual = algorithm(a22, c22);

	std::cout << "test #22: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Arc a23(
		Point(0.0, 2.0),
		Point(-2.0, 0.0),
		owner
	);
	Circle c23(Point(-1.0, 0.0), 1.0);
	result_expected = false;

	result_actual = algorithm(a23, c23);

	std::cout << "test #23: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';
}