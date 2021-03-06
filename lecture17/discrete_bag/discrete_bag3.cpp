#include "discrete_bag3.h"

namespace Discrete_bag3 {
	int maximum(int a, int b) {
		return a >= b ? a : b;
	}
}


int discrete_bag3(const int* m, const int* v, int length, int bag_mass) {
	int* f_long = new int[(bag_mass + 1) * (length + 1)];
	int** ff = new int* [bag_mass + 1];

	for (int i = 0; i < bag_mass + 1; ++i)
		ff[i] = f_long + i * (length + 1);

	for (int i = 0; i < bag_mass + 1; ++i)
		ff[i][0] = 0;
	for (int j = 0; j < length + 1; ++j)
		ff[0][j] = 0;

	for (int i = 1; i < bag_mass + 1; ++i) {
		for (int j = 1; j < length + 1; ++j) {
			if (i >= m[j - 1]) ff[i][j] = Discrete_bag3::maximum(ff[i][j - 1],
				v[j - 1] + ff[i - m[j - 1]][j - 1]);
			else ff[i][j] = ff[i][j - 1];
		}
	}

	int result = ff[bag_mass][length];

	delete[] ff;
	delete[] f_long;

	return result;
}

int discrete_bag_adapted3(const std::vector<std::pair<int, int>>& items, int bag_mass)
{
	int* m = new int[items.size()];
	int* v = new int[items.size()];

	for (std::size_t i = 0; i < items.size(); ++i) {
		m[i] = items.at(i).first;
		v[i] = items.at(i).second;
	}

	int result = discrete_bag3(m, v, items.size(), bag_mass);

	delete[] m;
	delete[] v;

	return result;
}
