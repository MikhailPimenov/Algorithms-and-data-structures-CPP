#include "test_levenstein.h"

void test_levenstein ( int ( *algorithm ) ( const char *, const char * ) )
{
    std::cout << "test_levenstein:\n";

    const char *s11 = "pig";
    const char *s12 = "big";
    int answer = 1;
    int result = algorithm ( s11, s12 );

    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s21 = "bag";
    const char *s22 = "big";
    answer = 1;
    result = algorithm ( s21, s22 );

    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s31 = "head";
    const char *s32 = "home";
    answer = 3;
    result = algorithm ( s31, s32 );

    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s41 = "table";
    const char *s42 = "table1234";
    answer = 4;
    result = algorithm ( s41, s42 );

    std::cout << "test #4: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s51 = "table";
    const char *s52 = "table";
    answer = 0;
    result = algorithm ( s51, s52 );

    std::cout << "test #5: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s61 = "flower";
    const char *s62 = "tower";
    answer = 2;
    result = algorithm ( s61, s62 );

    std::cout << "test #6: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s71 = "";
    const char *s72 = "";
    answer = 0;
    result = algorithm ( s71, s72 );

    std::cout << "test #7: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s81 = "answer";
    const char *s82 = "result";
    answer = 5;
    result = algorithm ( s81, s82 );

    std::cout << "test #8: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';


    const char *s91 = "pig";
    const char *s92 = "pig is big";
    answer = 7;
    result = algorithm ( s91, s92 );

    std::cout << "test #9: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';
}
