#include "test_horse.h"

void test_horse ( void ( *algorithm ) ( Path2_t &pathOut, const Vertex2_t &start, const Vertex2_t &finish ) )
{
    std::cout << "test_horse:\n";

    Path2_t result;
    Vertex2_t v1 = "e2";
    Vertex2_t v2 = "e4";
    algorithm ( result, v1, v2 );

    std::cout << v1 << " ->  ";
    for ( const auto &vertex : result )
        std::cout << vertex << ' ';
    std::cout << " -> " << v2 << '\n';


    v1 = "a1";
    v2 = "h8";
    result.clear();
    algorithm ( result, v1, v2 );

    std::cout << v1 << " ->  ";
    for ( const auto &vertex : result )
        std::cout << vertex << ' ';
    std::cout << " -> " << v2 << '\n';

}
