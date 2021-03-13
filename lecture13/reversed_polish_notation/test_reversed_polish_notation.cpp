#include "test_reversed_polish_notation.h"

void test_reversed_polish_notation ( int ( *algorithm ) ( const std::vector < Symbol * > &vector ) )
{
    std::cout << "test_reversed_polish_notation:\n";

    std::vector < Symbol * > vector1;
    Number n1 ( 5 );
    Number n2 ( 9 );
    Action a1 ( '+' );

    vector1.push_back ( &n1 );
    vector1.push_back ( &n2 );
    vector1.push_back ( &a1 );

    int answer = 14;
    int result = algorithm ( vector1 );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    std::vector < Symbol * > vector2;
    Number n12 ( 5 );
    Number n22 ( 9 );
    Action a12 ( '-' );

    vector2.push_back ( &n12 );
    vector2.push_back ( &n22 );
    vector2.push_back ( &a12 );

    answer = -4;
    result = algorithm ( vector2 );
    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    std::vector < Symbol * > vector3;
    Number n13 ( 5 );
    Number n23 ( 9 );
    Action a13 ( '-' );
    Number n33 ( 7 );
    Action a23 ( '*' );

    vector3.push_back ( &n13 );
    vector3.push_back ( &n23 );
    vector3.push_back ( &a13 );
    vector3.push_back ( &n33 );
    vector3.push_back ( &a23 );

    answer = -28;
    result = algorithm ( vector3 );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

}
