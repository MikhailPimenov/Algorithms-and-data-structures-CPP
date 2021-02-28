#include "test_grand_common_divisor.h"

void test_grand_common_divisor ( int ( *algorithm ) ( int, int ) )
{
    std::cout << "test #1: " << ( ( algorithm (  5, 25 ) == 5 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #2: " << ( ( algorithm ( 12, 16 ) == 4 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #3: " << ( ( algorithm ( 25,  5 ) == 5 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #4: " << ( ( algorithm (  8, 10 ) == 2 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #5: " << ( ( algorithm ( 12, 18 ) == 6 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #6: " << ( ( algorithm ( 18, 12 ) == 6 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #7: " << ( ( algorithm (  5,  0 ) == 5 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #8: " << ( ( algorithm (  0,  6 ) == 6 ) ? "ok" : "FAILED" ) << '\n';
}

