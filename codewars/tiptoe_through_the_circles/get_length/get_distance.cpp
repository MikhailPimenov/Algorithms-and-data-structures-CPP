#include "get_distance.h"

double get_distance(Point p1, Point p2) {
	return std::sqrt(std::pow(p1.m_x - p2.m_x, 2.0) + 
		             std::pow(p1.m_y - p2.m_y, 2.0));
}

double get_distance(double x1, double y1, double x2, double y2) {
	return std::sqrt(std::pow(x1 - x2, 2.0) + 
		             std::pow(y1 - y2, 2.0));
}