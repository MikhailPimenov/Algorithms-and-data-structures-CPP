#include "test_tiptoe_through_the_circles.h"

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&)) {
	std::cout << "test_tiptoe_through_the_circles:\n";
	std::cout << std::setprecision(16);
	bool verbose = true;

	std::vector<Circle> circles;
	double result_expected = 0.0;
	double result_actual = -1.0;
	
	
	Point a1(-3.0, 1.0);
	Point b1(4.25, 0.0);
	circles.emplace_back(0.0, 0.0, 2.5);
	circles.emplace_back(1.5, 2.0, 0.5);
	circles.emplace_back(3.5, 1.0, 1.0);
	circles.emplace_back(3.5, -1.7, 1.2);
	result_expected = 9.11821650244;

	result_actual = algorithm(a1, b1, circles);

	std::cout << "test  #1: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if(verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a2(0.0, 1.0);
	Point b2(0.0, -1.0);
	circles.emplace_back(0.0, 0.0, 0.8);
	circles.emplace_back(3.8, 0.0, 3.2);
	circles.emplace_back(-3.5, 0.0, 3.0);
	circles.emplace_back(-7.0, 0.0, 1.0);
	result_expected = 19.0575347577;

	result_actual = algorithm(a2, b2, circles);

	std::cout << "test  #2: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a3(3.0, 0.0);
	Point b3(0.0, 4.0);
	result_expected = 5.0;

	result_actual = algorithm(a3, b3, circles);

	std::cout << "test  #3: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

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
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a5(0, 1);
	Point b5(0, -1);
	circles.emplace_back(0, 0, 0.8);
	circles.emplace_back(-3.8, 0, 3.2);
	circles.emplace_back(3.5, 0, 3);
	circles.emplace_back(7, 0, 1);
	result_expected = 19.0575347577;

	result_actual = algorithm(a5, b5, circles);

	std::cout << "test  #5: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a6(-2.000298425089568, 3.749468164518476);
	Point b6(3.086806660052389, -0.3613790776580572);
	circles.emplace_back(-4.312177246902138, -1.825995144899935, 1.537304233969189);
	circles.emplace_back(4.090373425278813, -3.607347321230918, 0.9538899711100384);
	circles.emplace_back(-4.098228246439248, 4.120374575722963, 1.125000807014294);
	circles.emplace_back(-2.209169554989785, -0.7002085656858981, 0.2084384063025936);
	circles.emplace_back(-4.001088032964617, 1.893475188408047, 1.399483151757158);
	circles.emplace_back(-3.268968423362821, 0.7412259723059833, 0.432029886986129);
	circles.emplace_back(-3.054809097666293, -2.079985204618424, 0.8302456527249887);
	circles.emplace_back(4.658766083884984, 1.402585541363806, 0.0703870586818084);
	circles.emplace_back(4.372936950530857, -3.302281235810369, 0.9999477392295375);
	circles.emplace_back(-3.914669880177826, -2.945075233001262, 0.5932513790903613);
	circles.emplace_back(-1.791188039351255, 1.602634110022336, 0.9437262480380013);
	circles.emplace_back(0.9105801326222718, -0.4681416437961161, 0.605236313282512);
	circles.emplace_back(2.324651998933405, -1.960121297743171, 0.918448581942357);
	circles.emplace_back(-2.734545466955751, 1.599212891887873, 0.8008913443190977);
	circles.emplace_back(-2.588120114523917, 1.445159513968974, 1.120827562664635);
	circles.emplace_back(4.102725342381746, -3.953214439097792, 1.090417228988372);
	circles.emplace_back(3.463766851928085, 2.46860288316384, 0.8192173140356317);
	circles.emplace_back(-1.671539710368961, 1.421643409412354, 0.7879026158479974);
	circles.emplace_back(-4.972835585940629, -4.284591495525092, 1.008245448884554);
	circles.emplace_back(-3.752855423372239, -1.244009530637413, 1.249069330259226);
	circles.emplace_back(-3.493578697089106, -4.570442379917949, 0.6757102705771103);
	circles.emplace_back(4.542630279902369, -0.8300261502154171, 1.257818318600766);
	circles.emplace_back(0.01704404829069972, 0.237274628598243, 1.12488263763953);
	circles.emplace_back(0.6850501080043614, -4.899106363300234, 1.077860431349836);
	circles.emplace_back(-1.654746441636235, -1.733839919324964, 1.160000577406026);
	circles.emplace_back(-4.70944901695475, 1.875125195365399, 1.194895912217907);
	circles.emplace_back(4.221933789085597, 2.373881780076772, 1.255830672127195);
	circles.emplace_back(-1.683828334789723, -4.852343781385571, 0.7636736480286345);
	circles.emplace_back(-1.88443765277043, 1.607029458973557, 1.031193678476848);
	circles.emplace_back(-4.203592611011118, -2.86351538496092, 1.530315921525471);
	circles.emplace_back(3.838556620758027, -1.883792753797024, 0.6688127788947895);
	circles.emplace_back(2.870973229873925, 4.325217080768198, 0.7110365967964754);
	circles.emplace_back(-1.804937219712883, -2.672343102749437, 0.9072413007030263);
	circles.emplace_back(0.8649966702796519, -4.852948051411659, 1.361310354503803);
	circles.emplace_back(1.425558745395392, 1.964673504699022, 1.312462676432915);
	circles.emplace_back(-0.08666141657158732, 1.84692365815863, 1.352167781605385);
	circles.emplace_back(3.074735959526151, -3.726205842103809, 0.7545288563007488);
	circles.emplace_back(-3.126031432766467, 4.291208770591766, 0.8058143212692812);
	circles.emplace_back(-0.7387743960134685, -4.246743435505778, 0.6615151680773124);
	result_expected = 11.9228;

	result_actual = algorithm(a6, b6, circles);

	std::cout << "test  #6: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a7(1, 1);
	Point b7(9, 9);
	circles.emplace_back(0, 0, 0.1628746463684365);
	circles.emplace_back(0, 1, 0.3523985967272892);
	circles.emplace_back(0, 2, 0.5364255122607574);
	circles.emplace_back(0, 3, 0.4300622401060537);
	circles.emplace_back(0, 4, 0.3106004946632311);
	circles.emplace_back(0, 5, 0.5266889514634385);
	circles.emplace_back(0, 6, 0.5684803681215271);
	circles.emplace_back(0, 7, 0.5833063065307215);
	circles.emplace_back(0, 8, 0.1994006278691813);
	circles.emplace_back(0, 9, 0.1901628721738234);
	circles.emplace_back(0, 10, 0.4963121007895097);
	circles.emplace_back(1, 0, 0.7945029408903792);
	circles.emplace_back(1, 2, 0.2510755163384601);
	circles.emplace_back(1, 3, 0.7169563776114956);
	circles.emplace_back(1, 4, 0.5250582014909014);
	circles.emplace_back(1, 5, 0.1930718991206959);
	circles.emplace_back(1, 6, 0.4261120012728497);
	circles.emplace_back(1, 7, 0.2375767939025536);
	circles.emplace_back(1, 8, 0.5907849639421329);
	circles.emplace_back(1, 9, 0.3803132777335122);
	circles.emplace_back(1, 10, 0.4899552673799917);
	circles.emplace_back(2, 0, 0.5319813678273931);
	circles.emplace_back(2, 1, 0.3844743007561192);
	circles.emplace_back(2, 2, 0.292310345848091);
	circles.emplace_back(2, 3, 0.392366753029637);
	circles.emplace_back(2, 4, 0.5005855676019564);
	circles.emplace_back(2, 5, 0.6281589973485097);
	circles.emplace_back(2, 6, 0.4360745647223666);
	circles.emplace_back(2, 7, 0.675492997909896);
	circles.emplace_back(2, 8, 0.3913260711589828);
	circles.emplace_back(2, 9, 0.4938314033439383);
	circles.emplace_back(2, 10, 0.2520577947841957);
	circles.emplace_back(3, 0, 0.5762704281834885);
	circles.emplace_back(3, 1, 0.3109034419292584);
	circles.emplace_back(3, 2, 0.605750561482273);
	circles.emplace_back(3, 3, 0.4061566901626065);
	circles.emplace_back(3, 4, 0.6387910791439936);
	circles.emplace_back(3, 5, 0.3983294921228662);
	circles.emplace_back(3, 6, 0.5167727740248665);
	circles.emplace_back(3, 7, 0.3643342807190493);
	circles.emplace_back(3, 8, 0.3022542553720995);
	circles.emplace_back(3, 9, 0.5889043335104361);
	circles.emplace_back(3, 10, 0.6993306066608056);
	circles.emplace_back(4, 0, 0.652983741578646);
	circles.emplace_back(4, 1, 0.5801291283918545);
	circles.emplace_back(4, 2, 0.1467481157043949);
	circles.emplace_back(4, 3, 0.6416853299131616);
	circles.emplace_back(4, 4, 0.1581593501614407);
	circles.emplace_back(4, 5, 0.4961532718269154);
	circles.emplace_back(4, 6, 0.2940124519402161);
	circles.emplace_back(4, 7, 0.6900777980452403);
	circles.emplace_back(4, 8, 0.566799630713649);
	circles.emplace_back(4, 9, 0.3927921340567991);
	circles.emplace_back(4, 10, 0.5148965323576703);
	circles.emplace_back(5, 0, 0.1274027654668316);
	circles.emplace_back(5, 1, 0.503067686338909);
	circles.emplace_back(5, 2, 0.4777844483731314);
	circles.emplace_back(5, 3, 0.262592924782075);
	circles.emplace_back(5, 4, 0.3290316406404599);
	circles.emplace_back(5, 5, 0.4629337185295299);
	circles.emplace_back(5, 6, 0.5243985806358978);
	circles.emplace_back(5, 7, 0.5472880630055442);
	circles.emplace_back(5, 8, 0.3864086774876341);
	circles.emplace_back(5, 9, 0.2001247341977432);
	circles.emplace_back(5, 10, 0.4910248144296929);
	circles.emplace_back(6, 0, 0.3333424225682393);
	circles.emplace_back(6, 1, 0.3390456042950973);
	circles.emplace_back(6, 2, 0.3665664402069524);
	circles.emplace_back(6, 3, 0.4757285737199708);
	circles.emplace_back(6, 4, 0.823775384039618);
	circles.emplace_back(6, 5, 0.605539690121077);
	circles.emplace_back(6, 6, 0.8604423254029825);
	circles.emplace_back(6, 7, 0.3713895830092951);
	circles.emplace_back(6, 8, 0.5601797837996855);
	circles.emplace_back(6, 9, 0.7542402487015352);
	circles.emplace_back(6, 10, 0.4849949301453307);
	circles.emplace_back(7, 0, 0.3370519649935886);
	circles.emplace_back(7, 1, 0.4161911523202434);
	circles.emplace_back(7, 2, 0.6041885798564181);
	circles.emplace_back(7, 3, 0.2711943033384159);
	circles.emplace_back(7, 4, 0.6511102757183834);
	circles.emplace_back(7, 5, 0.5126366399461403);
	circles.emplace_back(7, 6, 0.7969563483959063);
	circles.emplace_back(7, 7, 0.6673986469628289);
	circles.emplace_back(7, 8, 0.5619564772350714);
	circles.emplace_back(7, 9, 0.3324886301765218);
	circles.emplace_back(7, 10, 0.7300074005266651);
	circles.emplace_back(8, 0, 0.6491321481065825);
	circles.emplace_back(8, 1, 0.4017128477571532);
	circles.emplace_back(8, 2, 0.2637480404460802);
	circles.emplace_back(8, 3, 0.5922080177580937);
	circles.emplace_back(8, 4, 0.3521049984963611);
	circles.emplace_back(8, 5, 0.2786758293164894);
	circles.emplace_back(8, 6, 0.5483823104063049);
	circles.emplace_back(8, 7, 0.592110608308576);
	circles.emplace_back(8, 8, 0.2816006015287712);
	circles.emplace_back(8, 9, 0.5140958129195496);
	circles.emplace_back(8, 10, 0.6654430777067318);
	circles.emplace_back(9, 0, 0.2196358360117301);
	circles.emplace_back(9, 1, 0.5013549668015912);
	circles.emplace_back(9, 2, 0.4389178612036631);
	circles.emplace_back(9, 3, 0.5264885412761942);
	circles.emplace_back(9, 4, 0.5317781867226585);
	circles.emplace_back(9, 5, 0.3550532921450212);
	circles.emplace_back(9, 6, 0.4161083685932681);
	circles.emplace_back(9, 7, 0.2114355121040717);
	circles.emplace_back(9, 8, 0.6029599722241983);
	circles.emplace_back(9, 10, 0.6235687331529334);
	circles.emplace_back(10, 0, 0.4041926589561626);
	circles.emplace_back(10, 1, 0.5229661515215411);
	circles.emplace_back(10, 2, 0.4306587716331705);
	circles.emplace_back(10, 3, 0.5710683602141217);
	circles.emplace_back(10, 4, 0.5276285207597539);
	circles.emplace_back(10, 5, 0.4876143969828263);
	circles.emplace_back(10, 6, 0.236933310306631);
	circles.emplace_back(10, 7, 0.4831113030435517);
	circles.emplace_back(10, 8, 0.5696406797273085);
	circles.emplace_back(10, 9, 0.6816570753464475);
	circles.emplace_back(10, 10, 0.3564727762481197);
	result_expected = 13.5171;

	result_actual = algorithm(a7, b7, circles);

	std::cout << "test  #7: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a8(0.0, 0.0);
	Point b8(2.0, 2.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0 + g_pi / 2.0;

	result_actual = algorithm(a8, b8, circles);

	std::cout << "test  #8: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a9(0.0, 0.0);
	Point b9(2.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0;

	result_actual = algorithm(a9, b9, circles);

	std::cout << "test  #9: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a10(0.0, 0.0);
	Point b10(3.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 3.0;

	result_actual = algorithm(a10, b10, circles);

	std::cout << "test  #10: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a11(0.0, 0.0);
	Point b11(4.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 4.0;

	result_actual = algorithm(a11, b11, circles);

	std::cout << "test  #11: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();
	

	Point a12(0.0, 0.0);
	Point b12(4.0, 0.0);
	circles.emplace_back(2.0, 2.0, 2.0);
	result_expected = 4.0;
	
	result_actual = algorithm(a12, b12, circles);

	std::cout << "test  #12: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a13(0.0, 0.0);
	Point b13(4.0, 0.0);
	circles.emplace_back(2.0, 4.0, 4.0);
	result_expected = 4.0;

	result_actual = algorithm(a13, b13, circles);

	std::cout << "test  #13: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a14(0.0, 0.0);
	Point b14(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 8.0;

	result_actual = algorithm(a14, b14, circles);

	std::cout << "test  #14: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a15(-2.0, 0.0);
	Point b15(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 10.0;

	result_actual = algorithm(a15, b15, circles);

	std::cout << "test  #15: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a16(0.0, 0.0);
	Point b16(2.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	circles.emplace_back(1.0, -0.5, 1.0);
	circles.emplace_back(1.0, -1.0, 1.0);
	circles.emplace_back(1.0, -1.5, 1.0);
	result_expected = 2.0 + g_pi;

	result_actual = algorithm(a16, b16, circles);

	std::cout << "test  #16: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();
}
