#include "types_tiptoe.h"

Point::Point() : m_x(0.0), m_y(0.0) {

}
Point::Point(double x, double y) : m_x(x), m_y(y) {

}

Circle::Circle() : m_center(), m_radius(1.0) {

}
Circle::Circle(Point center, double radius) : m_center(center), m_radius(radius) {
    
}
Circle::Circle(double x_center, double y_center, double radius) : m_center(x_center, y_center), m_radius(radius) {

}