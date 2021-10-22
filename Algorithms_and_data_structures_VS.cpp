#include <iomanip>
#include <iostream>

//#include "codewars/tiptoe_through_the_circles/get_graph/get_tangents/get_tangents.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/get_tangents/test_get_tangents.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/get_arcs/get_arcs.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/get_arcs/test_get_arcs.h"
//#include "codewars/tiptoe_through_the_circles/get_length/get_arc_length.h"
//#include "codewars/tiptoe_through_the_circles/get_length/test_get_arc_length.h"
//#include "codewars/tiptoe_through_the_circles/get_length/get_distance_from_line.h"
//#include "codewars/tiptoe_through_the_circles/get_length/test_get_distance_from_line.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/is_point_between_points.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/test_is_point_between_points.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/there_is_collision_between_tangent_and_circle.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/test_there_is_collision_between_tangent_and_circle.h"
//#include "codewars/tiptoe_through_the_circles/get_angle/get_angle.h"
//#include "codewars/tiptoe_through_the_circles/get_angle/test_get_angle.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_arcs/there_is_collision_between_arc_and_circle.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_arcs/test_there_is_collision_between_arc_and_circle.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/filter_tangents.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_tangents/test_filter_tangents.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/get_graph.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/test_get_graph.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_arcs/filter_arcs.h"
//#include "codewars/tiptoe_through_the_circles/get_graph/remove_arcs/test_filter_arcs.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/Double.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/test_double_hash.h"
//#include "codewars/tiptoe_through_the_circles/test_tiptoe_through_the_circles.h"
//#include "codewars/tiptoe_through_the_circles/tiptoe_through_the_circles.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/Arc.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/Circle.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/Point.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe/Tangent.h"
//#include "codewars/tiptoe_through_the_circles/types_tiptoe.h"


#include <cmath>
#include <deque>
#include <unordered_map>
#include <unordered_set>

const double g_pi = atan(1.0) * 4.0;

constexpr double g_epsilon = 1e-8;


// compares two double number with certain epsilon
bool are_equal(double a, double b, double epsilon = g_epsilon) {
	return a > b ? a - b < epsilon : b - a < epsilon;
}

// computes hash for double. This is needed for data structures
struct Double_hash {
	std::size_t operator()(double obj) const noexcept {
		// completely wrong, but it only creates more nodes in graph
		return std::hash<double>{}(obj);                         
	}
	static std::size_t call(double obj) noexcept {
		static const Double_hash instance;
		return instance(obj);
	}
};


struct Point {
	double m_x, m_y;

	Point() : m_x(0.0), m_y(0.0) {}
	Point(double x, double y) : m_x(x), m_y(y) {}
};

// computes hash for Point. This is needed for data structures
struct Point_hash {
	std::size_t operator()(const Point& obj) const noexcept {
		const std::size_t x = std::hash<double>{}(obj.m_x);
		const std::size_t y = std::hash<double>{}(obj.m_y);
		return (x + y) * (x + y + 1) / 2 + y;							// Cantor's pair
	}
	static std::size_t call(const Point& obj) noexcept {
		static const Point_hash instance;								// singleton
		return instance(obj);
	}
};

// returns true if point_1 == point_2
bool operator==(const Point& point_1, const Point& point_2) noexcept {
	return are_equal(point_1.m_x, point_2.m_x) && 
		   are_equal(point_1.m_y, point_2.m_y);
}

// returns true if point_1 != point_2
bool operator!=(const Point& point_1, const Point& point_2) noexcept {
	return !(point_1 == point_2);
}

// returns distance between two points
double get_distance(const Point& p1, const Point& p2) {
	return std::sqrt(std::pow(p1.m_x - p2.m_x, 2.0) +
		std::pow(p1.m_y - p2.m_y, 2.0));
}

struct Circle {
	Point m_center;
	double m_radius;

	Circle() : m_center(), m_radius(1.0) {}
	Circle(const Point &center, double radius) : m_center(center), m_radius(radius) {}
	Circle(double x_center, double y_center, double radius) : m_center(x_center, y_center), m_radius(radius) {}
};

// computes hash for Circle. This is needed for data structures
struct Circle_hash {
	std::size_t operator()(const Circle& obj) const noexcept {
		return Point_hash::call(obj.m_center) +
			   Double_hash::call(obj.m_radius);
	}
};

// returns true if circle_1 == circle_2
bool operator==(const Circle& circle_1, const Circle& circle_2) {
	return are_equal(circle_1.m_radius, circle_2.m_radius) && 
		   circle_1.m_center == circle_2.m_center;
}
// returns true if circle_1 != circle_2
bool operator!=(const Circle& circle_1, const Circle& circle_2) {
	return !(circle_1 == circle_2);
}

struct Tangent {
	Point m_a;
	Point m_b;
	double m_length;
	const Circle* m_circle_a;
	const Circle* m_circle_b;

	Tangent(
		const Point& a, 
		const Point& b, 
		const Circle& circle_a, 
		const Circle& circle_b
	) : 
		m_a(a),
		m_b(b),
		m_length(get_distance(a, b)),
		m_circle_a(&circle_a),
		m_circle_b(&circle_b) {
	}
};

