#include "Circle.h"

Circle::Circle() : m_center(), m_radius(1.0) {

}
Circle::Circle(Point center, double radius) : m_center(center), m_radius(radius) {

}
Circle::Circle(double x_center, double y_center, double radius) : m_center(x_center, y_center), m_radius(radius) {

}