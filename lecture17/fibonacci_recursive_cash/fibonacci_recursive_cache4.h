#pragma once

namespace Fibonacci_recursive_cache4 {
	static int cache[1000];

	void initialize_cache();
}

long long fibonacci_recursive_cache4(int n);