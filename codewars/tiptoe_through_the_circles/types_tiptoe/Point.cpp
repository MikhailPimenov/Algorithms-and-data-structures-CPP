#include "Point.h"

Point::Point() : m_x(0.0), m_y(0.0) {

}
Point::Point(double x, double y) : m_x(x), m_y(y) {

}

bool operator==(const Point &point_1, const Point& point_2) {
	return are_equal(point_1.m_x, point_2.m_x) && are_equal(point_2.m_y, point_2.m_y);
}


std::size_t Point_hash::operator()(const Point& obj) const noexcept {
	return std::hash<double>{}(obj.m_x) +
		   std::hash<double>{}(obj.m_y);
}

std::size_t Point_hash::call(const Point& obj) noexcept {
	static const Point_hash instance;
	return instance(obj);
}