// computes hash for Tangent. This is needed for data structures
struct Tangent_hash {
	std::size_t operator()(const Tangent& obj) const noexcept {
		return Point_hash::call(obj.m_a) +
			Point_hash::call(obj.m_b);										// symmetrical : hash(Tangent(a,b)) = hash(Tangent(b,a))
	}
};

// returns true if tangent_1 == tangent_2
bool operator==(const Tangent& tangent_1, const Tangent& tangent_2) noexcept {
	return (tangent_1.m_a == tangent_2.m_a &&
		tangent_1.m_b == tangent_2.m_b &&
		*tangent_1.m_circle_a == *tangent_2.m_circle_a &&
		*tangent_1.m_circle_b == *tangent_2.m_circle_b) ||
		(tangent_1.m_a == tangent_2.m_b &&
			tangent_1.m_b == tangent_2.m_a &&
			*tangent_1.m_circle_a == *tangent_2.m_circle_b &&
			*tangent_1.m_circle_b == *tangent_2.m_circle_a);
}

// returns true if tangent_1 != tangent_2
bool operator!=(const Tangent& tangent_1, const Tangent& tangent_2) noexcept {
	return !(tangent_1 == tangent_2);
}

// returns an angle between line(left_side, center) and positive direction of x axis
double get_angle_with_x_axis(const Point& left_side, const Point& center) {
	if (are_equal(left_side.m_x, center.m_x)) {
		if (left_side.m_y < center.m_y)
			return 3.0 * g_pi / 2.0;
		return g_pi / 2.0;
	}

	const double angle = atan((left_side.m_y - center.m_y) / (left_side.m_x - center.m_x));

	if (left_side.m_x < center.m_x)
		return angle + g_pi;

	if (left_side.m_y < center.m_y)
		return angle + 2.0 * g_pi;

	return angle;
}

// returns the length of arc
double get_arc_length(const Point& a, const Point& b, const Circle& circle) {

	const double angle_a = get_angle_with_x_axis(a, circle.m_center);
	const double angle_b = get_angle_with_x_axis(b, circle.m_center);

	// angles from 0 to 2*pi are considered
	const double delta_angle =
		angle_a > angle_b ? angle_a - angle_b :
		2.0 * g_pi + angle_a - angle_b;

	return circle.m_radius * delta_angle;
}

struct Arc {
	Point m_a;
	Point m_b;
	double m_length;
	const Circle* m_owner;

	Arc(
		const Point& a, 
		const Point& b, 
		const Circle& owner
	) : 
		m_a{ a },
		m_b{ b },
		m_length{ get_arc_length(a, b, owner) },
		m_owner{ &owner } {
	}
};

// computes hash for Arc. This is needed for data structures
struct Arc_hash {
	std::size_t operator()(const Arc& obj) const noexcept {
		return Point_hash::call(obj.m_a) +
			   Point_hash::call(obj.m_b) +
			   std::hash<double>{}(obj.m_length);
	}
};
	
bool operator==(const Arc& arc_1, const Arc& arc_2) noexcept {
	return arc_1.m_a == arc_2.m_a &&
		   arc_1.m_b == arc_2.m_b &&
		   arc_1.m_owner->m_center == arc_2.m_owner->m_center &&
		   are_equal(arc_1.m_length, arc_2.m_length);
}
bool operator!=(const Arc& arc_1, const Arc& arc_2) noexcept {
	return !(arc_1 == arc_2);
}

// type for length
using Length_t = double;
// hashing length
using Length_t_hash = Double_hash;
// to store tangents
using Tangents_t = std::unordered_set<Tangent, Tangent_hash>;
// to store arcs
using Arcs_t = std::unordered_set<Arc, Arc_hash>;
// to store points
using Points_t = std::unordered_set<Point, Point_hash>;
// to store points according to circle they belong to
using Points_on_circles_t = std::unordered_map<Circle, Points_t, Circle_hash>;
// node type for graph
using Vertex_t = Point;
// hashing node
using Vertex_t_hash = Point_hash;
// to store neighbors for the node in the graph with the cost (distance) of the edges
using Vertices_t = std::unordered_multimap<Vertex_t, Length_t, Vertex_t_hash>;
// queue - it is needed for dijkstra algorithm (breadth first search)
using Queue_t = std::deque<Vertex_t>;
// to store shortest distances - for dijkstra algorithm
using Distances_t = std::unordered_map<Vertex_t, Length_t, Vertex_t_hash>;;
// to store graph - for dijkstra algorithm
using Graph_t = std::unordered_map<Vertex_t, Vertices_t, Vertex_t_hash>;

// returns true if (x_1 <= a <= x_2) or (x_2 <= a <= x_1) 
bool is_between(double a, double x_1, double x_2) {
	return (x_1 < a && a < x_2) ||
		   (x_2 < a && a < x_1) ||
		   are_equal(a, x_1) ||
		   are_equal(a, x_2);
}

