#include "test_filter_tangents.h"

void test_filter_tangents(void (*algorithm)(Tangents_t&, const std::vector<Circle>&)) {
	std::cout << "test_filter_tangents:\n";

	std::vector<Circle> circles;
	Tangents_t actual;
	Tangents_t expected;

	Circle c11(Point(0.0, 0.0), 2.0);
	Circle c12(Point(4.0, 4.0), 2.0);
	circles.push_back(c11);
	circles.push_back(c12);

	actual.emplace(
		Point(2.0, 0.0), 
		Point(2.0, 4.0), 
		c11, 
		c12
	);
	actual.emplace(
		Point(0.0, 2.0), 
		Point(4.0, 2.0), 
		c11, 
		c12
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)), 
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)), 
		c11, 
		c12
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c11,
		c12
	);

	expected = actual;

	algorithm(actual, circles);
	std::cout << "test  #1: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c21(Point(0.0, 0.0), 2.0);
	Circle c22(Point(4.0, 4.0), 2.0);
	Circle c23(Point(0.0, 0.0), 2.0);
	Circle c24(Point(4.0, 4.0), 2.0);
	Circle c25(Point(0.0, 0.0), 1.0);
	Circle c26(Point(4.0, 4.0), 1.0);
	Circle c27(Point(1.0, 1.0), 0.5);
	Circle c28(Point(1.0, -1.0), 0.5);
	Circle c29(Point(-1.0, -1.0), 0.5);
	Circle c210(Point(-1.0, 1.0), 0.5);
	Circle c211(Point(5.0, 5.0), 0.5);
	Circle c212(Point(5.0, 3.0), 0.5);
	Circle c213(Point(3.0, 3.0), 0.5);
	Circle c214(Point(3.0, 5.0), 0.5);


	circles.push_back(c21);
	circles.push_back(c22);
	circles.push_back(c23);
	circles.push_back(c24);
	circles.push_back(c25);
	circles.push_back(c26);
	circles.push_back(c27);
	circles.push_back(c28);
	circles.push_back(c29);
	circles.push_back(c210);
	circles.push_back(c211);
	circles.push_back(c212);
	circles.push_back(c213);
	circles.push_back(c214);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c21,
		c22
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c21,
		c22
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c21,
		c22
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c21,
		c22
	);

	expected = actual;

	algorithm(actual, circles);
	std::cout << "test  #2: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c31(Point(0.0, 0.0), 2.0);
	Circle c32(Point(4.0, 4.0), 2.0);
	Circle c33(Point(1.0, 4.0), 0.5);
	circles.push_back(c31);
	circles.push_back(c32);
	circles.push_back(c33);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c31,
		c32
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c31,
		c32
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c31,
		c32
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c31,
		c32
	);

	expected.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c31,
		c32
	);
	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c31,
		c32
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c31,
		c32
	);
	

	algorithm(actual, circles);
	std::cout << "test  #3: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c41(Point(0.0, 0.0), 2.0);
	Circle c42(Point(4.0, 4.0), 2.0);
	Circle c43(Point(1.0, 4.0), 1.0);
	circles.push_back(c41);
	circles.push_back(c42);
	circles.push_back(c43);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c41,
		c42
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c41,
		c42
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c41,
		c42
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c41,
		c42
	);

	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c41,
		c42
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c41,
		c42
	);


	algorithm(actual, circles);
	std::cout << "test  #4: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c51(Point(0.0, 0.0), 2.0);
	Circle c52(Point(4.0, 4.0), 2.0);
	Circle c53(Point(3.0, 5.0), 1.0);
	circles.push_back(c51);
	circles.push_back(c52);
	circles.push_back(c53);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c51,
		c52
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c51,
		c52
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c51,
		c52
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c51,
		c52
	);

	expected.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c51,
		c52
	);
	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c51,
		c52
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c51,
		c52
	);


	algorithm(actual, circles);
	std::cout << "test  #5: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c61(Point(0.0, 0.0), 2.0);
	Circle c62(Point(4.0, 4.0), 2.0);
	Circle c63(Point(3.0, 5.0), 2.0);
	circles.push_back(c61);
	circles.push_back(c62);
	circles.push_back(c63);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c61,
		c62
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c61,
		c62
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c61,
		c62
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c61,
		c62
	);

	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c61,
		c62
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c61,
		c62
	);


	algorithm(actual, circles);
	std::cout << "test  #6: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();
	

	Circle c71(Point(0.0, 0.0), 2.0);
	Circle c72(Point(4.0, 4.0), 2.0);
	Circle c73(Point(2.0, 2.0), 0.5);
	circles.push_back(c71);
	circles.push_back(c72);
	circles.push_back(c73);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c71,
		c72
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c71,
		c72
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c71,
		c72
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c71,
		c72
	);

	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c71,
		c72
	);
	expected.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c71,
		c72
	);


	algorithm(actual, circles);
	std::cout << "test  #7: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c81(Point(0.0, 0.0), 2.0);
	Circle c82(Point(4.0, 4.0), 2.0);
	Circle c83(Point(2.0, 2.0), 3.0);
	circles.push_back(c81);
	circles.push_back(c82);
	circles.push_back(c83);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c81,
		c82
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c81,
		c82
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c81,
		c82
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c81,
		c82
	);

	algorithm(actual, circles);
	std::cout << "test  #8: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c91(Point(0.0, 0.0), 2.0);
	Circle c92(Point(4.0, 4.0), 2.0);
	Circle c93(Point(5.0, 5.0), 5.0);
	circles.push_back(c91);
	circles.push_back(c92);
	circles.push_back(c93);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c91,
		c92
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c91,
		c92
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c91,
		c92
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c91,
		c92
	);

	algorithm(actual, circles);
	std::cout << "test  #9: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();
}
