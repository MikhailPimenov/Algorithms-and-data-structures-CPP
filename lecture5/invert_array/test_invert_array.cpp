#include "test_invert_array.h"

bool is_equal ( const int *array1, const int *array2, int length )
{
	for ( int index = 0; index < length; ++index ) {
		if ( ( array1 + index ) && ( array2 + index ) ) {
			if ( array1[index] != array2[index] )
				return false;
		} else if ( ( array1 + index ) && ! ( array2 + index ) )
			return false;
		else if ( ! ( array1 + index ) && ( array2 + index ) )
			return false;
	}
	return true;
}
void test_invert_array ( void ( *algorithm ) ( int *, int ) )
{
	int array1[] = { 1, 2, 3, 4, 5 };
	int length1 = sizeof ( array1 ) / sizeof ( array1[0] );

	int result1[] = { 5, 4, 3, 2, 1 };
	algorithm ( array1, length1 );
	std::cout << "test#1: " << ( is_equal ( array1, result1, length1 ) ? "ok" : "FAILED" ) << '\n';


	int array2[] = { 0, 20, 35, 7, 15, 32 };
	int length2 = sizeof ( array2 ) / sizeof ( array2[0] );

	int result2[] = { 32, 15, 7, 35, 20, 0 };
	algorithm ( array2, length2 );
	std::cout << "test#2: " << ( is_equal ( array2, result2, length2 ) ? "ok" : "FAILED" ) << '\n';


	int array3[] = { 0, 0, 3, 0, 0, 0, 0, 0 };
	int length3 = sizeof ( array3 ) / sizeof ( array3[0] );

	int result3[] = { 0, 0, 0, 0, 0, 3, 0, 0 };
	algorithm ( array3, length3 );
	std::cout << "test#3: " << ( is_equal ( array3, result3, length3 ) ? "ok" : "FAILED" ) << '\n';

}
