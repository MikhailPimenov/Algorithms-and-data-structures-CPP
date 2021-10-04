#include "Tangent.h"

Tangent::Tangent(
	Point a,
	Point b,
	const Circle& circle_a,
	const Circle& circle_b
) : m_a(a),
    m_b(b),
	m_length(get_distance(a, b)),
	m_circle_a(circle_a),
	m_circle_b(circle_b) {

}