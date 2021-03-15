#include "test_discrete_bag.h"

void test_discrete_bag ( int ( * algorithm )( const std::vector < std::pair < int, int > >&, int ) )
{
    std::vector < std::pair < int, int > > vector =
    {
        std::pair < int, int > ( 1, 20 ),
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 3, 30 ),
        std::pair < int, int > ( 4, 40 ),
        std::pair < int, int > ( 5, 50 ),
    };
    int mass = 10;
    int answer = 120;
    int result = algorithm ( vector, mass );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    vector = {
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 4, 30 ),
        std::pair < int, int > ( 4, 40 ),
        std::pair < int, int > ( 5, 50 ),
    };
    mass = 10;
    answer = 110;
    result = algorithm ( vector, mass );
    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    vector = {
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 2, 30 ),
        std::pair < int, int > ( 4, 30 ),
        std::pair < int, int > ( 4, 40 ),
        std::pair < int, int > ( 5, 50 ),
    };
    mass = 10;
    answer = 130;
    result = algorithm ( vector, mass );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

}
