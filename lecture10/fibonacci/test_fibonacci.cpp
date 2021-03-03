#include "test_fibonacci.h"

void test_fibonacci(int (*algorithm) (int))
{
	std::cout << "test_fibonacci:\n";

	for (int i = 0; i < 40; ++i)
	{
		Timer t;
		int number = algorithm(i);
		double time = t.elapsed();

		std::cout << i + 1 << ' ' << number << '\n';
		std::cout << "\t\tt=" << time << '\n';
	}
}
