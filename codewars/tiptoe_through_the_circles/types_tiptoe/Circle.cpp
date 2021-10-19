#include "Circle.h"

Circle::Circle() : m_center(), m_radius(1.0) {

}
Circle::Circle(Point center, double radius) : m_center(center), m_radius(radius) {

}
Circle::Circle(double x_center, double y_center, double radius) : m_center(x_center, y_center), m_radius(radius) {

}

bool operator==(const Circle& circle_1, const Circle& circle_2) {
	return are_equal(circle_1.m_radius, circle_2.m_radius) && circle_1.m_center == circle_2.m_center;
}
bool operator!=(const Circle& circle_1, const Circle& circle_2) {
	return !(circle_1 == circle_2);
}

std::size_t Circle_hash::operator()(const Circle& obj) const noexcept {
	return Point_hash::call(obj.m_center) +
		   Double_hash::call(obj.m_radius);
}
