#include "test_tiptoe_through_the_circles.h"

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&)) {
	std::cout << "test_tiptoe_through_the_circles:\n";


	std::vector<Circle> circles;
	double result_expected = 0.0;
	double result_actual = -1.0;
	

	Point a1(-3.0, 1.0);
	Point b1(4.25, 0.0);
	circles.emplace_back(0.0, 0.0, 2.5);
	circles.emplace_back(1.5, 2.0, 0.5);
	circles.emplace_back(3.5, 1.0, 1.0);
	circles.emplace_back(3.5, -1.7, 1.2);
	result_expected = 9.11822;

	result_actual = algorithm(a1, b1, circles);

	std::cout << "test  #1: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a2(0.0, 1.0);
	Point b2(0.0, -1.0);
	circles.emplace_back(0.0, 0.0, 0.8);
	circles.emplace_back(3.8, 0.0, 3.2);
	circles.emplace_back(-3.5, 0.0, 3.0);
	circles.emplace_back(-7.0, 0.0, 1.0);
	result_expected = 19.0575;

	result_actual = algorithm(a2, b2, circles);

	std::cout << "test  #2: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a3(3.0, 0.0);
	Point b3(0.0, 4.0);
	result_expected = 5.0;

	result_actual = algorithm(a3, b3, circles);

	std::cout << "test  #3: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a4(0.0, 0.0);
	Point b4(20.0, 20.0);
	circles.emplace_back(4.0, 0.0, 3.0);
	circles.emplace_back(-4.0, 0.0, 3.0);
	circles.emplace_back(0.0, 4.0, 3.0);
	circles.emplace_back(0.0, -4.0, 3.0);
	result_expected = -1.0;

	result_actual = algorithm(a4, b4, circles);

	std::cout << "test  #4: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a5(0, 1);
	Point b5(0, -1);
	circles.emplace_back(0, 0, 0.8);
	circles.emplace_back(-3.8, 0, 3.2);
	circles.emplace_back(3.5, 0, 3);
	circles.emplace_back(7, 0, 1);
	result_expected = 19.0575;

	result_actual = algorithm(a5, b5, circles);

	std::cout << "test  #5: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a6(-2.0003, 3.74947);
	Point b6(3.08681, -0.361379);
	circles.emplace_back(-4.31218, -1.826, 1.5373);
	circles.emplace_back(4.09037, -3.60735, 0.95389);
	circles.emplace_back(-4.09823, 4.12037, 1.125);
	circles.emplace_back(-2.20917, -0.700209, 0.208438);
	circles.emplace_back(-4.00109, 1.89348, 1.39948);
	circles.emplace_back(-3.26897, 0.741226, 0.43203);
	circles.emplace_back(-3.05481, -2.07999, 0.830246);
	circles.emplace_back(4.65877, 1.40259, 0.0703871);
	circles.emplace_back(4.37294, -3.30228, 0.999948);
	circles.emplace_back(-3.91467, -2.94508, 0.593251);
	circles.emplace_back(-1.79119, 1.60263, 0.943726);
	circles.emplace_back(0.91058, -0.468142, 0.605236);
	circles.emplace_back(2.32465, -1.96012, 0.918449);
	circles.emplace_back(-2.73455, 1.59921, 0.800891);
	circles.emplace_back(-2.58812, 1.44516, 1.12083);
	circles.emplace_back(4.10273, -3.95321, 1.09042);
	circles.emplace_back(3.46377, 2.4686, 0.819217);
	circles.emplace_back(-1.67154, 1.42164, 0.787903);
	circles.emplace_back(-4.97284, -4.28459, 1.00825);
	circles.emplace_back(-3.75286, -1.24401, 1.24907);
	circles.emplace_back(-3.49358, -4.57044, 0.67571);
	circles.emplace_back(4.54263, -0.830026, 1.25782);
	circles.emplace_back(0.017044, 0.237275, 1.12488);
	circles.emplace_back(0.68505, -4.89911, 1.07786);
	circles.emplace_back(-1.65475, -1.73384, 1.16);
	circles.emplace_back(-4.70945, 1.87513, 1.1949);
	circles.emplace_back(4.22193, 2.37388, 1.25583);
	circles.emplace_back(-1.68383, -4.85234, 0.763674);
	circles.emplace_back(-1.88444, 1.60703, 1.03119);
	circles.emplace_back(-4.20359, -2.86352, 1.53032);
	circles.emplace_back(3.83856, -1.88379, 0.668813);
	circles.emplace_back(2.87097, 4.32522, 0.711037);
	circles.emplace_back(-1.80494, -2.67234, 0.907241);
	circles.emplace_back(0.864997, -4.85295, 1.36131);
	circles.emplace_back(1.42556, 1.96467, 1.31246);
	circles.emplace_back(-0.0866614, 1.84692, 1.35217);
	circles.emplace_back(3.07474, -3.72621, 0.754529);
	circles.emplace_back(-3.12603, 4.29121, 0.805814);
	circles.emplace_back(-0.738774, -4.24674, 0.661515);
	result_expected = 11.9228;

	result_actual = algorithm(a6, b6, circles);

	std::cout << "test  #6: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();


	Point a7(1, 1);
	Point b7(9, 9);
	circles.emplace_back(0, 0, 0.162875);
	circles.emplace_back(0, 1, 0.352399);
	circles.emplace_back(0, 2, 0.536426);
	circles.emplace_back(0, 3, 0.430062);
	circles.emplace_back(0, 4, 0.3106);
	circles.emplace_back(0, 5, 0.526689);
	circles.emplace_back(0, 6, 0.56848);
	circles.emplace_back(0, 7, 0.583306);
	circles.emplace_back(0, 8, 0.199401);
	circles.emplace_back(0, 9, 0.190163);
	circles.emplace_back(0, 10, 0.496312);
	circles.emplace_back(1, 0, 0.794503);
	circles.emplace_back(1, 2, 0.251076);
	circles.emplace_back(1, 3, 0.716956);
	circles.emplace_back(1, 4, 0.525058);
	circles.emplace_back(1, 5, 0.193072);
	circles.emplace_back(1, 6, 0.426112);
	circles.emplace_back(1, 7, 0.237577);
	circles.emplace_back(1, 8, 0.590785);
	circles.emplace_back(1, 9, 0.380313);
	circles.emplace_back(1, 10, 0.489955);
	circles.emplace_back(2, 0, 0.531981);
	circles.emplace_back(2, 1, 0.384474);
	circles.emplace_back(2, 2, 0.29231);
	circles.emplace_back(2, 3, 0.392367);
	circles.emplace_back(2, 4, 0.500586);
	circles.emplace_back(2, 5, 0.628159);
	circles.emplace_back(2, 6, 0.436075);
	circles.emplace_back(2, 7, 0.675493);
	circles.emplace_back(2, 8, 0.391326);
	circles.emplace_back(2, 9, 0.493831);
	circles.emplace_back(2, 10, 0.252058);
	circles.emplace_back(3, 0, 0.57627);
	circles.emplace_back(3, 1, 0.310903);
	circles.emplace_back(3, 2, 0.605751);
	circles.emplace_back(3, 3, 0.406157);
	circles.emplace_back(3, 4, 0.638791);
	circles.emplace_back(3, 5, 0.398329);
	circles.emplace_back(3, 6, 0.516773);
	circles.emplace_back(3, 7, 0.364334);
	circles.emplace_back(3, 8, 0.302254);
	circles.emplace_back(3, 9, 0.588904);
	circles.emplace_back(3, 10, 0.699331);
	circles.emplace_back(4, 0, 0.652984);
	circles.emplace_back(4, 1, 0.580129);
	circles.emplace_back(4, 2, 0.146748);
	circles.emplace_back(4, 3, 0.641685);
	circles.emplace_back(4, 4, 0.158159);
	circles.emplace_back(4, 5, 0.496153);
	circles.emplace_back(4, 6, 0.294012);
	circles.emplace_back(4, 7, 0.690078);
	circles.emplace_back(4, 8, 0.5668);
	circles.emplace_back(4, 9, 0.392792);
	circles.emplace_back(4, 10, 0.514897);
	circles.emplace_back(5, 0, 0.127403);
	circles.emplace_back(5, 1, 0.503068);
	circles.emplace_back(5, 2, 0.477784);
	circles.emplace_back(5, 3, 0.262593);
	circles.emplace_back(5, 4, 0.329032);
	circles.emplace_back(5, 5, 0.462934);
	circles.emplace_back(5, 6, 0.524399);
	circles.emplace_back(5, 7, 0.547288);
	circles.emplace_back(5, 8, 0.386409);
	circles.emplace_back(5, 9, 0.200125);
	circles.emplace_back(5, 10, 0.491025);
	circles.emplace_back(6, 0, 0.333342);
	circles.emplace_back(6, 1, 0.339046);
	circles.emplace_back(6, 2, 0.366566);
	circles.emplace_back(6, 3, 0.475729);
	circles.emplace_back(6, 4, 0.823775);
	circles.emplace_back(6, 5, 0.60554);
	circles.emplace_back(6, 6, 0.860442);
	circles.emplace_back(6, 7, 0.37139);
	circles.emplace_back(6, 8, 0.56018);
	circles.emplace_back(6, 9, 0.75424);
	circles.emplace_back(6, 10, 0.484995);
	circles.emplace_back(7, 0, 0.337052);
	circles.emplace_back(7, 1, 0.416191);
	circles.emplace_back(7, 2, 0.604189);
	circles.emplace_back(7, 3, 0.271194);
	circles.emplace_back(7, 4, 0.65111);
	circles.emplace_back(7, 5, 0.512637);
	circles.emplace_back(7, 6, 0.796956);
	circles.emplace_back(7, 7, 0.667399);
	circles.emplace_back(7, 8, 0.561956);
	circles.emplace_back(7, 9, 0.332489);
	circles.emplace_back(7, 10, 0.730007);
	circles.emplace_back(8, 0, 0.649132);
	circles.emplace_back(8, 1, 0.401713);
	circles.emplace_back(8, 2, 0.263748);
	circles.emplace_back(8, 3, 0.592208);
	circles.emplace_back(8, 4, 0.352105);
	circles.emplace_back(8, 5, 0.278676);
	circles.emplace_back(8, 6, 0.548382);
	circles.emplace_back(8, 7, 0.592111);
	circles.emplace_back(8, 8, 0.281601);
	circles.emplace_back(8, 9, 0.514096);
	circles.emplace_back(8, 10, 0.665443);
	circles.emplace_back(9, 0, 0.219636);
	circles.emplace_back(9, 1, 0.501355);
	circles.emplace_back(9, 2, 0.438918);
	circles.emplace_back(9, 3, 0.526489);
	circles.emplace_back(9, 4, 0.531778);
	circles.emplace_back(9, 5, 0.355053);
	circles.emplace_back(9, 6, 0.416108);
	circles.emplace_back(9, 7, 0.211436);
	circles.emplace_back(9, 8, 0.60296);
	circles.emplace_back(9, 10, 0.623569);
	circles.emplace_back(10, 0, 0.404193);
	circles.emplace_back(10, 1, 0.522966);
	circles.emplace_back(10, 2, 0.430659);
	circles.emplace_back(10, 3, 0.571068);
	circles.emplace_back(10, 4, 0.527629);
	circles.emplace_back(10, 5, 0.487614);
	circles.emplace_back(10, 6, 0.236933);
	circles.emplace_back(10, 7, 0.483111);
	circles.emplace_back(10, 8, 0.569641);
	circles.emplace_back(10, 9, 0.681657);
	circles.emplace_back(10, 10, 0.356473);
	result_expected = 13.5171;

	result_actual = algorithm(a7, b7, circles);

	std::cout << "test  #7: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	circles.clear();

}
