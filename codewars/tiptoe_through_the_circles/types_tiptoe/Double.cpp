#include "Double.h"

bool are_equal(double a, double b, double epsilon) {
	return a > b ? a - b < epsilon : b - a < epsilon;
}

bool is_between(double a, double x_1, double x_2) {
	return (x_1 < a&& a < x_2) ||
		(x_2 < a&& a < x_1) ||
		are_equal(a, x_1) ||
		are_equal(a, x_2);
}

bool Are_equal::operator()(double left, double right) const noexcept {
	return are_equal(left, right);
}

Double::Double(double value) : m_value{ value } {

}

Double::operator double() const noexcept {
	return this->m_value;
}

std::size_t Double_hash::operator()(const Double& obj) const noexcept {
	return std::hash<double>{}(static_cast<int>(g_hashing_multiplier * obj.m_value));
}

std::size_t Double_hash::call(const Double& obj) noexcept {
	static const Double_hash instance;
	return instance(obj);
}

bool operator==(const Double& left, const Double& right) noexcept {
	return are_equal(left.m_value, right.m_value);
}