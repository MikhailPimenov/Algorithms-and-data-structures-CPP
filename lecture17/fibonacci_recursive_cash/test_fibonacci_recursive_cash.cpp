#include "test_fibonacci_recursive_cash.h"

void test_fibonacci_recursive_cash(long long (*algorithm) (int))
{
	std::cout << "test_fibonacci_recursive_cash:\n";

	int n = 90;
	long long j = 0;
	for (int i = 1; i < n; ++i)
	{
		long long f = algorithm(i);
		std::cout << "n=" << i << ": " << f << ' ';
		/*while (j * j <= f)
		{
			long long k = j * j;
			if (k == f)
			{
				std::cout << "true " << j << ' ' << k;
				break;
			}
			++j;
		}*/
		std::cout << '\n';
	}
}
