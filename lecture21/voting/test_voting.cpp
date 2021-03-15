#include "test_voting.h"

void test_voting ( void ( *algorithm )( const std::string &stream,
                                        std::unordered_map < std::string, int > &dbOut ) )
{
    std::cout << "test_voting: " << '\n';

    std::string arkady = "Arkady";
    std::string anton  = "Anton";
    std::string andrew = "Andrew";

    std::string stream = "10";
    stream.append ( " " + arkady );
    stream.append ( " " + arkady );
    stream.append ( " " + anton  );
    stream.append ( " " + andrew );
    stream.append ( " " + arkady );
    stream.append ( " " + arkady );
    stream.append ( " " + anton  );
    stream.append ( " " + anton  );
    stream.append ( " " + andrew );
    stream.append ( " " + arkady );

    std::unordered_map < std::string, int > answer
    {
        std::pair < std::string, int > ( arkady, 5 ),
        std::pair < std::string, int > ( anton, 3 ),
        std::pair < std::string, int > ( andrew, 2 ),
    };
    std::unordered_map < std::string, int > result;
    algorithm ( stream, result );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

}
