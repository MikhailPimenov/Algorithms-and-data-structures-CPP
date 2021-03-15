#include "discrete_bag2.h"

namespace Discrete_bag2 {
	int maximum(int a, int b) {
		return a >= b ? a : b;
	}
}


int discrete_bag2(const int* values, const int* masses, int length, int mass) {
	int* f_long = new int[(length + 1) * (mass + 1)];
	int** f = new int* [mass + 1];

	for (int i = 0; i < mass + 1; ++i)
		f[i] = f_long + i * (length + 1);

	for (int i = 0; i < mass + 1; ++i)
		f[i][0] = 0;
	for (int j = 0; j < length + 1; ++j)
		f[0][j] = 0;

	for (int i = 1; i < mass + 1; ++i) {
		for (int j = 1; j < length + 1; ++j) {
			if (masses[j - 1] <= i) {
				f[i][j] = Discrete_bag2::maximum(f[i][j - 1],
					values[j - 1] + f[i - masses[j - 1]][j - 1]);
			}
			else {
				f[i][j] = f[i][j - 1];
			}
		}
	}

	int result = f[mass][length];

	delete[] f_long;
	delete[] f;

	return result;
}

int discrete_bag_adapted2(const std::vector<std::pair<int, int>>& items, int mass) {
	int* values = new int[items.size()];
	int* masses = new int[items.size()];

	for (std::size_t index = 0; index < items.size(); ++index) {
		values[index] = items[index].second;
		masses[index] = items[index].first;
	}

	int result = discrete_bag2(values, masses, items.size(), mass);

	delete[] masses;
	delete[] values;

	return result;
}
