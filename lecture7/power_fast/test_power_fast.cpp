#include "test_power_fast.h"

void test_power_fast ( int ( *algorithm )( int, int ) )
{
    std::cout << "test #1:  " << ( ( algorithm ( 2,  2 ) == 4 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #2:  " << ( ( algorithm ( 1,  2 ) == 1 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #3:  " << ( ( algorithm ( 2,  3 ) == 8 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #4:  " << ( ( algorithm ( 2,  4 ) == 16 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #5:  " << ( ( algorithm ( 2,  5 ) == 32 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #6:  " << ( ( algorithm ( 2,  6 ) == 64 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #7:  " << ( ( algorithm ( 2,  7 ) == 128 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #8:  " << ( ( algorithm ( 2,  8 ) == 256 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #9:  " << ( ( algorithm ( 2,  9 ) == 512 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #10: " << ( ( algorithm ( 2, 10 ) == 1024 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #11: " << ( ( algorithm ( 3, 2 ) == 9 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #12: " << ( ( algorithm ( 3, 3 ) == 27 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #13: " << ( ( algorithm ( 3, 4 ) == 81 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #14: " << ( ( algorithm ( 0, 2 ) == 0 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #15: " << ( ( algorithm ( 0, 10 ) == 0 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #16: " << ( ( algorithm ( 2, 0 ) == 1 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #17: " << ( ( algorithm ( 10, 0 ) == 1 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #18: " << ( ( algorithm ( 10, 5 ) == 100000 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #19: " << ( ( algorithm ( -1, 2 ) == 1 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #20: " << ( ( algorithm ( 2, -2 ) == -1 ) ? "ok" : "FAILED" ) << '\n';
    std::cout << "test #21: " << ( ( algorithm ( -2, -2 ) == -1 ) ? "ok" : "FAILED" ) << '\n';
}
