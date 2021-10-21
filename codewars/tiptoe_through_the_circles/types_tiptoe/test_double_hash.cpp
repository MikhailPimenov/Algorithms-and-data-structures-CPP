#include "test_double_hash.h"

void test_double_hash() {
	std::cout << "test_double_hash:\n";

	std::unordered_set <Double, Algorithm> set;

	set.insert(1.5);
	set.insert(1.4999999999999996);
	std::cout << "test  #1: " << (set.size() == 1u ? "ok" : "FAILED") << '\n';
	set.clear();


	set.insert(2.0);
	set.insert(1.9999999999999998);
	std::cout << "test  #2: " << (set.size() == 1u ? "ok" : "FAILED") << '\n';
	set.clear();


	set.insert(1.5);
	set.insert(1.4999999999999996);
	std::cout << "test  #3: " << (set.size() == 1u ? "ok" : "FAILED") << '\n';
	set.clear();


	set.insert(1.5);
	set.insert(1.4999999999999996);
	std::cout << "test  #4: " << (set.size() == 1u ? "ok" : "FAILED") << '\n';
	set.clear();

}