#pragma once

#include <functional>

#include "../constants_tiptoe.h"

bool are_equal(double a, double b, double epsilon = g_epsilon);

bool is_between(double a, double x_1, double x_2);

class Are_equal {
public:
	bool operator()(double left, double right) const noexcept;
};

struct Double {
	double m_value;

	Double(double value = 0.0);

	operator double() const noexcept;
	
};

struct Double_hash {
	std::size_t operator()(const Double& obj) const noexcept;
	static std::size_t call(const Double& obj) noexcept;
};

bool operator==(const Double& left, const Double& right) noexcept;