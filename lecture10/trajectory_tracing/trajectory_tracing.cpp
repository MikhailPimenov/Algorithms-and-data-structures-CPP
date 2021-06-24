#include "trajectory_tracing.h"

int min ( int a, int b )
{
    return ( a <= b ) ? a : b;
}
int trajectory_tracing ( int *prices, bool *allowed, int length, int destination )
{
    int *cost = new int[static_cast < unsigned > ( length )];

    cost[0] = prices[0];
    cost[1] = prices[1];

    for ( int index = 2; index < length; ++index )
    {
        if ( allowed[index] )
        {
            assert ( ( allowed[index - 1] || allowed[index - 2] )
                     && ( "trajectory_tracing(): invalid input data\n" ) );

            if ( allowed[index - 1] && allowed[index - 2] )
                cost[index] = min ( cost[index - 1], cost[index - 2] ) + prices[index];
            if ( allowed[index - 1] && !allowed[index - 2] )
                cost[index] = cost[index - 1] + prices[index];
            if ( !allowed[index - 1] && allowed[index - 2] )
                cost[index] = cost[index - 2] + prices[index];
        }
    }
    int result = cost[destination - 1];
    delete [] cost;

    return result;
}
