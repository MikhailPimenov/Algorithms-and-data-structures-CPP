#include "test_largest_sum_row_subsequence.h"

void test_largest_sum_row_subsequence ( int ( *algorithm )( const int *array, int length ) )
{
    std::cout << "test_largest_sum_row_subsequence:\n";

    int array1[] { -5, -5, -5, 10, 10, 10, -5, -5, 9, 9, 9, 9, -5, -5, };
    int length1 = ( sizeof ( array1 ) ) / sizeof ( array1[0] );

    int answer = 56;
    int result = algorithm ( array1, length1 );
    std::cout << "test #1: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array2[] { -5, -5, -5, 10, 10, 10, -500, -500, 9, 9, 9, 9, -5, -5, };
    int length2 = ( sizeof ( array2 ) ) / sizeof ( array2[0] );

    answer = 36;
    result = algorithm ( array2, length2 );
    std::cout << "test #2: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array3[] { -5, -5, -5, 10, 10, 10, -500, -500, 99, -5, -5, };
    int length3 = ( sizeof ( array3 ) ) / sizeof ( array3[0] );

    answer = 99;
    result = algorithm ( array3, length3 );
    std::cout << "test #3: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array4[] { -5, -5, -5, 10, 10, 10, -5, -5, 99, -5, -5, };
    int length4 = ( sizeof ( array4 ) ) / sizeof ( array4[0] );

    answer = 119;
    result = algorithm ( array4, length4 );
    std::cout << "test #4: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array5[] { 1, 10, 1 };
    int length5 = ( sizeof ( array5 ) ) / sizeof ( array5[0] );

    answer = 12;
    result = algorithm ( array5, length5 );
    std::cout << "test #5: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array6[] { 1, 10, -1 };
    int length6 = ( sizeof ( array6 ) ) / sizeof ( array6[0] );

    answer = 11;
    result = algorithm ( array6, length6 );
    std::cout << "test #6: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array7[] { 1, -10, 1 };
    int length7 = ( sizeof ( array7 ) ) / sizeof ( array7[0] );

    answer = 1;
    result = algorithm ( array7, length7 );
    std::cout << "test #7: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array8[] { 1, -10, 2 };
    int length8 = ( sizeof ( array8 ) ) / sizeof ( array8[0] );

    answer = 2;
    result = algorithm ( array8, length8 );
    std::cout << "test #8: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array9[] { -5, -5, -5, 10, -5, 10, -5, 10, -5, 10 };
    int length9 = ( sizeof ( array9 ) ) / sizeof ( array9[0] );

    answer = 25;
    result = algorithm ( array9, length9 );
    std::cout << "test #9: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array10[] { -5, -5, -5, 10, -5, 10, -5, 10, -50, 10 };
    int length10 = ( sizeof ( array10 ) ) / sizeof ( array10[0] );

    answer = 20;
    result = algorithm ( array10, length10 );
    std::cout << "test #10: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array11[] { -5, -5, -5, 10, -50, 10, -5, 10, -50, 10 };
    int length11 = ( sizeof ( array11 ) ) / sizeof ( array11[0] );

    answer = 15;
    result = algorithm ( array11, length11 );
    std::cout << "test #11: " << ( ( answer == result ) ? "ok" : "FAILED" ) << '\n';



    int array12[]{ -5, -5, -5, 5, -50, 5, -5, -5, -50, 100 };
    int length12 = (sizeof(array12)) / sizeof(array12[0]);

    answer = 100;
    result = algorithm(array12, length12);
    std::cout << "test #12: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array13[]{ -5, -5, -5, 10, 10, -5, -5, -5};
    int length13 = (sizeof(array13)) / sizeof(array13[0]);

    answer = 20;
    result = algorithm(array13, length13);
    std::cout << "test #13: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array14[]{ 100, -5, -5, 10, 10, -5, -5, 100 };
    int length14 = (sizeof(array14)) / sizeof(array14[0]);

    answer = 200;
    result = algorithm(array14, length14);
    std::cout << "test #14: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array15[]{-5, -5, -5, 10, 10, -5, -5, 10, 10, -5, -5, -5 };
    int length15 = (sizeof(array15)) / sizeof(array15[0]);

    answer = 30;
    result = algorithm(array15, length15);
    std::cout << "test #15: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array16[]{ 20, -5, -5, -5, -5, -5, -5, 30, -5, -5, -5 };
    int length16 = (sizeof(array16)) / sizeof(array16[0]);

    answer = 30;
    result = algorithm(array16, length16);
    std::cout << "test #16: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array17[]{ 20, -5, -5, 30, -5, -5, -5 };
    int length17 = (sizeof(array17)) / sizeof(array17[0]);

    answer = 40;
    result = algorithm(array17, length17);
    std::cout << "test #17: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array18[]{ -5, 20, -5, -5, 30, -5, -5, 30, -5, -5 };
    int length18 = (sizeof(array18)) / sizeof(array18[0]);

    answer = 60;
    result = algorithm(array18, length18);
    std::cout << "test #18: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array19[]{ -5, 20, -5, -5, -5, -5, -5, -5, 30, -5, -5, 30, -5, -5, 30, -5, -5, -5, -5, 10 };
    int length19 = (sizeof(array19)) / sizeof(array19[0]);

    answer = 70;
    result = algorithm(array19, length19);
    std::cout << "test #19: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array20[]{ -5, 20, -5, -5, -5, -5, -5, -5, 30, -5, -5, 30, -5, -5, 30, -5, -5, -500, -500, 500, -500, -500, -5, -5, 10 };
    int length20 = (sizeof(array20)) / sizeof(array20[0]);

    answer = 500;
    result = algorithm(array20, length20);
    std::cout << "test #20: " << ((answer == result) ? "ok" : "FAILED") << '\n';



    int array21[]{ 30, -5, -5, 30, -50, -500, -500, -500, 500 };
    int length21 = (sizeof(array21)) / sizeof(array21[0]);

    answer = 500;
    result = algorithm(array21, length21);
    std::cout << "test #21: " << ((answer == result) ? "ok" : "FAILED") << '\n';

}
