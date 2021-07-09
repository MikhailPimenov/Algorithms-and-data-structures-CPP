#include "fibonacci_recursive_cache4.h"

namespace Fibonacci_recursive_cache4 {
	void initialize_cache() {
		for (int i = 0; i < 1000; ++i)
			cache[i] = -1;
	}
}

long long fibonacci_recursive_cache4(int n) {
	if (n == 0 || n == 1) {
		if (Fibonacci_recursive_cache4::cache[n] == -1)
			Fibonacci_recursive_cache4::cache[n] = n;
		return Fibonacci_recursive_cache4::cache[n];
	}

	if (Fibonacci_recursive_cache4::cache[n] == -1)
		Fibonacci_recursive_cache4::cache[n] = fibonacci_recursive_cache4(n - 1) + fibonacci_recursive_cache4(n - 2);

	return Fibonacci_recursive_cache4::cache[n];
}