// returns distance between the center of the circle and the line tangent lays on
double get_distance(const Circle& circle, const Tangent& tangent) {
	// see distance between point and line
	const double numerator = std::abs(
		(tangent.m_b.m_x - tangent.m_a.m_x) * (tangent.m_a.m_y - circle.m_center.m_y) -
		(tangent.m_a.m_x - circle.m_center.m_x) * (tangent.m_b.m_y - tangent.m_a.m_y)
	);
	const double distance = get_distance(tangent.m_a, tangent.m_b);

	return numerator / distance;
}

// returns true if the projection of point on the line(point_1, point_2) lays between point_1 and point_2
bool is_point_between_points(const Point& point, const Point& point_1, const Point& point_2) {
	if (are_equal(point_1.m_x, point_2.m_x))
		return is_between(point.m_y, point_1.m_y, point_2.m_y);

	const double distance = get_distance(point_1, point_2);

	const double k = ((point_2.m_y - point_1.m_y) * (point.m_x - point_1.m_x) -
		(point_2.m_x - point_1.m_x) * (point.m_y - point_1.m_y)) /
		(distance * distance);

	const double x_n = point.m_x - k * (point_2.m_y - point_1.m_y);

	return is_between(x_n, point_1.m_x, point_2.m_x);
}

// returns true if tangent can not exist because circle covers it (or its part)
bool there_is_collision_between_tangent_and_circle(const Tangent& tangent, const Circle& circle) {

	// circle is far enough from line on which tangent is
	if (get_distance(circle, tangent) > circle.m_radius)
		return false;

	// circle intersects with tangent between tangent's ends
	if (is_point_between_points(circle.m_center, tangent.m_a, tangent.m_b))
		return true;

	// circle covers one of tangent's ends
	if (get_distance(circle.m_center, tangent.m_a) > circle.m_radius &&
		get_distance(circle.m_center, tangent.m_b) > circle.m_radius)
		return false;

	return true;
}

// removes all the tangents which can not exist
void filter_tangents(Tangents_t& tangents, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		for (auto tangent = tangents.cbegin(); tangent != tangents.cend();) {
			if (*(tangent->m_circle_a) != circle && *(tangent->m_circle_b) != circle) {
				if (there_is_collision_between_tangent_and_circle(*tangent, circle)) {
					tangent = tangents.erase(tangent);
					continue;
				}
			}
			++tangent;
		}
	}
}

// returns true if arc can not exist because circle covers it (or its part)
bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle) {

	const double distance = get_distance(arc.m_owner->m_center, circle.m_center);


	if (distance > arc.m_owner->m_radius + circle.m_radius ||               // arc and circle not intersect 
		arc.m_owner->m_radius > distance + circle.m_radius ||               // circle is deep inside arc and does not touch arc 
		are_equal(arc.m_owner->m_radius, distance + circle.m_radius))       // circle is inside arc, but touches it
		return false;


	// circle covers circumference of arc's owner

	const double angle_b = get_angle_with_x_axis(arc.m_b, arc.m_owner->m_center);
	const double angle = get_angle_with_x_axis(circle.m_center, arc.m_owner->m_center);
	const double angle_a = get_angle_with_x_axis(arc.m_a, arc.m_owner->m_center);

	// considering angles only from 0 to 2*pi
	const double angle_a_rotated = angle_a > angle_b ?
		angle_a - angle_b : 2.0 * g_pi + angle_a - angle_b;
	const double angle_b_rotated = 0.0;
	const double angle_rotated = angle > angle_b ?
		angle - angle_b : 2.0 * g_pi + angle - angle_b;


	// circle is from the side of arc
	if (is_between(angle_rotated, angle_a_rotated, angle_b_rotated))
		return true;

	// circle covers one of arc's ends
	if (get_distance(arc.m_a, circle.m_center) > circle.m_radius &&
		get_distance(arc.m_b, circle.m_center) > circle.m_radius)
		return false;

	return true;
}

// removes all the arcs which can not exist
void filter_arcs(Arcs_t& arcs, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		for (auto arc = arcs.cbegin(); arc != arcs.cend();) {
			if (*(arc->m_owner) != circle) {
				if (there_is_collision_between_arc_and_circle(*arc, circle)) {
					arc = arcs.erase(arc);
					continue;
				}
			}
			++arc;
		}
	}
}

