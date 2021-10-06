#include "test_get_tangents.h"

void test_get_tangents(Tangents_t(*algorithm)(const Circle&, const Circle&)) {
	std::cout << "test_get_tangents:\n";

	Tangents_t tangents_actual;
	Tangents_t tangents_expected;

	Circle c11(0.0, 0.0, 2.0);
	Circle c12(4.0, 4.0, 2.0);

	
	tangents_expected.emplace(
		Tangent(
			Point(0.0, 2.0), 
			Point(4.0, 2.0), 
			c11, 
			c12
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0), 
			Point(2.0, 4.0), 
			c11, 
			c12
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(std::sqrt(2.0), -std::sqrt(2.0)), 
			Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)), 
			c11, 
			c12
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-std::sqrt(2.0), std::sqrt(2.0)),
			Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
			c11, 
			c12
		)
	);

	tangents_actual = algorithm(c11, c12);
	std::cout << "test  #1: " << 
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	
	Circle c21(c12);
	Circle c22(c11);
	tangents_actual = algorithm(c21, c22);
	std::cout << "test  #2: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();
	

	Circle c31(0.0, 0.0, 2.0);
	Circle c32(-4.0, 4.0, 2.0);
	tangents_expected.emplace(
		Tangent(
			Point(0.0, 2.0),
			Point(-4.0, 2.0),
			c31,
			c32
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 4.0),
			c31,
			c32
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(std::sqrt(2.0), std::sqrt(2.0)),
			Point(-4.0 + std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
			c31,
			c32
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-std::sqrt(2.0), -std::sqrt(2.0)),
			Point(-4.0 - std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
			c31,
			c32
		)
	);

	tangents_actual = algorithm(c31, c32);
	std::cout << "test  #3: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c41(c32);
	Circle c42(c31);
	tangents_actual = algorithm(c41, c42);
	std::cout << "test  #4: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c51(0.0, 0.0, 2.0);
	Circle c52(0.0, 4.0 * std::sqrt(2.0), 2.0);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0),
			Point(2.0, 4.0 * std::sqrt(2.0)),
			c51,
			c52
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 4.0 * std::sqrt(2.0)),
			c51,
			c52
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(std::sqrt(2.0), std::sqrt(2.0)),
			Point(-std::sqrt(2.0), 3.0 * std::sqrt(2.0)),
			c51,
			c52
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-std::sqrt(2.0), std::sqrt(2.0)),
			Point(std::sqrt(2.0), 3.0 * std::sqrt(2.0)),
			c51,
			c52
		)
	);

	tangents_actual = algorithm(c51, c52);
	std::cout << "test  #5: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c61(c52);
	Circle c62(c51);
	tangents_actual = algorithm(c61, c62);
	std::cout << "test  #6: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c71(0.0, 0.0, 2.0);
	Circle c72(0.0, 4.0, 2.0);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0),
			Point(2.0, 4.0),
			c71,
			c72
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 4.0),
			c71,
			c72
		)
	);

	tangents_actual = algorithm(c71, c72);
	std::cout << "test  #7: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c81(c72);
	Circle c82(c71);
	tangents_actual = algorithm(c81, c82);
	std::cout << "test  #8: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c91(0.0, 0.0, 2.0);
	Circle c92(2.0, 2.0, 0.0);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0),
			Point(2.0, 2.0),
			c91,
			c92
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(0.0, 2.0),
			Point(2.0, 2.0),
			c91,
			c92
		)
	);

	tangents_actual = algorithm(c91, c92);
	std::cout << "test  #9: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c101(c92);
	Circle c102(c91);

	tangents_actual = algorithm(c101, c102);
	std::cout << "test #10: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c111(0.0, 0.0, 2.0);
	Circle c112(2.0, 2.0, 4.0);

	tangents_expected.emplace(
		Tangent(
			Point(0.0, -2.0),
			Point(2.0, -2.0),
			c111,
			c112
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 2.0),
			c111,
			c112
		)
	);

	tangents_actual = algorithm(c111, c112);
	std::cout << "test #11: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c121(c112);
	Circle c122(c111);

	tangents_actual = algorithm(c121, c122);
	std::cout << "test #12: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c131(0.0, 0.0, 2.0);
	Circle c132(0.0, 2.0, 2.0);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0),
			Point(2.0, 2.0),
			c131,
			c132
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 2.0),
			c131,
			c132
		)
	);

	tangents_actual = algorithm(c131, c132);
	std::cout << "test #13: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c141(c132);
	Circle c142(c131);
	tangents_actual = algorithm(c141, c142);
	std::cout << "test #14: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c151(0.0, 0.0, 2.0);
	Circle c152(0.0, 1.0, 2.0);
	tangents_expected.emplace(
		Tangent(
			Point(2.0, 0.0),
			Point(2.0, 1.0),
			c151,
			c152
		)
	);
	tangents_expected.emplace(
		Tangent(
			Point(-2.0, 0.0),
			Point(-2.0, 1.0),
			c151,
			c152
		)
	);

	tangents_actual = algorithm(c151, c152);
	std::cout << "test #15: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c161(c152);
	Circle c162(c151);
	tangents_actual = algorithm(c161, c162);
	std::cout << "test #16: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c171(0.0, 0.0, 2.0);
	Circle c172(0.0, 1.0, 1.0);
	tangents_actual = algorithm(c171, c172);
	std::cout << "test #17: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c181(c172);
	Circle c182(c171);
	tangents_actual = algorithm(c181, c182);
	std::cout << "test #18: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c191(0.0, 0.0, 2.0);
	Circle c192(0.0, 1.0, 0.5);
	tangents_actual = algorithm(c191, c192);
	std::cout << "test #19: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c201(c192);
	Circle c202(c191);
	tangents_actual = algorithm(c201, c202);
	std::cout << "test #20: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c211(0.0, 0.0, 2.0);
	Circle c212(0.0, 0.0, 2.0);
	tangents_actual = algorithm(c211, c212);
	std::cout << "test #21: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c221(c212);
	Circle c222(c211);
	tangents_actual = algorithm(c221, c222);
	std::cout << "test #22: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();


	Circle c231(0.0, 0.0, 2.0);
	Circle c232(0.0, 0.0, 1.0);
	tangents_actual = algorithm(c231, c232);
	std::cout << "test #23: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();


	Circle c241(c232);
	Circle c242(c231);
	tangents_actual = algorithm(c241, c242);
	std::cout << "test #24: " <<
		(tangents_actual == tangents_expected ? "ok" : "FAILED") << '\n';
	tangents_actual.clear();
	tangents_expected.clear();
}
