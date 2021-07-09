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
}
