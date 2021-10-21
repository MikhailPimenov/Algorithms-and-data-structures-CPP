#include "Tangent.h"

Tangent::Tangent(
	const Point &a,
	const Point &b,
	const Circle& circle_a,
	const Circle& circle_b
) : m_a(a),
    m_b(b),
	m_length(get_distance(a, b)),
	m_circle_a(&circle_a),
	m_circle_b(&circle_b) {

}

bool operator==(const Tangent& tangent_1, const Tangent& tangent_2) noexcept{
	return (tangent_1.m_a == tangent_2.m_a &&
    		tangent_1.m_b == tangent_2.m_b &&
			*tangent_1.m_circle_a == *tangent_2.m_circle_a &&
			*tangent_1.m_circle_b == *tangent_2.m_circle_b) ||
		   (tangent_1.m_a == tangent_2.m_b &&
			tangent_1.m_b == tangent_2.m_a &&
			*tangent_1.m_circle_a == *tangent_2.m_circle_b &&
			*tangent_1.m_circle_b == *tangent_2.m_circle_a);
}

bool operator!=(const Tangent& tangent_1, const Tangent& tangent_2) noexcept {
	return !(tangent_1 == tangent_2);
}

std::size_t Tangent_hash::operator()(const Tangent& obj) const noexcept {
	return Point_hash::call(obj.m_a) +
		   Point_hash::call(obj.m_b);										// symmetrical : hash(Tangent(a,b)) = hash(Tangent(b,a))
}
