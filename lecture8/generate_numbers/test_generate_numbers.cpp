#include "test_generate_numbers.h"

void test_generate_numbers ( void ( *algorithm ) ( int, int ) )
{
	std::cout << "test_generate_numbers:\n";
	algorithm ( 2, 5 );
}
