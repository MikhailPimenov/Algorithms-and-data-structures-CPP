#include "test_get_angle.h"

void test_get_angle_with_x_axis(double (*algorithm)(const Point&, const Point&)) {
	std::cout << "test_get_angle_with_x_axis:\n";

	double angle_expected = -1.0;
	double angle_actual = 1.0;

	Point p11(2.0, 0.0);
	Point p12(0.0, 0.0);
	angle_expected = 0.0;

	angle_actual = algorithm(p11, p12);
	std::cout << "test  #1: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p21(p12);
	Point p22(p11);
	angle_expected = g_pi;

	angle_actual = algorithm(p21, p22);
	std::cout << "test  #2: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p31(0.0, 2.0);
	Point p32(0.0, 0.0);
	angle_expected = g_pi / 2.0;

	angle_actual = algorithm(p31, p32);
	std::cout << "test  #3: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p41(p32);
	Point p42(p31);
	angle_expected = 3.0 * g_pi / 2.0;

	angle_actual = algorithm(p41, p42);
	std::cout << "test  #4: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p51(2.0, 2.0);
	Point p52(0.0, 0.0);
	angle_expected = g_pi / 4.0;

	angle_actual = algorithm(p51, p52);
	std::cout << "test  #5: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p61(p52);
	Point p62(p51);
	angle_expected = 5.0 * g_pi / 4.0;

	angle_actual = algorithm(p61, p62);
	std::cout << "test  #6: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED: " ) << '\n';
	

	Point p71(2.0, -2.0);
	Point p72(0.0, 0.0);
	angle_expected = 7.0 * g_pi / 4.0;

	angle_actual = algorithm(p71, p72);
	std::cout << "test  #7: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p81(p72);
	Point p82(p71);
	angle_expected = 3.0 * g_pi / 4.0;

	angle_actual = algorithm(p81, p82);
	std::cout << "test  #8: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p91(1.0, 0.0);
	Point p92(0.0, 0.0);
	angle_expected = 0.0;

	angle_actual = algorithm(p91, p92);
	std::cout << "test  #9: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p101(std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	Point p102(0.0, 0.0);
	angle_expected = g_pi / 6.0;

	angle_actual = algorithm(p101, p102);
	std::cout << "test #10: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p111(std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0);
	Point p112(0.0, 0.0);
	angle_expected = g_pi / 4.0;

	angle_actual = algorithm(p111, p112);
	std::cout << "test #11: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p121(1.0 / 2.0, std::sqrt(3.0) / 2.0);
	Point p122(0.0, 0.0);
	angle_expected = g_pi / 3.0;

	angle_actual = algorithm(p121, p122);
	std::cout << "test #12: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p131(0.0, 1.0);
	Point p132(0.0, 0.0);
	angle_expected = g_pi / 2.0;

	angle_actual = algorithm(p131, p132);
	std::cout << "test #13: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p141(-1.0 / 2.0, std::sqrt(3.0) / 2.0);
	Point p142(0.0, 0.0);
	angle_expected = 2.0 * g_pi / 3.0;

	angle_actual = algorithm(p141, p142);
	std::cout << "test #14: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p151(-std::sqrt(2.0) / 2.0, std::sqrt(2.0) / 2.0);
	Point p152(0.0, 0.0);
	angle_expected = 3.0 * g_pi / 4.0;

	angle_actual = algorithm(p151, p152);
	std::cout << "test #15: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p161(-std::sqrt(3.0) / 2.0, 1.0 / 2.0);
	Point p162(0.0, 0.0);
	angle_expected = 5.0 * g_pi / 6.0;

	angle_actual = algorithm(p161, p162);
	std::cout << "test #16: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p171(-1.0, 0.0);
	Point p172(0.0, 0.0);
	angle_expected = g_pi;

	angle_actual = algorithm(p171, p172);
	std::cout << "test #17: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p181(-std::sqrt(3.0) / 2.0, -1.0 / 2.0);
	Point p182(0.0, 0.0);
	angle_expected = 7.0 * g_pi / 6.0;

	angle_actual = algorithm(p181, p182);
	std::cout << "test #18: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p191(-std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0);
	Point p192(0.0, 0.0);
	angle_expected = 5.0 * g_pi / 4.0;

	angle_actual = algorithm(p191, p192);
	std::cout << "test #19: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p201(-1.0 / 2.0, -std::sqrt(3.0) / 2.0);
	Point p202(0.0, 0.0);
	angle_expected = 4.0 * g_pi / 3.0;

	angle_actual = algorithm(p201, p202);
	std::cout << "test #20: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p211(0.0, -1.0);
	Point p212(0.0, 0.0);
	angle_expected = 3.0 * g_pi / 2.0;

	angle_actual = algorithm(p211, p212);
	std::cout << "test #21: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p221(1.0 / 2.0, -std::sqrt(3.0) / 2.0);
	Point p222(0.0, 0.0);
	angle_expected = 5.0 * g_pi / 3.0;

	angle_actual = algorithm(p221, p222);
	std::cout << "test #22: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p231(std::sqrt(2.0) / 2.0, -std::sqrt(2.0) / 2.0);
	Point p232(0.0, 0.0);
	angle_expected = 7.0 * g_pi / 4.0;

	angle_actual = algorithm(p231, p232);
	std::cout << "test #23: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	

	Point p241(std::sqrt(3.0) / 2.0, -1.0 / 2.0);
	Point p242(0.0, 0.0);
	angle_expected = 11.0 * g_pi / 6.0;

	angle_actual = algorithm(p241, p242);
	std::cout << "test #24: " <<
		(are_equal(angle_actual, angle_expected) ? "ok" : "FAILED") << '\n';
	
}