// returns all possible tangents between these two circles
Tangents_t get_tangents(const Circle& circle_1, const Circle& circle_2) {

	// circles have common center - no tangents
	if (circle_1.m_center == circle_2.m_center)
		return {};

	// one circle is inside another one or have only one common point - no tangents
	const double distance_between_circles = get_distance(circle_1.m_center, circle_2.m_center);
	if (are_equal(distance_between_circles + circle_1.m_radius, circle_2.m_radius) ||
		are_equal(distance_between_circles + circle_2.m_radius, circle_1.m_radius) ||
		distance_between_circles + circle_1.m_radius < circle_2.m_radius ||
		distance_between_circles + circle_2.m_radius < circle_1.m_radius)
		return {};

	// circles intersects - no inner tangents
	bool no_inner_tangents = false;
	if (distance_between_circles < circle_1.m_radius + circle_2.m_radius ||
		are_equal(circle_1.m_radius + circle_2.m_radius, distance_between_circles))
		no_inner_tangents = true;

	const auto& circle_b =
		circle_2.m_center.m_y >= circle_1.m_center.m_y ? circle_2 : circle_1;  // upper circle
	const auto& circle_a =
		circle_2.m_center.m_y < circle_1.m_center.m_y ? circle_2 : circle_1;   // lower circle

	const double r_a = circle_a.m_radius;
	const double r_b = circle_b.m_radius;
	const double xo_a = circle_a.m_center.m_x;
	const double yo_a = circle_a.m_center.m_y;
	const double xo_b = circle_b.m_center.m_x;
	const double yo_b = circle_b.m_center.m_y;


	const double angle_sum_outer = std::asin((r_b - r_a) / distance_between_circles) +
		std::asin((xo_b - xo_a) / distance_between_circles);
	const double angle_subtraction_outer = std::asin((r_b - r_a) / distance_between_circles) -
		std::asin((xo_b - xo_a) / distance_between_circles);
	const double angle_sum_inner = std::asin((-r_b - r_a) / distance_between_circles) +
		std::asin((xo_b - xo_a) / distance_between_circles);
	const double angle_subtraction_inner = std::asin((-r_b - r_a) / distance_between_circles) -
		std::asin((xo_b - xo_a) / distance_between_circles);

	Tangents_t tangents;
	tangents.reserve(4u);


	// outer tangents
	const Point A_outer_1(
		xo_a + r_a * std::cos(angle_sum_outer),
		yo_a - r_a * std::sin(angle_sum_outer)
	);
	const Point B_outer_1(
		xo_b + r_b * std::cos(angle_sum_outer),
		yo_b - r_b * std::sin(angle_sum_outer)
	);
	tangents.emplace(A_outer_1, B_outer_1, circle_a, circle_b);


	const Point A_outer_2(
		xo_a - r_a * std::cos(angle_subtraction_outer),
		yo_a - r_a * std::sin(angle_subtraction_outer)
	);
	const Point B_outer_2(
		xo_b - r_b * std::cos(angle_subtraction_outer),
		yo_b - r_b * std::sin(angle_subtraction_outer)
	);
	tangents.emplace(A_outer_2, B_outer_2, circle_a, circle_b);


	if (no_inner_tangents)
		return tangents;


	// inner tangents
	const Point A_inner_1(
		xo_a + r_a * std::cos(angle_sum_inner),
		yo_a - r_a * std::sin(angle_sum_inner)
	);
	const Point B_inner_1(
		xo_b - r_b * std::cos(angle_sum_inner),
		yo_b + r_b * std::sin(angle_sum_inner)
	);
	tangents.emplace(A_inner_1, B_inner_1, circle_a, circle_b);


	const Point A_inner_2(
		xo_a - r_a * std::cos(angle_subtraction_inner),
		yo_a - r_a * std::sin(angle_subtraction_inner)
	);
	const Point B_inner_2(
		xo_b + r_b * std::cos(angle_subtraction_inner),
		yo_b + r_b * std::sin(angle_subtraction_inner)
	);
	tangents.emplace(A_inner_2, B_inner_2, circle_a, circle_b);


	return tangents;
}

// returns all possible arcs on this circle
Arcs_t get_arcs(const Points_t& points, const Circle& circle) {
	Arcs_t arcs;
	arcs.reserve(points.size() * (points.size() - 1u));

	for (const auto& point_a : points) {
		for (const auto& point_b : points) {
			if (point_a != point_b) {
				arcs.emplace(point_a, point_b, circle);
				arcs.emplace(point_b, point_a, circle);
			}
		}
	}

	return arcs;
}

// calculates distance which can not be exceeded during passing through this graph 
double get_unreachable_maximum(const Graph_t& graph) {
	double maximum = 0.0;
	for (const auto& [vertex, neighbors] : graph)
		for (const auto& [neighbor, distance] : neighbors)
			maximum += distance;

	return maximum * 10.0;
}

// dijkstra algorithm
double dijkstra_tiptoe(const Graph_t& graph, const Vertex_t& start, const Vertex_t& finish) {
	// modification for this particular task: 
	// if there is no tangent to start and/or finish point(s), 
	// it is (they are) not included in the graph 
	if (graph.find(start) == graph.cend() || graph.find(finish) == graph.cend())
		return -1.0;

	const double maximum = get_unreachable_maximum(graph);

	Distances_t distances;
	for (const auto& [vertex, _] : graph)
		distances.insert(std::pair<Vertex_t, double>(vertex, maximum));

	distances.at(start) = 0.0;

	Queue_t queue;
	queue.push_back(start);

	while (!queue.empty()) {
		const auto vertex = queue.front();
		queue.pop_front();

		for (const auto& [neighbor, edge_weight] : graph.at(vertex)) {
			if (distances.at(vertex) + edge_weight < distances.at(neighbor)) {
				distances.at(neighbor) = distances.at(vertex) + edge_weight;
				queue.push_back(neighbor);
			}
		}
	}
	return are_equal(distances.at(finish), maximum) ? -1.0 : distances.at(finish);
}

