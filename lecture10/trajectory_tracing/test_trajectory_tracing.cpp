#include "test_trajectory_tracing.h"

void test_trajectory_tracing ( int ( *algorithm ) ( int *prices, bool *allowed, int length, int destination ) )
{
    std::cout << "test_trajectory_tracing:\n";

    int prices[] { 5, 5, 5, 5, 5, 5, 100, 5, 5, 5, 100, 5, 100, 5, 100, 5, 100, 5 };
    bool allowed[] { false, true, true,
                     false, true, true, true, true,
                     false, true, true, true, true, true, true, true, true, true };
    int length = sizeof ( prices ) / sizeof ( prices[0] );
    std::cout << "test #1: " << ( ( algorithm ( prices, allowed, length, 18 ) == 50 ) ? "ok" : "FAILED" ) << '\n';

    int prices2[] { 5, 5, 5, 100, 5, 100, 5 };
    bool allowed2[] { true, true, true, true, false, true, true };
    int length2 = sizeof ( prices2 ) / sizeof ( prices2[0] );
    std::cout << "test #2: " << ( ( algorithm ( prices2, allowed2, length2, 7 ) == 215 ) ? "ok" : "FAILED" ) << '\n';
    
    int prices3[] { 5, 5, 5, 5, 5, 5, 5 };
    bool allowed3[] { true, true, true, true, true, true, true };
    int length3 = sizeof ( prices3 ) / sizeof ( prices3[0] );
    std::cout << "test #3: " << ( ( algorithm ( prices3, allowed3, length3, 7 ) == 20 ) ? "ok" : "FAILED" ) << '\n';

    int prices4[] { 5, 5, 100, 5, 100, 5, 5, 100, 5 };
    bool allowed4[] { true, true, true, true, true, true, true, true, true };
    int length4 = sizeof ( prices4 ) / sizeof ( prices4[0] );
    std::cout << "test #4: " << ( ( algorithm ( prices4, allowed4, length4, 9 ) == 30 ) ? "ok" : "FAILED" ) << '\n';

    int prices5[] { 5, 5, 100, 5, 100, 5, 5, 100, 5 };
    bool allowed5[] { true, true, true, true, true, true, false, true, true };
    int length5 = sizeof ( prices5 ) / sizeof ( prices5[0] );
    std::cout << "test #5: " << ( ( algorithm ( prices5, allowed5, length5, 9 ) == 125 ) ? "ok" : "FAILED" ) << '\n';
}
  