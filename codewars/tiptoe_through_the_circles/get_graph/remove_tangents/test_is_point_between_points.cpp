#include "test_is_point_between_points.h"


void test_is_point_between_points(bool (*algorithm)(const Point&, const Point&, const Point&)) {
	std::cout << "test_is_point_between_points:\n";

	bool result_expected = false;
	bool result_actual = true;

	Point pc1(2.0, 4.0);
	Point p11(2.0, 0.0);
	Point p12(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc1, p11, p12);
	std::cout << "test  #1: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc2(pc1);
	Point p21(p12);
	Point p22(p11);
	result_expected = true;

	result_actual = algorithm(pc2, p21, p22);
	std::cout << "test  #2: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc3(4.0, 2.0);
	Point p31(2.0, 0.0);
	Point p32(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc3, p31, p32);
	std::cout << "test  #3: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc4(pc3);
	Point p41(p32);
	Point p42(p31);
	result_expected = true;

	result_actual = algorithm(pc4, p41, p42);
	std::cout << "test  #4: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc5(-2.0, 0.0);
	Point p51(2.0, 0.0);
	Point p52(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc5, p51, p52);
	std::cout << "test  #5: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc6(pc5);
	Point p61(p52);
	Point p62(p51);
	result_expected = true;

	result_actual = algorithm(pc6, p61, p62);
	std::cout << "test  #6: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc7(0.0, -2.0);
	Point p71(2.0, 0.0);
	Point p72(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc7, p71, p72);
	std::cout << "test  #7: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc8(pc7);
	Point p81(p72);
	Point p82(p71);
	result_expected = true;

	result_actual = algorithm(pc8, p81, p82);
	std::cout << "test  #8: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc9(1.0, 4.0);
	Point p91(4.0, 0.0);
	Point p92(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc9, p91, p92);
	std::cout << "test  #9: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc10(pc9);
	Point p101(p92);
	Point p102(p91);
	result_expected = true;

	result_actual = algorithm(pc10, p101, p102);
	std::cout << "test #10: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc11(5.0, 2.0);
	Point p111(4.0, 0.0);
	Point p112(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc11, p111, p112);
	std::cout << "test #11: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc12(pc11);
	Point p121(p112);
	Point p122(p111);
	result_expected = true;

	result_actual = algorithm(pc12, p121, p122);
	std::cout << "test #12: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc13(-1.0, 0.0);
	Point p131(4.0, 0.0);
	Point p132(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc13, p131, p132);
	std::cout << "test #13: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc14(pc13);
	Point p141(p132);
	Point p142(p131);
	result_expected = true;

	result_actual = algorithm(pc14, p141, p142);
	std::cout << "test #14: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc15(3.0, -2.0);
	Point p151(4.0, 0.0);
	Point p152(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc15, p151, p152);
	std::cout << "test #15: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc16(pc15);
	Point p161(p152);
	Point p162(p151);
	result_expected = true;

	result_actual = algorithm(pc16, p161, p162);
	std::cout << "test #16: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc17(2.0, 2.0);
	Point p171(2.0, 0.0);
	Point p172(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc17, p171, p172);
	std::cout << "test #17: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc18(0.0, 0.0);
	Point p181(2.0, 0.0);
	Point p182(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc18, p181, p182);
	std::cout << "test #18: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc19(1000.0, 1000.0);
	Point p191(2.0, 0.0);
	Point p192(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc19, p191, p192);
	std::cout << "test #19: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc20(-1000.0, -1000.0);
	Point p201(2.0, 0.0);
	Point p202(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc20, p201, p202);
	std::cout << "test #20: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc21(4.0, 0.0);
	Point p211(2.0, 0.0);
	Point p212(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc21, p211, p212);
	std::cout << "test #21: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc22(-4.0, 0.0);
	Point p221(2.0, 0.0);
	Point p222(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc22, p221, p222);
	std::cout << "test #22: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc23(1000.0, 0.0);
	Point p231(2.0, 0.0);
	Point p232(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc23, p231, p232);
	std::cout << "test #23: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc24(-1000.0, 0.0);
	Point p241(2.0, 0.0);
	Point p242(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc24, p241, p242);
	std::cout << "test #24: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc25(1000.0, -1000.0);
	Point p251(2.0, 0.0);
	Point p252(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc25, p251, p252);
	std::cout << "test #25: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc26(-1000.0, 1000.0);
	Point p261(2.0, 0.0);
	Point p262(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc26, p261, p262);
	std::cout << "test #26: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';
	
	
	Point pc27(2.0, 2.0);
	Point p271(0.0, 0.0);
	Point p272(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc27, p271, p272);
	std::cout << "test #27: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc28(0.0, 0.0);
	Point p281(0.0, 0.0);
	Point p282(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc28, p281, p282);
	std::cout << "test #28: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc29(0.0, 4.0);
	Point p291(0.0, 0.0);
	Point p292(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc29, p291, p292);
	std::cout << "test #29: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc30(4.0, 0.0);
	Point p301(0.0, 0.0);
	Point p302(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc30, p301, p302);
	std::cout << "test #30: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc31(2.0, -2.0);
	Point p311(0.0, 0.0);
	Point p312(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc31, p311, p312);
	std::cout << "test #31: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc32(-2.0, 2.0);
	Point p321(0.0, 0.0);
	Point p322(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc32, p321, p322);
	std::cout << "test #32: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc33(2.0, 0.0);
	Point p331(0.0, 0.0);
	Point p332(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc33, p331, p332);
	std::cout << "test #33: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc34(0.0, 2.0);
	Point p341(0.0, 0.0);
	Point p342(2.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc34, p341, p342);
	std::cout << "test #34: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc35(4.0, 4.0);
	Point p351(0.0, 0.0);
	Point p352(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc35, p351, p352);
	std::cout << "test #35: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc36(-4.0, -4.0);
	Point p361(0.0, 0.0);
	Point p362(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc36, p361, p362);
	std::cout << "test #36: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc37(5.0, 0.0);
	Point p371(0.0, 0.0);
	Point p372(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc37, p371, p372);
	std::cout << "test #37: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc38(0.0, 5.0);
	Point p381(0.0, 0.0);
	Point p382(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc38, p381, p382);
	std::cout << "test #38: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc39(0.0, -5.0);
	Point p391(0.0, 0.0);
	Point p392(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc39, p391, p392);
	std::cout << "test #39: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc40(-5.0, 0.0);
	Point p401(0.0, 0.0);
	Point p402(2.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc40, p401, p402);
	std::cout << "test #40: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc41(2.0, 0.0);
	Point p411(0.0, 0.0);
	Point p412(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc41, p411, p412);
	std::cout << "test #41: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc42(0.0, 0.0);
	Point p421(0.0, 0.0);
	Point p422(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc42, p421, p422);
	std::cout << "test #42: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc43(1.0, 2.0);
	Point p431(0.0, 0.0);
	Point p432(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc43, p431, p432);
	std::cout << "test #43: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc44(1.0, -2.0);
	Point p441(0.0, 0.0);
	Point p442(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc44, p441, p442);
	std::cout << "test #44: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc45(1.0, 0.5);
	Point p451(0.0, 0.0);
	Point p452(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc45, p451, p452);
	std::cout << "test #45: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc46(1.0, 1.5);
	Point p461(0.0, 0.0);
	Point p462(2.0, 0.0);
	result_expected = true;

	result_actual = algorithm(pc46, p461, p462);
	std::cout << "test #46: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc47(2.0, 2.0);
	Point p471(0.0, 0.0);
	Point p472(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc47, p471, p472);
	std::cout << "test #47: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc48(2.0, 0.0);
	Point p481(0.0, 0.0);
	Point p482(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc48, p481, p482);
	std::cout << "test #48: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc49(0.0, 0.0);
	Point p491(0.0, 0.0);
	Point p492(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc49, p491, p492);
	std::cout << "test #49: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc50(0.0, 2.0);
	Point p501(0.0, 0.0);
	Point p502(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc50, p501, p502);
	std::cout << "test #50: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc51(0.0, 0.5);
	Point p511(0.0, 0.0);
	Point p512(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc51, p511, p512);
	std::cout << "test #51: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc52(0.0, 1.5);
	Point p521(0.0, 0.0);
	Point p522(0.0, 2.0);
	result_expected = true;

	result_actual = algorithm(pc52, p521, p522);
	std::cout << "test #52: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc53(0.0, 5.0);
	Point p531(0.0, 0.0);
	Point p532(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc53, p531, p532);
	std::cout << "test #53: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc54(0.0, -5.0);
	Point p541(0.0, 0.0);
	Point p542(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc54, p541, p542);
	std::cout << "test #54: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc55(2.0, 4.0);
	Point p551(0.0, 0.0);
	Point p552(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc55, p551, p552);
	std::cout << "test #55: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc56(-2.0, 4.0);
	Point p561(0.0, 0.0);
	Point p562(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc56, p561, p562);
	std::cout << "test #56: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc57(-2.0, -4.0);
	Point p571(0.0, 0.0);
	Point p572(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc57, p571, p572);
	std::cout << "test #57: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';


	Point pc58(-2.0, 4.0);
	Point p581(0.0, 0.0);
	Point p582(0.0, 2.0);
	result_expected = false;

	result_actual = algorithm(pc58, p581, p582);
	std::cout << "test #58: " <<
		(result_actual == result_expected ? "ok" : "FAILED") << '\n';

}