#include "test_square_sum_brute_force_improved.h"

static void print_vector(const std::vector<int>& vector) {
	std::cout << "vector: ";
	for (int element : vector)
		std::cout << element << ' ';
	std::cout << '\n';
}

void test_square_sum_brute_force_improved(std::vector<int>(*algorithm)(int)) {
	std::cout << "test_square_sum_brute_force_improved:\n";

	Timer entire_timer;
	for (int i = 1; i < 61; ++i) {
		std::cout << i << ' ';
		
		Timer timer;
		const auto result = algorithm(i);
		const double time = timer.elapsed();
		
		print_vector(result);
		std::cout << "time = " << time << '\n';
	}
	const double entire_time = entire_timer.elapsed();
	std::cout << "entire time = " << entire_time << '\n';
}