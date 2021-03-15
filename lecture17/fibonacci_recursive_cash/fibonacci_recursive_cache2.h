#pragma once
#include <iostream>

namespace Fibonacci_recursive_cache2 {
	static long long cache2[1000];
	void initialize_cache();
}

long long fibonacci_recursive_cache2(int n);
