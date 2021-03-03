#include "trajectory_tracing2.h"

int trajectory_tracing2(int* prices, bool* allowed, int length, int destination)
{
	if (destination == -1) destination = length;
	if (destination > length) return -1;

	int* costs = new int[destination];
	if (allowed[0]) costs[0] = prices[0];
	if (allowed[1]) costs[1] = prices[1] + (allowed[0] ? costs[0] : 0);

	for (int k = 2; k < destination; ++k)
	{
		assert(allowed[k - 1] || allowed[k - 2]);
		if (allowed[k - 1] && allowed[k - 2])
			costs[k] = prices[k] + (costs[k - 1] < costs[k - 2] ? costs[k - 1] : costs[k - 2]);
		else
			costs[k] = prices[k] + (allowed[k - 1] ? costs[k - 1] : costs[k - 2]);
	}
	int result = costs[destination - 1];
	delete[] costs;
	return result;
}
