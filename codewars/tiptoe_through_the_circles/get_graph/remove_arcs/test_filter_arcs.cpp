#include "test_filter_arcs.h"

void test_filter_arcs(void (*algorithm)(Arcs_t&, const std::vector<Circle>&)) {
	std::cout << "test_filter_arcs:\n";

	const Circle owner(Point(0.0, 0.0), 2.0);
	const Point a(2.0, 0.0);
	const Point b(0.0, 2.0);
	const Point c(-2.0, 0.0);
	const Point d(0.0, -2.0);
	std::vector<Circle> circles;
	Arcs_t expected;
	Arcs_t actual;


	Circle c11(Point(3.0, 3.0), 1.0);
	Circle c12(Point(5.0, 5.0), 1.0);
	Circle c13(Point(5.0, -5.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c11);
	circles.emplace_back(c12);
	circles.emplace_back(c13);
	
	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);
	
	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);
	
	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);
	
	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);
	
	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);

	expected = actual;

	algorithm(actual, circles);
	std::cout << "test  #1: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


	Circle c21(Point(3.0, 3.0), 1.0);
	Circle c22(Point(2.0, 2.0), 1.0);
	Circle c23(Point(5.0, -5.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c21);
	circles.emplace_back(c22);
	circles.emplace_back(c23);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	expected.emplace(a, b, owner);
	
	expected.emplace(a, c, owner);

	expected.emplace(a, d, owner);
	
	expected.emplace(c, b, owner);
	
	expected.emplace(d, b, owner);
	
	expected.emplace(d, c, owner);

	algorithm(actual, circles);
	std::cout << "test  #2: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


	Circle c31(Point(-2.0, -2.0), 1.0);
	Circle c32(Point(2.0, 2.0), 1.0);
	Circle c33(Point(5.0, -5.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c31);
	circles.emplace_back(c32);
	circles.emplace_back(c33);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	expected.emplace(a, d, owner);

	expected.emplace(c, b, owner);
	
	algorithm(actual, circles);
	std::cout << "test  #3: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


	Circle c41(Point(-2.0, -2.0), 1.0);
	Circle c42(Point(2.0, 2.0), 1.0);
	Circle c43(Point(2.0, -2.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c41);
	circles.emplace_back(c42);
	circles.emplace_back(c43);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	expected.emplace(c, b, owner);

	algorithm(actual, circles);
	std::cout << "test  #4: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();



	Circle c51(Point(-2.0, -2.0), 1.0);
	Circle c52(Point(2.0, 2.0), 1.0);
	Circle c53(Point(2.0, -2.0), 1.0);
	Circle c54(Point(-2.0, 2.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c51);
	circles.emplace_back(c52);
	circles.emplace_back(c53);
	circles.emplace_back(c54);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	algorithm(actual, circles);
	std::cout << "test  #5: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


	Circle c61(Point(-2.0, -2.0), 1.0);
	Circle c62(Point(3.0, 0.0), 1.0);
	Circle c63(Point(2.0, -2.0), 1.0);
	Circle c64(Point(-2.0, 2.0), 1.0);
	circles.emplace_back(owner);
	circles.emplace_back(c61);
	circles.emplace_back(c62);
	circles.emplace_back(c63);
	circles.emplace_back(c64);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	algorithm(actual, circles);
	std::cout << "test  #6: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();



	Circle c71(Point(-2.0, -2.0), 1.0);
	Circle c72(Point(3.0, 0.0), 1.0);
	Circle c73(Point(2.0, -2.0), 1.0);
	Circle c74(Point(-1.0, 0.0), 1.0);
	Circle c75(Point(0.0, 1.0), 0.5);

	circles.emplace_back(owner);
	circles.emplace_back(c71);
	circles.emplace_back(c72);
	circles.emplace_back(c73);
	circles.emplace_back(c74);
	circles.emplace_back(c75);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);

	expected.emplace(c, b, owner);

	algorithm(actual, circles);
	std::cout << "test  #7: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


	Circle c81(Point(-2.0, -2.0), 1.0);
	Circle c82(Point(3.0, 0.0), 1.0);
	Circle c83(Point(2.0, -2.0), 1.0);
	Circle c84(Point(1.0, 3.0), 2.0);
	Circle c85(Point(0.0, 1.0), 0.5);

	circles.emplace_back(owner);
	circles.emplace_back(c81);
	circles.emplace_back(c82);
	circles.emplace_back(c83);
	circles.emplace_back(c84);
	circles.emplace_back(c85);

	actual.emplace(a, b, owner);
	actual.emplace(b, a, owner);

	actual.emplace(a, c, owner);
	actual.emplace(c, a, owner);

	actual.emplace(a, d, owner);
	actual.emplace(d, a, owner);

	actual.emplace(b, c, owner);
	actual.emplace(c, b, owner);

	actual.emplace(b, d, owner);
	actual.emplace(d, b, owner);

	actual.emplace(c, d, owner);
	actual.emplace(d, c, owner);


	algorithm(actual, circles);
	std::cout << "test  #8: " << (actual == expected ? "ok" : "FAILED") << '\n';
	circles.clear();
	actual.clear();
	expected.clear();


}