// returns all points. Key - circle which point belongs to
Points_on_circles_t get_points(const Tangents_t& tangents) {
	Points_on_circles_t points;
	for (const auto& tangent : tangents) {
		if (points.find(*tangent.m_circle_a) == points.cend())
			points.insert(std::pair<Circle, Points_t>(*tangent.m_circle_a, Points_t()));
		if (points.find(*tangent.m_circle_b) == points.cend())
			points.insert(std::pair<Circle, Points_t>(*tangent.m_circle_b, Points_t()));

		points.at(*tangent.m_circle_a).insert(tangent.m_a);
		points.at(*tangent.m_circle_b).insert(tangent.m_b);
	}

	return points;
}

// returns graph for this entire task
Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles) {

	Tangents_t tangents;
	tangents.reserve(4.0 * (circles.size() + 2u) * (circles.size() + 1u));

	// finding all tangents
	for (auto circle_1 = circles.cbegin(); circle_1 != circles.cend(); ++circle_1) {
		for (auto circle_2 = circle_1 + 1u; circle_2 != circles.cend(); ++circle_2) {

			// tangents between two circles
			auto pair_tangents = get_tangents(*circle_1, *circle_2);

			// removing tangents which can not exist
			filter_tangents(pair_tangents, circles);
			tangents.insert(pair_tangents.cbegin(), pair_tangents.cend());
		}
	}

	// same with start and finish points and all other circles, considering points as circles
	const Circle circle_a(a, 0.0);
	const Circle circle_b(b, 0.0);
	for (const auto& circle : circles) {
		auto pair_tangents_a = get_tangents(circle_a, circle);
		filter_tangents(pair_tangents_a, circles);

		auto pair_tangents_b = get_tangents(circle, circle_b);
		filter_tangents(pair_tangents_b, circles);

		tangents.insert(pair_tangents_a.cbegin(), pair_tangents_a.cend());
		tangents.insert(pair_tangents_b.cbegin(), pair_tangents_b.cend());
	}

	// same with both start and finish points
	Tangents_t tangent_a_b = get_tangents(circle_a, circle_b);
	filter_tangents(tangent_a_b, circles);
	tangents.insert(tangent_a_b.cbegin(), tangent_a_b.cend());

	// all points with binding to their own circles
	const auto points_on_circles = get_points(tangents);

	// finding all arcs
	Arcs_t arcs;
	arcs.reserve(tangents.size() * tangents.size());
	for (const auto& [circle, points_on_circle] : points_on_circles) {
		auto arcs_on_circle = get_arcs(points_on_circle, circle);
		arcs.insert(arcs_on_circle.cbegin(), arcs_on_circle.cend());
	}

	// removing arc which can not exist
	filter_arcs(arcs, circles);

	// adding points to graph
	Graph_t graph;
	graph.reserve(tangents.size() * 2u + 2u);
	for (const auto& [_, points_on_circle] : points_on_circles) {
		for (const auto& point : points_on_circle) {
			if (graph.find(point) == graph.cend())
				graph.insert(std::pair<Vertex_t, Vertices_t>(point, Vertices_t()));
		}
	}

	// connecting points with each other according to tangent/arc they belong to
	for (auto& [vertex, neighbors] : graph) {
		for (const auto& tangent : tangents) {
			if (tangent.m_a == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(tangent.m_b, tangent.m_length));
			if (tangent.m_b == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(tangent.m_a, tangent.m_length));
		}
		for (const auto& arc : arcs) {
			if (arc.m_a == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(arc.m_b, arc.m_length));
			if (arc.m_b == vertex)
				neighbors.insert(std::pair<Vertex_t, double>(arc.m_a, arc.m_length));
		}
	}

	return graph;
}

