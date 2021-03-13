#include "test_brace_sequence.h"

void test_brace_sequence ( bool ( *algorithm )( const char *) )
{
    std::cout << "test_brace_sequence:\n";

    const char *cString1 = "[()]";
    bool answer = true;
    bool result = algorithm ( cString1 );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString2 = "z1![fv(fs)003]_f1(sdfsdf)";
    answer = true;
    result = algorithm ( cString2 );
    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString3 = "[(])";
    answer = false;
    result = algorithm ( cString3 );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString4 = "[";
    answer = false;
    result = algorithm ( cString4 );
    std::cout << "test #4: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString5 = "]";
    answer = false;
    result = algorithm ( cString5 );
    std::cout << "test #5: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString6 = "(";
    answer = false;
    result = algorithm ( cString6 );
    std::cout << "test #6: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString7 = ")";
    answer = false;
    result = algorithm ( cString7 );
    std::cout << "test #7: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString8 = "[][][[[]]]([([])])";
    answer = true;
    result = algorithm ( cString8 );
    std::cout << "test #8: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString9 = "()9]";
    answer = false;
    result = algorithm ( cString9 );
    std::cout << "test #9: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

    const char *cString10 = "[][][[]]]([([])])";
    answer = false;
    result = algorithm ( cString10 );
    std::cout << "test #10: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';

}
