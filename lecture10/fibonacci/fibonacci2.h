#pragma once

namespace Fibonacci2 {
	static int cache[100];
	void initialize_cache(int* cache, int length);
}

int fibonacci2(int n);

int fibonacci_cached2(int n);

int fibonacci_fast2(int n);
