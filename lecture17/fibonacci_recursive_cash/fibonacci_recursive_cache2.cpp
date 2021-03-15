#include "fibonacci_recursive_cache2.h"

namespace Fibonacci_recursive_cache2 {
	void initialize_cache() {
		for (int index = 0; index < 1000; ++index)
			cache2[index] = 0;
	}
}

long long fibonacci_recursive_cache2(int n)
{
	std::cout << "one more recursion level\n";
	if (n > 1000)
		return -1;

	if (!Fibonacci_recursive_cache2::cache2[n])
		if (n < 2)
			Fibonacci_recursive_cache2::cache2[n] = n;
		else
			Fibonacci_recursive_cache2::cache2[n] = fibonacci_recursive_cache2(n - 1) +
			fibonacci_recursive_cache2(n - 2);
	return Fibonacci_recursive_cache2::cache2[n];
}
