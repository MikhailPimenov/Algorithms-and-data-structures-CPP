#include "eratosthenes_sieve4.h"

void eratosthenes_sieve4(int n) {
	bool* allowed = new bool[n];
	
	for (int i = 0; i < n; ++i)
		allowed[i] = true;

	for (int divisor = 2; divisor < static_cast<int>(sqrt(n)) + 1; ++divisor)
		for (int number = 2 * divisor; number < n; number += divisor)
			if (allowed[number])
				allowed[number] = false;

	for (int number = 0; number < n; ++number)
		if (allowed[number])
			std::cout << number << '\n';

	delete[] allowed;
}
