#include "test_get_arc_length.h"

void test_get_arc_length(double (*algorithm)(const Point&, const Point&, const Circle&)) {
	std::cout << "test_get_arc_length:\n";
	
	double length_expected = 0.0;
	double length_actual = -1.0;

	Circle c1(0.0, 0.0, 1.0);
	Point p11(0.0, 1.0);
	Point p12(1.0, 0.0);
	length_expected = g_pi / 2.0;

	length_actual = algorithm(p11, p12, c1);
	std::cout << "test  #1: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c2(c1);
	Point p21(p12);
	Point p22(p11);
	length_expected = 3.0 * g_pi / 2.0;

	length_actual = algorithm(p21, p22, c2);
	std::cout << "test  #2: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c3(c1);
	Point p31(std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0);
	Point p32(-std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0);
	length_expected = g_pi / 2.0;

	length_actual = algorithm(p31, p32, c3);
	std::cout << "test  #3: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c4(c1);
	Point p41(p32);
	Point p42(p31);
	length_expected = 3.0 * g_pi / 2.0;

	length_actual = algorithm(p41, p42, c4);
	std::cout << "test  #4: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c5(c1);
	Point p51(std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	Point p52(1.0, 0.0);
	length_expected = g_pi / 6.0;

	length_actual = algorithm(p51, p52, c5);
	std::cout << "test  #5: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c6(c1);
	Point p61(p52);
	Point p62(p51);
	length_expected = 11.0 * g_pi / 6.0;

	length_actual = algorithm(p61, p62, c6);
	std::cout << "test  #6: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c7(c1);
	Point p71(0.0, 1.0);
	Point p72(std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0);
	length_expected = g_pi / 4.0;

	length_actual = algorithm(p71, p72, c7);
	std::cout << "test  #7: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c8(c1);
	Point p81(p72);
	Point p82(p71);
	length_expected = 7.0 * g_pi / 4.0;

	length_actual = algorithm(p81, p82, c8);
	std::cout << "test  #8: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c9(c1);
	Point p91(1.0 / 2.0, std::sqrt(3.0) / 2.0);
	Point p92(std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	length_expected = g_pi / 6.0;

	length_actual = algorithm(p91, p92, c9);
	std::cout << "test  #9: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c10(c1);
	Point p101(p92);
	Point p102(p91);
	length_expected = 11.0 * g_pi / 6.0;

	length_actual = algorithm(p101, p102, c10);
	std::cout << "test #10: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c11(c1);
	Point p111(0.0, 1.0);
	Point p112(std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	length_expected = g_pi / 3.0;

	length_actual = algorithm(p111, p112, c11);
	std::cout << "test #11: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c12(c1);
	Point p121(p112);
	Point p122(p111);
	length_expected = 5.0 * g_pi / 3.0;

	length_actual = algorithm(p121, p122, c12);
	std::cout << "test #12: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c13(c1);
	Point p131(0.0, -1.0);
	Point p132(std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	length_expected = 4.0 * g_pi / 3.0;

	length_actual = algorithm(p131, p132, c13);
	std::cout << "test #13: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c14(c1);
	Point p141(p132);
	Point p142(p131);
	length_expected = 2.0 * g_pi / 3.0;

	length_actual = algorithm(p141, p142, c14);
	std::cout << "test #14: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c15(c1);
	Point p151(-std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0);
	Point p152(-std::sqrt(3.0) / 2.0, -1.0 / 2.0);
	length_expected = g_pi / 12.0;

	length_actual = algorithm(p151, p152, c15);
	std::cout << "test #15: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';


	Circle c16(c1);
	Point p161(p152);
	Point p162(p151);
	length_expected = 23.0 * g_pi / 12.0;

	length_actual = algorithm(p161, p162, c16);
	std::cout << "test #16: " <<
		(are_equal(length_actual, length_expected) ? "ok" : "FAILED") << '\n';

}