double tiptoe_through_the_circles(Point a, Point b, const std::vector<Circle>& circles) {
	const auto graph = get_graph(a, b, circles);
	return dijkstra_tiptoe(graph, a, b);
}

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&)) {
	std::cout << "test_tiptoe_through_the_circles:\n";
	std::cout << std::setprecision(16);
	bool verbose = true;

	std::vector<Circle> circles;
	double result_expected = 0.0;
	double result_actual = -1.0;


	Point a1(-3.0, 1.0);
	Point b1(4.25, 0.0);
	circles.emplace_back(0.0, 0.0, 2.5);
	circles.emplace_back(1.5, 2.0, 0.5);
	circles.emplace_back(3.5, 1.0, 1.0);
	circles.emplace_back(3.5, -1.7, 1.2);
	result_expected = 9.11821650244;

	result_actual = algorithm(a1, b1, circles);

	std::cout << "test  #1: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a2(0.0, 1.0);
	Point b2(0.0, -1.0);
	circles.emplace_back(0.0, 0.0, 0.8);
	circles.emplace_back(3.8, 0.0, 3.2);
	circles.emplace_back(-3.5, 0.0, 3.0);
	circles.emplace_back(-7.0, 0.0, 1.0);
	result_expected = 19.0575347577;

	result_actual = algorithm(a2, b2, circles);

	std::cout << "test  #2: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a3(3.0, 0.0);
	Point b3(0.0, 4.0);
	result_expected = 5.0;

	result_actual = algorithm(a3, b3, circles);

	std::cout << "test  #3: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a4(0.0, 0.0);
	Point b4(20.0, 20.0);
	circles.emplace_back(4.0, 0.0, 3.0);
	circles.emplace_back(-4.0, 0.0, 3.0);
	circles.emplace_back(0.0, 4.0, 3.0);
	circles.emplace_back(0.0, -4.0, 3.0);
	result_expected = -1.0;

	result_actual = algorithm(a4, b4, circles);

	std::cout << "test  #4: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a5(0, 1);
	Point b5(0, -1);
	circles.emplace_back(0, 0, 0.8);
	circles.emplace_back(-3.8, 0, 3.2);
	circles.emplace_back(3.5, 0, 3);
	circles.emplace_back(7, 0, 1);
	result_expected = 19.0575347577;

	result_actual = algorithm(a5, b5, circles);

	std::cout << "test  #5: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a6(-2.000298425089568, 3.749468164518476);
	Point b6(3.086806660052389, -0.3613790776580572);
	circles.emplace_back(-4.312177246902138, -1.825995144899935, 1.537304233969189);
	circles.emplace_back(4.090373425278813, -3.607347321230918, 0.9538899711100384);
	circles.emplace_back(-4.098228246439248, 4.120374575722963, 1.125000807014294);
	circles.emplace_back(-2.209169554989785, -0.7002085656858981, 0.2084384063025936);
	circles.emplace_back(-4.001088032964617, 1.893475188408047, 1.399483151757158);
	circles.emplace_back(-3.268968423362821, 0.7412259723059833, 0.432029886986129);
	circles.emplace_back(-3.054809097666293, -2.079985204618424, 0.8302456527249887);
	circles.emplace_back(4.658766083884984, 1.402585541363806, 0.0703870586818084);
	circles.emplace_back(4.372936950530857, -3.302281235810369, 0.9999477392295375);
	circles.emplace_back(-3.914669880177826, -2.945075233001262, 0.5932513790903613);
	circles.emplace_back(-1.791188039351255, 1.602634110022336, 0.9437262480380013);
	circles.emplace_back(0.9105801326222718, -0.4681416437961161, 0.605236313282512);
	circles.emplace_back(2.324651998933405, -1.960121297743171, 0.918448581942357);
	circles.emplace_back(-2.734545466955751, 1.599212891887873, 0.8008913443190977);
	circles.emplace_back(-2.588120114523917, 1.445159513968974, 1.120827562664635);
	circles.emplace_back(4.102725342381746, -3.953214439097792, 1.090417228988372);
	circles.emplace_back(3.463766851928085, 2.46860288316384, 0.8192173140356317);
	circles.emplace_back(-1.671539710368961, 1.421643409412354, 0.7879026158479974);
	circles.emplace_back(-4.972835585940629, -4.284591495525092, 1.008245448884554);
	circles.emplace_back(-3.752855423372239, -1.244009530637413, 1.249069330259226);
	circles.emplace_back(-3.493578697089106, -4.570442379917949, 0.6757102705771103);
	circles.emplace_back(4.542630279902369, -0.8300261502154171, 1.257818318600766);
	circles.emplace_back(0.01704404829069972, 0.237274628598243, 1.12488263763953);
	circles.emplace_back(0.6850501080043614, -4.899106363300234, 1.077860431349836);
	circles.emplace_back(-1.654746441636235, -1.733839919324964, 1.160000577406026);
	circles.emplace_back(-4.70944901695475, 1.875125195365399, 1.194895912217907);
	circles.emplace_back(4.221933789085597, 2.373881780076772, 1.255830672127195);
	circles.emplace_back(-1.683828334789723, -4.852343781385571, 0.7636736480286345);
	circles.emplace_back(-1.88443765277043, 1.607029458973557, 1.031193678476848);
	circles.emplace_back(-4.203592611011118, -2.86351538496092, 1.530315921525471);
	circles.emplace_back(3.838556620758027, -1.883792753797024, 0.6688127788947895);
	circles.emplace_back(2.870973229873925, 4.325217080768198, 0.7110365967964754);
	circles.emplace_back(-1.804937219712883, -2.672343102749437, 0.9072413007030263);
	circles.emplace_back(0.8649966702796519, -4.852948051411659, 1.361310354503803);
	circles.emplace_back(1.425558745395392, 1.964673504699022, 1.312462676432915);
	circles.emplace_back(-0.08666141657158732, 1.84692365815863, 1.352167781605385);
	circles.emplace_back(3.074735959526151, -3.726205842103809, 0.7545288563007488);
	circles.emplace_back(-3.126031432766467, 4.291208770591766, 0.8058143212692812);
	circles.emplace_back(-0.7387743960134685, -4.246743435505778, 0.6615151680773124);
	result_expected = 11.9228;

	result_actual = algorithm(a6, b6, circles);

	std::cout << "test  #6: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a7(1, 1);
	Point b7(9, 9);
	circles.emplace_back(0, 0, 0.1628746463684365);
	circles.emplace_back(0, 1, 0.3523985967272892);
	circles.emplace_back(0, 2, 0.5364255122607574);
	circles.emplace_back(0, 3, 0.4300622401060537);
	circles.emplace_back(0, 4, 0.3106004946632311);
	circles.emplace_back(0, 5, 0.5266889514634385);
	circles.emplace_back(0, 6, 0.5684803681215271);
	circles.emplace_back(0, 7, 0.5833063065307215);
	circles.emplace_back(0, 8, 0.1994006278691813);
	circles.emplace_back(0, 9, 0.1901628721738234);
	circles.emplace_back(0, 10, 0.4963121007895097);
	circles.emplace_back(1, 0, 0.7945029408903792);
	circles.emplace_back(1, 2, 0.2510755163384601);
	circles.emplace_back(1, 3, 0.7169563776114956);
	circles.emplace_back(1, 4, 0.5250582014909014);
	circles.emplace_back(1, 5, 0.1930718991206959);
	circles.emplace_back(1, 6, 0.4261120012728497);
	circles.emplace_back(1, 7, 0.2375767939025536);
	circles.emplace_back(1, 8, 0.5907849639421329);
	circles.emplace_back(1, 9, 0.3803132777335122);
	circles.emplace_back(1, 10, 0.4899552673799917);
	circles.emplace_back(2, 0, 0.5319813678273931);
	circles.emplace_back(2, 1, 0.3844743007561192);
	circles.emplace_back(2, 2, 0.292310345848091);
	circles.emplace_back(2, 3, 0.392366753029637);
	circles.emplace_back(2, 4, 0.5005855676019564);
	circles.emplace_back(2, 5, 0.6281589973485097);
	circles.emplace_back(2, 6, 0.4360745647223666);
	circles.emplace_back(2, 7, 0.675492997909896);
	circles.emplace_back(2, 8, 0.3913260711589828);
	circles.emplace_back(2, 9, 0.4938314033439383);
	circles.emplace_back(2, 10, 0.2520577947841957);
	circles.emplace_back(3, 0, 0.5762704281834885);
	circles.emplace_back(3, 1, 0.3109034419292584);
	circles.emplace_back(3, 2, 0.605750561482273);
	circles.emplace_back(3, 3, 0.4061566901626065);
	circles.emplace_back(3, 4, 0.6387910791439936);
	circles.emplace_back(3, 5, 0.3983294921228662);
	circles.emplace_back(3, 6, 0.5167727740248665);
	circles.emplace_back(3, 7, 0.3643342807190493);
	circles.emplace_back(3, 8, 0.3022542553720995);
	circles.emplace_back(3, 9, 0.5889043335104361);
	circles.emplace_back(3, 10, 0.6993306066608056);
	circles.emplace_back(4, 0, 0.652983741578646);
	circles.emplace_back(4, 1, 0.5801291283918545);
	circles.emplace_back(4, 2, 0.1467481157043949);
	circles.emplace_back(4, 3, 0.6416853299131616);
	circles.emplace_back(4, 4, 0.1581593501614407);
	circles.emplace_back(4, 5, 0.4961532718269154);
	circles.emplace_back(4, 6, 0.2940124519402161);
	circles.emplace_back(4, 7, 0.6900777980452403);
	circles.emplace_back(4, 8, 0.566799630713649);
	circles.emplace_back(4, 9, 0.3927921340567991);
	circles.emplace_back(4, 10, 0.5148965323576703);
	circles.emplace_back(5, 0, 0.1274027654668316);
	circles.emplace_back(5, 1, 0.503067686338909);
	circles.emplace_back(5, 2, 0.4777844483731314);
	circles.emplace_back(5, 3, 0.262592924782075);
	circles.emplace_back(5, 4, 0.3290316406404599);
	circles.emplace_back(5, 5, 0.4629337185295299);
	circles.emplace_back(5, 6, 0.5243985806358978);
	circles.emplace_back(5, 7, 0.5472880630055442);
	circles.emplace_back(5, 8, 0.3864086774876341);
	circles.emplace_back(5, 9, 0.2001247341977432);
	circles.emplace_back(5, 10, 0.4910248144296929);
	circles.emplace_back(6, 0, 0.3333424225682393);
	circles.emplace_back(6, 1, 0.3390456042950973);
	circles.emplace_back(6, 2, 0.3665664402069524);
	circles.emplace_back(6, 3, 0.4757285737199708);
	circles.emplace_back(6, 4, 0.823775384039618);
	circles.emplace_back(6, 5, 0.605539690121077);
	circles.emplace_back(6, 6, 0.8604423254029825);
	circles.emplace_back(6, 7, 0.3713895830092951);
	circles.emplace_back(6, 8, 0.5601797837996855);
	circles.emplace_back(6, 9, 0.7542402487015352);
	circles.emplace_back(6, 10, 0.4849949301453307);
	circles.emplace_back(7, 0, 0.3370519649935886);
	circles.emplace_back(7, 1, 0.4161911523202434);
	circles.emplace_back(7, 2, 0.6041885798564181);
	circles.emplace_back(7, 3, 0.2711943033384159);
	circles.emplace_back(7, 4, 0.6511102757183834);
	circles.emplace_back(7, 5, 0.5126366399461403);
	circles.emplace_back(7, 6, 0.7969563483959063);
	circles.emplace_back(7, 7, 0.6673986469628289);
	circles.emplace_back(7, 8, 0.5619564772350714);
	circles.emplace_back(7, 9, 0.3324886301765218);
	circles.emplace_back(7, 10, 0.7300074005266651);
	circles.emplace_back(8, 0, 0.6491321481065825);
	circles.emplace_back(8, 1, 0.4017128477571532);
	circles.emplace_back(8, 2, 0.2637480404460802);
	circles.emplace_back(8, 3, 0.5922080177580937);
	circles.emplace_back(8, 4, 0.3521049984963611);
	circles.emplace_back(8, 5, 0.2786758293164894);
	circles.emplace_back(8, 6, 0.5483823104063049);
	circles.emplace_back(8, 7, 0.592110608308576);
	circles.emplace_back(8, 8, 0.2816006015287712);
	circles.emplace_back(8, 9, 0.5140958129195496);
	circles.emplace_back(8, 10, 0.6654430777067318);
	circles.emplace_back(9, 0, 0.2196358360117301);
	circles.emplace_back(9, 1, 0.5013549668015912);
	circles.emplace_back(9, 2, 0.4389178612036631);
	circles.emplace_back(9, 3, 0.5264885412761942);
	circles.emplace_back(9, 4, 0.5317781867226585);
	circles.emplace_back(9, 5, 0.3550532921450212);
	circles.emplace_back(9, 6, 0.4161083685932681);
	circles.emplace_back(9, 7, 0.2114355121040717);
	circles.emplace_back(9, 8, 0.6029599722241983);
	circles.emplace_back(9, 10, 0.6235687331529334);
	circles.emplace_back(10, 0, 0.4041926589561626);
	circles.emplace_back(10, 1, 0.5229661515215411);
	circles.emplace_back(10, 2, 0.4306587716331705);
	circles.emplace_back(10, 3, 0.5710683602141217);
	circles.emplace_back(10, 4, 0.5276285207597539);
	circles.emplace_back(10, 5, 0.4876143969828263);
	circles.emplace_back(10, 6, 0.236933310306631);
	circles.emplace_back(10, 7, 0.4831113030435517);
	circles.emplace_back(10, 8, 0.5696406797273085);
	circles.emplace_back(10, 9, 0.6816570753464475);
	circles.emplace_back(10, 10, 0.3564727762481197);
	result_expected = 13.5171;

	result_actual = algorithm(a7, b7, circles);

	std::cout << "test  #7: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a8(0.0, 0.0);
	Point b8(2.0, 2.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0 + g_pi / 2.0;

	result_actual = algorithm(a8, b8, circles);

	std::cout << "test  #8: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a9(0.0, 0.0);
	Point b9(2.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0;

	result_actual = algorithm(a9, b9, circles);

	std::cout << "test  #9: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a10(0.0, 0.0);
	Point b10(3.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 3.0;

	result_actual = algorithm(a10, b10, circles);

	std::cout << "test  #10: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a11(0.0, 0.0);
	Point b11(4.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 4.0;

	result_actual = algorithm(a11, b11, circles);

	std::cout << "test  #11: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a12(0.0, 0.0);
	Point b12(4.0, 0.0);
	circles.emplace_back(2.0, 2.0, 2.0);
	result_expected = 4.0;

	result_actual = algorithm(a12, b12, circles);

	std::cout << "test  #12: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a13(0.0, 0.0);
	Point b13(4.0, 0.0);
	circles.emplace_back(2.0, 4.0, 4.0);
	result_expected = 4.0;

	result_actual = algorithm(a13, b13, circles);

	std::cout << "test  #13: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a14(0.0, 0.0);
	Point b14(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 8.0;

	result_actual = algorithm(a14, b14, circles);

	std::cout << "test  #14: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a15(-2.0, 0.0);
	Point b15(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 10.0;

	result_actual = algorithm(a15, b15, circles);

	std::cout << "test  #15: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a16(0.0, 0.0);
	Point b16(2.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	circles.emplace_back(1.0, -0.5, 1.0);
	circles.emplace_back(1.0, -1.0, 1.0);
	circles.emplace_back(1.0, -1.5, 1.0);
	result_expected = 2.0 + g_pi;

	result_actual = algorithm(a16, b16, circles);

	std::cout << "test  #16: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();
}

int main()
{
/*
    test_get_tangents(get_tangents);
    test_get_arcs(get_arcs);
    test_get_angle_with_x_axis(get_angle_with_x_axis);
    test_get_arc_length(get_arc_length);
    test_get_distance_from_line(get_distance);
    test_is_point_between_points(is_point_between_points);
    test_there_is_collision_between_tangent_and_circle(there_is_collision_between_tangent_and_circle);
    test_there_is_collision_between_arc_and_circle(there_is_collision_between_arc_and_circle);
    test_filter_tangents(filter_tangents);
    test_filter_arcs(filter_arcs);
    test_double_hash();
    test_get_graph(get_graph);
*/


    test_tiptoe_through_the_circles(tiptoe_through_the_circles);

 	return 0;
}
