#include "fibonacci2.h"

namespace Fibonacci2 {
	void initialize_cache(int* cache, int length)
	{
		for (int i = 0; i < length; ++i)
			cache[i] = 0;
	}
}

int fibonacci2(int n)
{
	return n < 2 ? 1 : fibonacci2(n - 1) + fibonacci2(n - 2);
}

int fibonacci_cached2(int n)
{
	if (n > 100) return -1;

	if (n < 2) {
		if (Fibonacci2::cache[n] == 0)
			Fibonacci2::cache[n] = 1;
		return Fibonacci2::cache[n];
	}

	if (Fibonacci2::cache[n] == 0)
		Fibonacci2::cache[n] = fibonacci_cached2(n - 1) + fibonacci_cached2(n - 2);
	return Fibonacci2::cache[n - 1] + Fibonacci2::cache[n - 2];
}

int fibonacci_fast2(int n)
{
	if (n < 2) return 1;

	int* array = new int[n];
	array[0] = 1;
	array[1] = 1;

	for (int index = 2; index < n; ++index)
		array[index] = array[index - 1] + array[index - 2];

	int result = array[n - 1];

	delete[] array;

	return result;
}

