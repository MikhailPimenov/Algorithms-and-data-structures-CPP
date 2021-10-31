#include <iomanip>
#include <iostream>
#include <thread>

#include "timer/timer.h"

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
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

/*
The shortest path consists of tangents and arcs. 
The idea is to build a graph, and then to find the shortest path
using Dijkstra algorithm.
Nodes in the graph - points. 
All the points are on circumeferences of circles. 
Weight of edge (edge cost) is either the length 
of straight line between two points in case these points are 
the ends of tangent, or the length of the arc in case 
these points are on the circumeference of the same circle.

The first step is to find all the tangents between every two circles.
Two or four tangents between every two circles.
The second step is to remove all tangents that can not exist because some
of the circles can cover the path of the tangent (collision between tangent and circle).
The third step is to find all the arcs between points on every circle.
The fourth step is to remove all arcs that also can not exist because some
of the circles can cover the curve of the arc (collision between arc and circle).
The fifth step is to connect all the points according to what tangents and
arcs the belong to.
The sixth step is to find the shortest path in this graph using Dijkstra algorithm.

Start point and finish point are considered as the circles with zero radius 
Straight line between start and finish point is also considered as tangent.

Time complexity: O(n^4) 
Given a number of circles n:
Number of pairs circle-circle:                   n * (n - 1) / 2,                 O(n^2)
Number of tangents:                              4 * n * (n - 1) / 2,             O(n^2)
Number of points on each circle:                 4 * (n - 1) = m                  O(n)
Number of arcs on each circle:                   m * (m - 1)                      O(m^2) = O(n^2)
Number of arcs:                                  n * m * (m - 1)                  O(n^3)
Number of points:                                n * m = k                        O(n^2)
Number of circles to filter tangents:            n - 2                            O(n)
Number of circles to filter arcs :               n - 1                            O(n)
Filtering tangents:                              4 * n * (n - 1) / 2 * (n - 2)    O(n^3)
Filtering arcs:                                  n * m * (m - 1) * (n - 1)        O(n^4)
Complexity of Dijkstra algorithm for k nodes:                                     O(k^2) => O(n^4) 

Solution may have not optimal space complexity, because some data is duplicated
in several data structures instead of just having its pointers/references.

Graph also has duplicated nodes because of approximation of double. 
For example both Point(1.0, 0.0) and Point(0.99999999999999967, 0.0)
are in graph. But both of them have the same merged list neighbours which 
includes all the neighbors from both lists of neighbors before merging.
*/


const double g_pi = atan(1.0) * 4.0;

constexpr double g_epsilon = 1e-8;

// Types ===============================================================================

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
	double x, y;

	Point() : x(0.0), y(0.0) {}
	Point(double x, double y) : x(x), y(y) {}
};

// computes hash for Point. This is needed for data structures
struct Point_hash {
	std::size_t operator()(const Point& obj) const noexcept {
		const std::size_t x = Double_hash::call(obj.x);
		const std::size_t y = Double_hash::call(obj.y);
		return (x + y) * (x + y + 1) / 2 + y;							// Cantor's pair
	}
	static std::size_t call(const Point& obj) noexcept {
		static const Point_hash instance;								// singleton
		return instance(obj);
	}
};

// returns true if point_1 == point_2
bool operator==(const Point& point_1, const Point& point_2) noexcept {
	return are_equal(point_1.x, point_2.x) && 
		   are_equal(point_1.y, point_2.y);
}

// returns true if point_1 != point_2
bool operator!=(const Point& point_1, const Point& point_2) noexcept {
	return !(point_1 == point_2);
}

// returns distance between two points
double get_distance(const Point& p1, const Point& p2) {
	return std::sqrt(std::pow(p1.x - p2.x, 2.0) +
		std::pow(p1.y - p2.y, 2.0));
}

struct Circle {
	Point ctr;
	double r;

	Circle() : ctr(), r(1.0) {}
	Circle(const Point &center, double radius) : ctr(center), r(radius) {}
	Circle(double x_center, double y_center, double radius) : ctr(x_center, y_center), r(radius) {}
};

// computes hash for Circle. This is needed for data structures
struct Circle_hash {
	std::size_t operator()(const Circle& obj) const noexcept {
		return Point_hash::call(obj.ctr) +
			   Double_hash::call(obj.r);
	}
	static std::size_t call(const Circle& obj) noexcept {
		static const Circle_hash instance;
		return instance(obj);
	}
};

// computes hash for pair of circles. This is needed for data structures
struct Pair_circle_hash {
	std::size_t operator()(const std::pair<Circle, Circle>& pair) const noexcept {
		return Circle_hash::call(pair.first) + Circle_hash::call(pair.second);		// symmetrical
	}
};

// returns true if circle_1 == circle_2
bool operator==(const Circle& circle_1, const Circle& circle_2) {
	return are_equal(circle_1.r, circle_2.r) && 
		   circle_1.ctr == circle_2.ctr;
}

// returns true if pair_1 == pair_2 regardless of order of first and second circle
bool operator==(const std::pair<Circle, Circle>& pair_1, const std::pair<Circle, Circle>& pair_2) {
	return (pair_1.first == pair_2.first && pair_1.second == pair_2.second) ||
		   (pair_1.first == pair_2.second && pair_1.second == pair_2.first);
}

// returns true if circle_1 != circle_2
bool operator!=(const Circle& circle_1, const Circle& circle_2) {
	return !(circle_1 == circle_2);
}

// tangent between two circles. 
// Consists of two points. Also has length and owners (two circles)
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
	if (are_equal(left_side.x, center.x)) {
		if (left_side.y < center.y)
			return 3.0 * g_pi / 2.0;
		return g_pi / 2.0;
	}

	const double angle = atan((left_side.y - center.y) / (left_side.x - center.x));

	if (left_side.x < center.x)
		return angle + g_pi;

	if (left_side.y < center.y)
		return angle + 2.0 * g_pi;

	return angle;
}

// returns the length of arc
double get_arc_length(const Point& a, const Point& b, const Circle& circle) {

	const double angle_a = get_angle_with_x_axis(a, circle.ctr);
	const double angle_b = get_angle_with_x_axis(b, circle.ctr);

	// angles from 0 to 2*pi are considered
	const double delta_angle =
		angle_a > angle_b ? angle_a - angle_b :
		2.0 * g_pi + angle_a - angle_b;

	return circle.r * delta_angle;
}

// arc on the circle. 
// Consists of two points. Also has length and includes its owner (circle)
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

// returns true if arc_1 == arc_2
bool operator==(const Arc& arc_1, const Arc& arc_2) noexcept {
	return arc_1.m_a == arc_2.m_a &&
   		   arc_1.m_b == arc_2.m_b &&
		   arc_1.m_owner->ctr == arc_2.m_owner->ctr;
}

// returns true if arc_1 != arc_2
bool operator!=(const Arc& arc_1, const Arc& arc_2) noexcept {
	return !(arc_1 == arc_2);
}

// Data structures =====================================================================

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
// to store circles
using Circles_t = std::unordered_set<Circle, Circle_hash>;
// to store potentially colliding circles relatively to tangents between certain pair of circles
using Colliding_circles_with_tangent_t = std::unordered_map<std::pair<Circle, Circle>, Circles_t, Pair_circle_hash>;
// to store potentially colliding circles relatively to all arcs of certain circle
using Colliding_circles_with_arc_t = std::unordered_map<Circle, Circles_t, Circle_hash>;
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


// Logic to build a graph =======================================================

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
		(tangent.m_b.x - tangent.m_a.x) * (tangent.m_a.y - circle.ctr.y) -
		(tangent.m_a.x - circle.ctr.x) * (tangent.m_b.y - tangent.m_a.y)
	);
	const double distance = get_distance(tangent.m_a, tangent.m_b);

	return numerator / distance;
}

// returns true if the projection of point on the line(point_1, point_2) lays between point_1 and point_2
bool is_point_between_points(const Point& point, const Point& point_1, const Point& point_2) {
	if (are_equal(point_1.x, point_2.x))
		return is_between(point.y, point_1.y, point_2.y);

	const double distance = get_distance(point_1, point_2);

	const double k = ((point_2.y - point_1.y) * (point.x - point_1.x) -
		(point_2.x - point_1.x) * (point.y - point_1.y)) /
		(distance * distance);

	const double x_n = point.x - k * (point_2.y - point_1.y);

	return is_between(x_n, point_1.x, point_2.x);
}

// returns true if tangent can not exist because circle covers it (or its part)
bool there_is_collision_between_tangent_and_circle(const Tangent& tangent, const Circle& circle) {
	//return true;
	// circle is far enough from line which tangent is on
	if (get_distance(circle, tangent) > circle.r)
		return false;

	// circle intersects with tangent between tangent's ends
	if (is_point_between_points(circle.ctr, tangent.m_a, tangent.m_b))
		return true;

	// circle covers one of tangent's ends
	if (get_distance(circle.ctr, tangent.m_a) > circle.r &&
		get_distance(circle.ctr, tangent.m_b) > circle.r)
		return false;

	return true;
}

void there_is_collision_between_tangent_and_circles(const Tangent& tangent, const std::vector<Circle>& circles, std::atomic_bool& no_collision) {
	for (const auto& circle : circles) {
		if (no_collision) {
			if (circle != *tangent.m_circle_a && circle != *tangent.m_circle_b) {
				if (there_is_collision_between_tangent_and_circle(tangent, circle)) {
					no_collision = false;
					return;
				}
			}
			continue;
		}
		return;
	}
}

bool is_tangent_existing(const Tangent& tangent, const std::vector<Circle>& circles) {
	const std::size_t size = circles.size();

	std::vector<Circle> part_1;
	part_1.reserve(size / 4u + 1u);
	std::vector<Circle> part_2;
	part_2.reserve(size / 4u + 1u);
	std::vector<Circle> part_3;
	part_3.reserve(size / 4u + 1u);
	std::vector<Circle> part_4;
	part_4.reserve(size / 4u + 1u);

	for (std::size_t index = 0u; index < size / 4u; ++index)
		part_1.push_back(circles[index]);
	for (std::size_t index = size / 4u; index < size / 2u; ++index)
		part_2.push_back(circles[index]);
	for (std::size_t index = size / 2u; index < 3u * size / 4u; ++index)
		part_3.push_back(circles[index]);
	for (std::size_t index = 3u * size / 4u; index < size; ++index)
		part_4.push_back(circles[index]);

	std::atomic_bool no_collision{ true };

	std::thread thread_1(there_is_collision_between_tangent_and_circles, std::ref(tangent), std::ref(part_1), std::ref(no_collision));
	std::thread thread_2(there_is_collision_between_tangent_and_circles, std::ref(tangent), std::ref(part_2), std::ref(no_collision));
	std::thread thread_3(there_is_collision_between_tangent_and_circles, std::ref(tangent), std::ref(part_3), std::ref(no_collision));
	std::thread thread_4(there_is_collision_between_tangent_and_circles, std::ref(tangent), std::ref(part_4), std::ref(no_collision));

	thread_1.join();
	thread_2.join();
	thread_3.join();
	thread_4.join();
	
	return no_collision;
}

// returns all circles which can potentially collide with tangents between certain pair of circles
Colliding_circles_with_tangent_t get_colliding_circles_with_tangents(const std::vector<Circle>& circles) {
	Colliding_circles_with_tangent_t colliding_circles;
	colliding_circles.reserve((circles.size() * (circles.size() - 1u)));

	for (auto circle_1 = circles.cbegin();
		circle_1 != circles.cend();
		++circle_1)
	{
		for (auto circle_2 = circle_1 + 1u;
			circle_2 != circles.cend();
			++circle_2)
		{
			const std::pair<Circle, Circle> pair(*circle_1, *circle_2);
			colliding_circles.emplace(
				std::pair<std::pair<Circle, Circle>, Circles_t>(pair, Circles_t()));
			colliding_circles.at(pair).reserve(circles.size());

			const double radius = ((circle_1->r > circle_2->r) ? circle_1->r : circle_2->r);
			const Tangent line(circle_1->ctr, circle_2->ctr, *circle_1, *circle_2);

			for (auto circle = circles.cbegin();
				circle != circles.cend();
				++circle)
			{
				if ((*circle != *circle_1) && (*circle != *circle_2)) {
					//const double distance =	get_distance(*circle, line);

					//Timer timer;
					//const bool is_close_to_line = (distance < radius + circle->r || are_equal(distance, radius + circle->r));
					//const bool is_between_circles = is_point_between_points(circle->ctr, circle_1->ctr, circle_2->ctr);
					//const bool is_close_to_circles = (get_distance(circle->ctr, circle_1->ctr) < circle->r + circle_1->r) ||
													 //(get_distance(circle->ctr, circle_2->ctr) < circle->r + circle_2->r);

					colliding_circles.at(pair).emplace(*circle);

					//if (is_close_to_line && (is_between_circles || is_close_to_circles))
						//colliding_circles.at(pair).emplace(*circle);
					//if (is_close_to_line)
						//colliding_circles.at(pair).emplace(*circle);
				
					//std::cout << "inside cycle = " << timer.elapsed() << '\n';
				}
			}
		}
	}

	return colliding_circles;
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


bool there_is_collision(const Tangent& tangent, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		if (circle != *tangent.m_circle_a && circle != *tangent.m_circle_b) {
			if (there_is_collision_between_tangent_and_circle(tangent, circle))
				return true;
		}
	}
	return false;
}

bool there_is_collision(
	const Tangent& tangent, 
	const std::vector<Circle>& circles, 
	const std::vector<Circle>::const_iterator &cbegin, 
	const std::vector<Circle>::const_iterator &cend
) {
	for (auto circle = cbegin; circle != cend; ++circle) {
	//for (const auto& circle : circles) {
		if (*circle != *tangent.m_circle_a && *circle != *tangent.m_circle_b) {
			if (there_is_collision_between_tangent_and_circle(tangent, *circle))
				return true;
		}
	}
	return false;
}
bool there_is_collision(const Tangent& tangent, const Circles_t& circles) {
	for (const auto& circle : circles) {
		if (circle != *tangent.m_circle_a && circle != *tangent.m_circle_b) {
			if (there_is_collision_between_tangent_and_circle(tangent, circle))
				return true;
		}
	}
	return false;
}

// removes all the tangents which can not exist
void filter_tangents_fast(Tangents_t& tangents, const std::vector<Circle>& circles) {
	Timer timer;
	const auto colliding_circles = get_colliding_circles_with_tangents(circles);
	std::cout << "get_colliding_circles_with_tangents() \t" << timer.elapsed() << '\n';
	//Tangents_t temp;
	//temp.reserve(tangents.size());
	for (auto tangent = tangents.cbegin(); tangent != tangents.cend(); ) {
		bool there_is_collision{ false };
		const auto& pair = std::pair<const Circle, const Circle>(*(tangent->m_circle_a), *(tangent->m_circle_b));
		
		for (const auto& circle : colliding_circles.at(pair)) {
			if (there_is_collision_between_tangent_and_circle(*tangent, circle)) {
				there_is_collision = true;
				break;
			}
		}

		if (there_is_collision) {
			tangent = tangents.erase(tangent);
			continue;
			//temp.emplace(*tangent);
		}

		++tangent;
	}
	//tangents = std::move(temp);
}

struct Pair_double_hash {
	std::size_t operator()(const std::pair<double, double>& obj) const noexcept {
		const std::size_t x = Double_hash::call(obj.first);
		const std::size_t y = Double_hash::call(obj.second);
		return (x + y) * (x + y + 1) / 2 + y;							// Cantor's pair
	}
	static std::size_t call(const std::pair<double, double>& obj) noexcept {
		static const Pair_double_hash instance;								// singleton
		return instance(obj);
	}
};


std::pair<double, double> get_interval(double value_to_find, const std::vector<double>& sorted_values) {
	const auto right = std::upper_bound(
		sorted_values.cbegin(),
		sorted_values.cend(),
		value_to_find,
		[](double value_to_find, double value) {
			return value > value_to_find || are_equal(value, value_to_find);
		}
	);
	const auto left =
		(right == sorted_values.cbegin()) ?
		sorted_values.cbegin() :
		right - 1u;

	return std::make_pair(*left, *right);
}

std::pair<std::vector<Circle>::const_iterator, std::vector<Circle>::const_iterator> 
get_interval(double value_to_find, const std::vector<Circle>& sorted_circles) {
	const auto right = std::upper_bound(
		sorted_circles.cbegin(),
		sorted_circles.cend(),
		value_to_find,
		[](double value_to_find, const Circle& circle) {
			return circle.ctr.x - circle.r > value_to_find || 
				are_equal(circle.ctr.x - circle.r, value_to_find);
		}
	);
	const auto left =
		(right == sorted_circles.cbegin()) ?
		sorted_circles.cbegin() :
		right - 1u;

	return std::make_pair(left, right);
}

//void filter_tangents_advanced_thread(Tangents_t& tangents, )

void filter_tangents_advanced(Tangents_t& tangents, const std::vector<Circle>& circles) {
	// 4 * (n + n * log(n))
	const std::vector<Circle> left_all = [&]()->std::vector<Circle> {
		std::vector<Circle> local_copy(circles);
		std::sort(
			local_copy.begin(),
			local_copy.end(),
			[](const Circle& circle_1, const Circle& circle_2)->bool {
				return (circle_1.ctr.x - circle_1.r) < (circle_2.ctr.x - circle_2.r);
			}
		);
		return local_copy;
	}();

	// 2 * n + (2 * n * log(2 * n)) = 2n + 2n*(log(n)+1) ~ 2 * n * log(n)
	const std::vector<double> x_all = [&]()->std::vector<double> {
		std::vector<double> local_copy;
		local_copy.reserve(circles.size() * 2u);
		for (const auto& circle : circles) {
			local_copy.push_back(circle.ctr.x - circle.r);
			local_copy.push_back(circle.ctr.x + circle.r);
		}
		std::sort(
			local_copy.begin(),
			local_copy.end(),
			[](double x_1, double x_2)->bool {
				return x_1 < x_2;
			}
			);
		return local_copy;
	}();
		
	// 2n - 1 + (2n - 1) * n ~ 2 * (n ^ 2)
	std::unordered_map<std::pair<double, double>, Circles_t, Pair_double_hash> x_ranges;
	x_ranges.reserve(circles.size() * 2u - 1u);
	for (auto x = x_all.cbegin(); x < x_all.cend() - 1u; ++x) {
		const double left = *x;
		const double right = *(x + 1);
		const std::pair<double, double> range(left, right);
		x_ranges.insert(std::pair<std::pair<double, double>, Circles_t>(range, Circles_t()));

		for (const auto& circle : circles) {
			const double left_part = circle.ctr.x - circle.r;
			const double right_part = circle.ctr.x + circle.r;
			if ((left_part < right || are_equal(left_part, right)) &&
				(right_part > left || are_equal(right_part, left)))
				x_ranges.at(range).insert(circle);
				
		}
	}
	x_ranges.insert(std::pair<std::pair<double, double>, Circles_t>(std::make_pair(*x_all.cbegin(), *x_all.cbegin()), Circles_t()));


	for (auto tangent = tangents.cbegin(); tangent != tangents.cend();) {

		const double left_end_of_tangent =
			(tangent->m_a.x < tangent->m_b.x) ? 
			tangent->m_a.x : 
			tangent->m_b.x;
		
		
		const double right_end_of_tangent =
			(tangent->m_a.x > tangent->m_b.x) ?
			tangent->m_a.x :
			tangent->m_b.x; // if m_a.x and m_b.x are equal, what will be?

		const auto start = get_interval(left_end_of_tangent, left_all).first;
		const auto finish = get_interval(right_end_of_tangent, left_all).second;


		if (there_is_collision(*tangent, circles, start, finish)) {
			tangent = tangents.erase(tangent);
			continue;
		}

		const auto start1_finish1 = get_interval(left_end_of_tangent, x_all);

		const Circles_t& circles_covering_left_end = x_ranges.at(start1_finish1);

		if (there_is_collision(*tangent, circles_covering_left_end)) {
			tangent = tangents.erase(tangent);
			continue;
		}
		++tangent;
	}
}

// returns true if arc can not exist because circle covers it (or its part)
bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle) {

	const double distance = get_distance(arc.m_owner->ctr, circle.ctr);


	if (distance > arc.m_owner->r + circle.r ||               // arc and circle not intersect 
		arc.m_owner->r > distance + circle.r ||               // circle is deep inside arc and does not touch arc 
		are_equal(arc.m_owner->r, distance + circle.r))       // circle is inside arc, but touches it
		return false;


	// circle covers circumference of arc's owner -> there might be collision

	const double angle_b = get_angle_with_x_axis(arc.m_b, arc.m_owner->ctr);
	const double angle = get_angle_with_x_axis(circle.ctr, arc.m_owner->ctr);
	const double angle_a = get_angle_with_x_axis(arc.m_a, arc.m_owner->ctr);

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
	if (get_distance(arc.m_a, circle.ctr) > circle.r &&
		get_distance(arc.m_b, circle.ctr) > circle.r)
		return false;

	return true;
}

// returns all circles which can potentially collide with arcs on certain circle
Colliding_circles_with_arc_t get_colliding_circles_with_arc(const std::vector<Circle>& circles) {
	Colliding_circles_with_arc_t colliding_circles;
	colliding_circles.reserve(circles.size());

	for (const auto& circle : circles)
		colliding_circles.insert(std::pair<Circle, Circles_t>(circle, Circles_t())); // move to next cycle

	for (const auto& circle : circles) {
		for (const auto& covering_circle : circles) {
			const auto distance = get_distance(circle.ctr, covering_circle.ctr);
			if ((distance < circle.r + covering_circle.r ||
				are_equal(distance, circle.r + covering_circle.r)) &&
				circle.r < distance + covering_circle.r)
				colliding_circles.at(circle).insert(covering_circle);
		}
	}

	return colliding_circles;
}

// removes all the arcs which can not exist
void filter_arcs_fast(Arcs_t& arcs, const std::vector<Circle>& circles) {
	const auto colliding_circles = get_colliding_circles_with_arc(circles);
	for (auto arc = arcs.cbegin(); arc != arcs.cend(); ) {
		bool there_is_collision { false };
		for (const auto& circle : colliding_circles.at(*(arc->m_owner))) {
			if (there_is_collision_between_arc_and_circle(*arc, circle)) {
				there_is_collision = true;
				break;
			}
		}

		if (there_is_collision) {
			arc = arcs.erase(arc);
			continue;
		}
		
		++arc;
	}
}

// returns all possible tangents between these two circles
Tangents_t get_tangents(const Circle& circle_1, const Circle& circle_2, const std::vector<Circle>& circles) {

	// circles have common center - no tangents
	if (circle_1.ctr == circle_2.ctr)
		return {};

	// one circle is inside another one or have only one common point - no tangents
	const double distance_between_circles = get_distance(circle_1.ctr, circle_2.ctr);
	if (are_equal(distance_between_circles + circle_1.r, circle_2.r) ||
		are_equal(distance_between_circles + circle_2.r, circle_1.r) ||
		distance_between_circles + circle_1.r < circle_2.r ||
		distance_between_circles + circle_2.r < circle_1.r)
		return {};

	// circles intersects - no inner tangents
	bool no_inner_tangents = false;
	if (distance_between_circles < circle_1.r + circle_2.r ||
		are_equal(circle_1.r + circle_2.r, distance_between_circles))
		no_inner_tangents = true;

	const auto& circle_b =
		circle_2.ctr.y >= circle_1.ctr.y ? circle_2 : circle_1;  // upper circle
	const auto& circle_a =
		circle_2.ctr.y < circle_1.ctr.y ? circle_2 : circle_1;   // lower circle

	const double r_a = circle_a.r;
	const double r_b = circle_b.r;
	const double xo_a = circle_a.ctr.x;
	const double yo_a = circle_a.ctr.y;
	const double xo_b = circle_b.ctr.x;
	const double yo_b = circle_b.ctr.y;


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
			//if (Point_hash::call(point_a) != Point_hash::call(point_b)) {
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

	Queue_t queue; // may be use priority queue
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
Points_on_circles_t get_points_on_circles(const Tangents_t& tangents) {
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

// finds all tangents
void add_tangents(Tangents_t &tangents, const std::vector<Circle>& circles) {
	for (auto circle_1 = circles.cbegin(); circle_1 != circles.cend(); ++circle_1) {
		for (auto circle_2 = circle_1 + 1u; circle_2 != circles.cend(); ++circle_2) {

			// tangents between two circles
			auto pair_tangents = get_tangents(*circle_1, *circle_2, circles);

			tangents.insert(pair_tangents.cbegin(), pair_tangents.cend());
		}
	}
}

// finds all arcs
void add_arcs(Arcs_t& arcs, const Points_on_circles_t& points_on_circles) {
	for (const auto& [circle, points_on_circle] : points_on_circles) {
		auto arcs_on_circle = get_arcs(points_on_circle, circle);
		arcs.insert(arcs_on_circle.cbegin(), arcs_on_circle.cend());
	}
}

// adds all nodes 
void add_nodes_to_graph(Graph_t& graph, const Points_on_circles_t& points_on_circles) {
	for (const auto& [_, points_on_circle] : points_on_circles) {
		for (const auto& point : points_on_circle) {
			if (graph.find(point) == graph.cend())
				graph.insert(std::pair<Vertex_t, Vertices_t>(point, Vertices_t()));
		}
	}
}

// unites lists of neighbors for each 'approximately' similar 
// nodes such as Point(0.99999999999999967, 0.0) and Point(1.0, 0.0)
void merge_neighbors_for_similar_nodes(Graph_t& graph) {
	std::vector<std::pair<Vertex_t, Vertices_t>> graph_to_sort(graph.cbegin(), graph.cend());
	
	// sorting all nodes in graph - to make nodes 
	// like Point(2.0, 0.0) and Point(1.999999999999996, 0.0) be next to each other
	std::sort(
		graph_to_sort.begin(),
		graph_to_sort.end(),
		[](
			const std::pair<Vertex_t, Vertices_t>& vertex_and_neighbors_1, 
			const std::pair<Vertex_t, Vertices_t>& vertex_and_neighbors_2
			)-> bool {

			// Cantor's pair - this is how points with two values (x and y) can be sorted
			const double pair_1 =
				(vertex_and_neighbors_1.first.x + vertex_and_neighbors_1.first.y) *
				(vertex_and_neighbors_1.first.x + vertex_and_neighbors_1.first.y + 1.0) / 2.0 + 
				 vertex_and_neighbors_1.first.y;
			const double pair_2 =
				(vertex_and_neighbors_2.first.x + vertex_and_neighbors_2.first.y) *
				(vertex_and_neighbors_2.first.x + vertex_and_neighbors_2.first.y + 1.0) / 2.0 + 
				 vertex_and_neighbors_2.first.y;

			return pair_1 < pair_2;
		});

	// uniting and duplicating lists of neighbors for each 'approximately' similar node
	for (auto point = graph_to_sort.begin(); point < graph_to_sort.end() - 1u; ++point) {
		if (point->first == (point + 1u)->first) {
			point->second.merge((point + 1u)->second);
			(point + 1u)->second = point->second;

			graph.at(point->first) = point->second;
			graph.at((point + 1u)->first) = point->second;
		}
	}
}

// connects all nodes in graph according to tangents and arcs
void connect_nodes_of_graph(Graph_t& graph, const Tangents_t& tangents, const Arcs_t& arcs) {
	for (const auto& tangent : tangents) {
		graph.at(tangent.m_a).insert(std::pair<Vertex_t, double>(tangent.m_b, tangent.m_length));
		graph.at(tangent.m_b).insert(std::pair<Vertex_t, double>(tangent.m_a, tangent.m_length));
	}
	for (const auto& arc : arcs) {
		graph.at(arc.m_a).insert(std::pair<Vertex_t, double>(arc.m_b, arc.m_length));
		graph.at(arc.m_b).insert(std::pair<Vertex_t, double>(arc.m_a, arc.m_length));
	}
}

// returns graph for this entire task
Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles) {
	Timer timer;
	// all circles with start and finish points as circles with zero radius
	const auto circles_copy = [&]() {
		auto local_copy = circles;
		local_copy.emplace_back(a, 0.0);
		local_copy.emplace_back(b, 0.0);
		return local_copy;
	}();
	std::cout << "copy = \t\t\t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	// finding all tangents between circles and start/finish points
	Tangents_t tangents;
	tangents.reserve(4.0 * (circles_copy.size()) * (circles_copy.size() - 1u));
	std::cout << "tangents.reserve() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	add_tangents(tangents, circles_copy);
	std::cout << "add_tangents() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();


	Timer filter_tangents_timer;
	/*
	const std::vector<Tangent> tangents_vector(tangents.cbegin(), tangents.cend());
	//std::cout << "tangents_vector() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	const std::size_t size = tangents_vector.size();
	Tangents_t part_1, part_2, part_3, part_4;
	part_1.reserve(size / 4u + 1u);
	part_2.reserve(size / 4u + 1u);
	part_3.reserve(size / 4u + 1u);
	part_4.reserve(size / 4u + 1u);
	
	std::cout << "parts.reserve() = \t\t" << timer.elapsed() << '\n';
	timer.reset();


	for (std::size_t index = 0u; index < size / 4u; ++index)
		part_1.insert(tangents_vector[index]);
	for (std::size_t index = size / 4u; index < size / 2u; ++index)
		part_2.insert(tangents_vector[index]);
	for (std::size_t index = size / 2u; index < 3u * size / 4u; ++index)
		part_3.insert(tangents_vector[index]);
	for (std::size_t index = 3u * size / 4u; index < size; ++index)
		part_4.insert(tangents_vector[index]);

	std::cout << "parts.push_back() = \t\t" << timer.elapsed() << '\n';
	timer.reset();


	Timer parallel_timer;
	std::thread thread_1(filter_tangents, std::ref(part_1), std::ref(circles));
	std::cout << "thread_1() = \t\t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	std::thread thread_2(filter_tangents, std::ref(part_2), std::ref(circles));
	std::cout << "thread_2() = \t\t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	std::thread thread_3(filter_tangents, std::ref(part_3), std::ref(circles));
	std::cout << "thread_3() = \t\t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	std::thread thread_4(filter_tangents, std::ref(part_4), std::ref(circles));
	std::cout << "thread_4() = \t\t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();


	thread_2.join();
	std::cout << "thread_2.join() = \t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	thread_3.join();
	std::cout << "thread_3.join() = \t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	thread_4.join();
	std::cout << "thread_4.join() = \t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();
	thread_1.join();
	std::cout << "thread_1.join() = \t" << parallel_timer.elapsed() << '\n';
	parallel_timer.reset();

	std::cout << "filter_tangents_parallel() = \t" << timer.elapsed() << '\n';
	timer.reset();



	tangents.clear();

	tangents.merge(part_4);
	tangents.merge(part_1);
	tangents.merge(part_2);
	tangents.merge(part_3);
	std::cout << "tangents.merge() = \t\t" << timer.elapsed() << '\n';
	timer.reset();

	*/

	//removing tangents which can not exist
	//filter_tangents_fast(tangents, circles_copy);
	
	//filter_tangents(tangents, circles); 
	//filter_tangents_advanced(tangents, circles);
	for(int i = 0; i < 1; ++i)
		filter_tangents_advanced(tangents, circles);
	std::cout << "filter_tangents() = \t\t\t" << filter_tangents_timer.elapsed() << '\n';
	timer.reset();
	
	// all points with binding to their own circles
	const auto points_on_circles = get_points_on_circles(tangents);
	std::cout << "get_points_on_circles() = \t\t" << timer.elapsed() << '\n';
	timer.reset();


	// finding all arcs
	Arcs_t arcs;
	//arcs.reserve(tangents.size() * tangents.size());
	arcs.reserve(tangents.size() * tangents.size());
	std::cout << "arcs.reserve() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	add_arcs(arcs, points_on_circles);
	std::cout << "add_arcs() = \t\t\t\t" << timer.elapsed() << '\n';
	timer.reset();


	// removing arc which can not exist
	filter_arcs_fast(arcs, circles); // 105 ms
	std::cout << "filter_arcs() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	
	// adding points to graph
	Graph_t graph;
	graph.reserve(tangents.size() * 2u + 2u);
	std::cout << "graph.reserve() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();

	add_nodes_to_graph(graph, points_on_circles); // 68 ms
	std::cout << "add_nodes_to_graph() = \t\t\t" << timer.elapsed() << '\n';
	timer.reset();


	// connecting points with each other according to tangent/arc they belong to
	connect_nodes_of_graph(graph, tangents, arcs); // 291 ms	
	std::cout << "connect_nodes_of_graph() = \t\t" << timer.elapsed() << '\n';
	timer.reset();


	// uniting lists of neighbors for every pair of 'approximately' similar points
	// (hash for 2.0 and for 1.99999999999999994 differs, but these points are 'approximately' same)
	merge_neighbors_for_similar_nodes(graph); // 319 ms
	std::cout << "merge_neighbors_for_similar_nodes() = \t" << timer.elapsed() << '\n';
	timer.reset();

	
	return graph;
}

double tiptoe_through_the_circles(Point a, Point b, const std::vector<Circle>& circles) {
	Timer timer;
	const auto graph = get_graph(a, b, circles);
	std::cout << "graph = " << timer.elapsed() << '\n';
	timer.reset();
	const double result = dijkstra_tiptoe(graph, a, b);
	std::cout << "dijkstra = " << timer.elapsed() << '\n';
	return result;
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

	//result_actual = algorithm(a1, b1, circles);

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

	//result_actual = algorithm(a2, b2, circles);

	std::cout << "test  #2: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a3(3.0, 0.0);
	Point b3(0.0, 4.0);
	result_expected = 5.0;

	//result_actual = algorithm(a3, b3, circles);

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

	//result_actual = algorithm(a4, b4, circles);

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

	//result_actual = algorithm(a5, b5, circles);

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

	//result_actual = algorithm(a6, b6, circles);

	std::cout << "test  #6: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	const auto circles2 = circles;
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
	result_expected = 13.51711753058981;

	Timer timer;
	result_actual = algorithm(a7, b7, circles);
	std::cout << "time = " << timer.elapsed() << '\n';
	
	std::cout << "test  #7: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();

	/*
	Point a8(1, 1);
	Point b8(9, 9);
	circles.emplace_back(0, 0, 0.3498640827136114);
	circles.emplace_back(0, 1, 0.5531412089942023);
	circles.emplace_back(0, 2, 0.7099347036564723);
	circles.emplace_back(0, 3, 0.6517945740139112);
	circles.emplace_back(0, 4, 0.1975581311853603);
	circles.emplace_back(0, 5, 0.2253608767641708);
	circles.emplace_back(0, 6, 0.3157269774237648);
	circles.emplace_back(0, 7, 0.346215516119264);
	circles.emplace_back(0, 8, 0.5213144983397796);
	circles.emplace_back(0, 9, 0.5118164314655587);
	circles.emplace_back(0, 10, 0.2498079464072361);
	circles.emplace_back(1, 0, 0.5152214519446715);
	circles.emplace_back(1, 2, 0.522460746509023);
	circles.emplace_back(1, 3, 0.55523882440757);
	circles.emplace_back(1, 4, 0.6768058778950944);
	circles.emplace_back(1, 5, 0.2268603341421112);
	circles.emplace_back(1, 6, 0.4034650325076655);
	circles.emplace_back(1, 7, 0.6050873699365183);
	circles.emplace_back(1, 8, 0.4469928074860945);
	circles.emplace_back(1, 9, 0.5717837225412949);
	circles.emplace_back(1, 10, 0.623612377163954);
	circles.emplace_back(2, 0, 0.4732748430920765);
	circles.emplace_back(2, 1, 0.4116287773707881);
	circles.emplace_back(2, 2, 0.6735617255559191);
	circles.emplace_back(2, 3, 0.4685481223510578);
	circles.emplace_back(2, 4, 0.5217285147635266);
	circles.emplace_back(2, 5, 0.309985762112774);
	circles.emplace_back(2, 6, 0.5198963790899143);
	circles.emplace_back(2, 7, 0.5368135755183175);
	circles.emplace_back(2, 8, 0.5974121243460103);
	circles.emplace_back(2, 9, 0.5061762819299475);
	circles.emplace_back(2, 10, 0.4053584629436955);
	circles.emplace_back(3, 0, 0.6964988417224959);
	circles.emplace_back(3, 1, 0.2804337898967788);
	circles.emplace_back(3, 2, 0.503911703475751);
	circles.emplace_back(3, 3, 0.1262727547204122);
	circles.emplace_back(3, 4, 0.5151378431590273);
	circles.emplace_back(3, 5, 0.3608648557914421);
	circles.emplace_back(3, 6, 0.4173152281204238);
	circles.emplace_back(3, 7, 0.3183767212321982);
	circles.emplace_back(3, 8, 0.6159705261932685);
	circles.emplace_back(3, 9, 0.2098946778802201);
	circles.emplace_back(3, 10, 0.6259145677322522);
	circles.emplace_back(4, 0, 0.6778776474064215);
	circles.emplace_back(4, 1, 0.5636972558917478);
	circles.emplace_back(4, 2, 0.5609463461441919);
	circles.emplace_back(4, 3, 0.391939307958819);
	circles.emplace_back(4, 4, 0.456533202691935);
	circles.emplace_back(4, 5, 0.4328503980534151);
	circles.emplace_back(4, 6, 0.666378344851546);
	circles.emplace_back(4, 7, 0.5680479590082541);
	circles.emplace_back(4, 8, 0.4713804449653253);
	circles.emplace_back(4, 9, 0.4619080887408927);
	circles.emplace_back(4, 10, 0.2453971502138302);
	circles.emplace_back(5, 0, 0.3736096939304843);
	circles.emplace_back(5, 1, 0.6197382619371637);
	circles.emplace_back(5, 2, 0.2462751913117245);
	circles.emplace_back(5, 3, 0.5888057655422017);
	circles.emplace_back(5, 4, 0.5676657743984833);
	circles.emplace_back(5, 5, 0.540108250058256);
	circles.emplace_back(5, 6, 0.5732564409496262);
	circles.emplace_back(5, 7, 0.5362131939036772);
	circles.emplace_back(5, 8, 0.5966956639895216);
	circles.emplace_back(5, 9, 0.7095990309258923);
	circles.emplace_back(5, 10, 0.6521467766957357);
	circles.emplace_back(6, 0, 0.2913298482773826);
	circles.emplace_back(6, 1, 0.5453128289664164);
	circles.emplace_back(6, 2, 0.5184990051900967);
	circles.emplace_back(6, 3, 0.4425638609798625);
	circles.emplace_back(6, 4, 0.6909738992108032);
	circles.emplace_back(6, 5, 0.5680152265587821);
	circles.emplace_back(6, 6, 0.5126225439598784);
	circles.emplace_back(6, 7, 0.534147786651738);
	circles.emplace_back(6, 8, 0.6934135599760338);
	circles.emplace_back(6, 9, 0.5301154807442799);
	circles.emplace_back(6, 10, 0.5440546177094802);
	circles.emplace_back(7, 0, 0.5807529715122655);
	circles.emplace_back(7, 1, 0.2016703092260286);
	circles.emplace_back(7, 2, 0.3359757455298677);
	circles.emplace_back(7, 3, 0.1209188626846299);
	circles.emplace_back(7, 4, 0.4422572403447703);
	circles.emplace_back(7, 5, 0.1874080511508509);
	circles.emplace_back(7, 6, 0.3726722557330504);
	circles.emplace_back(7, 7, 0.4967940848087892);
	circles.emplace_back(7, 8, 0.5371130944462493);
	circles.emplace_back(7, 9, 0.3310332131339237);
	circles.emplace_back(7, 10, 0.4472145652631297);
	circles.emplace_back(8, 0, 0.6904042010894045);
	circles.emplace_back(8, 1, 0.4587661686586216);
	circles.emplace_back(8, 2, 0.5436307809082791);
	circles.emplace_back(8, 3, 0.5454444729024545);
	circles.emplace_back(8, 4, 0.4762066185241565);
	circles.emplace_back(8, 5, 0.4590658758999779);
	circles.emplace_back(8, 6, 0.2863612712128088);
	circles.emplace_back(8, 7, 0.2907396355876699);
	circles.emplace_back(8, 8, 0.7365040505072101);
	circles.emplace_back(8, 9, 0.3517932391958311);
	circles.emplace_back(8, 10, 0.5529436419485136);
	circles.emplace_back(9, 0, 0.7306468691909686);
	circles.emplace_back(9, 1, 0.715704770735465);
	circles.emplace_back(9, 2, 0.4394309112103656);
	circles.emplace_back(9, 3, 0.3308491398347542);
	circles.emplace_back(9, 4, 0.5295701368013397);
	circles.emplace_back(9, 5, 0.2673563046148047);
	circles.emplace_back(9, 6, 0.5163003812776878);
	circles.emplace_back(9, 7, 0.5068310855654999);
	circles.emplace_back(9, 8, 0.3956382245058194);
	circles.emplace_back(9, 10, 0.3345775581663474);
	circles.emplace_back(10, 0, 0.3511913699330762);
	circles.emplace_back(10, 1, 0.4324155964655801);
	circles.emplace_back(10, 2, 0.6198771046707406);
	circles.emplace_back(10, 3, 0.4545143844326958);
	circles.emplace_back(10, 4, 0.7026084109442309);
	circles.emplace_back(10, 5, 0.4149782466469332);
	circles.emplace_back(10, 6, 0.1558119867229834);
	circles.emplace_back(10, 7, 0.6274435873841867);
	circles.emplace_back(10, 8, 0.4697596208425239);
	circles.emplace_back(10, 9, 0.4500316646648571);
	circles.emplace_back(10, 10, 0.4176240554312244);
	result_expected = 16.07123503713144;

	timer.reset();
	result_actual = algorithm(a8, b8, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test  #8: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a9(1, 1);
	Point b9(9, 9);
	circles.emplace_back(0, 0, 0.6411503633251413);
	circles.emplace_back(0, 1, 0.1324126559542492);
	circles.emplace_back(0, 2, 0.3603490686742589);
	circles.emplace_back(0, 3, 0.3249868966871872);
	circles.emplace_back(0, 4, 0.2912041798001155);
	circles.emplace_back(0, 5, 0.4827428569318726);
	circles.emplace_back(0, 6, 0.3575487390859052);
	circles.emplace_back(0, 7, 0.4727076107868924);
	circles.emplace_back(0, 8, 0.4877580920001492);
	circles.emplace_back(0, 9, 0.5022985807852819);
	circles.emplace_back(0, 10, 0.2917644287226722);
	circles.emplace_back(1, 0, 0.2532976132119074);
	circles.emplace_back(1, 2, 0.2894964966690168);
	circles.emplace_back(1, 3, 0.4872087204130366);
	circles.emplace_back(1, 4, 0.205026710475795);
	circles.emplace_back(1, 5, 0.7105981229105964);
	circles.emplace_back(1, 6, 0.355356323509477);
	circles.emplace_back(1, 7, 0.4747574116336182);
	circles.emplace_back(1, 8, 0.1539802624611184);
	circles.emplace_back(1, 9, 0.5525853380793705);
	circles.emplace_back(1, 10, 0.3546466640895232);
	circles.emplace_back(2, 0, 0.3744509277166799);
	circles.emplace_back(2, 1, 0.4175620906753466);
	circles.emplace_back(2, 2, 0.8014802994439378);
	circles.emplace_back(2, 3, 0.2261918382486328);
	circles.emplace_back(2, 4, 0.2567017614142969);
	circles.emplace_back(2, 5, 0.3552656891522929);
	circles.emplace_back(2, 6, 0.4092884410405531);
	circles.emplace_back(2, 7, 0.3271228980040178);
	circles.emplace_back(2, 8, 0.3022548944922164);
	circles.emplace_back(2, 9, 0.3316161376191303);
	circles.emplace_back(2, 10, 0.1168938284972683);
	circles.emplace_back(3, 0, 0.4619425689568743);
	circles.emplace_back(3, 1, 0.6654812547611072);
	circles.emplace_back(3, 2, 0.472481136652641);
	circles.emplace_back(3, 3, 0.1848330848151818);
	circles.emplace_back(3, 4, 0.3324886291986331);
	circles.emplace_back(3, 5, 0.4546633606078103);
	circles.emplace_back(3, 6, 0.3688429803354665);
	circles.emplace_back(3, 7, 0.2738740036496892);
	circles.emplace_back(3, 8, 0.4994207257172092);
	circles.emplace_back(3, 9, 0.2823981530265883);
	circles.emplace_back(3, 10, 0.393656466412358);
	circles.emplace_back(4, 0, 0.303523850091733);
	circles.emplace_back(4, 1, 0.3958556283032522);
	circles.emplace_back(4, 2, 0.6892420151503756);
	circles.emplace_back(4, 3, 0.3474177439464256);
	circles.emplace_back(4, 4, 0.3665923489490524);
	circles.emplace_back(4, 5, 0.2837759209563955);
	circles.emplace_back(4, 6, 0.293722979282029);
	circles.emplace_back(4, 7, 0.5980690984753891);
	circles.emplace_back(4, 8, 0.3279343605274335);
	circles.emplace_back(4, 9, 0.6938371307915077);
	circles.emplace_back(4, 10, 0.3718451214255765);
	circles.emplace_back(5, 0, 0.5308646746678277);
	circles.emplace_back(5, 1, 0.4854972439119592);
	circles.emplace_back(5, 2, 0.5391982944449409);
	circles.emplace_back(5, 3, 0.2192101433174685);
	circles.emplace_back(5, 4, 0.3738221364794299);
	circles.emplace_back(5, 5, 0.6217979077482596);
	circles.emplace_back(5, 6, 0.3440009619807824);
	circles.emplace_back(5, 7, 0.4988811419578269);
	circles.emplace_back(5, 8, 0.3143852648092434);
	circles.emplace_back(5, 9, 0.3239545485237613);
	circles.emplace_back(5, 10, 0.3771216382971033);
	circles.emplace_back(6, 0, 0.7281135666416958);
	circles.emplace_back(6, 1, 0.5729224926559254);
	circles.emplace_back(6, 2, 0.600398076348938);
	circles.emplace_back(6, 3, 0.7318226620322094);
	circles.emplace_back(6, 4, 0.6070783634902909);
	circles.emplace_back(6, 5, 0.5486863777739927);
	circles.emplace_back(6, 6, 0.3723882282385603);
	circles.emplace_back(6, 7, 0.3419265219708905);
	circles.emplace_back(6, 8, 0.34270230748225);
	circles.emplace_back(6, 9, 0.4038590128300711);
	circles.emplace_back(6, 10, 0.4684593688929453);
	circles.emplace_back(7, 0, 0.4751386109506711);
	circles.emplace_back(7, 1, 0.6707505219848826);
	circles.emplace_back(7, 2, 0.5013083730591461);
	circles.emplace_back(7, 3, 0.5999209789792076);
	circles.emplace_back(7, 4, 0.3941434172680601);
	circles.emplace_back(7, 5, 0.4292761857854202);
	circles.emplace_back(7, 6, 0.5616806014208123);
	circles.emplace_back(7, 7, 0.445537830912508);
	circles.emplace_back(7, 8, 0.6260991535848006);
	circles.emplace_back(7, 9, 0.7865624276222661);
	circles.emplace_back(7, 10, 0.2554532312555238);
	circles.emplace_back(8, 0, 0.2235148521373048);
	circles.emplace_back(8, 1, 0.3311558233341202);
	circles.emplace_back(8, 2, 0.1766814082162455);
	circles.emplace_back(8, 3, 0.6955743464408443);
	circles.emplace_back(8, 4, 0.1789116759086028);
	circles.emplace_back(8, 5, 0.3106217246269807);
	circles.emplace_back(8, 6, 0.4457955898018554);
	circles.emplace_back(8, 7, 0.4463126790476963);
	circles.emplace_back(8, 8, 0.06461187957320362);
	circles.emplace_back(8, 9, 0.5454033916583284);
	circles.emplace_back(8, 10, 0.4623261931585148);
	circles.emplace_back(9, 0, 0.5139436444966122);
	circles.emplace_back(9, 1, 0.743971910350956);
	circles.emplace_back(9, 2, 0.5053439736133442);
	circles.emplace_back(9, 3, 0.3941138421418145);
	circles.emplace_back(9, 4, 0.2348963142139837);
	circles.emplace_back(9, 5, 0.5932746986160055);
	circles.emplace_back(9, 6, 0.4200850510736927);
	circles.emplace_back(9, 7, 0.4056963957147673);
	circles.emplace_back(9, 8, 0.6269863257883116);
	circles.emplace_back(9, 10, 0.5321129586780443);
	circles.emplace_back(10, 0, 0.3520768899237737);
	circles.emplace_back(10, 1, 0.4788289674790576);
	circles.emplace_back(10, 2, 0.4193597306264564);
	circles.emplace_back(10, 3, 0.759827177063562);
	circles.emplace_back(10, 4, 0.6623621327569708);
	circles.emplace_back(10, 5, 0.4093711327062919);
	circles.emplace_back(10, 6, 0.1267727791098878);
	circles.emplace_back(10, 7, 0.3261232882970944);
	circles.emplace_back(10, 8, 0.4097579277819022);
	circles.emplace_back(10, 9, 0.3836663228692487);
	circles.emplace_back(10, 10, 0.5838326432509348);
	result_expected = 13.7274470620482;

	timer.reset();
	result_actual = algorithm(a9, b9, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test  #9: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a10(1, 1);
	Point b10(9, 9);
	circles.emplace_back(0, 0, 0.6139950381824747);
	circles.emplace_back(0, 1, 0.5740614952286706);
	circles.emplace_back(0, 2, 0.2875384076731279);
	circles.emplace_back(0, 3, 0.5048240768490359);
	circles.emplace_back(0, 4, 0.4630760345840826);
	circles.emplace_back(0, 5, 0.2439041312551126);
	circles.emplace_back(0, 6, 0.5510304645868018);
	circles.emplace_back(0, 7, 0.484747013146989);
	circles.emplace_back(0, 8, 0.5115464857080951);
	circles.emplace_back(0, 9, 0.7598786493530497);
	circles.emplace_back(0, 10, 0.5820107358740643);
	circles.emplace_back(1, 0, 0.3071900999872014);
	circles.emplace_back(1, 2, 0.5847196258837357);
	circles.emplace_back(1, 3, 0.5535652592545375);
	circles.emplace_back(1, 4, 0.591770773124881);
	circles.emplace_back(1, 5, 0.2746651724679395);
	circles.emplace_back(1, 6, 0.5084328288445249);
	circles.emplace_back(1, 7, 0.4730808833381161);
	circles.emplace_back(1, 8, 0.46574076928664);
	circles.emplace_back(1, 9, 0.3270276630995795);
	circles.emplace_back(1, 10, 0.1753684085095301);
	circles.emplace_back(2, 0, 0.8357769105350599);
	circles.emplace_back(2, 1, 0.2824470781954005);
	circles.emplace_back(2, 2, 0.7636079494608566);
	circles.emplace_back(2, 3, 0.2424291072646156);
	circles.emplace_back(2, 4, 0.3987103877356276);
	circles.emplace_back(2, 5, 0.3338369216071442);
	circles.emplace_back(2, 6, 0.4346786393551156);
	circles.emplace_back(2, 7, 0.4872932717436924);
	circles.emplace_back(2, 8, 0.3875136486953124);
	circles.emplace_back(2, 9, 0.4500952837290242);
	circles.emplace_back(2, 10, 0.4178827934665605);
	circles.emplace_back(3, 0, 0.5022747161099687);
	circles.emplace_back(3, 1, 0.3742873804410919);
	circles.emplace_back(3, 2, 0.3820789932506159);
	circles.emplace_back(3, 3, 0.3452480855165049);
	circles.emplace_back(3, 4, 0.3536122728371993);
	circles.emplace_back(3, 5, 0.5451421271776781);
	circles.emplace_back(3, 6, 0.4444929928751662);
	circles.emplace_back(3, 7, 0.1964118999196216);
	circles.emplace_back(3, 8, 0.1843140309909359);
	circles.emplace_back(3, 9, 0.448013231693767);
	circles.emplace_back(3, 10, 0.5729337963508442);
	circles.emplace_back(4, 0, 0.4236823669401928);
	circles.emplace_back(4, 1, 0.5886812620097771);
	circles.emplace_back(4, 2, 0.3613742142682895);
	circles.emplace_back(4, 3, 0.2979251330019906);
	circles.emplace_back(4, 4, 0.6245603353483602);
	circles.emplace_back(4, 5, 0.3366370329866186);
	circles.emplace_back(4, 6, 0.4744735890766605);
	circles.emplace_back(4, 7, 0.4890707797603682);
	circles.emplace_back(4, 8, 0.4273472825763747);
	circles.emplace_back(4, 9, 0.1759845074499026);
	circles.emplace_back(4, 10, 0.4197201180970296);
	circles.emplace_back(5, 0, 0.3724495806964114);
	circles.emplace_back(5, 1, 0.4054641623748466);
	circles.emplace_back(5, 2, 0.5907199336448684);
	circles.emplace_back(5, 3, 0.6478415025165304);
	circles.emplace_back(5, 4, 0.5743776540504768);
	circles.emplace_back(5, 5, 0.3861061899689958);
	circles.emplace_back(5, 6, 0.4435253203148022);
	circles.emplace_back(5, 7, 0.08644151163753122);
	circles.emplace_back(5, 8, 0.5946627867640927);
	circles.emplace_back(5, 9, 0.7688585647149011);
	circles.emplace_back(5, 10, 0.580565799982287);
	circles.emplace_back(6, 0, 0.5725805492838845);
	circles.emplace_back(6, 1, 0.2624760165112093);
	circles.emplace_back(6, 2, 0.3198981302557513);
	circles.emplace_back(6, 3, 0.4267166797304526);
	circles.emplace_back(6, 4, 0.5000046577071771);
	circles.emplace_back(6, 5, 0.4779654012294486);
	circles.emplace_back(6, 6, 0.5574059721780941);
	circles.emplace_back(6, 7, 0.3493451794842258);
	circles.emplace_back(6, 8, 0.4716479589929804);
	circles.emplace_back(6, 9, 0.1927369761513546);
	circles.emplace_back(6, 10, 0.5938159531680867);
	circles.emplace_back(7, 0, 0.2187718577915803);
	circles.emplace_back(7, 1, 0.3980335339671001);
	circles.emplace_back(7, 2, 0.5323278983356431);
	circles.emplace_back(7, 3, 0.3505241856677457);
	circles.emplace_back(7, 4, 0.3435367251047864);
	circles.emplace_back(7, 5, 0.3321977386018261);
	circles.emplace_back(7, 6, 0.4137967786984518);
	circles.emplace_back(7, 7, 0.2106844420311972);
	circles.emplace_back(7, 8, 0.3085950445616618);
	circles.emplace_back(7, 9, 0.681762957922183);
	circles.emplace_back(7, 10, 0.5615562015445903);
	circles.emplace_back(8, 0, 0.3257145021809265);
	circles.emplace_back(8, 1, 0.6945678202668205);
	circles.emplace_back(8, 2, 0.5887837974121793);
	circles.emplace_back(8, 3, 0.27457243159879);
	circles.emplace_back(8, 4, 0.5411384387640282);
	circles.emplace_back(8, 5, 0.5061719730729237);
	circles.emplace_back(8, 6, 0.6179917119210586);
	circles.emplace_back(8, 7, 0.8480573085369542);
	circles.emplace_back(8, 8, 0.5573898398084566);
	circles.emplace_back(8, 9, 0.3879552038619294);
	circles.emplace_back(8, 10, 0.444063072069548);
	circles.emplace_back(9, 0, 0.6027773290174082);
	circles.emplace_back(9, 1, 0.391200968879275);
	circles.emplace_back(9, 2, 0.2554605443263426);
	circles.emplace_back(9, 3, 0.3785356681561097);
	circles.emplace_back(9, 4, 0.5251049162121489);
	circles.emplace_back(9, 5, 0.4532028627349063);
	circles.emplace_back(9, 6, 0.5199455952504649);
	circles.emplace_back(9, 7, 0.7269986515631899);
	circles.emplace_back(9, 8, 0.3709368768380955);
	circles.emplace_back(9, 10, 0.1073613664833829);
	circles.emplace_back(10, 0, 0.6347814522916451);
	circles.emplace_back(10, 1, 0.3171809136634692);
	circles.emplace_back(10, 2, 0.6366050456883385);
	circles.emplace_back(10, 3, 0.3278741062385961);
	circles.emplace_back(10, 4, 0.5416563192615286);
	circles.emplace_back(10, 5, 0.1885629022261128);
	circles.emplace_back(10, 6, 0.4499041176633909);
	circles.emplace_back(10, 7, 0.3191533992765471);
	circles.emplace_back(10, 8, 0.2447088089073077);
	circles.emplace_back(10, 9, 0.5841368753230199);
	circles.emplace_back(10, 10, 0.4843616673024371);
	result_expected = 14.69287157740538;

	timer.reset();
	result_actual = algorithm(a10, b10, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #10: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a11(1, 1);
	Point b11(9, 9);
	circles.emplace_back(0, 0, 0.6145201016915962);
	circles.emplace_back(0, 1, 0.3907159311929718);
	circles.emplace_back(0, 2, 0.2349405927350744);
	circles.emplace_back(0, 3, 0.3498753558145836);
	circles.emplace_back(0, 4, 0.4192333935527131);
	circles.emplace_back(0, 5, 0.2834607690805569);
	circles.emplace_back(0, 6, 0.1779894448583945);
	circles.emplace_back(0, 7, 0.4628423256101086);
	circles.emplace_back(0, 8, 0.5134815015597268);
	circles.emplace_back(0, 9, 0.4104048418113962);
	circles.emplace_back(0, 10, 0.6982320191105827);
	circles.emplace_back(1, 0, 0.2489057823317125);
	circles.emplace_back(1, 2, 0.380958359199576);
	circles.emplace_back(1, 3, 0.5097901556873694);
	circles.emplace_back(1, 4, 0.5351541038369759);
	circles.emplace_back(1, 5, 0.5814437643857673);
	circles.emplace_back(1, 6, 0.5786512044025585);
	circles.emplace_back(1, 7, 0.5562959423521533);
	circles.emplace_back(1, 8, 0.1446561297168955);
	circles.emplace_back(1, 9, 0.5089250999735668);
	circles.emplace_back(1, 10, 0.2134641146985814);
	circles.emplace_back(2, 0, 0.4933750845724716);
	circles.emplace_back(2, 1, 0.756829048669897);
	circles.emplace_back(2, 2, 0.6742575516225769);
	circles.emplace_back(2, 3, 0.5413024798734113);
	circles.emplace_back(2, 4, 0.3903952295193449);
	circles.emplace_back(2, 5, 0.1202536502620205);
	circles.emplace_back(2, 6, 0.7792531482176855);
	circles.emplace_back(2, 7, 0.3542434121249243);
	circles.emplace_back(2, 8, 0.4527095895493403);
	circles.emplace_back(2, 9, 0.6734483156120404);
	circles.emplace_back(2, 10, 0.4973357045324519);
	circles.emplace_back(3, 0, 0.4714170937193558);
	circles.emplace_back(3, 1, 0.1627824304858222);
	circles.emplace_back(3, 2, 0.7340902087977156);
	circles.emplace_back(3, 3, 0.4876155282603576);
	circles.emplace_back(3, 4, 0.5992240621475503);
	circles.emplace_back(3, 5, 0.7804942474002018);
	circles.emplace_back(3, 6, 0.6466349057620391);
	circles.emplace_back(3, 7, 0.6134563145460561);
	circles.emplace_back(3, 8, 0.476513432781212);
	circles.emplace_back(3, 9, 0.5807516278931871);
	circles.emplace_back(3, 10, 0.4789594607194885);
	circles.emplace_back(4, 0, 0.4186592280166224);
	circles.emplace_back(4, 1, 0.5703470590291545);
	circles.emplace_back(4, 2, 0.5565268028760328);
	circles.emplace_back(4, 3, 0.8086539100622758);
	circles.emplace_back(4, 4, 0.1643891723128036);
	circles.emplace_back(4, 5, 0.4379746299935505);
	circles.emplace_back(4, 6, 0.665451884851791);
	circles.emplace_back(4, 7, 0.2895862137665972);
	circles.emplace_back(4, 8, 0.5799682471202686);
	circles.emplace_back(4, 9, 0.2206447056261822);
	circles.emplace_back(4, 10, 0.44809279369656);
	circles.emplace_back(5, 0, 0.6393656342988834);
	circles.emplace_back(5, 1, 0.2306613927008584);
	circles.emplace_back(5, 2, 0.08487668938469141);
	circles.emplace_back(5, 3, 0.2960278699407354);
	circles.emplace_back(5, 4, 0.4383295530220493);
	circles.emplace_back(5, 5, 0.3555792219238356);
	circles.emplace_back(5, 6, 0.3768187383888289);
	circles.emplace_back(5, 7, 0.3978561755502596);
	circles.emplace_back(5, 8, 0.08067872410174459);
	circles.emplace_back(5, 9, 0.4788230397971347);
	circles.emplace_back(5, 10, 0.6053166110767051);
	circles.emplace_back(6, 0, 0.5412604822078719);
	circles.emplace_back(6, 1, 0.4683859659126028);
	circles.emplace_back(6, 2, 0.3469970504986122);
	circles.emplace_back(6, 3, 0.3193184523610398);
	circles.emplace_back(6, 4, 0.7992499470943585);
	circles.emplace_back(6, 5, 0.6885032899444923);
	circles.emplace_back(6, 6, 0.4962127519072965);
	circles.emplace_back(6, 7, 0.595240516285412);
	circles.emplace_back(6, 8, 0.5787074761698022);
	circles.emplace_back(6, 9, 0.6644924672087654);
	circles.emplace_back(6, 10, 0.2017105176346377);
	circles.emplace_back(7, 0, 0.1999188261805102);
	circles.emplace_back(7, 1, 0.2593667749548331);
	circles.emplace_back(7, 2, 0.2222040321445093);
	circles.emplace_back(7, 3, 0.4132233665557578);
	circles.emplace_back(7, 4, 0.4447717723203823);
	circles.emplace_back(7, 5, 0.5013440868118778);
	circles.emplace_back(7, 6, 0.261129724024795);
	circles.emplace_back(7, 7, 0.5292079198407009);
	circles.emplace_back(7, 8, 0.4967986470786854);
	circles.emplace_back(7, 9, 0.4493496187264099);
	circles.emplace_back(7, 10, 0.4715533658629283);
	circles.emplace_back(8, 0, 0.5130675454856828);
	circles.emplace_back(8, 1, 0.1620391175849363);
	circles.emplace_back(8, 2, 0.4117036545882001);
	circles.emplace_back(8, 3, 0.1882251808186993);
	circles.emplace_back(8, 4, 0.5044926903443411);
	circles.emplace_back(8, 5, 0.3071186358807608);
	circles.emplace_back(8, 6, 0.6422823559725657);
	circles.emplace_back(8, 7, 0.4211845461046323);
	circles.emplace_back(8, 8, 0.4290433996589854);
	circles.emplace_back(8, 9, 0.5345047865761444);
	circles.emplace_back(8, 10, 0.3035182504216209);
	circles.emplace_back(9, 0, 0.4543561843922361);
	circles.emplace_back(9, 1, 0.7590990240918473);
	circles.emplace_back(9, 2, 0.4770995720056816);
	circles.emplace_back(9, 3, 0.5385804072255268);
	circles.emplace_back(9, 4, 0.252544792718254);
	circles.emplace_back(9, 5, 0.6293001142563298);
	circles.emplace_back(9, 6, 0.4277926348848268);
	circles.emplace_back(9, 7, 0.1308593007037416);
	circles.emplace_back(9, 8, 0.5674531088909134);
	circles.emplace_back(9, 10, 0.4596075027482584);
	circles.emplace_back(10, 0, 0.4696004184661433);
	circles.emplace_back(10, 1, 0.57888136098627);
	circles.emplace_back(10, 2, 0.2833484153961763);
	circles.emplace_back(10, 3, 0.48910357367713);
	circles.emplace_back(10, 4, 0.722016264195554);
	circles.emplace_back(10, 5, 0.3647782122949138);
	circles.emplace_back(10, 6, 0.5930024808039889);
	circles.emplace_back(10, 7, 0.5736607196973637);
	circles.emplace_back(10, 8, 0.369196446868591);
	circles.emplace_back(10, 9, 0.3444355987245217);
	circles.emplace_back(10, 10, 0.2445299386745319);
	result_expected = 14.98672182510387;

	timer.reset();
	result_actual = algorithm(a11, b11, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #11: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a12(1, 1);
	Point b12(9, 9);
	circles.emplace_back(0, 0, 0.7506019865395501);
	circles.emplace_back(0, 1, 0.4856071472866461);
	circles.emplace_back(0, 2, 0.3374469975242391);
	circles.emplace_back(0, 3, 0.4497501039644703);
	circles.emplace_back(0, 4, 0.4234789050417021);
	circles.emplace_back(0, 5, 0.2247573624132201);
	circles.emplace_back(0, 6, 0.4449969198787585);
	circles.emplace_back(0, 7, 0.3946972269332036);
	circles.emplace_back(0, 8, 0.4700915106805041);
	circles.emplace_back(0, 9, 0.3866427530301735);
	circles.emplace_back(0, 10, 0.673798899189569);
	circles.emplace_back(1, 0, 0.4429041845491156);
	circles.emplace_back(1, 2, 0.4268755506025627);
	circles.emplace_back(1, 3, 0.3295254288939759);
	circles.emplace_back(1, 4, 0.3942131668562069);
	circles.emplace_back(1, 5, 0.5720846093958244);
	circles.emplace_back(1, 6, 0.4527818781556561);
	circles.emplace_back(1, 7, 0.4416746713919565);
	circles.emplace_back(1, 8, 0.2106690155575052);
	circles.emplace_back(1, 9, 0.3348384560784325);
	circles.emplace_back(1, 10, 0.5257730349199846);
	circles.emplace_back(2, 0, 0.6386935936985537);
	circles.emplace_back(2, 1, 0.5725168500328436);
	circles.emplace_back(2, 2, 0.4840060051297769);
	circles.emplace_back(2, 3, 0.5750620202394202);
	circles.emplace_back(2, 4, 0.5020567384315654);
	circles.emplace_back(2, 5, 0.3034349253633991);
	circles.emplace_back(2, 6, 0.2532953044166789);
	circles.emplace_back(2, 7, 0.6022182482527568);
	circles.emplace_back(2, 8, 0.5244836128083988);
	circles.emplace_back(2, 9, 0.4775157727533951);
	circles.emplace_back(2, 10, 0.333808048046194);
	circles.emplace_back(3, 0, 0.2942656924249604);
	circles.emplace_back(3, 1, 0.1777731613023207);
	circles.emplace_back(3, 2, 0.3201573128113523);
	circles.emplace_back(3, 3, 0.4370888927718624);
	circles.emplace_back(3, 4, 0.4818982175784186);
	circles.emplace_back(3, 5, 0.3687241757987067);
	circles.emplace_back(3, 6, 0.461883656331338);
	circles.emplace_back(3, 7, 0.5853232118999585);
	circles.emplace_back(3, 8, 0.5459370994241908);
	circles.emplace_back(3, 9, 0.2987666432512924);
	circles.emplace_back(3, 10, 0.5232205925742164);
	circles.emplace_back(4, 0, 0.4193082866957411);
	circles.emplace_back(4, 1, 0.4251557315932586);
	circles.emplace_back(4, 2, 0.4929290308384224);
	circles.emplace_back(4, 3, 0.6587507650488987);
	circles.emplace_back(4, 4, 0.2648229352897033);
	circles.emplace_back(4, 5, 0.4285965201677754);
	circles.emplace_back(4, 6, 0.513766508619301);
	circles.emplace_back(4, 7, 0.338473534793593);
	circles.emplace_back(4, 8, 0.3480205790838227);
	circles.emplace_back(4, 9, 0.3055049657123163);
	circles.emplace_back(4, 10, 0.4258751096902415);
	circles.emplace_back(5, 0, 0.6945945311570539);
	circles.emplace_back(5, 1, 0.7004707466578111);
	circles.emplace_back(5, 2, 0.3760059328051284);
	circles.emplace_back(5, 3, 0.5266168278409168);
	circles.emplace_back(5, 4, 0.4118698900798335);
	circles.emplace_back(5, 5, 0.2444740151753649);
	circles.emplace_back(5, 6, 0.4756471070693806);
	circles.emplace_back(5, 7, 0.3086806527106091);
	circles.emplace_back(5, 8, 0.4896301798755303);
	circles.emplace_back(5, 9, 0.5992753892904147);
	circles.emplace_back(5, 10, 0.4169346397044137);
	circles.emplace_back(6, 0, 0.4701045424444601);
	circles.emplace_back(6, 1, 0.3536090145120397);
	circles.emplace_back(6, 2, 0.1988011175533757);
	circles.emplace_back(6, 3, 0.4209859795169905);
	circles.emplace_back(6, 4, 0.5373833338497206);
	circles.emplace_back(6, 5, 0.3457013543928042);
	circles.emplace_back(6, 6, 0.461543946317397);
	circles.emplace_back(6, 7, 0.4224248924525454);
	circles.emplace_back(6, 8, 0.4172875900520012);
	circles.emplace_back(6, 9, 0.569776494638063);
	circles.emplace_back(6, 10, 0.3032218111446127);
	circles.emplace_back(7, 0, 0.600643668626435);
	circles.emplace_back(7, 1, 0.5430183856515214);
	circles.emplace_back(7, 2, 0.6216707408661023);
	circles.emplace_back(7, 3, 0.4328349657123908);
	circles.emplace_back(7, 4, 0.5405575168551877);
	circles.emplace_back(7, 5, 0.5303230293793604);
	circles.emplace_back(7, 6, 0.081484772474505);
	circles.emplace_back(7, 7, 0.3227465482195839);
	circles.emplace_back(7, 8, 0.2759761466877535);
	circles.emplace_back(7, 9, 0.3091967242537066);
	circles.emplace_back(7, 10, 0.3963106934214011);
	circles.emplace_back(8, 0, 0.2934115852927789);
	circles.emplace_back(8, 1, 0.6187175379367545);
	circles.emplace_back(8, 2, 0.346795165236108);
	circles.emplace_back(8, 3, 0.2315137705067173);
	circles.emplace_back(8, 4, 0.6033794333925471);
	circles.emplace_back(8, 5, 0.3265888977097347);
	circles.emplace_back(8, 6, 0.4271830743877217);
	circles.emplace_back(8, 7, 0.2186938591534272);
	circles.emplace_back(8, 8, 0.3851946577196941);
	circles.emplace_back(8, 9, 0.41335980494041);
	circles.emplace_back(8, 10, 0.2035436735255644);
	circles.emplace_back(9, 0, 0.4784515166888013);
	circles.emplace_back(9, 1, 0.6178213486215099);
	circles.emplace_back(9, 2, 0.5538525424199179);
	circles.emplace_back(9, 3, 0.388474094378762);
	circles.emplace_back(9, 4, 0.5460838031256571);
	circles.emplace_back(9, 5, 0.4762158754980191);
	circles.emplace_back(9, 6, 0.5872746163280681);
	circles.emplace_back(9, 7, 0.5979917262447998);
	circles.emplace_back(9, 8, 0.6783347694436088);
	circles.emplace_back(9, 10, 0.5486730782082304);
	circles.emplace_back(10, 0, 0.471918463264592);
	circles.emplace_back(10, 1, 0.5148765011457727);
	circles.emplace_back(10, 2, 0.3693256333703175);
	circles.emplace_back(10, 3, 0.462570895976387);
	circles.emplace_back(10, 4, 0.2943533447803929);
	circles.emplace_back(10, 5, 0.6869741164846346);
	circles.emplace_back(10, 6, 0.2537896426627412);
	circles.emplace_back(10, 7, 0.5091384337982162);
	circles.emplace_back(10, 8, 0.2862344294087961);
	circles.emplace_back(10, 9, 0.3260851952014491);
	circles.emplace_back(10, 10, 0.5257366258883849);
	result_expected = 12.49336694213408;

	timer.reset();
	result_actual = algorithm(a12, b12, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #12: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a13(1, 1);
	Point b13(9, 9);
	circles.emplace_back(0, 0, 0.2078724663471803);
	circles.emplace_back(0, 1, 0.3518540621967986);
	circles.emplace_back(0, 2, 0.723065383429639);
	circles.emplace_back(0, 3, 0.2506722307065501);
	circles.emplace_back(0, 4, 0.1012273793807253);
	circles.emplace_back(0, 5, 0.5595602217363194);
	circles.emplace_back(0, 6, 0.2447613856522366);
	circles.emplace_back(0, 7, 0.2994968496495858);
	circles.emplace_back(0, 8, 0.320203548646532);
	circles.emplace_back(0, 9, 0.6001671646954492);
	circles.emplace_back(0, 10, 0.6284079373581335);
	circles.emplace_back(1, 0, 0.4822092334041372);
	circles.emplace_back(1, 2, 0.4114591562887653);
	circles.emplace_back(1, 3, 0.5654832578497008);
	circles.emplace_back(1, 4, 0.3391107151983306);
	circles.emplace_back(1, 5, 0.2095397915923968);
	circles.emplace_back(1, 6, 0.5665704447543248);
	circles.emplace_back(1, 7, 0.4500809976132586);
	circles.emplace_back(1, 8, 0.4060401846421882);
	circles.emplace_back(1, 9, 0.4606385810533538);
	circles.emplace_back(1, 10, 0.3440654081990942);
	circles.emplace_back(2, 0, 0.4294342170702293);
	circles.emplace_back(2, 1, 0.3029613851336762);
	circles.emplace_back(2, 2, 0.4849429816240445);
	circles.emplace_back(2, 3, 0.4248559213941916);
	circles.emplace_back(2, 4, 0.5175474805058912);
	circles.emplace_back(2, 5, 0.2887246527476236);
	circles.emplace_back(2, 6, 0.5163500594208017);
	circles.emplace_back(2, 7, 0.4916933061322197);
	circles.emplace_back(2, 8, 0.4572026654379442);
	circles.emplace_back(2, 9, 0.3733422803459689);
	circles.emplace_back(2, 10, 0.3278186176205054);
	circles.emplace_back(3, 0, 0.2732723351335153);
	circles.emplace_back(3, 1, 0.5459477321477607);
	circles.emplace_back(3, 2, 0.6252761152340099);
	circles.emplace_back(3, 3, 0.4045259347418323);
	circles.emplace_back(3, 4, 0.7436086734523997);
	circles.emplace_back(3, 5, 0.3509526807116344);
	circles.emplace_back(3, 6, 0.4855610943166539);
	circles.emplace_back(3, 7, 0.6637041904265061);
	circles.emplace_back(3, 8, 0.8173147573834285);
	circles.emplace_back(3, 9, 0.5158576955320313);
	circles.emplace_back(3, 10, 0.3043897167546675);
	circles.emplace_back(4, 0, 0.7992815787205473);
	circles.emplace_back(4, 1, 0.3313991108676418);
	circles.emplace_back(4, 2, 0.4127384773688391);
	circles.emplace_back(4, 3, 0.3657824541209265);
	circles.emplace_back(4, 4, 0.4794531088555232);
	circles.emplace_back(4, 5, 0.1542140993988141);
	circles.emplace_back(4, 6, 0.4423137628706172);
	circles.emplace_back(4, 7, 0.3159690980566666);
	circles.emplace_back(4, 8, 0.4753060935297981);
	circles.emplace_back(4, 9, 0.6121771214297042);
	circles.emplace_back(4, 10, 0.5355200316058472);
	circles.emplace_back(5, 0, 0.5611060454277321);
	circles.emplace_back(5, 1, 0.2486253246897832);
	circles.emplace_back(5, 2, 0.474890237278305);
	circles.emplace_back(5, 3, 0.3595784005941823);
	circles.emplace_back(5, 4, 0.7499545209808275);
	circles.emplace_back(5, 5, 0.5770029368111863);
	circles.emplace_back(5, 6, 0.3892832355340943);
	circles.emplace_back(5, 7, 0.2816787063376978);
	circles.emplace_back(5, 8, 0.5071447374997661);
	circles.emplace_back(5, 9, 0.4443779576802626);
	circles.emplace_back(5, 10, 0.7034051369642839);
	circles.emplace_back(6, 0, 0.4934057743521407);
	circles.emplace_back(6, 1, 0.8326509934617207);
	circles.emplace_back(6, 2, 0.3751305466750637);
	circles.emplace_back(6, 3, 0.2704891359200701);
	circles.emplace_back(6, 4, 0.34903287619818);
	circles.emplace_back(6, 5, 0.5331027081934735);
	circles.emplace_back(6, 6, 0.5398559205466881);
	circles.emplace_back(6, 7, 0.2739159792428836);
	circles.emplace_back(6, 8, 0.7208073740126565);
	circles.emplace_back(6, 9, 0.5005563945276662);
	circles.emplace_back(6, 10, 0.7109429667005315);
	circles.emplace_back(7, 0, 0.4637007826706394);
	circles.emplace_back(7, 1, 0.3243535525398329);
	circles.emplace_back(7, 2, 0.3043535689590499);
	circles.emplace_back(7, 3, 0.5960825439775362);
	circles.emplace_back(7, 4, 0.545128284743987);
	circles.emplace_back(7, 5, 0.5173176386626437);
	circles.emplace_back(7, 6, 0.5116895993007347);
	circles.emplace_back(7, 7, 0.4278304709354415);
	circles.emplace_back(7, 8, 0.4101615382125601);
	circles.emplace_back(7, 9, 0.5243800084339455);
	circles.emplace_back(7, 10, 0.6025184898404404);
	circles.emplace_back(8, 0, 0.3373502016300335);
	circles.emplace_back(8, 1, 0.2522490389412269);
	circles.emplace_back(8, 2, 0.5917595816077664);
	circles.emplace_back(8, 3, 0.4944186039967462);
	circles.emplace_back(8, 4, 0.4904601888963953);
	circles.emplace_back(8, 5, 0.5551552923163399);
	circles.emplace_back(8, 6, 0.1243354036705568);
	circles.emplace_back(8, 7, 0.6430443244753405);
	circles.emplace_back(8, 8, 0.5141109351301566);
	circles.emplace_back(8, 9, 0.296439817151986);
	circles.emplace_back(8, 10, 0.5085104153724387);
	circles.emplace_back(9, 0, 0.3337886509252712);
	circles.emplace_back(9, 1, 0.4914167305687442);
	circles.emplace_back(9, 2, 0.5562095870962366);
	circles.emplace_back(9, 3, 0.573942409758456);
	circles.emplace_back(9, 4, 0.2302817350951955);
	circles.emplace_back(9, 5, 0.2533670790726319);
	circles.emplace_back(9, 6, 0.1717699095373973);
	circles.emplace_back(9, 7, 0.3972671766998246);
	circles.emplace_back(9, 8, 0.3953503534896299);
	circles.emplace_back(9, 10, 0.44534281140659);
	circles.emplace_back(10, 0, 0.5287987420102581);
	circles.emplace_back(10, 1, 0.2009388349251822);
	circles.emplace_back(10, 2, 0.7500633175252005);
	circles.emplace_back(10, 3, 0.2965618860209361);
	circles.emplace_back(10, 4, 0.4296694461023435);
	circles.emplace_back(10, 5, 0.7503123515518382);
	circles.emplace_back(10, 6, 0.2864878211868927);
	circles.emplace_back(10, 7, 0.3705798773327842);
	circles.emplace_back(10, 8, 0.5295469788601622);
	circles.emplace_back(10, 9, 0.7020932491170242);
	circles.emplace_back(10, 10, 0.4997817261843011);
	result_expected = 12.54895262026183;

	timer.reset();
	result_actual = algorithm(a13, b13, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #13: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a14(1, 1);
	Point b14(9, 9);
	circles.emplace_back(0, 0, 0.4249701515072957);
	circles.emplace_back(0, 1, 0.6808825216954574);
	circles.emplace_back(0, 2, 0.3072795001091436);
	circles.emplace_back(0, 3, 0.6552467846078798);
	circles.emplace_back(0, 4, 0.3583087297389284);
	circles.emplace_back(0, 5, 0.6769315467914566);
	circles.emplace_back(0, 6, 0.6217206089990214);
	circles.emplace_back(0, 7, 0.5559677990851923);
	circles.emplace_back(0, 8, 0.6725888390326872);
	circles.emplace_back(0, 9, 0.3349203210091218);
	circles.emplace_back(0, 10, 0.4274188817711547);
	circles.emplace_back(1, 0, 0.5266627204371616);
	circles.emplace_back(1, 2, 0.529190150485374);
	circles.emplace_back(1, 3, 0.4094858472933993);
	circles.emplace_back(1, 4, 0.4176978829549625);
	circles.emplace_back(1, 5, 0.4793686828343198);
	circles.emplace_back(1, 6, 0.3265277050668374);
	circles.emplace_back(1, 7, 0.2770142435794696);
	circles.emplace_back(1, 8, 0.6493630801560357);
	circles.emplace_back(1, 9, 0.3765889764530584);
	circles.emplace_back(1, 10, 0.2775055269012228);
	circles.emplace_back(2, 0, 0.4815025591989979);
	circles.emplace_back(2, 1, 0.2149796760873869);
	circles.emplace_back(2, 2, 0.6575259576318785);
	circles.emplace_back(2, 3, 0.4148999240482226);
	circles.emplace_back(2, 4, 0.3825690287863835);
	circles.emplace_back(2, 5, 0.4383926281007007);
	circles.emplace_back(2, 6, 0.4430248965276405);
	circles.emplace_back(2, 7, 0.4027974767843261);
	circles.emplace_back(2, 8, 0.4962367636850104);
	circles.emplace_back(2, 9, 0.4466138552175835);
	circles.emplace_back(2, 10, 0.484853762271814);
	circles.emplace_back(3, 0, 0.3822127133840695);
	circles.emplace_back(3, 1, 0.3691158808534965);
	circles.emplace_back(3, 2, 0.5212016326608137);
	circles.emplace_back(3, 3, 0.5749439456267282);
	circles.emplace_back(3, 4, 0.3290104734012857);
	circles.emplace_back(3, 5, 0.6766090692719444);
	circles.emplace_back(3, 6, 0.5822571738855913);
	circles.emplace_back(3, 7, 0.4802169191418215);
	circles.emplace_back(3, 8, 0.3522579584503546);
	circles.emplace_back(3, 9, 0.3857655938481912);
	circles.emplace_back(3, 10, 0.5081634001107886);
	circles.emplace_back(4, 0, 0.4186218348098918);
	circles.emplace_back(4, 1, 0.311131470487453);
	circles.emplace_back(4, 2, 0.373408736824058);
	circles.emplace_back(4, 3, 0.7441908973501995);
	circles.emplace_back(4, 4, 0.5420090592233464);
	circles.emplace_back(4, 5, 0.2785028375918046);
	circles.emplace_back(4, 6, 0.4401616766816005);
	circles.emplace_back(4, 7, 0.6030960609437898);
	circles.emplace_back(4, 8, 0.5414646462304518);
	circles.emplace_back(4, 9, 0.2293305272469297);
	circles.emplace_back(4, 10, 0.5109968045493588);
	circles.emplace_back(5, 0, 0.5108364275889471);
	circles.emplace_back(5, 1, 0.3407307470915839);
	circles.emplace_back(5, 2, 0.4819804471218958);
	circles.emplace_back(5, 3, 0.4629334781086072);
	circles.emplace_back(5, 4, 0.5005281948717311);
	circles.emplace_back(5, 5, 0.5933369581354782);
	circles.emplace_back(5, 6, 0.6706014333525673);
	circles.emplace_back(5, 7, 0.3705092129996047);
	circles.emplace_back(5, 8, 0.3077709282981232);
	circles.emplace_back(5, 9, 0.3490676059154794);
	circles.emplace_back(5, 10, 0.576680426322855);
	circles.emplace_back(6, 0, 0.4096493117278442);
	circles.emplace_back(6, 1, 0.5704644558252766);
	circles.emplace_back(6, 2, 0.5053899698657914);
	circles.emplace_back(6, 3, 0.5979023339459673);
	circles.emplace_back(6, 4, 0.4105599300703034);
	circles.emplace_back(6, 5, 0.2862429498927668);
	circles.emplace_back(6, 6, 0.509468442457728);
	circles.emplace_back(6, 7, 0.3824395824456587);
	circles.emplace_back(6, 8, 0.1002695809816942);
	circles.emplace_back(6, 9, 0.5306511969538406);
	circles.emplace_back(6, 10, 0.5263896268559619);
	circles.emplace_back(7, 0, 0.6067963546374813);
	circles.emplace_back(7, 1, 0.6254440760007128);
	circles.emplace_back(7, 2, 0.5891880545066669);
	circles.emplace_back(7, 3, 0.4392233720747754);
	circles.emplace_back(7, 4, 0.7253325157100334);
	circles.emplace_back(7, 5, 0.59609990415629);
	circles.emplace_back(7, 6, 0.4063420956255868);
	circles.emplace_back(7, 7, 0.3965447456343099);
	circles.emplace_back(7, 8, 0.3695922265062109);
	circles.emplace_back(7, 9, 0.4408410483738407);
	circles.emplace_back(7, 10, 0.6047444409923628);
	circles.emplace_back(8, 0, 0.5730419437168166);
	circles.emplace_back(8, 1, 0.5255622443044558);
	circles.emplace_back(8, 2, 0.5142442393815144);
	circles.emplace_back(8, 3, 0.1775637784274295);
	circles.emplace_back(8, 4, 0.3588351388229057);
	circles.emplace_back(8, 5, 0.4669849111000076);
	circles.emplace_back(8, 6, 0.447017647116445);
	circles.emplace_back(8, 7, 0.8072685699211434);
	circles.emplace_back(8, 8, 0.643131264927797);
	circles.emplace_back(8, 9, 0.3728508293861523);
	circles.emplace_back(8, 10, 0.4795580096310004);
	circles.emplace_back(9, 0, 0.5138814461650326);
	circles.emplace_back(9, 1, 0.4078397401375696);
	circles.emplace_back(9, 2, 0.507196225435473);
	circles.emplace_back(9, 3, 0.5695311994990334);
	circles.emplace_back(9, 4, 0.2858507885830477);
	circles.emplace_back(9, 5, 0.596774126845412);
	circles.emplace_back(9, 6, 0.2893300000810995);
	circles.emplace_back(9, 7, 0.4141012277221307);
	circles.emplace_back(9, 8, 0.3966644988628104);
	circles.emplace_back(9, 10, 0.4760647293878719);
	circles.emplace_back(10, 0, 0.4326154669979587);
	circles.emplace_back(10, 1, 0.3774326851358637);
	circles.emplace_back(10, 2, 0.4603309559868649);
	circles.emplace_back(10, 3, 0.3514071292011067);
	circles.emplace_back(10, 4, 0.07993177848402411);
	circles.emplace_back(10, 5, 0.464091621316038);
	circles.emplace_back(10, 6, 0.6288521607639268);
	circles.emplace_back(10, 7, 0.357771657477133);
	circles.emplace_back(10, 8, 0.5139400387415662);
	circles.emplace_back(10, 9, 0.6289698609849438);
	circles.emplace_back(10, 10, 0.5848140678601339);
	result_expected = 14.74674113879269;

	timer.reset();
	result_actual = algorithm(a14, b14, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #14: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a15(1, 1);
	Point b15(9, 9);
	circles.emplace_back(0, 0, 0.4871988053200766);
	circles.emplace_back(0, 1, 0.4702791046584025);
	circles.emplace_back(0, 2, 0.1643577579176053);
	circles.emplace_back(0, 3, 0.3322191053302959);
	circles.emplace_back(0, 4, 0.5703055714024231);
	circles.emplace_back(0, 5, 0.6318160740891471);
	circles.emplace_back(0, 6, 0.3547903863480315);
	circles.emplace_back(0, 7, 0.638685881649144);
	circles.emplace_back(0, 8, 0.277127747121267);
	circles.emplace_back(0, 9, 0.5320764616364613);
	circles.emplace_back(0, 10, 0.6402921698754653);
	circles.emplace_back(1, 0, 0.2321410802425816);
	circles.emplace_back(1, 2, 0.5529231392545625);
	circles.emplace_back(1, 3, 0.345979061932303);
	circles.emplace_back(1, 4, 0.5786449478706345);
	circles.emplace_back(1, 5, 0.2051285415189341);
	circles.emplace_back(1, 6, 0.2545607301173732);
	circles.emplace_back(1, 7, 0.3960005004191771);
	circles.emplace_back(1, 8, 0.5473044793820009);
	circles.emplace_back(1, 9, 0.1298605324001983);
	circles.emplace_back(1, 10, 0.2031207752181217);
	circles.emplace_back(2, 0, 0.3518944716313854);
	circles.emplace_back(2, 1, 0.5755903845420107);
	circles.emplace_back(2, 2, 0.5371362033532933);
	circles.emplace_back(2, 3, 0.3183308384148404);
	circles.emplace_back(2, 4, 0.5520906649762765);
	circles.emplace_back(2, 5, 0.4477745234733447);
	circles.emplace_back(2, 6, 0.7622522329213097);
	circles.emplace_back(2, 7, 0.5504627645714208);
	circles.emplace_back(2, 8, 0.5248983780154958);
	circles.emplace_back(2, 9, 0.4676928126951679);
	circles.emplace_back(2, 10, 0.2110306597547606);
	circles.emplace_back(3, 0, 0.275315589713864);
	circles.emplace_back(3, 1, 0.4376398172462359);
	circles.emplace_back(3, 2, 0.6255054790293798);
	circles.emplace_back(3, 3, 0.4490889021428302);
	circles.emplace_back(3, 4, 0.2679093886865303);
	circles.emplace_back(3, 5, 0.5518380863824859);
	circles.emplace_back(3, 6, 0.257230751006864);
	circles.emplace_back(3, 7, 0.5674769650446251);
	circles.emplace_back(3, 8, 0.1205150603083894);
	circles.emplace_back(3, 9, 0.512584862136282);
	circles.emplace_back(3, 10, 0.1376769877737388);
	circles.emplace_back(4, 0, 0.3278068346204236);
	circles.emplace_back(4, 1, 0.6206450500292703);
	circles.emplace_back(4, 2, 0.4502127574989572);
	circles.emplace_back(4, 3, 0.3973982454976067);
	circles.emplace_back(4, 4, 0.5399990602629259);
	circles.emplace_back(4, 5, 0.3546300100861117);
	circles.emplace_back(4, 6, 0.3223973725223914);
	circles.emplace_back(4, 7, 0.4042982812738046);
	circles.emplace_back(4, 8, 0.4757715241285041);
	circles.emplace_back(4, 9, 0.5524063971592114);
	circles.emplace_back(4, 10, 0.3748140326002612);
	circles.emplace_back(5, 0, 0.3005079945316538);
	circles.emplace_back(5, 1, 0.6709953981684521);
	circles.emplace_back(5, 2, 0.5391400075284764);
	circles.emplace_back(5, 3, 0.3484742142492905);
	circles.emplace_back(5, 4, 0.43516130594071);
	circles.emplace_back(5, 5, 0.4200432886602357);
	circles.emplace_back(5, 6, 0.5093104497296735);
	circles.emplace_back(5, 7, 0.3118666583904997);
	circles.emplace_back(5, 8, 0.4836944738170132);
	circles.emplace_back(5, 9, 0.4152545682387426);
	circles.emplace_back(5, 10, 0.5888815547106787);
	circles.emplace_back(6, 0, 0.146028171130456);
	circles.emplace_back(6, 1, 0.1942938480293378);
	circles.emplace_back(6, 2, 0.4346428954275325);
	circles.emplace_back(6, 3, 0.3011827234877273);
	circles.emplace_back(6, 4, 0.5606691120425239);
	circles.emplace_back(6, 5, 0.5521170614054426);
	circles.emplace_back(6, 6, 0.4309709216700867);
	circles.emplace_back(6, 7, 0.302126212301664);
	circles.emplace_back(6, 8, 0.5694785699481144);
	circles.emplace_back(6, 9, 0.4019126586383209);
	circles.emplace_back(6, 10, 0.3253171858610585);
	circles.emplace_back(7, 0, 0.600385355274193);
	circles.emplace_back(7, 1, 0.3027342261979356);
	circles.emplace_back(7, 2, 0.5196631626924499);
	circles.emplace_back(7, 3, 0.2582601963775232);
	circles.emplace_back(7, 4, 0.1281587245641276);
	circles.emplace_back(7, 5, 0.7853419054532423);
	circles.emplace_back(7, 6, 0.5738765787100419);
	circles.emplace_back(7, 7, 0.5018047006102279);
	circles.emplace_back(7, 8, 0.5781452280236408);
	circles.emplace_back(7, 9, 0.5584298139670864);
	circles.emplace_back(7, 10, 0.367151335417293);
	circles.emplace_back(8, 0, 0.3851751419948414);
	circles.emplace_back(8, 1, 0.4723551443545148);
	circles.emplace_back(8, 2, 0.5726224653655663);
	circles.emplace_back(8, 3, 0.3986396640306338);
	circles.emplace_back(8, 4, 0.5376013045432045);
	circles.emplace_back(8, 5, 0.3783820957643911);
	circles.emplace_back(8, 6, 0.4311192939290777);
	circles.emplace_back(8, 7, 0.5380344146629795);
	circles.emplace_back(8, 8, 0.6012211448745802);
	circles.emplace_back(8, 9, 0.4387609581230208);
	circles.emplace_back(8, 10, 0.7107029553735629);
	circles.emplace_back(9, 0, 0.5517043102299795);
	circles.emplace_back(9, 1, 0.3172258117469027);
	circles.emplace_back(9, 2, 0.3290367086185143);
	circles.emplace_back(9, 3, 0.4388023151317611);
	circles.emplace_back(9, 4, 0.3716026378562674);
	circles.emplace_back(9, 5, 0.6383718530880287);
	circles.emplace_back(9, 6, 0.510169210913591);
	circles.emplace_back(9, 7, 0.2547351241344586);
	circles.emplace_back(9, 8, 0.2475743777817115);
	circles.emplace_back(9, 10, 0.4709856105269864);
	circles.emplace_back(10, 0, 0.4908989378018305);
	circles.emplace_back(10, 1, 0.3332553820917383);
	circles.emplace_back(10, 2, 0.4736867697676643);
	circles.emplace_back(10, 3, 0.399584801425226);
	circles.emplace_back(10, 4, 0.4656986313639209);
	circles.emplace_back(10, 5, 0.59853038827423);
	circles.emplace_back(10, 6, 0.5292083170032128);
	circles.emplace_back(10, 7, 0.2972422884078696);
	circles.emplace_back(10, 8, 0.2439359006239101);
	circles.emplace_back(10, 9, 0.4066724797943607);
	circles.emplace_back(10, 10, 0.6248612275114283);
	result_expected = 16.79656548837717;

	timer.reset();
	result_actual = algorithm(a15, b15, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #15: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a16(1, 1);
	Point b16(9, 9);
	circles.emplace_back(0, 0, 0.3748170363949612);
	circles.emplace_back(0, 1, 0.3358717567054555);
	circles.emplace_back(0, 2, 0.4249504573876038);
	circles.emplace_back(0, 3, 0.6949722930556163);
	circles.emplace_back(0, 4, 0.3721772571327165);
	circles.emplace_back(0, 5, 0.6111200854880735);
	circles.emplace_back(0, 6, 0.2858056986937299);
	circles.emplace_back(0, 7, 0.426147205545567);
	circles.emplace_back(0, 8, 0.4445407412247732);
	circles.emplace_back(0, 9, 0.4951930577633902);
	circles.emplace_back(0, 10, 0.4437979590380564);
	circles.emplace_back(1, 0, 0.4630933109438047);
	circles.emplace_back(1, 2, 0.547057377663441);
	circles.emplace_back(1, 3, 0.6197574768913909);
	circles.emplace_back(1, 4, 0.6136058597126975);
	circles.emplace_back(1, 5, 0.5822158006718382);
	circles.emplace_back(1, 6, 0.3707588608609512);
	circles.emplace_back(1, 7, 0.5922270639566705);
	circles.emplace_back(1, 8, 0.2172070637578145);
	circles.emplace_back(1, 9, 0.3736123405164107);
	circles.emplace_back(1, 10, 0.8330005851807073);
	circles.emplace_back(2, 0, 0.3003156804246828);
	circles.emplace_back(2, 1, 0.4183631392428651);
	circles.emplace_back(2, 2, 0.6220911370357498);
	circles.emplace_back(2, 3, 0.4755207269685343);
	circles.emplace_back(2, 4, 0.3171764882979914);
	circles.emplace_back(2, 5, 0.5725341100478545);
	circles.emplace_back(2, 6, 0.7278374414658174);
	circles.emplace_back(2, 7, 0.3732415140839294);
	circles.emplace_back(2, 8, 0.1227520477725193);
	circles.emplace_back(2, 9, 0.6703476941445842);
	circles.emplace_back(2, 10, 0.5573534911265596);
	circles.emplace_back(3, 0, 0.7069376829313114);
	circles.emplace_back(3, 1, 0.2069603523937985);
	circles.emplace_back(3, 2, 0.802748229377903);
	circles.emplace_back(3, 3, 0.2652968883281573);
	circles.emplace_back(3, 4, 0.2028971229912713);
	circles.emplace_back(3, 5, 0.4703418017132208);
	circles.emplace_back(3, 6, 0.5259502867469564);
	circles.emplace_back(3, 7, 0.4778424167772755);
	circles.emplace_back(3, 8, 0.1926987088518217);
	circles.emplace_back(3, 9, 0.387792111444287);
	circles.emplace_back(3, 10, 0.2543219711864367);
	circles.emplace_back(4, 0, 0.2781922954833135);
	circles.emplace_back(4, 1, 0.4962323197396472);
	circles.emplace_back(4, 2, 0.5510061611188576);
	circles.emplace_back(4, 3, 0.3593229098478332);
	circles.emplace_back(4, 4, 0.4848598701646551);
	circles.emplace_back(4, 5, 0.2810860465513542);
	circles.emplace_back(4, 6, 0.2552577792434021);
	circles.emplace_back(4, 7, 0.402621927880682);
	circles.emplace_back(4, 8, 0.6633517421549185);
	circles.emplace_back(4, 9, 0.1014255863847211);
	circles.emplace_back(4, 10, 0.3461404659552499);
	circles.emplace_back(5, 0, 0.4815194117138162);
	circles.emplace_back(5, 1, 0.6618733348092064);
	circles.emplace_back(5, 2, 0.569490824569948);
	circles.emplace_back(5, 3, 0.5918940531788394);
	circles.emplace_back(5, 4, 0.5147993598366156);
	circles.emplace_back(5, 5, 0.2116828974103555);
	circles.emplace_back(5, 6, 0.4628346042009071);
	circles.emplace_back(5, 7, 0.4969423022819683);
	circles.emplace_back(5, 8, 0.647136121080257);
	circles.emplace_back(5, 9, 0.1827189465751871);
	circles.emplace_back(5, 10, 0.5204286831663921);
	circles.emplace_back(6, 0, 0.3222664392320439);
	circles.emplace_back(6, 1, 0.400180820398964);
	circles.emplace_back(6, 2, 0.535126145160757);
	circles.emplace_back(6, 3, 0.4307618786813691);
	circles.emplace_back(6, 4, 0.4282396272523328);
	circles.emplace_back(6, 5, 0.3484524721512571);
	circles.emplace_back(6, 6, 0.6573046186706051);
	circles.emplace_back(6, 7, 0.6650553993182257);
	circles.emplace_back(6, 8, 0.5055473769782111);
	circles.emplace_back(6, 9, 0.6481587808812037);
	circles.emplace_back(6, 10, 0.4311077091610059);
	circles.emplace_back(7, 0, 0.5587203645380213);
	circles.emplace_back(7, 1, 0.409818894113414);
	circles.emplace_back(7, 2, 0.4970716295996681);
	circles.emplace_back(7, 3, 0.5148131666472181);
	circles.emplace_back(7, 4, 0.6941825117217376);
	circles.emplace_back(7, 5, 0.2655943645862862);
	circles.emplace_back(7, 6, 0.3535822555655613);
	circles.emplace_back(7, 7, 0.484492778009735);
	circles.emplace_back(7, 8, 0.3881990907015279);
	circles.emplace_back(7, 9, 0.3552531772060319);
	circles.emplace_back(7, 10, 0.4930611135670915);
	circles.emplace_back(8, 0, 0.8244054334005341);
	circles.emplace_back(8, 1, 0.4367929457919672);
	circles.emplace_back(8, 2, 0.2585280838189646);
	circles.emplace_back(8, 3, 0.4296474267030135);
	circles.emplace_back(8, 4, 0.5070386301493272);
	circles.emplace_back(8, 5, 0.4209287853213027);
	circles.emplace_back(8, 6, 0.7582302969647571);
	circles.emplace_back(8, 7, 0.281593424663879);
	circles.emplace_back(8, 8, 0.3534234141698107);
	circles.emplace_back(8, 9, 0.4260566386627033);
	circles.emplace_back(8, 10, 0.4778105250326916);
	circles.emplace_back(9, 0, 0.5082882695132867);
	circles.emplace_back(9, 1, 0.3143477588659152);
	circles.emplace_back(9, 2, 0.3786475007655099);
	circles.emplace_back(9, 3, 0.6663809449179098);
	circles.emplace_back(9, 4, 0.197086668969132);
	circles.emplace_back(9, 5, 0.2630933815380558);
	circles.emplace_back(9, 6, 0.5528461641864851);
	circles.emplace_back(9, 7, 0.4968231121776625);
	circles.emplace_back(9, 8, 0.5280671771848574);
	circles.emplace_back(9, 10, 0.5403209972893819);
	circles.emplace_back(10, 0, 0.6503662386210635);
	circles.emplace_back(10, 1, 0.4926068086875602);
	circles.emplace_back(10, 2, 0.3948451830307022);
	circles.emplace_back(10, 3, 0.7417290104320272);
	circles.emplace_back(10, 4, 0.4067523579346016);
	circles.emplace_back(10, 5, 0.6489448277978226);
	circles.emplace_back(10, 6, 0.4095655858749523);
	circles.emplace_back(10, 7, 0.4891106433933601);
	circles.emplace_back(10, 8, 0.6271345746936277);
	circles.emplace_back(10, 9, 0.3639086969895288);
	circles.emplace_back(10, 10, 0.170200158865191);
	result_expected = 17.31021875860946;

	timer.reset();
	result_actual = algorithm(a16, b16, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #16: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a17(1, 1);
	Point b17(9, 9);
	circles.emplace_back(0, 0, 0.6754345031222329);
	circles.emplace_back(0, 1, 0.4045999421970919);
	circles.emplace_back(0, 2, 0.2451303380308673);
	circles.emplace_back(0, 3, 0.518274599709548);
	circles.emplace_back(0, 4, 0.5245735849952325);
	circles.emplace_back(0, 5, 0.5243062840076164);
	circles.emplace_back(0, 6, 0.3077146646333858);
	circles.emplace_back(0, 7, 0.4651502689579501);
	circles.emplace_back(0, 8, 0.3563077142229303);
	circles.emplace_back(0, 9, 0.406463150982745);
	circles.emplace_back(0, 10, 0.6289881176082417);
	circles.emplace_back(1, 0, 0.514985615783371);
	circles.emplace_back(1, 2, 0.597224424756132);
	circles.emplace_back(1, 3, 0.3913049658061936);
	circles.emplace_back(1, 4, 0.4757081375224516);
	circles.emplace_back(1, 5, 0.2625022912630811);
	circles.emplace_back(1, 6, 0.3281432756921276);
	circles.emplace_back(1, 7, 0.3191813550191);
	circles.emplace_back(1, 8, 0.4693585748551413);
	circles.emplace_back(1, 9, 0.4936809491598979);
	circles.emplace_back(1, 10, 0.3086886051809415);
	circles.emplace_back(2, 0, 0.2088896685512736);
	circles.emplace_back(2, 1, 0.5051560376537964);
	circles.emplace_back(2, 2, 0.6675117342034355);
	circles.emplace_back(2, 3, 0.5696357218315825);
	circles.emplace_back(2, 4, 0.587374686752446);
	circles.emplace_back(2, 5, 0.3903921766905114);
	circles.emplace_back(2, 6, 0.5069244578713551);
	circles.emplace_back(2, 7, 0.5136555336182936);
	circles.emplace_back(2, 8, 0.4739205149235204);
	circles.emplace_back(2, 9, 0.4177369081182405);
	circles.emplace_back(2, 10, 0.4770234616706148);
	circles.emplace_back(3, 0, 0.3150826142868027);
	circles.emplace_back(3, 1, 0.471959665347822);
	circles.emplace_back(3, 2, 0.4391275736270472);
	circles.emplace_back(3, 3, 0.2787521679187193);
	circles.emplace_back(3, 4, 0.4593317072605714);
	circles.emplace_back(3, 5, 0.5716243268223479);
	circles.emplace_back(3, 6, 0.6558690381003544);
	circles.emplace_back(3, 7, 0.3361123180249706);
	circles.emplace_back(3, 8, 0.3125876670470461);
	circles.emplace_back(3, 9, 0.4161648216890171);
	circles.emplace_back(3, 10, 0.2905697247711941);
	circles.emplace_back(4, 0, 0.3050628982717171);
	circles.emplace_back(4, 1, 0.3623938381439075);
	circles.emplace_back(4, 2, 0.6353602503659204);
	circles.emplace_back(4, 3, 0.3565385878784582);
	circles.emplace_back(4, 4, 0.7822237530956044);
	circles.emplace_back(4, 5, 0.3197638714453205);
	circles.emplace_back(4, 6, 0.3990463233785704);
	circles.emplace_back(4, 7, 0.3902680228231475);
	circles.emplace_back(4, 8, 0.441508885868825);
	circles.emplace_back(4, 9, 0.4234419781481847);
	circles.emplace_back(4, 10, 0.5938853808911517);
	circles.emplace_back(5, 0, 0.1626277138246223);
	circles.emplace_back(5, 1, 0.176814447180368);
	circles.emplace_back(5, 2, 0.5369366211583838);
	circles.emplace_back(5, 3, 0.2765035997377708);
	circles.emplace_back(5, 4, 0.4343944190768525);
	circles.emplace_back(5, 5, 0.4788864106172696);
	circles.emplace_back(5, 6, 0.4789526439970359);
	circles.emplace_back(5, 7, 0.3061203879537061);
	circles.emplace_back(5, 8, 0.5717426934046671);
	circles.emplace_back(5, 9, 0.3244929360458627);
	circles.emplace_back(5, 10, 0.3778468372067437);
	circles.emplace_back(6, 0, 0.3097949668066576);
	circles.emplace_back(6, 1, 0.5873215484200045);
	circles.emplace_back(6, 2, 0.3060264203930274);
	circles.emplace_back(6, 3, 0.5907319422578439);
	circles.emplace_back(6, 4, 0.4834151403279975);
	circles.emplace_back(6, 5, 0.6225420501781628);
	circles.emplace_back(6, 6, 0.5796602359274402);
	circles.emplace_back(6, 7, 0.5778540929546579);
	circles.emplace_back(6, 8, 0.6815532523440196);
	circles.emplace_back(6, 9, 0.3367008543340489);
	circles.emplace_back(6, 10, 0.560185156040825);
	circles.emplace_back(7, 0, 0.7728686943417414);
	circles.emplace_back(7, 1, 0.49931433100719);
	circles.emplace_back(7, 2, 0.5185646787984296);
	circles.emplace_back(7, 3, 0.5406504685292021);
	circles.emplace_back(7, 4, 0.5396397391101345);
	circles.emplace_back(7, 5, 0.2993014208273962);
	circles.emplace_back(7, 6, 0.3860407138941809);
	circles.emplace_back(7, 7, 0.7649347763741389);
	circles.emplace_back(7, 8, 0.4561875615036115);
	circles.emplace_back(7, 9, 0.5868231022031978);
	circles.emplace_back(7, 10, 0.3895579700125381);
	circles.emplace_back(8, 0, 0.5313714860239998);
	circles.emplace_back(8, 1, 0.2164100287249312);
	circles.emplace_back(8, 2, 0.5864681984530762);
	circles.emplace_back(8, 3, 0.3847845627693459);
	circles.emplace_back(8, 4, 0.3555539831751958);
	circles.emplace_back(8, 5, 0.09020216984208673);
	circles.emplace_back(8, 6, 0.6231726703466848);
	circles.emplace_back(8, 7, 0.2903059356613085);
	circles.emplace_back(8, 8, 0.4704454960534349);
	circles.emplace_back(8, 9, 0.2325992421945557);
	circles.emplace_back(8, 10, 0.4609036981360987);
	circles.emplace_back(9, 0, 0.2958890202222392);
	circles.emplace_back(9, 1, 0.4919186461949721);
	circles.emplace_back(9, 2, 0.38256823529955);
	circles.emplace_back(9, 3, 0.602085951087065);
	circles.emplace_back(9, 4, 0.536957333679311);
	circles.emplace_back(9, 5, 0.4278496867278591);
	circles.emplace_back(9, 6, 0.5420728122582659);
	circles.emplace_back(9, 7, 0.5008950445102528);
	circles.emplace_back(9, 8, 0.600902014109306);
	circles.emplace_back(9, 10, 0.3588924281531945);
	circles.emplace_back(10, 0, 0.3760366886621341);
	circles.emplace_back(10, 1, 0.3935431842925027);
	circles.emplace_back(10, 2, 0.580853793094866);
	circles.emplace_back(10, 3, 0.1690568516263738);
	circles.emplace_back(10, 4, 0.6238304489990696);
	circles.emplace_back(10, 5, 0.3986819989280775);
	circles.emplace_back(10, 6, 0.1425409058807418);
	circles.emplace_back(10, 7, 0.5542174097383394);
	circles.emplace_back(10, 8, 0.6629068005597218);
	circles.emplace_back(10, 9, 0.5910475590499118);
	circles.emplace_back(10, 10, 0.3198579390300438);
	result_expected = 15.90732348954008;

	timer.reset();
	result_actual = algorithm(a17, b17, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #17: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a18(1, 1);
	Point b18(9, 9);
	circles.emplace_back(0, 0, 0.3866760147968307);
	circles.emplace_back(0, 1, 0.6152092648437246);
	circles.emplace_back(0, 2, 0.201472584460862);
	circles.emplace_back(0, 3, 0.6047706155804917);
	circles.emplace_back(0, 4, 0.3639047146076336);
	circles.emplace_back(0, 5, 0.6369793064659461);
	circles.emplace_back(0, 6, 0.5463908386649564);
	circles.emplace_back(0, 7, 0.2471815177006647);
	circles.emplace_back(0, 8, 0.2195930557558313);
	circles.emplace_back(0, 9, 0.6825868995627388);
	circles.emplace_back(0, 10, 0.2399587108986452);
	circles.emplace_back(1, 0, 0.5303817468462512);
	circles.emplace_back(1, 2, 0.3251251343870535);
	circles.emplace_back(1, 3, 0.5830095316981897);
	circles.emplace_back(1, 4, 0.1919189856620505);
	circles.emplace_back(1, 5, 0.437713521416299);
	circles.emplace_back(1, 6, 0.3596113344887271);
	circles.emplace_back(1, 7, 0.7295846452703699);
	circles.emplace_back(1, 8, 0.3443317997502163);
	circles.emplace_back(1, 9, 0.4760687119094655);
	circles.emplace_back(1, 10, 0.7765997536713257);
	circles.emplace_back(2, 0, 0.5036605164175852);
	circles.emplace_back(2, 1, 0.2502977867843583);
	circles.emplace_back(2, 2, 0.4718483135802671);
	circles.emplace_back(2, 3, 0.6455923164496198);
	circles.emplace_back(2, 4, 0.4427705714246258);
	circles.emplace_back(2, 5, 0.4477984092431143);
	circles.emplace_back(2, 6, 0.1050078565953299);
	circles.emplace_back(2, 7, 0.5964905750239268);
	circles.emplace_back(2, 8, 0.4839561406290158);
	circles.emplace_back(2, 9, 0.5317784779937937);
	circles.emplace_back(2, 10, 0.2968137536896392);
	circles.emplace_back(3, 0, 0.2450961975613609);
	circles.emplace_back(3, 1, 0.5748626498272642);
	circles.emplace_back(3, 2, 0.4775958593236282);
	circles.emplace_back(3, 3, 0.4169355853227898);
	circles.emplace_back(3, 4, 0.6277911439770832);
	circles.emplace_back(3, 5, 0.4932342491811141);
	circles.emplace_back(3, 6, 0.518963369471021);
	circles.emplace_back(3, 7, 0.5254993223352358);
	circles.emplace_back(3, 8, 0.1235225292155519);
	circles.emplace_back(3, 9, 0.365431879623793);
	circles.emplace_back(3, 10, 0.4335078566567972);
	circles.emplace_back(4, 0, 0.3157264861045405);
	circles.emplace_back(4, 1, 0.3912171740317717);
	circles.emplace_back(4, 2, 0.2245997767662629);
	circles.emplace_back(4, 3, 0.439071470615454);
	circles.emplace_back(4, 4, 0.3727842462016269);
	circles.emplace_back(4, 5, 0.3007508432725444);
	circles.emplace_back(4, 6, 0.3991054123034701);
	circles.emplace_back(4, 7, 0.6538801196264102);
	circles.emplace_back(4, 8, 0.4144714555470273);
	circles.emplace_back(4, 9, 0.3855971716577187);
	circles.emplace_back(4, 10, 0.1718778729205951);
	circles.emplace_back(5, 0, 0.4237041150452569);
	circles.emplace_back(5, 1, 0.4293656230671331);
	circles.emplace_back(5, 2, 0.5952812770614401);
	circles.emplace_back(5, 3, 0.4012696766993031);
	circles.emplace_back(5, 4, 0.4691360033350065);
	circles.emplace_back(5, 5, 0.2780558238504454);
	circles.emplace_back(5, 6, 0.6757630612934008);
	circles.emplace_back(5, 7, 0.3440670270239934);
	circles.emplace_back(5, 8, 0.4561105855973437);
	circles.emplace_back(5, 9, 0.6730865468038246);
	circles.emplace_back(5, 10, 0.3558751983800903);
	circles.emplace_back(6, 0, 0.3712735039880499);
	circles.emplace_back(6, 1, 0.342792124603875);
	circles.emplace_back(6, 2, 0.5032374798087403);
	circles.emplace_back(6, 3, 0.5679408103460446);
	circles.emplace_back(6, 4, 0.2172921933000907);
	circles.emplace_back(6, 5, 0.5059537393273785);
	circles.emplace_back(6, 6, 0.6177642323775216);
	circles.emplace_back(6, 7, 0.4806958304950967);
	circles.emplace_back(6, 8, 0.2531312526902184);
	circles.emplace_back(6, 9, 0.5999739869730547);
	circles.emplace_back(6, 10, 0.6362249958096072);
	circles.emplace_back(7, 0, 0.2726410541916266);
	circles.emplace_back(7, 1, 0.5242579158162698);
	circles.emplace_back(7, 2, 0.2515756325097754);
	circles.emplace_back(7, 3, 0.09951814084779471);
	circles.emplace_back(7, 4, 0.5239488771418109);
	circles.emplace_back(7, 5, 0.5437259336700663);
	circles.emplace_back(7, 6, 0.3434316057013347);
	circles.emplace_back(7, 7, 0.4277557528344914);
	circles.emplace_back(7, 8, 0.3550497211748734);
	circles.emplace_back(7, 9, 0.2812014534836635);
	circles.emplace_back(7, 10, 0.4897631456376985);
	circles.emplace_back(8, 0, 0.4005981043679639);
	circles.emplace_back(8, 1, 0.4900231475243345);
	circles.emplace_back(8, 2, 0.5385123351356015);
	circles.emplace_back(8, 3, 0.1570551327662542);
	circles.emplace_back(8, 4, 0.5256740654585883);
	circles.emplace_back(8, 5, 0.7729186576092616);
	circles.emplace_back(8, 6, 0.4523459050571546);
	circles.emplace_back(8, 7, 0.5330136084230617);
	circles.emplace_back(8, 8, 0.6107124511850998);
	circles.emplace_back(8, 9, 0.7151311813155189);
	circles.emplace_back(8, 10, 0.5147201476385816);
	circles.emplace_back(9, 0, 0.4968904818641022);
	circles.emplace_back(9, 1, 0.5050093068508431);
	circles.emplace_back(9, 2, 0.4019562527770176);
	circles.emplace_back(9, 3, 0.7518533341353759);
	circles.emplace_back(9, 4, 0.5943004247965291);
	circles.emplace_back(9, 5, 0.3258561306400224);
	circles.emplace_back(9, 6, 0.7364498736569658);
	circles.emplace_back(9, 7, 0.6520570890745148);
	circles.emplace_back(9, 8, 0.5696549534099177);
	circles.emplace_back(9, 10, 0.8355540337739512);
	circles.emplace_back(10, 0, 0.3487180639291182);
	circles.emplace_back(10, 1, 0.3832778941607103);
	circles.emplace_back(10, 2, 0.4593386979075149);
	circles.emplace_back(10, 3, 0.2846388381673023);
	circles.emplace_back(10, 4, 0.4487611001590266);
	circles.emplace_back(10, 5, 0.2909120296826586);
	circles.emplace_back(10, 6, 0.3987528595374897);
	circles.emplace_back(10, 7, 0.3869421115843579);
	circles.emplace_back(10, 8, 0.5509974412852898);
	circles.emplace_back(10, 9, 0.3165189534192905);
	circles.emplace_back(10, 10, 0.746350855124183);
	result_expected = 17.61768871639577;

	timer.reset();
	result_actual = algorithm(a18, b18, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #18: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a19(1, 1);
	Point b19(9, 9);
	circles.emplace_back(0, 0, 0.3421131402952596);
	circles.emplace_back(0, 1, 0.2485923419008031);
	circles.emplace_back(0, 2, 0.5280581170460209);
	circles.emplace_back(0, 3, 0.3777911490993574);
	circles.emplace_back(0, 4, 0.5712268392322585);
	circles.emplace_back(0, 5, 0.465716153034009);
	circles.emplace_back(0, 6, 0.5022742200409993);
	circles.emplace_back(0, 7, 0.4533322730334475);
	circles.emplace_back(0, 8, 0.1811025996459648);
	circles.emplace_back(0, 9, 0.4658573104301467);
	circles.emplace_back(0, 10, 0.5498559010913595);
	circles.emplace_back(1, 0, 0.4115950326668099);
	circles.emplace_back(1, 2, 0.2229590742615983);
	circles.emplace_back(1, 3, 0.5443150103325024);
	circles.emplace_back(1, 4, 0.4239928669994697);
	circles.emplace_back(1, 5, 0.3928169024409726);
	circles.emplace_back(1, 6, 0.361029899935238);
	circles.emplace_back(1, 7, 0.3829965727636591);
	circles.emplace_back(1, 8, 0.3029564590891823);
	circles.emplace_back(1, 9, 0.1447236075298861);
	circles.emplace_back(1, 10, 0.4167653578100726);
	circles.emplace_back(2, 0, 0.5956444923067465);
	circles.emplace_back(2, 1, 0.2873286571120843);
	circles.emplace_back(2, 2, 0.5141428933711722);
	circles.emplace_back(2, 3, 0.7042449709726497);
	circles.emplace_back(2, 4, 0.4416181763866916);
	circles.emplace_back(2, 5, 0.802504520653747);
	circles.emplace_back(2, 6, 0.2774854826973751);
	circles.emplace_back(2, 7, 0.6224260396091267);
	circles.emplace_back(2, 8, 0.4363553710514679);
	circles.emplace_back(2, 9, 0.4470930680399761);
	circles.emplace_back(2, 10, 0.1132182200672105);
	circles.emplace_back(3, 0, 0.5198531136615202);
	circles.emplace_back(3, 1, 0.436638274253346);
	circles.emplace_back(3, 2, 0.2778415927430615);
	circles.emplace_back(3, 3, 0.1694544038968161);
	circles.emplace_back(3, 4, 0.297453402983956);
	circles.emplace_back(3, 5, 0.7287893366301432);
	circles.emplace_back(3, 6, 0.2717084172880277);
	circles.emplace_back(3, 7, 0.6297863059910014);
	circles.emplace_back(3, 8, 0.3650431249989197);
	circles.emplace_back(3, 9, 0.5979217497864738);
	circles.emplace_back(3, 10, 0.5557090846588835);
	circles.emplace_back(4, 0, 0.430484878574498);
	circles.emplace_back(4, 1, 0.2171697898535058);
	circles.emplace_back(4, 2, 0.4063696220749989);
	circles.emplace_back(4, 3, 0.345160987204872);
	circles.emplace_back(4, 4, 0.2321916488232091);
	circles.emplace_back(4, 5, 0.5439154230756685);
	circles.emplace_back(4, 6, 0.4594228418776765);
	circles.emplace_back(4, 7, 0.5809514330467209);
	circles.emplace_back(4, 8, 0.2992278008954599);
	circles.emplace_back(4, 9, 0.5422857257304713);
	circles.emplace_back(4, 10, 0.5864916283870115);
	circles.emplace_back(5, 0, 0.506454149982892);
	circles.emplace_back(5, 1, 0.2896454454632476);
	circles.emplace_back(5, 2, 0.543810172076337);
	circles.emplace_back(5, 3, 0.6158257698873058);
	circles.emplace_back(5, 4, 0.4747192268958315);
	circles.emplace_back(5, 5, 0.609146076743491);
	circles.emplace_back(5, 6, 0.4239780447212979);
	circles.emplace_back(5, 7, 0.5709135495359078);
	circles.emplace_back(5, 8, 0.3265614926582202);
	circles.emplace_back(5, 9, 0.631991217029281);
	circles.emplace_back(5, 10, 0.3091354072792455);
	circles.emplace_back(6, 0, 0.7666853586444631);
	circles.emplace_back(6, 1, 0.5301723325392231);
	circles.emplace_back(6, 2, 0.6420302487211301);
	circles.emplace_back(6, 3, 0.3464680145261809);
	circles.emplace_back(6, 4, 0.6336469974601641);
	circles.emplace_back(6, 5, 0.5228799421107396);
	circles.emplace_back(6, 6, 0.6969704338582232);
	circles.emplace_back(6, 7, 0.6526951600564643);
	circles.emplace_back(6, 8, 0.3480676634470001);
	circles.emplace_back(6, 9, 0.2456830186536536);
	circles.emplace_back(6, 10, 0.5690141211496665);
	circles.emplace_back(7, 0, 0.3070994614390656);
	circles.emplace_back(7, 1, 0.4963476270670071);
	circles.emplace_back(7, 2, 0.511182890064083);
	circles.emplace_back(7, 3, 0.2649881405057385);
	circles.emplace_back(7, 4, 0.1045175828738138);
	circles.emplace_back(7, 5, 0.5516905950615182);
	circles.emplace_back(7, 6, 0.3955390812596306);
	circles.emplace_back(7, 7, 0.1790903850691393);
	circles.emplace_back(7, 8, 0.4339168953476474);
	circles.emplace_back(7, 9, 0.6912057612324133);
	circles.emplace_back(7, 10, 0.1950733180856332);
	circles.emplace_back(8, 0, 0.3813785807462409);
	circles.emplace_back(8, 1, 0.4981830742908642);
	circles.emplace_back(8, 2, 0.5315645447233691);
	circles.emplace_back(8, 3, 0.6381469687214121);
	circles.emplace_back(8, 4, 0.4951262432383373);
	circles.emplace_back(8, 5, 0.4407436347333714);
	circles.emplace_back(8, 6, 0.2113370158011094);
	circles.emplace_back(8, 7, 0.292936922586523);
	circles.emplace_back(8, 8, 0.5661708225728944);
	circles.emplace_back(8, 9, 0.5946524039609358);
	circles.emplace_back(8, 10, 0.6981330091366544);
	circles.emplace_back(9, 0, 0.7617349067470058);
	circles.emplace_back(9, 1, 0.4773790351347997);
	circles.emplace_back(9, 2, 0.3197599316714331);
	circles.emplace_back(9, 3, 0.3486729245865717);
	circles.emplace_back(9, 4, 0.6023952398216351);
	circles.emplace_back(9, 5, 0.711354383197613);
	circles.emplace_back(9, 6, 0.5435948376310989);
	circles.emplace_back(9, 7, 0.4999132154742256);
	circles.emplace_back(9, 8, 0.7675560233881696);
	circles.emplace_back(9, 10, 0.2145118619548157);
	circles.emplace_back(10, 0, 0.4715810968307778);
	circles.emplace_back(10, 1, 0.619351564371027);
	circles.emplace_back(10, 2, 0.7022587708896025);
	circles.emplace_back(10, 3, 0.165644854051061);
	circles.emplace_back(10, 4, 0.08221626214217394);
	circles.emplace_back(10, 5, 0.5926367463776842);
	circles.emplace_back(10, 6, 0.3905914740404114);
	circles.emplace_back(10, 7, 0.4021092116134241);
	circles.emplace_back(10, 8, 0.3728356244741007);
	circles.emplace_back(10, 9, 0.5766081799054518);
	circles.emplace_back(10, 10, 0.6919801067328081);
	result_expected = 17.21433284181037;

	timer.reset();
	result_actual = algorithm(a19, b19, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #19: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a20(1, 1);
	Point b20(9, 9);
	circles.emplace_back(0, 0, 0.3067495257826522);
	circles.emplace_back(0, 1, 0.3715873104287311);
	circles.emplace_back(0, 2, 0.3958901649573818);
	circles.emplace_back(0, 3, 0.1577535664429888);
	circles.emplace_back(0, 4, 0.5086925837444142);
	circles.emplace_back(0, 5, 0.2812433174578473);
	circles.emplace_back(0, 6, 0.6111658089095726);
	circles.emplace_back(0, 7, 0.4686070531373843);
	circles.emplace_back(0, 8, 0.4011330132605508);
	circles.emplace_back(0, 9, 0.4704714865190908);
	circles.emplace_back(0, 10, 0.33725563979242);
	circles.emplace_back(1, 0, 0.3835888856789097);
	circles.emplace_back(1, 2, 0.4292361147003248);
	circles.emplace_back(1, 3, 0.5781934122322127);
	circles.emplace_back(1, 4, 0.539125907071866);
	circles.emplace_back(1, 5, 0.5412357557332143);
	circles.emplace_back(1, 6, 0.5512828805716709);
	circles.emplace_back(1, 7, 0.1466532905353233);
	circles.emplace_back(1, 8, 0.3839515699306503);
	circles.emplace_back(1, 9, 0.5034814191749319);
	circles.emplace_back(1, 10, 0.5261822025524452);
	circles.emplace_back(2, 0, 0.5488227038411423);
	circles.emplace_back(2, 1, 0.4773589730495587);
	circles.emplace_back(2, 2, 0.4829638249939308);
	circles.emplace_back(2, 3, 0.6304752660216764);
	circles.emplace_back(2, 4, 0.6257663436932489);
	circles.emplace_back(2, 5, 0.2619732098886743);
	circles.emplace_back(2, 6, 0.2443556817015633);
	circles.emplace_back(2, 7, 0.3579571320908144);
	circles.emplace_back(2, 8, 0.4995936709223315);
	circles.emplace_back(2, 9, 0.406395173468627);
	circles.emplace_back(2, 10, 0.7203434612369165);
	circles.emplace_back(3, 0, 0.6050405071349815);
	circles.emplace_back(3, 1, 0.5776215133024379);
	circles.emplace_back(3, 2, 0.4627332946518436);
	circles.emplace_back(3, 3, 0.2328798403730616);
	circles.emplace_back(3, 4, 0.5949866998242214);
	circles.emplace_back(3, 5, 0.6133726007072254);
	circles.emplace_back(3, 6, 0.5208149679237977);
	circles.emplace_back(3, 7, 0.4603345796233043);
	circles.emplace_back(3, 8, 0.4441287656547502);
	circles.emplace_back(3, 9, 0.2400350377662107);
	circles.emplace_back(3, 10, 0.4372026646742597);
	circles.emplace_back(4, 0, 0.5411688396474347);
	circles.emplace_back(4, 1, 0.6232118389802054);
	circles.emplace_back(4, 2, 0.7420077140210196);
	circles.emplace_back(4, 3, 0.5671397339785471);
	circles.emplace_back(4, 4, 0.454757935157977);
	circles.emplace_back(4, 5, 0.5169756525428966);
	circles.emplace_back(4, 6, 0.4801566515816376);
	circles.emplace_back(4, 7, 0.2775508908787742);
	circles.emplace_back(4, 8, 0.1699875263264403);
	circles.emplace_back(4, 9, 0.5351042445050552);
	circles.emplace_back(4, 10, 0.5364072902826592);
	circles.emplace_back(5, 0, 0.2692223921651021);
	circles.emplace_back(5, 1, 0.4022482476895675);
	circles.emplace_back(5, 2, 0.6776678529800847);
	circles.emplace_back(5, 3, 0.3932977103395388);
	circles.emplace_back(5, 4, 0.4862868996569887);
	circles.emplace_back(5, 5, 0.1694537745555863);
	circles.emplace_back(5, 6, 0.3081819980638101);
	circles.emplace_back(5, 7, 0.5141177925048396);
	circles.emplace_back(5, 8, 0.5411380309844389);
	circles.emplace_back(5, 9, 0.2877073269104585);
	circles.emplace_back(5, 10, 0.4374087513657287);
	circles.emplace_back(6, 0, 0.6392593157244846);
	circles.emplace_back(6, 1, 0.4328995978692546);
	circles.emplace_back(6, 2, 0.1972416108241305);
	circles.emplace_back(6, 3, 0.6710251930402592);
	circles.emplace_back(6, 4, 0.464401992294006);
	circles.emplace_back(6, 5, 0.6875745319062844);
	circles.emplace_back(6, 6, 0.5592571973567828);
	circles.emplace_back(6, 7, 0.5242840563179925);
	circles.emplace_back(6, 8, 0.2161604405147955);
	circles.emplace_back(6, 9, 0.2979984978446737);
	circles.emplace_back(6, 10, 0.2142843389650807);
	circles.emplace_back(7, 0, 0.5567915595369414);
	circles.emplace_back(7, 1, 0.2908170948503539);
	circles.emplace_back(7, 2, 0.2917231943691149);
	circles.emplace_back(7, 3, 0.2426932234084234);
	circles.emplace_back(7, 4, 0.4305274256737903);
	circles.emplace_back(7, 5, 0.4717660535825416);
	circles.emplace_back(7, 6, 0.5049543423810974);
	circles.emplace_back(7, 7, 0.4179776651551947);
	circles.emplace_back(7, 8, 0.1442320893751457);
	circles.emplace_back(7, 9, 0.2912928639678284);
	circles.emplace_back(7, 10, 0.3906693607801571);
	circles.emplace_back(8, 0, 0.4934372342890128);
	circles.emplace_back(8, 1, 0.347286091488786);
	circles.emplace_back(8, 2, 0.4523152448935434);
	circles.emplace_back(8, 3, 0.4390397297451272);
	circles.emplace_back(8, 4, 0.3128828229149803);
	circles.emplace_back(8, 5, 0.4862066610949114);
	circles.emplace_back(8, 6, 0.275709747034125);
	circles.emplace_back(8, 7, 0.3382830415153876);
	circles.emplace_back(8, 8, 0.3859906490659341);
	circles.emplace_back(8, 9, 0.5868864850373938);
	circles.emplace_back(8, 10, 0.3888493505073711);
	circles.emplace_back(9, 0, 0.6540697386721149);
	circles.emplace_back(9, 1, 0.8189296981086954);
	circles.emplace_back(9, 2, 0.3256996649550274);
	circles.emplace_back(9, 3, 0.2209770000306889);
	circles.emplace_back(9, 4, 0.2556095399195328);
	circles.emplace_back(9, 5, 0.54088760165032);
	circles.emplace_back(9, 6, 0.2925998618127778);
	circles.emplace_back(9, 7, 0.4210400775773451);
	circles.emplace_back(9, 8, 0.4665425533661618);
	circles.emplace_back(9, 10, 0.4171199539443478);
	circles.emplace_back(10, 0, 0.5993356279330327);
	circles.emplace_back(10, 1, 0.3636108125327155);
	circles.emplace_back(10, 2, 0.3687600773060694);
	circles.emplace_back(10, 3, 0.4891480657970533);
	circles.emplace_back(10, 4, 0.2359079265268519);
	circles.emplace_back(10, 5, 0.5585176293505355);
	circles.emplace_back(10, 6, 0.5372800885001198);
	circles.emplace_back(10, 7, 0.3327301559736952);
	circles.emplace_back(10, 8, 0.4283948387252167);
	circles.emplace_back(10, 9, 0.42981243270915);
	circles.emplace_back(10, 10, 0.5343024179572239);
	result_expected = 15.11552899882889;

	timer.reset();
	result_actual = algorithm(a20, b20, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #20: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();






	Point a21(1, 1);
	Point b21(9, 9);
	circles.emplace_back(0, 0, 0.5742309801047668);
	circles.emplace_back(0, 1, 0.4012684581102803);
	circles.emplace_back(0, 2, 0.6796988301677629);
	circles.emplace_back(0, 3, 0.2405686142155901);
	circles.emplace_back(0, 4, 0.4560148970922455);
	circles.emplace_back(0, 5, 0.1973289727466181);
	circles.emplace_back(0, 6, 0.4030462923226878);
	circles.emplace_back(0, 7, 0.5521514941239729);
	circles.emplace_back(0, 8, 0.2914873730158433);
	circles.emplace_back(0, 9, 0.758380934712477);
	circles.emplace_back(0, 10, 0.5681152504635975);
	circles.emplace_back(1, 0, 0.6207993811229243);
	circles.emplace_back(1, 2, 0.4004099225392565);
	circles.emplace_back(1, 3, 0.6197767171310261);
	circles.emplace_back(1, 4, 0.4291181317297741);
	circles.emplace_back(1, 5, 0.365960031026043);
	circles.emplace_back(1, 6, 0.5651134878164157);
	circles.emplace_back(1, 7, 0.7219521587016061);
	circles.emplace_back(1, 8, 0.5862413317663595);
	circles.emplace_back(1, 9, 0.6366092453012243);
	circles.emplace_back(1, 10, 0.598235254897736);
	circles.emplace_back(2, 0, 0.1920793957309797);
	circles.emplace_back(2, 1, 0.7587531248806044);
	circles.emplace_back(2, 2, 0.1510091718519107);
	circles.emplace_back(2, 3, 0.3626039076363668);
	circles.emplace_back(2, 4, 0.2989618816645816);
	circles.emplace_back(2, 5, 0.2868225116981193);
	circles.emplace_back(2, 6, 0.4925212932983413);
	circles.emplace_back(2, 7, 0.4338983190944418);
	circles.emplace_back(2, 8, 0.6342965941177681);
	circles.emplace_back(2, 9, 0.5276740043191239);
	circles.emplace_back(2, 10, 0.5895991027588025);
	circles.emplace_back(3, 0, 0.2467046804493293);
	circles.emplace_back(3, 1, 0.2234284294070676);
	circles.emplace_back(3, 2, 0.3617033489746973);
	circles.emplace_back(3, 3, 0.3580854671308771);
	circles.emplace_back(3, 4, 0.3145970673998817);
	circles.emplace_back(3, 5, 0.5187217845814303);
	circles.emplace_back(3, 6, 0.4741791861830279);
	circles.emplace_back(3, 7, 0.333939677872695);
	circles.emplace_back(3, 8, 0.2648664440726861);
	circles.emplace_back(3, 9, 0.4786743269534781);
	circles.emplace_back(3, 10, 0.4281556484056637);
	circles.emplace_back(4, 0, 0.4745191892841831);
	circles.emplace_back(4, 1, 0.4785231044283136);
	circles.emplace_back(4, 2, 0.4858979511307552);
	circles.emplace_back(4, 3, 0.2942208952037618);
	circles.emplace_back(4, 4, 0.2565410442883149);
	circles.emplace_back(4, 5, 0.2761975511675701);
	circles.emplace_back(4, 6, 0.2070919235469773);
	circles.emplace_back(4, 7, 0.1527065858943388);
	circles.emplace_back(4, 8, 0.2488479877123609);
	circles.emplace_back(4, 9, 0.4405648121377453);
	circles.emplace_back(4, 10, 0.2481332144932821);
	circles.emplace_back(5, 0, 0.5339832897065208);
	circles.emplace_back(5, 1, 0.6881042670691385);
	circles.emplace_back(5, 2, 0.6159171942388638);
	circles.emplace_back(5, 3, 0.5074090176494792);
	circles.emplace_back(5, 4, 0.4124668334377929);
	circles.emplace_back(5, 5, 0.2355461208382621);
	circles.emplace_back(5, 6, 0.5755104748299346);
	circles.emplace_back(5, 7, 0.2805164571153);
	circles.emplace_back(5, 8, 0.6199605866102501);
	circles.emplace_back(5, 9, 0.3429119542473927);
	circles.emplace_back(5, 10, 0.6973085306352004);
	circles.emplace_back(6, 0, 0.5194544819416478);
	circles.emplace_back(6, 1, 0.5939586841268465);
	circles.emplace_back(6, 2, 0.4056772025534883);
	circles.emplace_back(6, 3, 0.4387514041503891);
	circles.emplace_back(6, 4, 0.3994329481618479);
	circles.emplace_back(6, 5, 0.5265351864276454);
	circles.emplace_back(6, 6, 0.5317188818240538);
	circles.emplace_back(6, 7, 0.6511718075489625);
	circles.emplace_back(6, 8, 0.2964238883228972);
	circles.emplace_back(6, 9, 0.4294441771460697);
	circles.emplace_back(6, 10, 0.403534827218391);
	circles.emplace_back(7, 0, 0.7244850640883669);
	circles.emplace_back(7, 1, 0.6285799685167148);
	circles.emplace_back(7, 2, 0.3810557982651517);
	circles.emplace_back(7, 3, 0.5621426187688484);
	circles.emplace_back(7, 4, 0.302777487016283);
	circles.emplace_back(7, 5, 0.5646451329113915);
	circles.emplace_back(7, 6, 0.3707532227737829);
	circles.emplace_back(7, 7, 0.2907831946620718);
	circles.emplace_back(7, 8, 0.4614181959768757);
	circles.emplace_back(7, 9, 0.45248243578244);
	circles.emplace_back(7, 10, 0.7064155648229643);
	circles.emplace_back(8, 0, 0.2265541520202532);
	circles.emplace_back(8, 1, 0.2863193709170446);
	circles.emplace_back(8, 2, 0.5708440610440447);
	circles.emplace_back(8, 3, 0.5006117273820564);
	circles.emplace_back(8, 4, 0.2780977351823822);
	circles.emplace_back(8, 5, 0.2459699434926733);
	circles.emplace_back(8, 6, 0.3575085292803123);
	circles.emplace_back(8, 7, 0.3011301873950288);
	circles.emplace_back(8, 8, 0.3774685114854947);
	circles.emplace_back(8, 9, 0.1968677259748801);
	circles.emplace_back(8, 10, 0.316910092276521);
	circles.emplace_back(9, 0, 0.3814697184367105);
	circles.emplace_back(9, 1, 0.3443057345459238);
	circles.emplace_back(9, 2, 0.1129749776562676);
	circles.emplace_back(9, 3, 0.260385315050371);
	circles.emplace_back(9, 4, 0.4569160508690402);
	circles.emplace_back(9, 5, 0.3904353950405493);
	circles.emplace_back(9, 6, 0.3798224087571725);
	circles.emplace_back(9, 7, 0.2821618453832343);
	circles.emplace_back(9, 8, 0.1418294694973156);
	circles.emplace_back(9, 10, 0.6430269589880481);
	circles.emplace_back(10, 0, 0.4438866218319162);
	circles.emplace_back(10, 1, 0.524214370851405);
	circles.emplace_back(10, 2, 0.5137683487264439);
	circles.emplace_back(10, 3, 0.6144297935301438);
	circles.emplace_back(10, 4, 0.4578659906750545);
	circles.emplace_back(10, 5, 0.4331127633573487);
	circles.emplace_back(10, 6, 0.1000736252171919);
	circles.emplace_back(10, 7, 0.2968142802128568);
	circles.emplace_back(10, 8, 0.5124799767276272);
	circles.emplace_back(10, 9, 0.4619874111609533);
	circles.emplace_back(10, 10, 0.6525392080424354);
	result_expected = 11.91428396991884;

	timer.reset();
	result_actual = algorithm(a21, b21, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #21: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a22(1, 1);
	Point b22(9, 9);
	circles.emplace_back(0, 0, 0.5097426157677546);
	circles.emplace_back(0, 1, 0.2954168829834088);
	circles.emplace_back(0, 2, 0.3207367384107783);
	circles.emplace_back(0, 3, 0.7257933263434097);
	circles.emplace_back(0, 4, 0.5787943003932013);
	circles.emplace_back(0, 5, 0.6680550453951583);
	circles.emplace_back(0, 6, 0.6276019121753051);
	circles.emplace_back(0, 7, 0.5250158144859597);
	circles.emplace_back(0, 8, 0.2733713135356083);
	circles.emplace_back(0, 9, 0.4005824617808685);
	circles.emplace_back(0, 10, 0.5652337369741872);
	circles.emplace_back(1, 0, 0.5386163347167894);
	circles.emplace_back(1, 2, 0.4818079771706834);
	circles.emplace_back(1, 3, 0.3561398582300171);
	circles.emplace_back(1, 4, 0.4943767368094996);
	circles.emplace_back(1, 5, 0.3214985373197123);
	circles.emplace_back(1, 6, 0.2519105065846816);
	circles.emplace_back(1, 7, 0.5646121930098161);
	circles.emplace_back(1, 8, 0.3282954246969894);
	circles.emplace_back(1, 9, 0.3445351582719013);
	circles.emplace_back(1, 10, 0.2750512486556545);
	circles.emplace_back(2, 0, 0.3766935979714617);
	circles.emplace_back(2, 1, 0.5210677596973255);
	circles.emplace_back(2, 2, 0.3758790544001385);
	circles.emplace_back(2, 3, 0.5419426076347008);
	circles.emplace_back(2, 4, 0.3388507574563846);
	circles.emplace_back(2, 5, 0.6728707914473488);
	circles.emplace_back(2, 6, 0.3097351760370657);
	circles.emplace_back(2, 7, 0.748215658427216);
	circles.emplace_back(2, 8, 0.3798097247024998);
	circles.emplace_back(2, 9, 0.5053834921913222);
	circles.emplace_back(2, 10, 0.5082184771774336);
	circles.emplace_back(3, 0, 0.4779284473741427);
	circles.emplace_back(3, 1, 0.7491911757504567);
	circles.emplace_back(3, 2, 0.6104317763121798);
	circles.emplace_back(3, 3, 0.3719227631343529);
	circles.emplace_back(3, 4, 0.5431289805332199);
	circles.emplace_back(3, 5, 0.2989191008498892);
	circles.emplace_back(3, 6, 0.5250007073627785);
	circles.emplace_back(3, 7, 0.604825475695543);
	circles.emplace_back(3, 8, 0.4075978994602337);
	circles.emplace_back(3, 9, 0.3480279333656653);
	circles.emplace_back(3, 10, 0.2357388925971463);
	circles.emplace_back(4, 0, 0.6891534157795831);
	circles.emplace_back(4, 1, 0.5728958444902673);
	circles.emplace_back(4, 2, 0.3214931161841377);
	circles.emplace_back(4, 3, 0.5660800650017336);
	circles.emplace_back(4, 4, 0.3358344035921618);
	circles.emplace_back(4, 5, 0.3548405055189505);
	circles.emplace_back(4, 6, 0.6037101056193933);
	circles.emplace_back(4, 7, 0.4491068528266624);
	circles.emplace_back(4, 8, 0.3261598762823268);
	circles.emplace_back(4, 9, 0.52853836028371);
	circles.emplace_back(4, 10, 0.2972468128195032);
	circles.emplace_back(5, 0, 0.6392817366169765);
	circles.emplace_back(5, 1, 0.4102834230987355);
	circles.emplace_back(5, 2, 0.3700961001450196);
	circles.emplace_back(5, 3, 0.5274944826727733);
	circles.emplace_back(5, 4, 0.466170193743892);
	circles.emplace_back(5, 5, 0.4781802580459043);
	circles.emplace_back(5, 6, 0.3731367433676496);
	circles.emplace_back(5, 7, 0.6838420102139935);
	circles.emplace_back(5, 8, 0.4832810304360464);
	circles.emplace_back(5, 9, 0.2686926300404593);
	circles.emplace_back(5, 10, 0.1682454359019175);
	circles.emplace_back(6, 0, 0.6379986945306882);
	circles.emplace_back(6, 1, 0.3151489013107494);
	circles.emplace_back(6, 2, 0.8322861705673859);
	circles.emplace_back(6, 3, 0.2234699396649376);
	circles.emplace_back(6, 4, 0.5300904301693663);
	circles.emplace_back(6, 5, 0.6557840164052322);
	circles.emplace_back(6, 6, 0.6131421788362786);
	circles.emplace_back(6, 7, 0.4540008083218708);
	circles.emplace_back(6, 8, 0.6631543360417709);
	circles.emplace_back(6, 9, 0.2216140357078984);
	circles.emplace_back(6, 10, 0.4662108444375917);
	circles.emplace_back(7, 0, 0.1191562505671754);
	circles.emplace_back(7, 1, 0.2966568218311295);
	circles.emplace_back(7, 2, 0.2120431511895731);
	circles.emplace_back(7, 3, 0.5748504074988886);
	circles.emplace_back(7, 4, 0.5347966809058562);
	circles.emplace_back(7, 5, 0.5796600918984041);
	circles.emplace_back(7, 6, 0.1807533563347533);
	circles.emplace_back(7, 7, 0.5846772563410922);
	circles.emplace_back(7, 8, 0.5792939579347148);
	circles.emplace_back(7, 9, 0.5142620866885409);
	circles.emplace_back(7, 10, 0.570872903172858);
	circles.emplace_back(8, 0, 0.3192519626347348);
	circles.emplace_back(8, 1, 0.6211803101236001);
	circles.emplace_back(8, 2, 0.7899348616367206);
	circles.emplace_back(8, 3, 0.6171369468094781);
	circles.emplace_back(8, 4, 0.3932262540562078);
	circles.emplace_back(8, 5, 0.3466019490966573);
	circles.emplace_back(8, 6, 0.7793864035746082);
	circles.emplace_back(8, 7, 0.5681653774576262);
	circles.emplace_back(8, 8, 0.6885759244440123);
	circles.emplace_back(8, 9, 0.414702370413579);
	circles.emplace_back(8, 10, 0.2365708846366033);
	circles.emplace_back(9, 0, 0.5319828399689868);
	circles.emplace_back(9, 1, 0.5095446814550086);
	circles.emplace_back(9, 2, 0.6190603418508545);
	circles.emplace_back(9, 3, 0.5874723536660894);
	circles.emplace_back(9, 4, 0.6979059408651664);
	circles.emplace_back(9, 5, 0.4819239317206666);
	circles.emplace_back(9, 6, 0.5833075791830197);
	circles.emplace_back(9, 7, 0.5542868651216849);
	circles.emplace_back(9, 8, 0.3379226428689435);
	circles.emplace_back(9, 10, 0.7122935035033151);
	circles.emplace_back(10, 0, 0.4690511094639078);
	circles.emplace_back(10, 1, 0.5036280454834923);
	circles.emplace_back(10, 2, 0.3406888469355181);
	circles.emplace_back(10, 3, 0.3728483068523928);
	circles.emplace_back(10, 4, 0.5242253218078986);
	circles.emplace_back(10, 5, 0.3593810971593484);
	circles.emplace_back(10, 6, 0.3812671617837622);
	circles.emplace_back(10, 7, 0.4274359312606975);
	circles.emplace_back(10, 8, 0.5499987056711688);
	circles.emplace_back(10, 9, 0.3708302398910746);
	circles.emplace_back(10, 10, 0.27973286092747);
	result_expected = 18.11294822544123;

	timer.reset();
	result_actual = algorithm(a22, b22, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #22: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a23(1, 1);
	Point b23(9, 9);
	circles.emplace_back(0, 0, 0.2644301808206365);
	circles.emplace_back(0, 1, 0.5143602766329423);
	circles.emplace_back(0, 2, 0.3766845896607265);
	circles.emplace_back(0, 3, 0.5517720272066071);
	circles.emplace_back(0, 4, 0.4520655468804762);
	circles.emplace_back(0, 5, 0.6905106896767392);
	circles.emplace_back(0, 6, 0.5556274750968441);
	circles.emplace_back(0, 7, 0.3043968848185614);
	circles.emplace_back(0, 8, 0.5818576182005927);
	circles.emplace_back(0, 9, 0.1481830399716273);
	circles.emplace_back(0, 10, 0.5040141913807019);
	circles.emplace_back(1, 0, 0.6799033188493923);
	circles.emplace_back(1, 2, 0.5157344286097213);
	circles.emplace_back(1, 3, 0.3760183511534705);
	circles.emplace_back(1, 4, 0.5313431916525587);
	circles.emplace_back(1, 5, 0.6011955823050812);
	circles.emplace_back(1, 6, 0.3025037421612069);
	circles.emplace_back(1, 7, 0.2631207511061802);
	circles.emplace_back(1, 8, 0.5141257159179077);
	circles.emplace_back(1, 9, 0.5216031906427815);
	circles.emplace_back(1, 10, 0.4792812757892534);
	circles.emplace_back(2, 0, 0.3179173352429643);
	circles.emplace_back(2, 1, 0.4987788574537262);
	circles.emplace_back(2, 2, 0.3323150038020685);
	circles.emplace_back(2, 3, 0.7235048594651744);
	circles.emplace_back(2, 4, 0.2524477172875777);
	circles.emplace_back(2, 5, 0.4941670667147264);
	circles.emplace_back(2, 6, 0.5305554957361892);
	circles.emplace_back(2, 7, 0.3711595338536426);
	circles.emplace_back(2, 8, 0.6102082675555721);
	circles.emplace_back(2, 9, 0.6444170927396043);
	circles.emplace_back(2, 10, 0.6016282114433125);
	circles.emplace_back(3, 0, 0.5668385854689404);
	circles.emplace_back(3, 1, 0.3656760387355462);
	circles.emplace_back(3, 2, 0.422631362057291);
	circles.emplace_back(3, 3, 0.4179514114977792);
	circles.emplace_back(3, 4, 0.4612655193312094);
	circles.emplace_back(3, 5, 0.2736373791703954);
	circles.emplace_back(3, 6, 0.4361247950932011);
	circles.emplace_back(3, 7, 0.408210904081352);
	circles.emplace_back(3, 8, 0.4219019691227004);
	circles.emplace_back(3, 9, 0.2964462336385623);
	circles.emplace_back(3, 10, 0.6838100600754842);
	circles.emplace_back(4, 0, 0.2997550645144656);
	circles.emplace_back(4, 1, 0.1722665448440239);
	circles.emplace_back(4, 2, 0.2873371316352859);
	circles.emplace_back(4, 3, 0.3563562644412741);
	circles.emplace_back(4, 4, 0.2873570422874763);
	circles.emplace_back(4, 5, 0.3255896179703995);
	circles.emplace_back(4, 6, 0.3579178631538525);
	circles.emplace_back(4, 7, 0.2197460837429389);
	circles.emplace_back(4, 8, 0.5314691555919125);
	circles.emplace_back(4, 9, 0.3284290441079065);
	circles.emplace_back(4, 10, 0.2079668419668451);
	circles.emplace_back(5, 0, 0.6728563280543313);
	circles.emplace_back(5, 1, 0.4390944733517244);
	circles.emplace_back(5, 2, 0.3798718231497332);
	circles.emplace_back(5, 3, 0.4456601564073935);
	circles.emplace_back(5, 4, 0.719686945877038);
	circles.emplace_back(5, 5, 0.2304005847545341);
	circles.emplace_back(5, 6, 0.6419466969324276);
	circles.emplace_back(5, 7, 0.3763533076504245);
	circles.emplace_back(5, 8, 0.5468634655466303);
	circles.emplace_back(5, 9, 0.8442005562828854);
	circles.emplace_back(5, 10, 0.5068726843921467);
	circles.emplace_back(6, 0, 0.6880426354939118);
	circles.emplace_back(6, 1, 0.647037874138914);
	circles.emplace_back(6, 2, 0.4854260762454942);
	circles.emplace_back(6, 3, 0.5367685542209074);
	circles.emplace_back(6, 4, 0.4116314316401258);
	circles.emplace_back(6, 5, 0.4788129338761791);
	circles.emplace_back(6, 6, 0.3677177868084982);
	circles.emplace_back(6, 7, 0.2414482350228354);
	circles.emplace_back(6, 8, 0.4841257404768839);
	circles.emplace_back(6, 9, 0.40381493603345);
	circles.emplace_back(6, 10, 0.254257803526707);
	circles.emplace_back(7, 0, 0.6099271629704163);
	circles.emplace_back(7, 1, 0.2928848473588004);
	circles.emplace_back(7, 2, 0.2915398923447355);
	circles.emplace_back(7, 3, 0.249969422374852);
	circles.emplace_back(7, 4, 0.3612645669607445);
	circles.emplace_back(7, 5, 0.4290514543885365);
	circles.emplace_back(7, 6, 0.6325981639092788);
	circles.emplace_back(7, 7, 0.5482090142788365);
	circles.emplace_back(7, 8, 0.5303666912717745);
	circles.emplace_back(7, 9, 0.4282865436980501);
	circles.emplace_back(7, 10, 0.4509825275978073);
	circles.emplace_back(8, 0, 0.2850751071469858);
	circles.emplace_back(8, 1, 0.3543759557185694);
	circles.emplace_back(8, 2, 0.226933928229846);
	circles.emplace_back(8, 3, 0.2559846799587831);
	circles.emplace_back(8, 4, 0.7044596554012968);
	circles.emplace_back(8, 5, 0.2752710533095524);
	circles.emplace_back(8, 6, 0.1117394900182262);
	circles.emplace_back(8, 7, 0.4243851786246523);
	circles.emplace_back(8, 8, 0.5869664970086887);
	circles.emplace_back(8, 9, 0.4243029854027554);
	circles.emplace_back(8, 10, 0.3912501059705392);
	circles.emplace_back(9, 0, 0.5535418212180957);
	circles.emplace_back(9, 1, 0.2458219980122521);
	circles.emplace_back(9, 2, 0.2038920343620703);
	circles.emplace_back(9, 3, 0.6670172611484304);
	circles.emplace_back(9, 4, 0.3760014617582783);
	circles.emplace_back(9, 5, 0.5429028845624998);
	circles.emplace_back(9, 6, 0.5326106737134978);
	circles.emplace_back(9, 7, 0.5327303495490924);
	circles.emplace_back(9, 8, 0.5762602645670994);
	circles.emplace_back(9, 10, 0.3280062624486163);
	circles.emplace_back(10, 0, 0.5688774158013984);
	circles.emplace_back(10, 1, 0.6794046623865142);
	circles.emplace_back(10, 2, 0.2002973956754431);
	circles.emplace_back(10, 3, 0.654486824129708);
	circles.emplace_back(10, 4, 0.3789865969447419);
	circles.emplace_back(10, 5, 0.5347490638727322);
	circles.emplace_back(10, 6, 0.3985071517294272);
	circles.emplace_back(10, 7, 0.5743862432660535);
	circles.emplace_back(10, 8, 0.4650991000933573);
	circles.emplace_back(10, 9, 0.7148383544990793);
	circles.emplace_back(10, 10, 0.6926545263966545);
	result_expected = 15.70633562298226;

	timer.reset();
	result_actual = algorithm(a23, b23, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #23: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a24(1, 1);
	Point b24(9, 9);
	circles.emplace_back(0, 0, 0.3661797567503527);
	circles.emplace_back(0, 1, 0.618819014984183);
	circles.emplace_back(0, 2, 0.4162153218174353);
	circles.emplace_back(0, 3, 0.2074792142724618);
	circles.emplace_back(0, 4, 0.2982649342389777);
	circles.emplace_back(0, 5, 0.415981235797517);
	circles.emplace_back(0, 6, 0.4265474787214771);
	circles.emplace_back(0, 7, 0.5575730522861704);
	circles.emplace_back(0, 8, 0.2813176351832226);
	circles.emplace_back(0, 9, 0.5182749963132665);
	circles.emplace_back(0, 10, 0.3819634892279282);
	circles.emplace_back(1, 0, 0.330155898607336);
	circles.emplace_back(1, 2, 0.2126401533605531);
	circles.emplace_back(1, 3, 0.4973283425671979);
	circles.emplace_back(1, 4, 0.3491942817578092);
	circles.emplace_back(1, 5, 0.3543749490519986);
	circles.emplace_back(1, 6, 0.3656265489058569);
	circles.emplace_back(1, 7, 0.4468785430071875);
	circles.emplace_back(1, 8, 0.4606438499176875);
	circles.emplace_back(1, 9, 0.3977524909889326);
	circles.emplace_back(1, 10, 0.4274701678426936);
	circles.emplace_back(2, 0, 0.5986534361494705);
	circles.emplace_back(2, 1, 0.2805147407809273);
	circles.emplace_back(2, 2, 0.4804070947458967);
	circles.emplace_back(2, 3, 0.4382383491145447);
	circles.emplace_back(2, 4, 0.5075887157348916);
	circles.emplace_back(2, 5, 0.3301132306689397);
	circles.emplace_back(2, 6, 0.6476732425158843);
	circles.emplace_back(2, 7, 0.4344393191160634);
	circles.emplace_back(2, 8, 0.4220061533851549);
	circles.emplace_back(2, 9, 0.5504591884324327);
	circles.emplace_back(2, 10, 0.6917443947633728);
	circles.emplace_back(3, 0, 0.550206273724325);
	circles.emplace_back(3, 1, 0.4043777587590739);
	circles.emplace_back(3, 2, 0.2303256262326613);
	circles.emplace_back(3, 3, 0.5629644941305741);
	circles.emplace_back(3, 4, 0.7792236478300765);
	circles.emplace_back(3, 5, 0.7183008772088214);
	circles.emplace_back(3, 6, 0.4778329378226772);
	circles.emplace_back(3, 7, 0.5613929068436846);
	circles.emplace_back(3, 8, 0.3505205723689869);
	circles.emplace_back(3, 9, 0.2473092249361798);
	circles.emplace_back(3, 10, 0.563722824328579);
	circles.emplace_back(4, 0, 0.5492678016191348);
	circles.emplace_back(4, 1, 0.721256518852897);
	circles.emplace_back(4, 2, 0.3611448616487905);
	circles.emplace_back(4, 3, 0.6144369075307622);
	circles.emplace_back(4, 4, 0.5749929660698399);
	circles.emplace_back(4, 5, 0.4396241314010694);
	circles.emplace_back(4, 6, 0.1951161007164046);
	circles.emplace_back(4, 7, 0.1831250306451693);
	circles.emplace_back(4, 8, 0.3492730606114492);
	circles.emplace_back(4, 9, 0.2809942462714389);
	circles.emplace_back(4, 10, 0.3581663568271324);
	circles.emplace_back(5, 0, 0.3767082466045394);
	circles.emplace_back(5, 1, 0.2640223098685965);
	circles.emplace_back(5, 2, 0.6104280988918617);
	circles.emplace_back(5, 3, 0.4352789311436936);
	circles.emplace_back(5, 4, 0.5671214938396588);
	circles.emplace_back(5, 5, 0.49467163158115);
	circles.emplace_back(5, 6, 0.3746817183913663);
	circles.emplace_back(5, 7, 0.3998427339596674);
	circles.emplace_back(5, 8, 0.6648609595606103);
	circles.emplace_back(5, 9, 0.5764992030104622);
	circles.emplace_back(5, 10, 0.3768275096314028);
	circles.emplace_back(6, 0, 0.6016039448557421);
	circles.emplace_back(6, 1, 0.282961130538024);
	circles.emplace_back(6, 2, 0.1956094648456201);
	circles.emplace_back(6, 3, 0.4366180227370933);
	circles.emplace_back(6, 4, 0.5458286103559657);
	circles.emplace_back(6, 5, 0.6695265313843265);
	circles.emplace_back(6, 6, 0.2851855626096949);
	circles.emplace_back(6, 7, 0.2897169101284817);
	circles.emplace_back(6, 8, 0.4293011790839955);
	circles.emplace_back(6, 9, 0.4369431503349915);
	circles.emplace_back(6, 10, 0.3676402255659923);
	circles.emplace_back(7, 0, 0.4289220710517839);
	circles.emplace_back(7, 1, 0.5487839744193479);
	circles.emplace_back(7, 2, 0.2658945525297895);
	circles.emplace_back(7, 3, 0.5332900831243023);
	circles.emplace_back(7, 4, 0.7405059836106375);
	circles.emplace_back(7, 5, 0.447562604653649);
	circles.emplace_back(7, 6, 0.4123076807940378);
	circles.emplace_back(7, 7, 0.3961784187471494);
	circles.emplace_back(7, 8, 0.3387982242973521);
	circles.emplace_back(7, 9, 0.4157023106468841);
	circles.emplace_back(7, 10, 0.1953533439198509);
	circles.emplace_back(8, 0, 0.7176713613560423);
	circles.emplace_back(8, 1, 0.3521351750241593);
	circles.emplace_back(8, 2, 0.6096402509836479);
	circles.emplace_back(8, 3, 0.6946263924473897);
	circles.emplace_back(8, 4, 0.3384525142377242);
	circles.emplace_back(8, 5, 0.4633019176544622);
	circles.emplace_back(8, 6, 0.4067387246293947);
	circles.emplace_back(8, 7, 0.3346305819461122);
	circles.emplace_back(8, 8, 0.4095410214504227);
	circles.emplace_back(8, 9, 0.5575913160340861);
	circles.emplace_back(8, 10, 0.7604243310866877);
	circles.emplace_back(9, 0, 0.4846931237960234);
	circles.emplace_back(9, 1, 0.1629580717300996);
	circles.emplace_back(9, 2, 0.681605285522528);
	circles.emplace_back(9, 3, 0.4715380680514499);
	circles.emplace_back(9, 4, 0.5524339234689251);
	circles.emplace_back(9, 5, 0.4126668398967013);
	circles.emplace_back(9, 6, 0.4659232500242069);
	circles.emplace_back(9, 7, 0.2415213665692136);
	circles.emplace_back(9, 8, 0.2989145063096657);
	circles.emplace_back(9, 10, 0.5264108657604083);
	circles.emplace_back(10, 0, 0.2147627865197137);
	circles.emplace_back(10, 1, 0.6230630636913702);
	circles.emplace_back(10, 2, 0.2535916308173909);
	circles.emplace_back(10, 3, 0.5590758705278859);
	circles.emplace_back(10, 4, 0.615757457097061);
	circles.emplace_back(10, 5, 0.5338323126314207);
	circles.emplace_back(10, 6, 0.2572005894267931);
	circles.emplace_back(10, 7, 0.2882000107085332);
	circles.emplace_back(10, 8, 0.5729768284829333);
	circles.emplace_back(10, 9, 0.1489224304212257);
	circles.emplace_back(10, 10, 0.5106931967893615);
	result_expected = 15.16885571581733;

	timer.reset();
	result_actual = algorithm(a24, b24, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #24: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a25(1, 1);
	Point b25(9, 9);
	circles.emplace_back(0, 0, 0.2422575695207342);
	circles.emplace_back(0, 1, 0.6163136790739372);
	circles.emplace_back(0, 2, 0.4376306830672547);
	circles.emplace_back(0, 3, 0.6583554655546322);
	circles.emplace_back(0, 4, 0.662341085798107);
	circles.emplace_back(0, 5, 0.5903633934678509);
	circles.emplace_back(0, 6, 0.4601990082068368);
	circles.emplace_back(0, 7, 0.3832299696514383);
	circles.emplace_back(0, 8, 0.4878669203957542);
	circles.emplace_back(0, 9, 0.5759205444948747);
	circles.emplace_back(0, 10, 0.2901406752644107);
	circles.emplace_back(1, 0, 0.6429678950691595);
	circles.emplace_back(1, 2, 0.4069292600965127);
	circles.emplace_back(1, 3, 0.3472176627488807);
	circles.emplace_back(1, 4, 0.4777778831077739);
	circles.emplace_back(1, 5, 0.6242357781389728);
	circles.emplace_back(1, 6, 0.3619275590172037);
	circles.emplace_back(1, 7, 0.3180311936186627);
	circles.emplace_back(1, 8, 0.820615295204334);
	circles.emplace_back(1, 9, 0.3438019313151017);
	circles.emplace_back(1, 10, 0.651092417514883);
	circles.emplace_back(2, 0, 0.7797796418191865);
	circles.emplace_back(2, 1, 0.4561745122773573);
	circles.emplace_back(2, 2, 0.3744275564560667);
	circles.emplace_back(2, 3, 0.3165348985930905);
	circles.emplace_back(2, 4, 0.2847389034228399);
	circles.emplace_back(2, 5, 0.5429144824622198);
	circles.emplace_back(2, 6, 0.5236875456059351);
	circles.emplace_back(2, 7, 0.4594442818081006);
	circles.emplace_back(2, 8, 0.4774997853906825);
	circles.emplace_back(2, 9, 0.7448628489626571);
	circles.emplace_back(2, 10, 0.3438459692755714);
	circles.emplace_back(3, 0, 0.4730592546751722);
	circles.emplace_back(3, 1, 0.2277927126036957);
	circles.emplace_back(3, 2, 0.3855832352070138);
	circles.emplace_back(3, 3, 0.3009112522238865);
	circles.emplace_back(3, 4, 0.5340375415747985);
	circles.emplace_back(3, 5, 0.4678046223940328);
	circles.emplace_back(3, 6, 0.5871034675044938);
	circles.emplace_back(3, 7, 0.1809960367390886);
	circles.emplace_back(3, 8, 0.4428489701589569);
	circles.emplace_back(3, 9, 0.7871130465762689);
	circles.emplace_back(3, 10, 0.5594297352014109);
	circles.emplace_back(4, 0, 0.4621067334199324);
	circles.emplace_back(4, 1, 0.6538169752573594);
	circles.emplace_back(4, 2, 0.4883623809786513);
	circles.emplace_back(4, 3, 0.5562716883374378);
	circles.emplace_back(4, 4, 0.5294877594569698);
	circles.emplace_back(4, 5, 0.3854335402837023);
	circles.emplace_back(4, 6, 0.7568073424743488);
	circles.emplace_back(4, 7, 0.4626034728018567);
	circles.emplace_back(4, 8, 0.3626454644137994);
	circles.emplace_back(4, 9, 0.4515725761419162);
	circles.emplace_back(4, 10, 0.5468486135127023);
	circles.emplace_back(5, 0, 0.2296857029898092);
	circles.emplace_back(5, 1, 0.4721767435083166);
	circles.emplace_back(5, 2, 0.3042267376324162);
	circles.emplace_back(5, 3, 0.5386856741504743);
	circles.emplace_back(5, 4, 0.7231733719585464);
	circles.emplace_back(5, 5, 0.4145273383939639);
	circles.emplace_back(5, 6, 0.5283926773583516);
	circles.emplace_back(5, 7, 0.2682118215830996);
	circles.emplace_back(5, 8, 0.3999346990836784);
	circles.emplace_back(5, 9, 0.5628048254409804);
	circles.emplace_back(5, 10, 0.2797297371318564);
	circles.emplace_back(6, 0, 0.6832763771759346);
	circles.emplace_back(6, 1, 0.1792059152154252);
	circles.emplace_back(6, 2, 0.2617712915176525);
	circles.emplace_back(6, 3, 0.3056170768802985);
	circles.emplace_back(6, 4, 0.5294390809955075);
	circles.emplace_back(6, 5, 0.2237069853348657);
	circles.emplace_back(6, 6, 0.3451406972715631);
	circles.emplace_back(6, 7, 0.4402342410525307);
	circles.emplace_back(6, 8, 0.3183416738407686);
	circles.emplace_back(6, 9, 0.3963432687101885);
	circles.emplace_back(6, 10, 0.443305927910842);
	circles.emplace_back(7, 0, 0.4142901625251397);
	circles.emplace_back(7, 1, 0.18182166677434);
	circles.emplace_back(7, 2, 0.7081181165529414);
	circles.emplace_back(7, 3, 0.259620531485416);
	circles.emplace_back(7, 4, 0.3700256040086969);
	circles.emplace_back(7, 5, 0.5648932981537654);
	circles.emplace_back(7, 6, 0.3228814071742818);
	circles.emplace_back(7, 7, 0.3433601446682587);
	circles.emplace_back(7, 8, 0.322114036954008);
	circles.emplace_back(7, 9, 0.460720678162761);
	circles.emplace_back(7, 10, 0.434539018641226);
	circles.emplace_back(8, 0, 0.4374886060366407);
	circles.emplace_back(8, 1, 0.355085957958363);
	circles.emplace_back(8, 2, 0.3407081208424643);
	circles.emplace_back(8, 3, 0.2823482389329001);
	circles.emplace_back(8, 4, 0.5293537568533793);
	circles.emplace_back(8, 5, 0.1979016426717863);
	circles.emplace_back(8, 6, 0.2828326636226848);
	circles.emplace_back(8, 7, 0.3199241135967895);
	circles.emplace_back(8, 8, 0.2824379293480888);
	circles.emplace_back(8, 9, 0.5662973372032866);
	circles.emplace_back(8, 10, 0.451343774353154);
	circles.emplace_back(9, 0, 0.3035817309049889);
	circles.emplace_back(9, 1, 0.1772881224984303);
	circles.emplace_back(9, 2, 0.4135298870271072);
	circles.emplace_back(9, 3, 0.4309552458347752);
	circles.emplace_back(9, 4, 0.6156394445104524);
	circles.emplace_back(9, 5, 0.3397508653113618);
	circles.emplace_back(9, 6, 0.5801448033889756);
	circles.emplace_back(9, 7, 0.3686542778508737);
	circles.emplace_back(9, 8, 0.2883080336032435);
	circles.emplace_back(9, 10, 0.3846367676043883);
	circles.emplace_back(10, 0, 0.1833927672123536);
	circles.emplace_back(10, 1, 0.4262527466984465);
	circles.emplace_back(10, 2, 0.6437908005667851);
	circles.emplace_back(10, 3, 0.7529397582868114);
	circles.emplace_back(10, 4, 0.1369195705046877);
	circles.emplace_back(10, 5, 0.5968056622194126);
	circles.emplace_back(10, 6, 0.5162196061341092);
	circles.emplace_back(10, 7, 0.1707360111409798);
	circles.emplace_back(10, 8, 0.1413544952636585);
	circles.emplace_back(10, 9, 0.3880218123318627);
	circles.emplace_back(10, 10, 0.3710518420441076);
	result_expected = 15.00554047147732;

	timer.reset();
	result_actual = algorithm(a25, b25, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #25: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();
	*/


    /*
	Point a26(1, 1);
	Point b26(9, 9); 
	{
		circles.emplace_back(0, 0, 0.507887558103539);
		circles.emplace_back(0, 1, 0.5364221298834309);
		circles.emplace_back(0, 2, 0.7257915950613096);
		circles.emplace_back(0, 3, 0.3875533411977812);
		circles.emplace_back(0, 4, 0.7646755900466814);
		circles.emplace_back(0, 5, 0.4552026230609044);
		circles.emplace_back(0, 6, 0.3809570380719379);
		circles.emplace_back(0, 7, 0.5199922253144905);
		circles.emplace_back(0, 8, 0.4644884450593963);
		circles.emplace_back(0, 9, 0.6711653752019628);
		circles.emplace_back(0, 10, 0.6724490056978538);
		circles.emplace_back(1, 0, 0.503168690088205);
		circles.emplace_back(1, 2, 0.4806892842287198);
		circles.emplace_back(1, 3, 0.4786011673277244);
		circles.emplace_back(1, 4, 0.249916593474336);
		circles.emplace_back(1, 5, 0.617905727843754);
		circles.emplace_back(1, 6, 0.2757884549209848);
		circles.emplace_back(1, 7, 0.2970777274807915);
		circles.emplace_back(1, 8, 0.6089737101690843);
		circles.emplace_back(1, 9, 0.2821257876930758);
		circles.emplace_back(1, 10, 0.5810455415630713);
		circles.emplace_back(2, 0, 0.2405437346315011);
		circles.emplace_back(2, 1, 0.5421878473134711);
		circles.emplace_back(2, 2, 0.3831383731914684);
		circles.emplace_back(2, 3, 0.294626103923656);
		circles.emplace_back(2, 4, 0.3417062600841745);
		circles.emplace_back(2, 5, 0.4789360362337902);
		circles.emplace_back(2, 6, 0.416763577493839);
		circles.emplace_back(2, 7, 0.5264381028944626);
		circles.emplace_back(2, 8, 0.7723066463833674);
		circles.emplace_back(2, 9, 0.6172529925825074);
		circles.emplace_back(2, 10, 0.548916556010954);
		circles.emplace_back(3, 0, 0.3677730137715116);
		circles.emplace_back(3, 1, 0.8499198237201199);
		circles.emplace_back(3, 2, 0.6007964483695104);
		circles.emplace_back(3, 3, 0.5652779365656897);
		circles.emplace_back(3, 4, 0.3138766270363703);
		circles.emplace_back(3, 5, 0.5719020638382062);
		circles.emplace_back(3, 6, 0.2440546714933589);
		circles.emplace_back(3, 7, 0.4246751670492813);
		circles.emplace_back(3, 8, 0.317574536637403);
		circles.emplace_back(3, 9, 0.4671121714403852);
		circles.emplace_back(3, 10, 0.3589211727725342);
		circles.emplace_back(4, 0, 0.3817998005775735);
		circles.emplace_back(4, 1, 0.602077315771021);
		circles.emplace_back(4, 2, 0.5060311130946502);
		circles.emplace_back(4, 3, 0.4857616004766896);
		circles.emplace_back(4, 4, 0.2948857181472704);
		circles.emplace_back(4, 5, 0.3110903801629319);
		circles.emplace_back(4, 6, 0.4599050836404786);
		circles.emplace_back(4, 7, 0.08209782235790043);
		circles.emplace_back(4, 8, 0.2839732887921855);
		circles.emplace_back(4, 9, 0.3243535388493911);
		circles.emplace_back(4, 10, 0.6495370100950822);
		circles.emplace_back(5, 0, 0.2720341951819137);
		circles.emplace_back(5, 1, 0.5553844672394916);
		circles.emplace_back(5, 2, 0.5167352324584499);
		circles.emplace_back(5, 3, 0.3743514930596575);
		circles.emplace_back(5, 4, 0.1095510217593983);
		circles.emplace_back(5, 5, 0.4580338290659711);
		circles.emplace_back(5, 6, 0.4890064589912071);
		circles.emplace_back(5, 7, 0.1623581856256351);
		circles.emplace_back(5, 8, 0.3587901954771951);
		circles.emplace_back(5, 9, 0.5872005433542654);
		circles.emplace_back(5, 10, 0.3484193871030584);
		circles.emplace_back(6, 0, 0.33163860978093);
		circles.emplace_back(6, 1, 0.6444580323295668);
		circles.emplace_back(6, 2, 0.5013862828491256);
		circles.emplace_back(6, 3, 0.3672156568849459);
		circles.emplace_back(6, 4, 0.5039814103161916);
		circles.emplace_back(6, 5, 0.5754702904494479);
		circles.emplace_back(6, 6, 0.3678840716136619);
		circles.emplace_back(6, 7, 0.297189368144609);
		circles.emplace_back(6, 8, 0.3612910462310537);
		circles.emplace_back(6, 9, 0.594964377139695);
		circles.emplace_back(6, 10, 0.6026830701855942);
		circles.emplace_back(7, 0, 0.1684297561878338);
		circles.emplace_back(7, 1, 0.5853949196403846);
		circles.emplace_back(7, 2, 0.5598037434043363);
		circles.emplace_back(7, 3, 0.6203342982335016);
		circles.emplace_back(7, 4, 0.3503685550997034);
		circles.emplace_back(7, 5, 0.3718739421805367);
		circles.emplace_back(7, 6, 0.502699465979822);
		circles.emplace_back(7, 7, 0.3594022947130724);
		circles.emplace_back(7, 8, 0.3032570485258475);
		circles.emplace_back(7, 9, 0.3585415389155969);
		circles.emplace_back(7, 10, 0.3800740168662742);
		circles.emplace_back(8, 0, 0.5991277155233546);
		circles.emplace_back(8, 1, 0.398197807953693);
		circles.emplace_back(8, 2, 0.4591960897436365);
		circles.emplace_back(8, 3, 0.5587922203587368);
		circles.emplace_back(8, 4, 0.3329258686630055);
		circles.emplace_back(8, 5, 0.5338561184937134);
		circles.emplace_back(8, 6, 0.2432718083029613);
		circles.emplace_back(8, 7, 0.4448843975784257);
		circles.emplace_back(8, 8, 0.4143461868865415);
		circles.emplace_back(8, 9, 0.2279760921606794);
		circles.emplace_back(8, 10, 0.3520130583783612);
		circles.emplace_back(9, 0, 0.3073866985039785);
		circles.emplace_back(9, 1, 0.3411176378605887);
		circles.emplace_back(9, 2, 0.5118264686549082);
		circles.emplace_back(9, 3, 0.5917971078073606);
		circles.emplace_back(9, 4, 0.4004236215027049);
		circles.emplace_back(9, 5, 0.3929050718201324);
		circles.emplace_back(9, 6, 0.3057011036435142);
		circles.emplace_back(9, 7, 0.3952303198864683);
		circles.emplace_back(9, 8, 0.3366577203618362);
		circles.emplace_back(9, 10, 0.4884015067247673);
		circles.emplace_back(10, 0, 0.2035991445416584);
		circles.emplace_back(10, 1, 0.2906427822774276);
		circles.emplace_back(10, 2, 0.6152314988197759);
		circles.emplace_back(10, 3, 0.1773813509149477);
		circles.emplace_back(10, 4, 0.345209893793799);
		circles.emplace_back(10, 5, 0.4706063734134659);
		circles.emplace_back(10, 6, 0.557326492597349);
		circles.emplace_back(10, 7, 0.4333395632682368);
		circles.emplace_back(10, 8, 0.5033273596549407);
		circles.emplace_back(10, 9, 0.5001012664055452);
		circles.emplace_back(10, 10, 0.5524645389290527); 
	}
	result_expected = 11.53768059156304;
	timer.reset();
	result_actual = algorithm(a26, b26, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #26: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a27(1, 1);
	Point b27(9, 9);
	{
		circles.emplace_back(0, 0, 0.2623417508555576);
		circles.emplace_back(0, 1, 0.4648194944718853);
		circles.emplace_back(0, 2, 0.4549558704486116);
		circles.emplace_back(0, 3, 0.4686762335943058);
		circles.emplace_back(0, 4, 0.4937102040974423);
		circles.emplace_back(0, 5, 0.4332771204644814);
		circles.emplace_back(0, 6, 0.6311852097278461);
		circles.emplace_back(0, 7, 0.3296615754486993);
		circles.emplace_back(0, 8, 0.8681708694202825);
		circles.emplace_back(0, 9, 0.7314675430068746);
		circles.emplace_back(0, 10, 0.4158527398249134);
		circles.emplace_back(1, 0, 0.5120677984552457);
		circles.emplace_back(1, 2, 0.3890862594125792);
		circles.emplace_back(1, 3, 0.5317178514087573);
		circles.emplace_back(1, 4, 0.6600806016242131);
		circles.emplace_back(1, 5, 0.6660093912156299);
		circles.emplace_back(1, 6, 0.2523993004811927);
		circles.emplace_back(1, 7, 0.5923529071966186);
		circles.emplace_back(1, 8, 0.244833312719129);
		circles.emplace_back(1, 9, 0.311955304001458);
		circles.emplace_back(1, 10, 0.4209131180075928);
		circles.emplace_back(2, 0, 0.4283130198949948);
		circles.emplace_back(2, 1, 0.4800998963182792);
		circles.emplace_back(2, 2, 0.6171083432855085);
		circles.emplace_back(2, 3, 0.2585317590041086);
		circles.emplace_back(2, 4, 0.5940763103077188);
		circles.emplace_back(2, 5, 0.2280994476517662);
		circles.emplace_back(2, 6, 0.7044017537729814);
		circles.emplace_back(2, 7, 0.5900868522701784);
		circles.emplace_back(2, 8, 0.2070107612991705);
		circles.emplace_back(2, 9, 0.491135137877427);
		circles.emplace_back(2, 10, 0.2972379879327491);
		circles.emplace_back(3, 0, 0.5023752060486003);
		circles.emplace_back(3, 1, 0.3892809560755268);
		circles.emplace_back(3, 2, 0.1547216554870829);
		circles.emplace_back(3, 3, 0.5530946630286052);
		circles.emplace_back(3, 4, 0.3520323431817814);
		circles.emplace_back(3, 5, 0.4564345039660111);
		circles.emplace_back(3, 6, 0.4266110852127895);
		circles.emplace_back(3, 7, 0.4891227056505159);
		circles.emplace_back(3, 8, 0.6958669737679883);
		circles.emplace_back(3, 9, 0.530793153704144);
		circles.emplace_back(3, 10, 0.5623422244330868);
		circles.emplace_back(4, 0, 0.05286168374586851);
		circles.emplace_back(4, 1, 0.2092814053175971);
		circles.emplace_back(4, 2, 0.407773594208993);
		circles.emplace_back(4, 3, 0.3179383370792493);
		circles.emplace_back(4, 4, 0.3411973261507228);
		circles.emplace_back(4, 5, 0.3084028904093429);
		circles.emplace_back(4, 6, 0.5532629428664222);
		circles.emplace_back(4, 7, 0.1203783450415358);
		circles.emplace_back(4, 8, 0.3206862296210602);
		circles.emplace_back(4, 9, 0.3415509118465707);
		circles.emplace_back(4, 10, 0.4601739213103428);
		circles.emplace_back(5, 0, 0.5964664570754393);
		circles.emplace_back(5, 1, 0.352372753364034);
		circles.emplace_back(5, 2, 0.3656654053134843);
		circles.emplace_back(5, 3, 0.5423047187039628);
		circles.emplace_back(5, 4, 0.2507252352079377);
		circles.emplace_back(5, 5, 0.4742231010692194);
		circles.emplace_back(5, 6, 0.4733209195313975);
		circles.emplace_back(5, 7, 0.6936285425210371);
		circles.emplace_back(5, 8, 0.1329370986437425);
		circles.emplace_back(5, 9, 0.4443015904398635);
		circles.emplace_back(5, 10, 0.4859517139149829);
		circles.emplace_back(6, 0, 0.4911378568271175);
		circles.emplace_back(6, 1, 0.4859592651715502);
		circles.emplace_back(6, 2, 0.2978141102241352);
		circles.emplace_back(6, 3, 0.3789127937285229);
		circles.emplace_back(6, 4, 0.4693683080608025);
		circles.emplace_back(6, 5, 0.6144371300702914);
		circles.emplace_back(6, 6, 0.6211437647463753);
		circles.emplace_back(6, 7, 0.454001882742159);
		circles.emplace_back(6, 8, 0.4447273383149877);
		circles.emplace_back(6, 9, 0.1650410825153813);
		circles.emplace_back(6, 10, 0.6960037059383467);
		circles.emplace_back(7, 0, 0.4250673333881423);
		circles.emplace_back(7, 1, 0.3177524861181155);
		circles.emplace_back(7, 2, 0.458851759484969);
		circles.emplace_back(7, 3, 0.3168321528704837);
		circles.emplace_back(7, 4, 0.632326974417083);
		circles.emplace_back(7, 5, 0.2314243747154251);
		circles.emplace_back(7, 6, 0.7665187371661887);
		circles.emplace_back(7, 7, 0.4345545987831428);
		circles.emplace_back(7, 8, 0.3510228960542008);
		circles.emplace_back(7, 9, 0.4136593878502026);
		circles.emplace_back(7, 10, 0.4668176598614082);
		circles.emplace_back(8, 0, 0.6298382056178525);
		circles.emplace_back(8, 1, 0.310037172655575);
		circles.emplace_back(8, 2, 0.5821070330450311);
		circles.emplace_back(8, 3, 0.4792308063944801);
		circles.emplace_back(8, 4, 0.5689633860485628);
		circles.emplace_back(8, 5, 0.1860935228643939);
		circles.emplace_back(8, 6, 0.1393769923830405);
		circles.emplace_back(8, 7, 0.2111760940169916);
		circles.emplace_back(8, 8, 0.4454375730128959);
		circles.emplace_back(8, 9, 0.5891699072672054);
		circles.emplace_back(8, 10, 0.2368208607891574);
		circles.emplace_back(9, 0, 0.5105095198145136);
		circles.emplace_back(9, 1, 0.3604761767433956);
		circles.emplace_back(9, 2, 0.6047470635501667);
		circles.emplace_back(9, 3, 0.5349935718113557);
		circles.emplace_back(9, 4, 0.463926039612852);
		circles.emplace_back(9, 5, 0.5454757292987779);
		circles.emplace_back(9, 6, 0.4085179791552946);
		circles.emplace_back(9, 7, 0.4389195109019056);
		circles.emplace_back(9, 8, 0.6318838843842968);
		circles.emplace_back(9, 10, 0.2796042165951803);
		circles.emplace_back(10, 0, 0.6191833014367149);
		circles.emplace_back(10, 1, 0.3362883161986246);
		circles.emplace_back(10, 2, 0.5606773141538725);
		circles.emplace_back(10, 3, 0.4056335979374125);
		circles.emplace_back(10, 4, 0.7049576853169128);
		circles.emplace_back(10, 5, 0.6167053668061271);
		circles.emplace_back(10, 6, 0.4622828094055876);
		circles.emplace_back(10, 7, 0.6971395130502059);
		circles.emplace_back(10, 8, 0.4094120784429833);
		circles.emplace_back(10, 9, 0.6001219585770741);
		circles.emplace_back(10, 10, 0.6026036999886856);
	}
	result_expected = 13.61324429179996;
	timer.reset();
	result_actual = algorithm(a27, b27, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #27: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a28(1, 1);
	Point b28(9, 9);
	{
		circles.emplace_back(0, 0, 0.280193176609464);
		circles.emplace_back(0, 1, 0.5122769438428804);
		circles.emplace_back(0, 2, 0.2525701673934236);
		circles.emplace_back(0, 3, 0.4887382315238937);
		circles.emplace_back(0, 4, 0.1626704602735117);
		circles.emplace_back(0, 5, 0.2908314200816676);
		circles.emplace_back(0, 6, 0.5173273999476805);
		circles.emplace_back(0, 7, 0.3958960693096742);
		circles.emplace_back(0, 8, 0.4743031622143462);
		circles.emplace_back(0, 9, 0.2975034189177677);
		circles.emplace_back(0, 10, 0.3396356320241466);
		circles.emplace_back(1, 0, 0.7245882397284731);
		circles.emplace_back(1, 2, 0.4705974641488865);
		circles.emplace_back(1, 3, 0.619305660459213);
		circles.emplace_back(1, 4, 0.6131003342801705);
		circles.emplace_back(1, 5, 0.5287155091529712);
		circles.emplace_back(1, 6, 0.2037445758702233);
		circles.emplace_back(1, 7, 0.2347326458198949);
		circles.emplace_back(1, 8, 0.5258940855273977);
		circles.emplace_back(1, 9, 0.3051802003523335);
		circles.emplace_back(1, 10, 0.2136485672788694);
		circles.emplace_back(2, 0, 0.5337435672758147);
		circles.emplace_back(2, 1, 0.4348898735130206);
		circles.emplace_back(2, 2, 0.4856464463984593);
		circles.emplace_back(2, 3, 0.2421963879140094);
		circles.emplace_back(2, 4, 0.3164561559213325);
		circles.emplace_back(2, 5, 0.3458490832010284);
		circles.emplace_back(2, 6, 0.1210738820722327);
		circles.emplace_back(2, 7, 0.5238950739847495);
		circles.emplace_back(2, 8, 0.3361764668254182);
		circles.emplace_back(2, 9, 0.6277891725534573);
		circles.emplace_back(2, 10, 0.3996497727697715);
		circles.emplace_back(3, 0, 0.3560011429013684);
		circles.emplace_back(3, 1, 0.5023896016879007);
		circles.emplace_back(3, 2, 0.6396560358116403);
		circles.emplace_back(3, 3, 0.3887445809086785);
		circles.emplace_back(3, 4, 0.5012671753065661);
		circles.emplace_back(3, 5, 0.3093363689957186);
		circles.emplace_back(3, 6, 0.3974260542774573);
		circles.emplace_back(3, 7, 0.4415159698342904);
		circles.emplace_back(3, 8, 0.5264305846067145);
		circles.emplace_back(3, 9, 0.6058008816791698);
		circles.emplace_back(3, 10, 0.359762834594585);
		circles.emplace_back(4, 0, 0.3587862452259287);
		circles.emplace_back(4, 1, 0.6295695740031079);
		circles.emplace_back(4, 2, 0.4717340922681614);
		circles.emplace_back(4, 3, 0.2603536345297471);
		circles.emplace_back(4, 4, 0.246818234003149);
		circles.emplace_back(4, 5, 0.2594512810232117);
		circles.emplace_back(4, 6, 0.5173382655484602);
		circles.emplace_back(4, 7, 0.465050476253964);
		circles.emplace_back(4, 8, 0.4616146007319912);
		circles.emplace_back(4, 9, 0.379997109551914);
		circles.emplace_back(4, 10, 0.3702373887179419);
		circles.emplace_back(5, 0, 0.4819409471238032);
		circles.emplace_back(5, 1, 0.7803656015312299);
		circles.emplace_back(5, 2, 0.1829902493627742);
		circles.emplace_back(5, 3, 0.4663585190428421);
		circles.emplace_back(5, 4, 0.5024736879626289);
		circles.emplace_back(5, 5, 0.2906702754786238);
		circles.emplace_back(5, 6, 0.5021503831492736);
		circles.emplace_back(5, 7, 0.7101490690140053);
		circles.emplace_back(5, 8, 0.6017635688418522);
		circles.emplace_back(5, 9, 0.5381560735171661);
		circles.emplace_back(5, 10, 0.5317005810560659);
		circles.emplace_back(6, 0, 0.4197550290031358);
		circles.emplace_back(6, 1, 0.4762015523621812);
		circles.emplace_back(6, 2, 0.5231219248613342);
		circles.emplace_back(6, 3, 0.4025513827102259);
		circles.emplace_back(6, 4, 0.522785127419047);
		circles.emplace_back(6, 5, 0.3464942444348708);
		circles.emplace_back(6, 6, 0.1868297409033403);
		circles.emplace_back(6, 7, 0.4192270667525008);
		circles.emplace_back(6, 8, 0.4182859283639118);
		circles.emplace_back(6, 9, 0.8042581325629726);
		circles.emplace_back(6, 10, 0.6780693566193804);
		circles.emplace_back(7, 0, 0.5106591078685596);
		circles.emplace_back(7, 1, 0.3705528667895123);
		circles.emplace_back(7, 2, 0.4302935116225853);
		circles.emplace_back(7, 3, 0.3406219094758853);
		circles.emplace_back(7, 4, 0.5979718213202432);
		circles.emplace_back(7, 5, 0.6504022211534902);
		circles.emplace_back(7, 6, 0.6626630971441045);
		circles.emplace_back(7, 7, 0.51224665583577);
		circles.emplace_back(7, 8, 0.6323851949768141);
		circles.emplace_back(7, 9, 0.4895290235755965);
		circles.emplace_back(7, 10, 0.2427003260934725);
		circles.emplace_back(8, 0, 0.275816224864684);
		circles.emplace_back(8, 1, 0.4063599088462069);
		circles.emplace_back(8, 2, 0.6635759074939415);
		circles.emplace_back(8, 3, 0.7170723451534285);
		circles.emplace_back(8, 4, 0.2532253099372611);
		circles.emplace_back(8, 5, 0.5911095421062782);
		circles.emplace_back(8, 6, 0.4695378928212449);
		circles.emplace_back(8, 7, 0.5240226865047589);
		circles.emplace_back(8, 8, 0.2826977975433692);
		circles.emplace_back(8, 9, 0.3036049676360562);
		circles.emplace_back(8, 10, 0.4131281086010858);
		circles.emplace_back(9, 0, 0.3419186311075464);
		circles.emplace_back(9, 1, 0.5701173336943611);
		circles.emplace_back(9, 2, 0.4561959340469912);
		circles.emplace_back(9, 3, 0.4717294531641528);
		circles.emplace_back(9, 4, 0.5282282594824209);
		circles.emplace_back(9, 5, 0.4550063278293237);
		circles.emplace_back(9, 6, 0.6919748352142051);
		circles.emplace_back(9, 7, 0.4485571917844936);
		circles.emplace_back(9, 8, 0.4270521899918094);
		circles.emplace_back(9, 10, 0.4817783942213282);
		circles.emplace_back(10, 0, 0.3590076673077419);
		circles.emplace_back(10, 1, 0.6836574918357655);
		circles.emplace_back(10, 2, 0.4733350046211853);
		circles.emplace_back(10, 3, 0.4168892308836803);
		circles.emplace_back(10, 4, 0.3265571733238176);
		circles.emplace_back(10, 5, 0.3373668954474852);
		circles.emplace_back(10, 6, 0.3718813622603193);
		circles.emplace_back(10, 7, 0.70251093597617);
		circles.emplace_back(10, 8, 0.4964231751160696);
		circles.emplace_back(10, 9, 0.5118577296612784);
		circles.emplace_back(10, 10, 0.5793017994845285);
	}
	result_expected = 15.28924921298935;
	timer.reset();
	result_actual = algorithm(a28, b28, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #28: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a29(1, 1);
	Point b29(9, 9);
	{
		circles.emplace_back(0, 0, 0.2873547617113217);
		circles.emplace_back(0, 1, 0.3125250929268077);
		circles.emplace_back(0, 2, 0.4263944540871307);
		circles.emplace_back(0, 3, 0.3670132188359275);
		circles.emplace_back(0, 4, 0.7252673057606444);
		circles.emplace_back(0, 5, 0.1218516524182632);
		circles.emplace_back(0, 6, 0.2119259460596368);
		circles.emplace_back(0, 7, 0.5934190646046772);
		circles.emplace_back(0, 8, 0.182225140160881);
		circles.emplace_back(0, 9, 0.4899027792038396);
		circles.emplace_back(0, 10, 0.3406387232942507);
		circles.emplace_back(1, 0, 0.5633941861102357);
		circles.emplace_back(1, 2, 0.4423528777202591);
		circles.emplace_back(1, 3, 0.6237486808793619);
		circles.emplace_back(1, 4, 0.1560961040435359);
		circles.emplace_back(1, 5, 0.4031993884826079);
		circles.emplace_back(1, 6, 0.3535896759247407);
		circles.emplace_back(1, 7, 0.2058311165543273);
		circles.emplace_back(1, 8, 0.5195883047534152);
		circles.emplace_back(1, 9, 0.4289506709435955);
		circles.emplace_back(1, 10, 0.6036291783442721);
		circles.emplace_back(2, 0, 0.3916318538831547);
		circles.emplace_back(2, 1, 0.4383184752194211);
		circles.emplace_back(2, 2, 0.5367681525880471);
		circles.emplace_back(2, 3, 0.4667578935390338);
		circles.emplace_back(2, 4, 0.4743333135964349);
		circles.emplace_back(2, 5, 0.1910496712429449);
		circles.emplace_back(2, 6, 0.6927296856651083);
		circles.emplace_back(2, 7, 0.312217011465691);
		circles.emplace_back(2, 8, 0.6695964015321806);
		circles.emplace_back(2, 9, 0.5168377647874877);
		circles.emplace_back(2, 10, 0.4507541563594714);
		circles.emplace_back(3, 0, 0.7147126573836431);
		circles.emplace_back(3, 1, 0.6235805281670764);
		circles.emplace_back(3, 2, 0.4824752916349098);
		circles.emplace_back(3, 3, 0.3765394730726257);
		circles.emplace_back(3, 4, 0.2576995832612738);
		circles.emplace_back(3, 5, 0.4973308156477287);
		circles.emplace_back(3, 6, 0.694271236541681);
		circles.emplace_back(3, 7, 0.3056802422041073);
		circles.emplace_back(3, 8, 0.2700632966822013);
		circles.emplace_back(3, 9, 0.2306574923219159);
		circles.emplace_back(3, 10, 0.3697917558951303);
		circles.emplace_back(4, 0, 0.3140901314327493);
		circles.emplace_back(4, 1, 0.2868256272515282);
		circles.emplace_back(4, 2, 0.2386324747698381);
		circles.emplace_back(4, 3, 0.6351868378696963);
		circles.emplace_back(4, 4, 0.5288539204979316);
		circles.emplace_back(4, 5, 0.5744987305020913);
		circles.emplace_back(4, 6, 0.3438281373353675);
		circles.emplace_back(4, 7, 0.4637279000831768);
		circles.emplace_back(4, 8, 0.5576342394808307);
		circles.emplace_back(4, 9, 0.311712529300712);
		circles.emplace_back(4, 10, 0.4974232691572979);
		circles.emplace_back(5, 0, 0.3211813247529789);
		circles.emplace_back(5, 1, 0.3647579945856705);
		circles.emplace_back(5, 2, 0.565740592754446);
		circles.emplace_back(5, 3, 0.3923012187005952);
		circles.emplace_back(5, 4, 0.5336429313523695);
		circles.emplace_back(5, 5, 0.3721074814209714);
		circles.emplace_back(5, 6, 0.6555494526168332);
		circles.emplace_back(5, 7, 0.6212652257876471);
		circles.emplace_back(5, 8, 0.4434583867667243);
		circles.emplace_back(5, 9, 0.5129411857808008);
		circles.emplace_back(5, 10, 0.341996357194148);
		circles.emplace_back(6, 0, 0.3834959411295131);
		circles.emplace_back(6, 1, 0.3688545529497787);
		circles.emplace_back(6, 2, 0.5167692719260231);
		circles.emplace_back(6, 3, 0.6358004627516493);
		circles.emplace_back(6, 4, 0.3923761333571747);
		circles.emplace_back(6, 5, 0.4329067720798775);
		circles.emplace_back(6, 6, 0.5534087583655491);
		circles.emplace_back(6, 7, 0.6639124624198303);
		circles.emplace_back(6, 8, 0.2878075835527852);
		circles.emplace_back(6, 9, 0.6774670892162248);
		circles.emplace_back(6, 10, 0.6143433811375871);
		circles.emplace_back(7, 0, 0.1849076526006684);
		circles.emplace_back(7, 1, 0.4061451672809198);
		circles.emplace_back(7, 2, 0.4276784124551341);
		circles.emplace_back(7, 3, 0.4595131445908919);
		circles.emplace_back(7, 4, 0.3940274368738755);
		circles.emplace_back(7, 5, 0.2108731241198256);
		circles.emplace_back(7, 6, 0.4226996105862781);
		circles.emplace_back(7, 7, 0.6076585596660152);
		circles.emplace_back(7, 8, 0.3084942674031481);
		circles.emplace_back(7, 9, 0.5371485146926716);
		circles.emplace_back(7, 10, 0.5782665482489392);
		circles.emplace_back(8, 0, 0.1983445696765557);
		circles.emplace_back(8, 1, 0.2737250238424167);
		circles.emplace_back(8, 2, 0.4533368651987985);
		circles.emplace_back(8, 3, 0.4967140585882589);
		circles.emplace_back(8, 4, 0.3037891635904089);
		circles.emplace_back(8, 5, 0.2810678297420964);
		circles.emplace_back(8, 6, 0.392664999444969);
		circles.emplace_back(8, 7, 0.3900838534114882);
		circles.emplace_back(8, 8, 0.4186216768110171);
		circles.emplace_back(8, 9, 0.4376873064553365);
		circles.emplace_back(8, 10, 0.5581160583766177);
		circles.emplace_back(9, 0, 0.2319433708442375);
		circles.emplace_back(9, 1, 0.3056957794586196);
		circles.emplace_back(9, 2, 0.2792232645442709);
		circles.emplace_back(9, 3, 0.5536917071091011);
		circles.emplace_back(9, 4, 0.2035405604867264);
		circles.emplace_back(9, 5, 0.6260821521515026);
		circles.emplace_back(9, 6, 0.6658478326862678);
		circles.emplace_back(9, 7, 0.3451665294589475);
		circles.emplace_back(9, 8, 0.8499196060700341);
		circles.emplace_back(9, 10, 0.4313658492872491);
		circles.emplace_back(10, 0, 0.7523460240801796);
		circles.emplace_back(10, 1, 0.403459609975107);
		circles.emplace_back(10, 2, 0.6116225856123492);
		circles.emplace_back(10, 3, 0.546373349823989);
		circles.emplace_back(10, 4, 0.3728447403525934);
		circles.emplace_back(10, 5, 0.5337483034702017);
		circles.emplace_back(10, 6, 0.2476020690752193);
		circles.emplace_back(10, 7, 0.4204542955616489);
		circles.emplace_back(10, 8, 0.6308152129640803);
		circles.emplace_back(10, 9, 0.3434491920517758);
		circles.emplace_back(10, 10, 0.4149696535198018);
	}
	result_expected = 14.7138017746558;
	timer.reset();
	result_actual = algorithm(a29, b29, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #29: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a30(1, 1);
	Point b30(9, 9);
	{
		circles.emplace_back(0, 0, 0.1754429169232026);
		circles.emplace_back(0, 1, 0.434973882115446);
		circles.emplace_back(0, 2, 0.5521912296535447);
		circles.emplace_back(0, 3, 0.7212054357631131);
		circles.emplace_back(0, 4, 0.2284241462359205);
		circles.emplace_back(0, 5, 0.6717067131539807);
		circles.emplace_back(0, 6, 0.2969060740666464);
		circles.emplace_back(0, 7, 0.3144534225342795);
		circles.emplace_back(0, 8, 0.31742941851262);
		circles.emplace_back(0, 9, 0.2546419504797086);
		circles.emplace_back(0, 10, 0.4351606064708903);
		circles.emplace_back(1, 0, 0.2275278781307861);
		circles.emplace_back(1, 2, 0.2081871597329155);
		circles.emplace_back(1, 3, 0.5419963089516386);
		circles.emplace_back(1, 4, 0.799856638466008);
		circles.emplace_back(1, 5, 0.3412556095747277);
		circles.emplace_back(1, 6, 0.3100529626244679);
		circles.emplace_back(1, 7, 0.5623196027940139);
		circles.emplace_back(1, 8, 0.2084228066029027);
		circles.emplace_back(1, 9, 0.1827791892690584);
		circles.emplace_back(1, 10, 0.2792444499442354);
		circles.emplace_back(2, 0, 0.439262812002562);
		circles.emplace_back(2, 1, 0.3796236544148996);
		circles.emplace_back(2, 2, 0.3244461151538416);
		circles.emplace_back(2, 3, 0.7375058252597227);
		circles.emplace_back(2, 4, 0.5559945862507447);
		circles.emplace_back(2, 5, 0.3611109019489959);
		circles.emplace_back(2, 6, 0.3989089083625004);
		circles.emplace_back(2, 7, 0.4843271112302318);
		circles.emplace_back(2, 8, 0.3498911862960085);
		circles.emplace_back(2, 9, 0.6208419027971104);
		circles.emplace_back(2, 10, 0.3960611483780667);
		circles.emplace_back(3, 0, 0.3308430753881111);
		circles.emplace_back(3, 1, 0.478124862886034);
		circles.emplace_back(3, 2, 0.4054902886273339);
		circles.emplace_back(3, 3, 0.6574344456894323);
		circles.emplace_back(3, 4, 0.2335368434200063);
		circles.emplace_back(3, 5, 0.2447756731649861);
		circles.emplace_back(3, 6, 0.3189738012151793);
		circles.emplace_back(3, 7, 0.3336813519475981);
		circles.emplace_back(3, 8, 0.5558731999481097);
		circles.emplace_back(3, 9, 0.3300917345797643);
		circles.emplace_back(3, 10, 0.3242243119748309);
		circles.emplace_back(4, 0, 0.2207692076219246);
		circles.emplace_back(4, 1, 0.4359865768114105);
		circles.emplace_back(4, 2, 0.3125229162862525);
		circles.emplace_back(4, 3, 0.6213250289903953);
		circles.emplace_back(4, 4, 0.4405099271563813);
		circles.emplace_back(4, 5, 0.1885487288469449);
		circles.emplace_back(4, 6, 0.4241529680555686);
		circles.emplace_back(4, 7, 0.4051398915471509);
		circles.emplace_back(4, 8, 0.6810507216257974);
		circles.emplace_back(4, 9, 0.7189410971710458);
		circles.emplace_back(4, 10, 0.3301550866803154);
		circles.emplace_back(5, 0, 0.1555601521627978);
		circles.emplace_back(5, 1, 0.6629507588921114);
		circles.emplace_back(5, 2, 0.5778568599605932);
		circles.emplace_back(5, 3, 0.4728959198808297);
		circles.emplace_back(5, 4, 0.3634931461187079);
		circles.emplace_back(5, 5, 0.4464687612606212);
		circles.emplace_back(5, 6, 0.4344576707342639);
		circles.emplace_back(5, 7, 0.2713130077114329);
		circles.emplace_back(5, 8, 0.5457182484911755);
		circles.emplace_back(5, 9, 0.345686540636234);
		circles.emplace_back(5, 10, 0.2962100841337815);
		circles.emplace_back(6, 0, 0.5161906614666805);
		circles.emplace_back(6, 1, 0.4517350186826661);
		circles.emplace_back(6, 2, 0.3650934711797163);
		circles.emplace_back(6, 3, 0.7535266692051664);
		circles.emplace_back(6, 4, 0.3519592800876126);
		circles.emplace_back(6, 5, 0.4157285324530676);
		circles.emplace_back(6, 6, 0.4242568994639441);
		circles.emplace_back(6, 7, 0.477336810179986);
		circles.emplace_back(6, 8, 0.08564310406800359);
		circles.emplace_back(6, 9, 0.6567769014509395);
		circles.emplace_back(6, 10, 0.6862034921301529);
		circles.emplace_back(7, 0, 0.6477121947566047);
		circles.emplace_back(7, 1, 0.5135814068606123);
		circles.emplace_back(7, 2, 0.6804259802447632);
		circles.emplace_back(7, 3, 0.5551365210441872);
		circles.emplace_back(7, 4, 0.4416719898814335);
		circles.emplace_back(7, 5, 0.4065481237834319);
		circles.emplace_back(7, 6, 0.08475626085419208);
		circles.emplace_back(7, 7, 0.4591140859527513);
		circles.emplace_back(7, 8, 0.2582927050301805);
		circles.emplace_back(7, 9, 0.54389491842594);
		circles.emplace_back(7, 10, 0.4240669547813013);
		circles.emplace_back(8, 0, 0.7833132746396586);
		circles.emplace_back(8, 1, 0.1092477429891005);
		circles.emplace_back(8, 2, 0.6373426865553483);
		circles.emplace_back(8, 3, 0.433302262541838);
		circles.emplace_back(8, 4, 0.569505260582082);
		circles.emplace_back(8, 5, 0.2529016381362453);
		circles.emplace_back(8, 6, 0.2350464975228533);
		circles.emplace_back(8, 7, 0.466344830696471);
		circles.emplace_back(8, 8, 0.5473663381068036);
		circles.emplace_back(8, 9, 0.5000839822227136);
		circles.emplace_back(8, 10, 0.4465589731698856);
		circles.emplace_back(9, 0, 0.6513013963820412);
		circles.emplace_back(9, 1, 0.5132498950464651);
		circles.emplace_back(9, 2, 0.4696680376539006);
		circles.emplace_back(9, 3, 0.1793171042343601);
		circles.emplace_back(9, 4, 0.2159056193428114);
		circles.emplace_back(9, 5, 0.4220443228958174);
		circles.emplace_back(9, 6, 0.5220790382707491);
		circles.emplace_back(9, 7, 0.5272775042569264);
		circles.emplace_back(9, 8, 0.486163101461716);
		circles.emplace_back(9, 10, 0.607741864467971);
		circles.emplace_back(10, 0, 0.2488571776309982);
		circles.emplace_back(10, 1, 0.5023251009872183);
		circles.emplace_back(10, 2, 0.4113635937916115);
		circles.emplace_back(10, 3, 0.5983433990506455);
		circles.emplace_back(10, 4, 0.5464002847904339);
		circles.emplace_back(10, 5, 0.4490802652901039);
		circles.emplace_back(10, 6, 0.6185853910865262);
		circles.emplace_back(10, 7, 0.34072416506242);
		circles.emplace_back(10, 8, 0.4520111875841394);
		circles.emplace_back(10, 9, 0.5337293775519356);
		circles.emplace_back(10, 10, 0.3498169138329104);
	}
	result_expected = 17.97272272613947;
	timer.reset();
	result_actual = algorithm(a30, b30, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #30: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();

	Point a31(1, 1);
	Point b31(9, 9);
	{
		circles.emplace_back(0, 0, 0.6010854202089831);
		circles.emplace_back(0, 1, 0.7703747634077445);
		circles.emplace_back(0, 2, 0.4475038315868005);
		circles.emplace_back(0, 3, 0.584820477780886);
		circles.emplace_back(0, 4, 0.3566170391393825);
		circles.emplace_back(0, 5, 0.5685896774986758);
		circles.emplace_back(0, 6, 0.3154324760427699);
		circles.emplace_back(0, 7, 0.4028632509754971);
		circles.emplace_back(0, 8, 0.5439960486022756);
		circles.emplace_back(0, 9, 0.3678798087174073);
		circles.emplace_back(0, 10, 0.5509924933081493);
		circles.emplace_back(1, 0, 0.4864403982879594);
		circles.emplace_back(1, 2, 0.2803461001021788);
		circles.emplace_back(1, 3, 0.5101103628287091);
		circles.emplace_back(1, 4, 0.3472837159177288);
		circles.emplace_back(1, 5, 0.5201154134469107);
		circles.emplace_back(1, 6, 0.6222828800557181);
		circles.emplace_back(1, 7, 0.427233673282899);
		circles.emplace_back(1, 8, 0.645351380459033);
		circles.emplace_back(1, 9, 0.1876026385696605);
		circles.emplace_back(1, 10, 0.478670457447879);
		circles.emplace_back(2, 0, 0.4917896894970908);
		circles.emplace_back(2, 1, 0.4702823189785704);
		circles.emplace_back(2, 2, 0.4202169711934403);
		circles.emplace_back(2, 3, 0.6427135689882562);
		circles.emplace_back(2, 4, 0.776586152636446);
		circles.emplace_back(2, 5, 0.5756995878880843);
		circles.emplace_back(2, 6, 0.4998157588066533);
		circles.emplace_back(2, 7, 0.5590108417673036);
		circles.emplace_back(2, 8, 0.2016834588954225);
		circles.emplace_back(2, 9, 0.2872805343708023);
		circles.emplace_back(2, 10, 0.5693578808801248);
		circles.emplace_back(3, 0, 0.4911939534125849);
		circles.emplace_back(3, 1, 0.2968092102790251);
		circles.emplace_back(3, 2, 0.5859233002876862);
		circles.emplace_back(3, 3, 0.654205018398352);
		circles.emplace_back(3, 4, 0.605777729745023);
		circles.emplace_back(3, 5, 0.5573274528840556);
		circles.emplace_back(3, 6, 0.5211867635836824);
		circles.emplace_back(3, 7, 0.6472901108907535);
		circles.emplace_back(3, 8, 0.6378461799351498);
		circles.emplace_back(3, 9, 0.4218876026803627);
		circles.emplace_back(3, 10, 0.5956289171939716);
		circles.emplace_back(4, 0, 0.4612780009629205);
		circles.emplace_back(4, 1, 0.6541994691593572);
		circles.emplace_back(4, 2, 0.5498780587920918);
		circles.emplace_back(4, 3, 0.5106686854502186);
		circles.emplace_back(4, 4, 0.6008432663278654);
		circles.emplace_back(4, 5, 0.5795868287561461);
		circles.emplace_back(4, 6, 0.4268095042789355);
		circles.emplace_back(4, 7, 0.714596177986823);
		circles.emplace_back(4, 8, 0.2581902393372729);
		circles.emplace_back(4, 9, 0.5016504038823768);
		circles.emplace_back(4, 10, 0.2757528944173828);
		circles.emplace_back(5, 0, 0.5433563811471686);
		circles.emplace_back(5, 1, 0.3849402140127495);
		circles.emplace_back(5, 2, 0.6202050386695191);
		circles.emplace_back(5, 3, 0.4029571324819699);
		circles.emplace_back(5, 4, 0.5947312868898734);
		circles.emplace_back(5, 5, 0.4435108405770734);
		circles.emplace_back(5, 6, 0.156478998879902);
		circles.emplace_back(5, 7, 0.5557714330265299);
		circles.emplace_back(5, 8, 0.3265454591950401);
		circles.emplace_back(5, 9, 0.4911127074854448);
		circles.emplace_back(5, 10, 0.6879406320629641);
		circles.emplace_back(6, 0, 0.2209973726654425);
		circles.emplace_back(6, 1, 0.6195200379705056);
		circles.emplace_back(6, 2, 0.2994881109567359);
		circles.emplace_back(6, 3, 0.3243359652115032);
		circles.emplace_back(6, 4, 0.3417956283548847);
		circles.emplace_back(6, 5, 0.4954001804580912);
		circles.emplace_back(6, 6, 0.2635170120047405);
		circles.emplace_back(6, 7, 0.3905622399179265);
		circles.emplace_back(6, 8, 0.1812724031740799);
		circles.emplace_back(6, 9, 0.1309809401398525);
		circles.emplace_back(6, 10, 0.6018151809694245);
		circles.emplace_back(7, 0, 0.5320023850305006);
		circles.emplace_back(7, 1, 0.3108705396065488);
		circles.emplace_back(7, 2, 0.5586565831443294);
		circles.emplace_back(7, 3, 0.6024495295481757);
		circles.emplace_back(7, 4, 0.6079454268096015);
		circles.emplace_back(7, 5, 0.3516903203213587);
		circles.emplace_back(7, 6, 0.4941183421527967);
		circles.emplace_back(7, 7, 0.4168956303270533);
		circles.emplace_back(7, 8, 0.5887178365839645);
		circles.emplace_back(7, 9, 0.6468649564543739);
		circles.emplace_back(7, 10, 0.4818256078055128);
		circles.emplace_back(8, 0, 0.5553624238120392);
		circles.emplace_back(8, 1, 0.6221508159069344);
		circles.emplace_back(8, 2, 0.3931157633895054);
		circles.emplace_back(8, 3, 0.3988755576079711);
		circles.emplace_back(8, 4, 0.6866091129602864);
		circles.emplace_back(8, 5, 0.5850085192127153);
		circles.emplace_back(8, 6, 0.5096120240399614);
		circles.emplace_back(8, 7, 0.507896222337149);
		circles.emplace_back(8, 8, 0.6953792452113703);
		circles.emplace_back(8, 9, 0.3850022139726206);
		circles.emplace_back(8, 10, 0.4722605396294966);
		circles.emplace_back(9, 0, 0.4995879899477586);
		circles.emplace_back(9, 1, 0.2005769820185378);
		circles.emplace_back(9, 2, 0.3290153783513233);
		circles.emplace_back(9, 3, 0.3915498679736629);
		circles.emplace_back(9, 4, 0.415538546978496);
		circles.emplace_back(9, 5, 0.3873105558799579);
		circles.emplace_back(9, 6, 0.4231647363631055);
		circles.emplace_back(9, 7, 0.5620742492610589);
		circles.emplace_back(9, 8, 0.2919362574582919);
		circles.emplace_back(9, 10, 0.7559279148699716);
		circles.emplace_back(10, 0, 0.3203222305281088);
		circles.emplace_back(10, 1, 0.46186221933458);
		circles.emplace_back(10, 2, 0.6148069793125615);
		circles.emplace_back(10, 3, 0.3411695546703413);
		circles.emplace_back(10, 4, 0.5807229320285842);
		circles.emplace_back(10, 5, 0.2296349104726687);
		circles.emplace_back(10, 6, 0.4273993182694539);
		circles.emplace_back(10, 7, 0.5045635381015018);
		circles.emplace_back(10, 8, 0.361283888365142);
		circles.emplace_back(10, 9, 0.2981190396705642);
		circles.emplace_back(10, 10, 0.5803433192661032);
	}
	result_expected = 17.05255117027776;
	timer.reset();
	result_actual = algorithm(a31, b31, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #31: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a32(1, 1);
	Point b32(9, 9);
	{
		circles.emplace_back(0, 0, 0.5531877021538093);
		circles.emplace_back(0, 1, 0.5992589085130021);
		circles.emplace_back(0, 2, 0.4115395844215527);
		circles.emplace_back(0, 3, 0.5652075953548774);
		circles.emplace_back(0, 4, 0.6879240525187924);
		circles.emplace_back(0, 5, 0.3058542855782434);
		circles.emplace_back(0, 6, 0.3054171459982172);
		circles.emplace_back(0, 7, 0.3220798941096291);
		circles.emplace_back(0, 8, 0.2343303456204012);
		circles.emplace_back(0, 9, 0.1354304569540545);
		circles.emplace_back(0, 10, 0.2767950002336875);
		circles.emplace_back(1, 0, 0.5617961015319451);
		circles.emplace_back(1, 2, 0.5592538581462577);
		circles.emplace_back(1, 3, 0.2459146019769832);
		circles.emplace_back(1, 4, 0.3230208358028904);
		circles.emplace_back(1, 5, 0.6934426834573969);
		circles.emplace_back(1, 6, 0.6263123440789059);
		circles.emplace_back(1, 7, 0.3160491770831868);
		circles.emplace_back(1, 8, 0.5772081800037995);
		circles.emplace_back(1, 9, 0.49775756446179);
		circles.emplace_back(1, 10, 0.2933671792270616);
		circles.emplace_back(2, 0, 0.4351013884646818);
		circles.emplace_back(2, 1, 0.8185025120386854);
		circles.emplace_back(2, 2, 0.4370544442674145);
		circles.emplace_back(2, 3, 0.8051136932568624);
		circles.emplace_back(2, 4, 0.5306586022255942);
		circles.emplace_back(2, 5, 0.2852770637953654);
		circles.emplace_back(2, 6, 0.4422955516492948);
		circles.emplace_back(2, 7, 0.4839136892231181);
		circles.emplace_back(2, 8, 0.3501346920384094);
		circles.emplace_back(2, 9, 0.3693833081284538);
		circles.emplace_back(2, 10, 0.4679378358414397);
		circles.emplace_back(3, 0, 0.27199515060056);
		circles.emplace_back(3, 1, 0.6616123243002221);
		circles.emplace_back(3, 2, 0.6195811346406117);
		circles.emplace_back(3, 3, 0.2551775954430923);
		circles.emplace_back(3, 4, 0.3281441358150914);
		circles.emplace_back(3, 5, 0.1896461807889864);
		circles.emplace_back(3, 6, 0.5322737129637971);
		circles.emplace_back(3, 7, 0.3942185448249802);
		circles.emplace_back(3, 8, 0.2320138602750376);
		circles.emplace_back(3, 9, 0.3516521188197657);
		circles.emplace_back(3, 10, 0.557672043540515);
		circles.emplace_back(4, 0, 0.3261883180355653);
		circles.emplace_back(4, 1, 0.4991759659023955);
		circles.emplace_back(4, 2, 0.6105072689009831);
		circles.emplace_back(4, 3, 0.399514195905067);
		circles.emplace_back(4, 4, 0.4753284102072939);
		circles.emplace_back(4, 5, 0.5600389781640842);
		circles.emplace_back(4, 6, 0.4089860698906705);
		circles.emplace_back(4, 7, 0.3364642344648018);
		circles.emplace_back(4, 8, 0.2520825564628467);
		circles.emplace_back(4, 9, 0.2057589506031945);
		circles.emplace_back(4, 10, 0.4016572416527197);
		circles.emplace_back(5, 0, 0.343315831781365);
		circles.emplace_back(5, 1, 0.3177085483213887);
		circles.emplace_back(5, 2, 0.554267296870239);
		circles.emplace_back(5, 3, 0.3498666952131316);
		circles.emplace_back(5, 4, 0.6401255693519488);
		circles.emplace_back(5, 5, 0.2510384876048192);
		circles.emplace_back(5, 6, 0.7395408102544024);
		circles.emplace_back(5, 7, 0.4954313804162666);
		circles.emplace_back(5, 8, 0.2474009258905426);
		circles.emplace_back(5, 9, 0.6080124778440222);
		circles.emplace_back(5, 10, 0.4772388707147911);
		circles.emplace_back(6, 0, 0.1786690710810944);
		circles.emplace_back(6, 1, 0.4754679531091824);
		circles.emplace_back(6, 2, 0.5146107531851157);
		circles.emplace_back(6, 3, 0.5098328394116833);
		circles.emplace_back(6, 4, 0.5163890876574442);
		circles.emplace_back(6, 5, 0.3261436389992013);
		circles.emplace_back(6, 6, 0.3838092447957024);
		circles.emplace_back(6, 7, 0.2843526407377794);
		circles.emplace_back(6, 8, 0.4054689573822543);
		circles.emplace_back(6, 9, 0.3348379586124793);
		circles.emplace_back(6, 10, 0.2971835847711191);
		circles.emplace_back(7, 0, 0.4658755318494514);
		circles.emplace_back(7, 1, 0.4676420119358227);
		circles.emplace_back(7, 2, 0.6312106123426929);
		circles.emplace_back(7, 3, 0.341786547540687);
		circles.emplace_back(7, 4, 0.3398820596979931);
		circles.emplace_back(7, 5, 0.6011209225980565);
		circles.emplace_back(7, 6, 0.4465074517065659);
		circles.emplace_back(7, 7, 0.3429239287739619);
		circles.emplace_back(7, 8, 0.4066042055608705);
		circles.emplace_back(7, 9, 0.3546821729047224);
		circles.emplace_back(7, 10, 0.4457015926251188);
		circles.emplace_back(8, 0, 0.4834538617869839);
		circles.emplace_back(8, 1, 0.5204907170729711);
		circles.emplace_back(8, 2, 0.6898364688036963);
		circles.emplace_back(8, 3, 0.4125642162049189);
		circles.emplace_back(8, 4, 0.5502345714485273);
		circles.emplace_back(8, 5, 0.5779146277578547);
		circles.emplace_back(8, 6, 0.4467100863112137);
		circles.emplace_back(8, 7, 0.5657900570193305);
		circles.emplace_back(8, 8, 0.7983455655863508);
		circles.emplace_back(8, 9, 0.4062479640590027);
		circles.emplace_back(8, 10, 0.4792621566681191);
		circles.emplace_back(9, 0, 0.5343025788897648);
		circles.emplace_back(9, 1, 0.6737072638934478);
		circles.emplace_back(9, 2, 0.4574286398710683);
		circles.emplace_back(9, 3, 0.6754628889961168);
		circles.emplace_back(9, 4, 0.3698638381669297);
		circles.emplace_back(9, 5, 0.1847240643342957);
		circles.emplace_back(9, 6, 0.2591445385711267);
		circles.emplace_back(9, 7, 0.7280577304540202);
		circles.emplace_back(9, 8, 0.3251140345120803);
		circles.emplace_back(9, 10, 0.4635758470511064);
		circles.emplace_back(10, 0, 0.4267597825499251);
		circles.emplace_back(10, 1, 0.3715424638940021);
		circles.emplace_back(10, 2, 0.475165749178268);
		circles.emplace_back(10, 3, 0.2077829157700762);
		circles.emplace_back(10, 4, 0.3891081902431324);
		circles.emplace_back(10, 5, 0.3509742430178449);
		circles.emplace_back(10, 6, 0.5108778707915916);
		circles.emplace_back(10, 7, 0.4426693767076358);
		circles.emplace_back(10, 8, 0.6312789206625894);
		circles.emplace_back(10, 9, 0.43824356503319);
		circles.emplace_back(10, 10, 0.4819342086324468);
	}
	result_expected = 13.33167459351174;
	timer.reset();
	result_actual = algorithm(a32, b32, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #32: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a33(1, 1);
	Point b33(9, 9);
	{
		circles.emplace_back(0, 0, 0.4953499549767002);
		circles.emplace_back(0, 1, 0.4075193054275587);
		circles.emplace_back(0, 2, 0.5614321808097884);
		circles.emplace_back(0, 3, 0.1178517934167758);
		circles.emplace_back(0, 4, 0.3208652484929189);
		circles.emplace_back(0, 5, 0.627379868295975);
		circles.emplace_back(0, 6, 0.4628819425357505);
		circles.emplace_back(0, 7, 0.5050438655773177);
		circles.emplace_back(0, 8, 0.1710904193809256);
		circles.emplace_back(0, 9, 0.4682265321956947);
		circles.emplace_back(0, 10, 0.3515995888737962);
		circles.emplace_back(1, 0, 0.648062551044859);
		circles.emplace_back(1, 2, 0.4470423228805885);
		circles.emplace_back(1, 3, 0.7172450137557461);
		circles.emplace_back(1, 4, 0.3656224676175043);
		circles.emplace_back(1, 5, 0.4931462245294824);
		circles.emplace_back(1, 6, 0.2252100737532601);
		circles.emplace_back(1, 7, 0.5960624053375795);
		circles.emplace_back(1, 8, 0.4099701958475634);
		circles.emplace_back(1, 9, 0.542196560301818);
		circles.emplace_back(1, 10, 0.2985340501880273);
		circles.emplace_back(2, 0, 0.1711109445663169);
		circles.emplace_back(2, 1, 0.2858072575880214);
		circles.emplace_back(2, 2, 0.6353102704742923);
		circles.emplace_back(2, 3, 0.5226583352079615);
		circles.emplace_back(2, 4, 0.5028589713620022);
		circles.emplace_back(2, 5, 0.4764415389625355);
		circles.emplace_back(2, 6, 0.3299905307823792);
		circles.emplace_back(2, 7, 0.6080815955763682);
		circles.emplace_back(2, 8, 0.4370340724708512);
		circles.emplace_back(2, 9, 0.5057838008506224);
		circles.emplace_back(2, 10, 0.4551630938658491);
		circles.emplace_back(3, 0, 0.4488313982030377);
		circles.emplace_back(3, 1, 0.4909634134965017);
		circles.emplace_back(3, 2, 0.6348930890439078);
		circles.emplace_back(3, 3, 0.4681220900500193);
		circles.emplace_back(3, 4, 0.4282869640504941);
		circles.emplace_back(3, 5, 0.7381562584312632);
		circles.emplace_back(3, 6, 0.5122330819023773);
		circles.emplace_back(3, 7, 0.4925305156270042);
		circles.emplace_back(3, 8, 0.4927753595402464);
		circles.emplace_back(3, 9, 0.4442536766873673);
		circles.emplace_back(3, 10, 0.5432643755106256);
		circles.emplace_back(4, 0, 0.5656004086369648);
		circles.emplace_back(4, 1, 0.2335661254590377);
		circles.emplace_back(4, 2, 0.157470437628217);
		circles.emplace_back(4, 3, 0.1949977063341066);
		circles.emplace_back(4, 4, 0.5725777121493593);
		circles.emplace_back(4, 5, 0.5678893433650956);
		circles.emplace_back(4, 6, 0.2066540925996378);
		circles.emplace_back(4, 7, 0.501133111375384);
		circles.emplace_back(4, 8, 0.2966568250441924);
		circles.emplace_back(4, 9, 0.5596021394943819);
		circles.emplace_back(4, 10, 0.5100862444611266);
		circles.emplace_back(5, 0, 0.4834100258303806);
		circles.emplace_back(5, 1, 0.3624498402932659);
		circles.emplace_back(5, 2, 0.4701286261668429);
		circles.emplace_back(5, 3, 0.4481510046171024);
		circles.emplace_back(5, 4, 0.4547933182446286);
		circles.emplace_back(5, 5, 0.5011354707414284);
		circles.emplace_back(5, 6, 0.3802982806926593);
		circles.emplace_back(5, 7, 0.4029956375481561);
		circles.emplace_back(5, 8, 0.7201202631695196);
		circles.emplace_back(5, 9, 0.4154126623878255);
		circles.emplace_back(5, 10, 0.6737077617784962);
		circles.emplace_back(6, 0, 0.4183083928423002);
		circles.emplace_back(6, 1, 0.2398334513185546);
		circles.emplace_back(6, 2, 0.5723838951671496);
		circles.emplace_back(6, 3, 0.622231163433753);
		circles.emplace_back(6, 4, 0.5823385247262195);
		circles.emplace_back(6, 5, 0.2724246372235939);
		circles.emplace_back(6, 6, 0.4024931712308898);
		circles.emplace_back(6, 7, 0.4643037063768133);
		circles.emplace_back(6, 8, 0.6872834990965202);
		circles.emplace_back(6, 9, 0.4612145243911072);
		circles.emplace_back(6, 10, 0.8326436907285825);
		circles.emplace_back(7, 0, 0.5166038669412956);
		circles.emplace_back(7, 1, 0.7681683880509809);
		circles.emplace_back(7, 2, 0.4810934879584238);
		circles.emplace_back(7, 3, 0.2316202150890604);
		circles.emplace_back(7, 4, 0.6097589434823021);
		circles.emplace_back(7, 5, 0.6743424519198015);
		circles.emplace_back(7, 6, 0.7108482348499819);
		circles.emplace_back(7, 7, 0.5959411178017034);
		circles.emplace_back(7, 8, 0.5886990602826699);
		circles.emplace_back(7, 9, 0.5767179087968543);
		circles.emplace_back(7, 10, 0.3466994014335796);
		circles.emplace_back(8, 0, 0.4542651226976886);
		circles.emplace_back(8, 1, 0.6682846089592204);
		circles.emplace_back(8, 2, 0.2638758915709332);
		circles.emplace_back(8, 3, 0.5226750886766239);
		circles.emplace_back(8, 4, 0.3184777297312394);
		circles.emplace_back(8, 5, 0.5848321273690089);
		circles.emplace_back(8, 6, 0.3301645924570039);
		circles.emplace_back(8, 7, 0.3534453348023817);
		circles.emplace_back(8, 8, 0.4595823282608762);
		circles.emplace_back(8, 9, 0.5341636160155758);
		circles.emplace_back(8, 10, 0.1089145950274542);
		circles.emplace_back(9, 0, 0.3652425254462286);
		circles.emplace_back(9, 1, 0.6365209978306666);
		circles.emplace_back(9, 2, 0.4368042919551954);
		circles.emplace_back(9, 3, 0.2538963937433437);
		circles.emplace_back(9, 4, 0.6304927413119003);
		circles.emplace_back(9, 5, 0.4560499964514747);
		circles.emplace_back(9, 6, 0.5209537802031263);
		circles.emplace_back(9, 7, 0.3221451009856537);
		circles.emplace_back(9, 8, 0.5717830433277413);
		circles.emplace_back(9, 10, 0.3917949363822117);
		circles.emplace_back(10, 0, 0.363855742639862);
		circles.emplace_back(10, 1, 0.4612773415865377);
		circles.emplace_back(10, 2, 0.3507896953029558);
		circles.emplace_back(10, 3, 0.3406106474110857);
		circles.emplace_back(10, 4, 0.2821909444173798);
		circles.emplace_back(10, 5, 0.5544253348605707);
		circles.emplace_back(10, 6, 0.3077923240838572);
		circles.emplace_back(10, 7, 0.5443707276368513);
		circles.emplace_back(10, 8, 0.4121187578653916);
		circles.emplace_back(10, 9, 0.225913164136);
		circles.emplace_back(10, 10, 0.4673990172101185);
	}
	result_expected = 19.1764326307966;
	timer.reset();
	result_actual = algorithm(a33, b33, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #33: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a34(1, 1);
	Point b34(9, 9);
	{
		circles.emplace_back(0, 0, 0.5553117817500606);
		circles.emplace_back(0, 1, 0.4695921038975939);
		circles.emplace_back(0, 2, 0.2608002337859943);
		circles.emplace_back(0, 3, 0.4761073580710217);
		circles.emplace_back(0, 4, 0.473057346814312);
		circles.emplace_back(0, 5, 0.3315708309179172);
		circles.emplace_back(0, 6, 0.4414169137598947);
		circles.emplace_back(0, 7, 0.4873263985617086);
		circles.emplace_back(0, 8, 0.1314465055475011);
		circles.emplace_back(0, 9, 0.5287585312267765);
		circles.emplace_back(0, 10, 0.3540173716144636);
		circles.emplace_back(1, 0, 0.3594845692394301);
		circles.emplace_back(1, 2, 0.1632921871030703);
		circles.emplace_back(1, 3, 0.3904877949273214);
		circles.emplace_back(1, 4, 0.5686745920451358);
		circles.emplace_back(1, 5, 0.3828485269797966);
		circles.emplace_back(1, 6, 0.3211941553512588);
		circles.emplace_back(1, 7, 0.1323789013316855);
		circles.emplace_back(1, 8, 0.5455425839172676);
		circles.emplace_back(1, 9, 0.3006779401330277);
		circles.emplace_back(1, 10, 0.7825316846603527);
		circles.emplace_back(2, 0, 0.727396947867237);
		circles.emplace_back(2, 1, 0.2706107747973874);
		circles.emplace_back(2, 2, 0.4403412111802026);
		circles.emplace_back(2, 3, 0.3167609231779352);
		circles.emplace_back(2, 4, 0.6509324164828285);
		circles.emplace_back(2, 5, 0.4740755929844453);
		circles.emplace_back(2, 6, 0.2200171368895099);
		circles.emplace_back(2, 7, 0.6431419436121359);
		circles.emplace_back(2, 8, 0.440530177555047);
		circles.emplace_back(2, 9, 0.3344542370410636);
		circles.emplace_back(2, 10, 0.2466075059724971);
		circles.emplace_back(3, 0, 0.3570204815128818);
		circles.emplace_back(3, 1, 0.6608919312944636);
		circles.emplace_back(3, 2, 0.421565632824786);
		circles.emplace_back(3, 3, 0.5704856342403218);
		circles.emplace_back(3, 4, 0.3527893610531464);
		circles.emplace_back(3, 5, 0.314777086651884);
		circles.emplace_back(3, 6, 0.4815035780193284);
		circles.emplace_back(3, 7, 0.4127058372600004);
		circles.emplace_back(3, 8, 0.2216546083102003);
		circles.emplace_back(3, 9, 0.4904270777245983);
		circles.emplace_back(3, 10, 0.4167270741658285);
		circles.emplace_back(4, 0, 0.3302988405106589);
		circles.emplace_back(4, 1, 0.3523312520468607);
		circles.emplace_back(4, 2, 0.4861381176626309);
		circles.emplace_back(4, 3, 0.6643928461940959);
		circles.emplace_back(4, 4, 0.4352781270397827);
		circles.emplace_back(4, 5, 0.6127938119927421);
		circles.emplace_back(4, 6, 0.2026073900749907);
		circles.emplace_back(4, 7, 0.426055049453862);
		circles.emplace_back(4, 8, 0.4329822226194665);
		circles.emplace_back(4, 9, 0.4412064746255055);
		circles.emplace_back(4, 10, 0.5436776779359206);
		circles.emplace_back(5, 0, 0.4518571642460301);
		circles.emplace_back(5, 1, 0.4953779184026643);
		circles.emplace_back(5, 2, 0.5241579564521089);
		circles.emplace_back(5, 3, 0.3161054299911484);
		circles.emplace_back(5, 4, 0.4323410778539255);
		circles.emplace_back(5, 5, 0.3349494310794398);
		circles.emplace_back(5, 6, 0.3903260547900572);
		circles.emplace_back(5, 7, 0.2689772646641359);
		circles.emplace_back(5, 8, 0.4009983540745452);
		circles.emplace_back(5, 9, 0.5947985005332157);
		circles.emplace_back(5, 10, 0.1976968860486522);
		circles.emplace_back(6, 0, 0.7633999114623293);
		circles.emplace_back(6, 1, 0.4006886902498081);
		circles.emplace_back(6, 2, 0.3205804249970242);
		circles.emplace_back(6, 3, 0.4424638115102425);
		circles.emplace_back(6, 4, 0.1130885898834094);
		circles.emplace_back(6, 5, 0.3170505617978051);
		circles.emplace_back(6, 6, 0.329901033709757);
		circles.emplace_back(6, 7, 0.3677310506114736);
		circles.emplace_back(6, 8, 0.4864788258215412);
		circles.emplace_back(6, 9, 0.4320290542440489);
		circles.emplace_back(6, 10, 0.544799597072415);
		circles.emplace_back(7, 0, 0.5001469817245379);
		circles.emplace_back(7, 1, 0.5109867054736241);
		circles.emplace_back(7, 2, 0.100645882752724);
		circles.emplace_back(7, 3, 0.5029426743043587);
		circles.emplace_back(7, 4, 0.7925921304384246);
		circles.emplace_back(7, 5, 0.670042566745542);
		circles.emplace_back(7, 6, 0.5041365991579368);
		circles.emplace_back(7, 7, 0.4131538985995576);
		circles.emplace_back(7, 8, 0.4010468453401699);
		circles.emplace_back(7, 9, 0.6335231281584128);
		circles.emplace_back(7, 10, 0.4825799864949658);
		circles.emplace_back(8, 0, 0.5709046997828409);
		circles.emplace_back(8, 1, 0.4737636612961069);
		circles.emplace_back(8, 2, 0.5122070552548393);
		circles.emplace_back(8, 3, 0.4001446410315111);
		circles.emplace_back(8, 4, 0.6993909644661471);
		circles.emplace_back(8, 5, 0.3808693502331152);
		circles.emplace_back(8, 6, 0.4768789645051583);
		circles.emplace_back(8, 7, 0.3460777417989447);
		circles.emplace_back(8, 8, 0.631820633704774);
		circles.emplace_back(8, 9, 0.4625216594198718);
		circles.emplace_back(8, 10, 0.2327068647136912);
		circles.emplace_back(9, 0, 0.4245610076235607);
		circles.emplace_back(9, 1, 0.600537238153629);
		circles.emplace_back(9, 2, 0.2237457372481003);
		circles.emplace_back(9, 3, 0.2895180359249934);
		circles.emplace_back(9, 4, 0.5365588416578247);
		circles.emplace_back(9, 5, 0.4486043707234785);
		circles.emplace_back(9, 6, 0.2540752465138212);
		circles.emplace_back(9, 7, 0.5185983458301052);
		circles.emplace_back(9, 8, 0.5067836634116247);
		circles.emplace_back(9, 10, 0.5294760967371985);
		circles.emplace_back(10, 0, 0.4001231651986017);
		circles.emplace_back(10, 1, 0.3366400036728009);
		circles.emplace_back(10, 2, 0.35890342828352);
		circles.emplace_back(10, 3, 0.6103783015860245);
		circles.emplace_back(10, 4, 0.3692072747508064);
		circles.emplace_back(10, 5, 0.2074627516558394);
		circles.emplace_back(10, 6, 0.3921163345919922);
		circles.emplace_back(10, 7, 0.445025975885801);
		circles.emplace_back(10, 8, 0.6921553358668461);
		circles.emplace_back(10, 9, 0.4021334938472137);
		circles.emplace_back(10, 10, 0.5622177181066945);
	}
	result_expected = 15.52091608205293;
	timer.reset();
	result_actual = algorithm(a34, b34, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #34: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a35(1, 1);
	Point b35(9, 9);
	{
		circles.emplace_back(0, 0, 0.4313014381332323);
		circles.emplace_back(0, 1, 0.323414951772429);
		circles.emplace_back(0, 2, 0.3081093625864014);
		circles.emplace_back(0, 3, 0.3202841340797022);
		circles.emplace_back(0, 4, 0.3195184948621317);
		circles.emplace_back(0, 5, 0.50659311900381);
		circles.emplace_back(0, 6, 0.5280292223906144);
		circles.emplace_back(0, 7, 0.5120996267767622);
		circles.emplace_back(0, 8, 0.6868975382996723);
		circles.emplace_back(0, 9, 0.6835504656890407);
		circles.emplace_back(0, 10, 0.5587786113610491);
		circles.emplace_back(1, 0, 0.6914491865085438);
		circles.emplace_back(1, 2, 0.3438765815226361);
		circles.emplace_back(1, 3, 0.2751751773292199);
		circles.emplace_back(1, 4, 0.5914531200891361);
		circles.emplace_back(1, 5, 0.05040439416188747);
		circles.emplace_back(1, 6, 0.6878832311136648);
		circles.emplace_back(1, 7, 0.5119616100797429);
		circles.emplace_back(1, 8, 0.2228452080627903);
		circles.emplace_back(1, 9, 0.419726253231056);
		circles.emplace_back(1, 10, 0.5701925973175094);
		circles.emplace_back(2, 0, 0.3425185915315523);
		circles.emplace_back(2, 1, 0.2190794575726613);
		circles.emplace_back(2, 2, 0.3425102093489841);
		circles.emplace_back(2, 3, 0.4914961416972801);
		circles.emplace_back(2, 4, 0.6981324089923874);
		circles.emplace_back(2, 5, 0.4220212651183828);
		circles.emplace_back(2, 6, 0.274198357318528);
		circles.emplace_back(2, 7, 0.2918064622906968);
		circles.emplace_back(2, 8, 0.341509485268034);
		circles.emplace_back(2, 9, 0.2390839703148231);
		circles.emplace_back(2, 10, 0.4120838356437161);
		circles.emplace_back(3, 0, 0.7503230162663385);
		circles.emplace_back(3, 1, 0.2778237419435755);
		circles.emplace_back(3, 2, 0.5070594222983346);
		circles.emplace_back(3, 3, 0.4074324085609987);
		circles.emplace_back(3, 4, 0.1608837800798938);
		circles.emplace_back(3, 5, 0.8561936501646414);
		circles.emplace_back(3, 6, 0.5705969836330042);
		circles.emplace_back(3, 7, 0.4633462355704978);
		circles.emplace_back(3, 8, 0.1986278471304104);
		circles.emplace_back(3, 9, 0.7397139689186588);
		circles.emplace_back(3, 10, 0.4659559717169031);
		circles.emplace_back(4, 0, 0.4714948284672573);
		circles.emplace_back(4, 1, 0.4434939629165456);
		circles.emplace_back(4, 2, 0.4721671708161011);
		circles.emplace_back(4, 3, 0.2506565376883372);
		circles.emplace_back(4, 4, 0.5908381958724931);
		circles.emplace_back(4, 5, 0.376179997692816);
		circles.emplace_back(4, 6, 0.619539555371739);
		circles.emplace_back(4, 7, 0.3696539828320965);
		circles.emplace_back(4, 8, 0.2214671752648428);
		circles.emplace_back(4, 9, 0.5121883566258475);
		circles.emplace_back(4, 10, 0.5144670497858896);
		circles.emplace_back(5, 0, 0.4986615124857053);
		circles.emplace_back(5, 1, 0.576685952511616);
		circles.emplace_back(5, 2, 0.4895823274506256);
		circles.emplace_back(5, 3, 0.1817356972256675);
		circles.emplace_back(5, 4, 0.4552464274456725);
		circles.emplace_back(5, 5, 0.6064617689000442);
		circles.emplace_back(5, 6, 0.4760783656267449);
		circles.emplace_back(5, 7, 0.3729618326062337);
		circles.emplace_back(5, 8, 0.6183247528737411);
		circles.emplace_back(5, 9, 0.4753668156685307);
		circles.emplace_back(5, 10, 0.4110993169946596);
		circles.emplace_back(6, 0, 0.288576945872046);
		circles.emplace_back(6, 1, 0.6466793047031387);
		circles.emplace_back(6, 2, 0.2481373160379007);
		circles.emplace_back(6, 3, 0.1484135779319331);
		circles.emplace_back(6, 4, 0.5152422327781095);
		circles.emplace_back(6, 5, 0.5371261935448274);
		circles.emplace_back(6, 6, 0.4859747947426513);
		circles.emplace_back(6, 7, 0.4149851930094883);
		circles.emplace_back(6, 8, 0.2568178331712261);
		circles.emplace_back(6, 9, 0.4129547660937533);
		circles.emplace_back(6, 10, 0.5067145350622013);
		circles.emplace_back(7, 0, 0.4516598901478573);
		circles.emplace_back(7, 1, 0.2870117567712441);
		circles.emplace_back(7, 2, 0.6832659840350971);
		circles.emplace_back(7, 3, 0.7119862233521417);
		circles.emplace_back(7, 4, 0.351312053273432);
		circles.emplace_back(7, 5, 0.7018334964523092);
		circles.emplace_back(7, 6, 0.4638342404505238);
		circles.emplace_back(7, 7, 0.534491781075485);
		circles.emplace_back(7, 8, 0.660077632474713);
		circles.emplace_back(7, 9, 0.3999773290241137);
		circles.emplace_back(7, 10, 0.7001176137244328);
		circles.emplace_back(8, 0, 0.508525384333916);
		circles.emplace_back(8, 1, 0.3572979916585609);
		circles.emplace_back(8, 2, 0.2692603035131469);
		circles.emplace_back(8, 3, 0.5830415589502081);
		circles.emplace_back(8, 4, 0.316860670899041);
		circles.emplace_back(8, 5, 0.4797996937064454);
		circles.emplace_back(8, 6, 0.207239916943945);
		circles.emplace_back(8, 7, 0.5981810368364676);
		circles.emplace_back(8, 8, 0.4171301347436383);
		circles.emplace_back(8, 9, 0.4061352231306955);
		circles.emplace_back(8, 10, 0.3541364776203409);
		circles.emplace_back(9, 0, 0.1989660801133141);
		circles.emplace_back(9, 1, 0.6008217080729082);
		circles.emplace_back(9, 2, 0.3664096462307498);
		circles.emplace_back(9, 3, 0.5661851559067145);
		circles.emplace_back(9, 4, 0.4445357974385842);
		circles.emplace_back(9, 5, 0.6880175308557227);
		circles.emplace_back(9, 6, 0.493318208749406);
		circles.emplace_back(9, 7, 0.4075427225092426);
		circles.emplace_back(9, 8, 0.1928658148040995);
		circles.emplace_back(9, 10, 0.3109999078558758);
		circles.emplace_back(10, 0, 0.3800198710290715);
		circles.emplace_back(10, 1, 0.2888739742571488);
		circles.emplace_back(10, 2, 0.3897941544419155);
		circles.emplace_back(10, 3, 0.5898494531633333);
		circles.emplace_back(10, 4, 0.5604717806680127);
		circles.emplace_back(10, 5, 0.3307428473839536);
		circles.emplace_back(10, 6, 0.5445705512305722);
		circles.emplace_back(10, 7, 0.4531604222254828);
		circles.emplace_back(10, 8, 0.2778496826766059);
		circles.emplace_back(10, 9, 0.2799332183087245);
		circles.emplace_back(10, 10, 0.432554206601344);
	}
	result_expected = 15.75483932773297;
	timer.reset();
	result_actual = algorithm(a35, b35, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #35: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a36(1, 1);
	Point b36(9, 9);
	{
		circles.emplace_back(0, 0, 0.3069982313783839);
		circles.emplace_back(0, 1, 0.4566792671335861);
		circles.emplace_back(0, 2, 0.3568243919173256);
		circles.emplace_back(0, 3, 0.4156849799444899);
		circles.emplace_back(0, 4, 0.4052241648780182);
		circles.emplace_back(0, 5, 0.5443034543422982);
		circles.emplace_back(0, 6, 0.361946277343668);
		circles.emplace_back(0, 7, 0.2213530175155029);
		circles.emplace_back(0, 8, 0.3243122694315388);
		circles.emplace_back(0, 9, 0.5373106174869463);
		circles.emplace_back(0, 10, 0.2198392512509599);
		circles.emplace_back(1, 0, 0.3702918188413605);
		circles.emplace_back(1, 2, 0.3957834362285211);
		circles.emplace_back(1, 3, 0.1585487427888438);
		circles.emplace_back(1, 4, 0.4883437086129561);
		circles.emplace_back(1, 5, 0.3941197406267747);
		circles.emplace_back(1, 6, 0.09938167047221214);
		circles.emplace_back(1, 7, 0.5003505271626636);
		circles.emplace_back(1, 8, 0.6114443009952083);
		circles.emplace_back(1, 9, 0.4331549381604418);
		circles.emplace_back(1, 10, 0.2701175484107807);
		circles.emplace_back(2, 0, 0.399594413372688);
		circles.emplace_back(2, 1, 0.3437938623363152);
		circles.emplace_back(2, 2, 0.6551287442212924);
		circles.emplace_back(2, 3, 0.5223038618685677);
		circles.emplace_back(2, 4, 0.6602265626890584);
		circles.emplace_back(2, 5, 0.3250420222291723);
		circles.emplace_back(2, 6, 0.2854224854847416);
		circles.emplace_back(2, 7, 0.2437084502773359);
		circles.emplace_back(2, 8, 0.5888687650440261);
		circles.emplace_back(2, 9, 0.3320935067022219);
		circles.emplace_back(2, 10, 0.2894527364289388);
		circles.emplace_back(3, 0, 0.2629492202075198);
		circles.emplace_back(3, 1, 0.2591372866882011);
		circles.emplace_back(3, 2, 0.7874211265007034);
		circles.emplace_back(3, 3, 0.3978300107410178);
		circles.emplace_back(3, 4, 0.3432563523994759);
		circles.emplace_back(3, 5, 0.4702976553468033);
		circles.emplace_back(3, 6, 0.3515584528679028);
		circles.emplace_back(3, 7, 0.2149158902233466);
		circles.emplace_back(3, 8, 0.7057266962947324);
		circles.emplace_back(3, 9, 0.6158803828759118);
		circles.emplace_back(3, 10, 0.5778971808264032);
		circles.emplace_back(4, 0, 0.201403591199778);
		circles.emplace_back(4, 1, 0.3351953520672395);
		circles.emplace_back(4, 2, 0.5278826254187151);
		circles.emplace_back(4, 3, 0.5579141799593345);
		circles.emplace_back(4, 4, 0.2715469684218988);
		circles.emplace_back(4, 5, 0.2718494401546195);
		circles.emplace_back(4, 6, 0.512180781061761);
		circles.emplace_back(4, 7, 0.6349532326916233);
		circles.emplace_back(4, 8, 0.1956629564752802);
		circles.emplace_back(4, 9, 0.4417090582894161);
		circles.emplace_back(4, 10, 0.5407790249912068);
		circles.emplace_back(5, 0, 0.5146864600712433);
		circles.emplace_back(5, 1, 0.448532448685728);
		circles.emplace_back(5, 2, 0.3291004260303452);
		circles.emplace_back(5, 3, 0.616518782149069);
		circles.emplace_back(5, 4, 0.3503804350504652);
		circles.emplace_back(5, 5, 0.4943246135255321);
		circles.emplace_back(5, 6, 0.4442462167935446);
		circles.emplace_back(5, 7, 0.5758741373894736);
		circles.emplace_back(5, 8, 0.3310919832671061);
		circles.emplace_back(5, 9, 0.6486696485197171);
		circles.emplace_back(5, 10, 0.4890980773838237);
		circles.emplace_back(6, 0, 0.745458183134906);
		circles.emplace_back(6, 1, 0.4509186713257805);
		circles.emplace_back(6, 2, 0.6085049716522917);
		circles.emplace_back(6, 3, 0.474536335025914);
		circles.emplace_back(6, 4, 0.2178653045324609);
		circles.emplace_back(6, 5, 0.4874289825791493);
		circles.emplace_back(6, 6, 0.490319850272499);
		circles.emplace_back(6, 7, 0.3920618918957189);
		circles.emplace_back(6, 8, 0.1624744021100923);
		circles.emplace_back(6, 9, 0.3673971804091707);
		circles.emplace_back(6, 10, 0.1674234675010666);
		circles.emplace_back(7, 0, 0.4931053071515634);
		circles.emplace_back(7, 1, 0.2368380519328639);
		circles.emplace_back(7, 2, 0.6479678590083494);
		circles.emplace_back(7, 3, 0.6468614261364564);
		circles.emplace_back(7, 4, 0.4790780664654448);
		circles.emplace_back(7, 5, 0.3142826032591984);
		circles.emplace_back(7, 6, 0.2913751816609874);
		circles.emplace_back(7, 7, 0.5766056900611147);
		circles.emplace_back(7, 8, 0.255291039054282);
		circles.emplace_back(7, 9, 0.393344213697128);
		circles.emplace_back(7, 10, 0.4613418065244332);
		circles.emplace_back(8, 0, 0.3236429631477222);
		circles.emplace_back(8, 1, 0.5518651222111657);
		circles.emplace_back(8, 2, 0.4046658218605444);
		circles.emplace_back(8, 3, 0.4192824999103322);
		circles.emplace_back(8, 4, 0.4135865056654438);
		circles.emplace_back(8, 5, 0.6647590733366087);
		circles.emplace_back(8, 6, 0.5809800575254485);
		circles.emplace_back(8, 7, 0.548437437065877);
		circles.emplace_back(8, 8, 0.4724363881861791);
		circles.emplace_back(8, 9, 0.3200395294697955);
		circles.emplace_back(8, 10, 0.5058030892862007);
		circles.emplace_back(9, 0, 0.3840601904550567);
		circles.emplace_back(9, 1, 0.7611131829908118);
		circles.emplace_back(9, 2, 0.5145182143198326);
		circles.emplace_back(9, 3, 0.5064644097117706);
		circles.emplace_back(9, 4, 0.6777854055399075);
		circles.emplace_back(9, 5, 0.74339009297546);
		circles.emplace_back(9, 6, 0.4358813327969983);
		circles.emplace_back(9, 7, 0.5070975580019876);
		circles.emplace_back(9, 8, 0.3743011640617624);
		circles.emplace_back(9, 10, 0.3778485180577263);
		circles.emplace_back(10, 0, 0.3154361530439928);
		circles.emplace_back(10, 1, 0.3072167801437899);
		circles.emplace_back(10, 2, 0.5284510348225012);
		circles.emplace_back(10, 3, 0.3744820590829477);
		circles.emplace_back(10, 4, 0.4165997759671882);
		circles.emplace_back(10, 5, 0.6015046265674755);
		circles.emplace_back(10, 6, 0.6408908119658008);
		circles.emplace_back(10, 7, 0.5065739592304453);
		circles.emplace_back(10, 8, 0.3122550922678783);
		circles.emplace_back(10, 9, 0.6064354873029515);
		circles.emplace_back(10, 10, 0.6404249407583847);
	}
	result_expected = 15.45628204867654;
	timer.reset();
	result_actual = algorithm(a36, b36, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #36: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();

	*/


	/*
	Point a37(1, 1);
	Point b37(9, 9);
	{
		circles.emplace_back(0, 0, 0.2442294869804755);
		circles.emplace_back(0, 1, 0.4495302494382485);
		circles.emplace_back(0, 2, 0.4458869771333411);
		circles.emplace_back(0, 3, 0.7266923871589824);
		circles.emplace_back(0, 4, 0.3141284277895465);
		circles.emplace_back(0, 5, 0.5316437979927287);
		circles.emplace_back(0, 6, 0.2173890608595684);
		circles.emplace_back(0, 7, 0.225096586975269);
		circles.emplace_back(0, 8, 0.5049611367518082);
		circles.emplace_back(0, 9, 0.4083670213585719);
		circles.emplace_back(0, 10, 0.2933697630884126);
		circles.emplace_back(1, 0, 0.5155817226273939);
		circles.emplace_back(1, 2, 0.336852096975781);
		circles.emplace_back(1, 3, 0.5523773887893185);
		circles.emplace_back(1, 4, 0.2476870111422613);
		circles.emplace_back(1, 5, 0.3082668985007331);
		circles.emplace_back(1, 6, 0.5944269817555323);
		circles.emplace_back(1, 7, 0.4438680860912427);
		circles.emplace_back(1, 8, 0.6887011432321742);
		circles.emplace_back(1, 9, 0.6297774140490219);
		circles.emplace_back(1, 10, 0.4616881428519264);
		circles.emplace_back(2, 0, 0.4285192070296034);
		circles.emplace_back(2, 1, 0.3170996154891327);
		circles.emplace_back(2, 2, 0.2022120489506051);
		circles.emplace_back(2, 3, 0.4160697862738743);
		circles.emplace_back(2, 4, 0.5338673822348937);
		circles.emplace_back(2, 5, 0.0882138964952901);
		circles.emplace_back(2, 6, 0.5070712857646867);
		circles.emplace_back(2, 7, 0.5597978355595842);
		circles.emplace_back(2, 8, 0.1346988456090912);
		circles.emplace_back(2, 9, 0.3319535493152216);
		circles.emplace_back(2, 10, 0.4997714700875804);
		circles.emplace_back(3, 0, 0.4166794825578108);
		circles.emplace_back(3, 1, 0.4080909382319078);
		circles.emplace_back(3, 2, 0.5334825010271743);
		circles.emplace_back(3, 3, 0.3903699082089588);
		circles.emplace_back(3, 4, 0.672447425709106);
		circles.emplace_back(3, 5, 0.2687270497670397);
		circles.emplace_back(3, 6, 0.2277624997543171);
		circles.emplace_back(3, 7, 0.4561259022681042);
		circles.emplace_back(3, 8, 0.2867837958270684);
		circles.emplace_back(3, 9, 0.6251099973684177);
		circles.emplace_back(3, 10, 0.5110887591959908);
		circles.emplace_back(4, 0, 0.5015227229101583);
		circles.emplace_back(4, 1, 0.2551487693795934);
		circles.emplace_back(4, 2, 0.4472988420864567);
		circles.emplace_back(4, 3, 0.1227427906589583);
		circles.emplace_back(4, 4, 0.331375519442372);
		circles.emplace_back(4, 5, 0.2485388692701235);
		circles.emplace_back(4, 6, 0.3867941427743062);
		circles.emplace_back(4, 7, 0.5998874225886538);
		circles.emplace_back(4, 8, 0.5526501674903557);
		circles.emplace_back(4, 9, 0.309299953118898);
		circles.emplace_back(4, 10, 0.4391966474941);
		circles.emplace_back(5, 0, 0.6588290076004341);
		circles.emplace_back(5, 1, 0.7706180541543289);
		circles.emplace_back(5, 2, 0.4311198890442028);
		circles.emplace_back(5, 3, 0.4902644224232062);
		circles.emplace_back(5, 4, 0.6057718170108274);
		circles.emplace_back(5, 5, 0.1949718006653711);
		circles.emplace_back(5, 6, 0.6013259189436212);
		circles.emplace_back(5, 7, 0.7359934182604775);
		circles.emplace_back(5, 8, 0.5301896228687838);
		circles.emplace_back(5, 9, 0.4215269225416705);
		circles.emplace_back(5, 10, 0.4336117092752829);
		circles.emplace_back(6, 0, 0.3173464741325006);
		circles.emplace_back(6, 1, 0.1839394674869254);
		circles.emplace_back(6, 2, 0.405134427244775);
		circles.emplace_back(6, 3, 0.3693190893391147);
		circles.emplace_back(6, 4, 0.4602557589998468);
		circles.emplace_back(6, 5, 0.4992426204727962);
		circles.emplace_back(6, 6, 0.4894293493358418);
		circles.emplace_back(6, 7, 0.5753994770580902);
		circles.emplace_back(6, 8, 0.261523650563322);
		circles.emplace_back(6, 9, 0.5486577232601121);
		circles.emplace_back(6, 10, 0.4090402231318876);
		circles.emplace_back(7, 0, 0.41717999225948);
		circles.emplace_back(7, 1, 0.411247051670216);
		circles.emplace_back(7, 2, 0.4001711211400106);
		circles.emplace_back(7, 3, 0.6298844928620383);
		circles.emplace_back(7, 4, 0.3340592574561015);
		circles.emplace_back(7, 5, 0.5923901442205534);
		circles.emplace_back(7, 6, 0.3705293827923015);
		circles.emplace_back(7, 7, 0.3431748603237793);
		circles.emplace_back(7, 8, 0.5962578861275688);
		circles.emplace_back(7, 9, 0.4481305805733427);
		circles.emplace_back(7, 10, 0.5299390073167159);
		circles.emplace_back(8, 0, 0.5787615700392053);
		circles.emplace_back(8, 1, 0.2707486585015431);
		circles.emplace_back(8, 2, 0.3576041124528274);
		circles.emplace_back(8, 3, 0.5612583187641575);
		circles.emplace_back(8, 4, 0.3534356319112703);
		circles.emplace_back(8, 5, 0.4744913848349824);
		circles.emplace_back(8, 6, 0.2106726573547348);
		circles.emplace_back(8, 7, 0.5268065481679514);
		circles.emplace_back(8, 8, 0.319817981380038);
		circles.emplace_back(8, 9, 0.5430974561953917);
		circles.emplace_back(8, 10, 0.522340802452527);
		circles.emplace_back(9, 0, 0.5459151030750945);
		circles.emplace_back(9, 1, 0.331459577078931);
		circles.emplace_back(9, 2, 0.4930490827420726);
		circles.emplace_back(9, 3, 0.1774457460036501);
		circles.emplace_back(9, 4, 0.5363460245775059);
		circles.emplace_back(9, 5, 0.2897774359909818);
		circles.emplace_back(9, 6, 0.5055982195073738);
		circles.emplace_back(9, 7, 0.2462456762557849);
		circles.emplace_back(9, 8, 0.4227026318432763);
		circles.emplace_back(9, 10, 0.5884516061050817);
		circles.emplace_back(10, 0, 0.6104701796779409);
		circles.emplace_back(10, 1, 0.3615315878530964);
		circles.emplace_back(10, 2, 0.4649573541479185);
		circles.emplace_back(10, 3, 0.4209080765722319);
		circles.emplace_back(10, 4, 0.2974969353759661);
		circles.emplace_back(10, 5, 0.397887535742484);
		circles.emplace_back(10, 6, 0.610221750405617);
		circles.emplace_back(10, 7, 0.4665126253617927);
		circles.emplace_back(10, 8, 0.6343051059404388);
		circles.emplace_back(10, 9, 0.5437243265798315);
		circles.emplace_back(10, 10, 0.3208837162004783);
	}
	result_expected = 15.45628204867654;
	timer.reset();
	result_actual = algorithm(a37, b37, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #37: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a38(1, 1);
	Point b38(9, 9);
	{
		circles.emplace_back(0, 0, 0.2442294869804755);
		circles.emplace_back(0, 1, 0.4495302494382485);
		circles.emplace_back(0, 2, 0.4458869771333411);
		circles.emplace_back(0, 3, 0.7266923871589824);
		circles.emplace_back(0, 4, 0.3141284277895465);
		circles.emplace_back(0, 5, 0.5316437979927287);
		circles.emplace_back(0, 6, 0.2173890608595684);
		circles.emplace_back(0, 7, 0.225096586975269);
		circles.emplace_back(0, 8, 0.5049611367518082);
		circles.emplace_back(0, 9, 0.4083670213585719);
		circles.emplace_back(0, 10, 0.2933697630884126);
		circles.emplace_back(1, 0, 0.5155817226273939);
		circles.emplace_back(1, 2, 0.336852096975781);
		circles.emplace_back(1, 3, 0.5523773887893185);
		circles.emplace_back(1, 4, 0.2476870111422613);
		circles.emplace_back(1, 5, 0.3082668985007331);
		circles.emplace_back(1, 6, 0.5944269817555323);
		circles.emplace_back(1, 7, 0.4438680860912427);
		circles.emplace_back(1, 8, 0.6887011432321742);
		circles.emplace_back(1, 9, 0.6297774140490219);
		circles.emplace_back(1, 10, 0.4616881428519264);
		circles.emplace_back(2, 0, 0.4285192070296034);
		circles.emplace_back(2, 1, 0.3170996154891327);
		circles.emplace_back(2, 2, 0.2022120489506051);
		circles.emplace_back(2, 3, 0.4160697862738743);
		circles.emplace_back(2, 4, 0.5338673822348937);
		circles.emplace_back(2, 5, 0.0882138964952901);
		circles.emplace_back(2, 6, 0.5070712857646867);
		circles.emplace_back(2, 7, 0.5597978355595842);
		circles.emplace_back(2, 8, 0.1346988456090912);
		circles.emplace_back(2, 9, 0.3319535493152216);
		circles.emplace_back(2, 10, 0.4997714700875804);
		circles.emplace_back(3, 0, 0.4166794825578108);
		circles.emplace_back(3, 1, 0.4080909382319078);
		circles.emplace_back(3, 2, 0.5334825010271743);
		circles.emplace_back(3, 3, 0.3903699082089588);
		circles.emplace_back(3, 4, 0.672447425709106);
		circles.emplace_back(3, 5, 0.2687270497670397);
		circles.emplace_back(3, 6, 0.2277624997543171);
		circles.emplace_back(3, 7, 0.4561259022681042);
		circles.emplace_back(3, 8, 0.2867837958270684);
		circles.emplace_back(3, 9, 0.6251099973684177);
		circles.emplace_back(3, 10, 0.5110887591959908);
		circles.emplace_back(4, 0, 0.5015227229101583);
		circles.emplace_back(4, 1, 0.2551487693795934);
		circles.emplace_back(4, 2, 0.4472988420864567);
		circles.emplace_back(4, 3, 0.1227427906589583);
		circles.emplace_back(4, 4, 0.331375519442372);
		circles.emplace_back(4, 5, 0.2485388692701235);
		circles.emplace_back(4, 6, 0.3867941427743062);
		circles.emplace_back(4, 7, 0.5998874225886538);
		circles.emplace_back(4, 8, 0.5526501674903557);
		circles.emplace_back(4, 9, 0.309299953118898);
		circles.emplace_back(4, 10, 0.4391966474941);
		circles.emplace_back(5, 0, 0.6588290076004341);
		circles.emplace_back(5, 1, 0.7706180541543289);
		circles.emplace_back(5, 2, 0.4311198890442028);
		circles.emplace_back(5, 3, 0.4902644224232062);
		circles.emplace_back(5, 4, 0.6057718170108274);
		circles.emplace_back(5, 5, 0.1949718006653711);
		circles.emplace_back(5, 6, 0.6013259189436212);
		circles.emplace_back(5, 7, 0.7359934182604775);
		circles.emplace_back(5, 8, 0.5301896228687838);
		circles.emplace_back(5, 9, 0.4215269225416705);
		circles.emplace_back(5, 10, 0.4336117092752829);
		circles.emplace_back(6, 0, 0.3173464741325006);
		circles.emplace_back(6, 1, 0.1839394674869254);
		circles.emplace_back(6, 2, 0.405134427244775);
		circles.emplace_back(6, 3, 0.3693190893391147);
		circles.emplace_back(6, 4, 0.4602557589998468);
		circles.emplace_back(6, 5, 0.4992426204727962);
		circles.emplace_back(6, 6, 0.4894293493358418);
		circles.emplace_back(6, 7, 0.5753994770580902);
		circles.emplace_back(6, 8, 0.261523650563322);
		circles.emplace_back(6, 9, 0.5486577232601121);
		circles.emplace_back(6, 10, 0.4090402231318876);
		circles.emplace_back(7, 0, 0.41717999225948);
		circles.emplace_back(7, 1, 0.411247051670216);
		circles.emplace_back(7, 2, 0.4001711211400106);
		circles.emplace_back(7, 3, 0.6298844928620383);
		circles.emplace_back(7, 4, 0.3340592574561015);
		circles.emplace_back(7, 5, 0.5923901442205534);
		circles.emplace_back(7, 6, 0.3705293827923015);
		circles.emplace_back(7, 7, 0.3431748603237793);
		circles.emplace_back(7, 8, 0.5962578861275688);
		circles.emplace_back(7, 9, 0.4481305805733427);
		circles.emplace_back(7, 10, 0.5299390073167159);
		circles.emplace_back(8, 0, 0.5787615700392053);
		circles.emplace_back(8, 1, 0.2707486585015431);
		circles.emplace_back(8, 2, 0.3576041124528274);
		circles.emplace_back(8, 3, 0.5612583187641575);
		circles.emplace_back(8, 4, 0.3534356319112703);
		circles.emplace_back(8, 5, 0.4744913848349824);
		circles.emplace_back(8, 6, 0.2106726573547348);
		circles.emplace_back(8, 7, 0.5268065481679514);
		circles.emplace_back(8, 8, 0.319817981380038);
		circles.emplace_back(8, 9, 0.5430974561953917);
		circles.emplace_back(8, 10, 0.522340802452527);
		circles.emplace_back(9, 0, 0.5459151030750945);
		circles.emplace_back(9, 1, 0.331459577078931);
		circles.emplace_back(9, 2, 0.4930490827420726);
		circles.emplace_back(9, 3, 0.1774457460036501);
		circles.emplace_back(9, 4, 0.5363460245775059);
		circles.emplace_back(9, 5, 0.2897774359909818);
		circles.emplace_back(9, 6, 0.5055982195073738);
		circles.emplace_back(9, 7, 0.2462456762557849);
		circles.emplace_back(9, 8, 0.4227026318432763);
		circles.emplace_back(9, 10, 0.5884516061050817);
		circles.emplace_back(10, 0, 0.6104701796779409);
		circles.emplace_back(10, 1, 0.3615315878530964);
		circles.emplace_back(10, 2, 0.4649573541479185);
		circles.emplace_back(10, 3, 0.4209080765722319);
		circles.emplace_back(10, 4, 0.2974969353759661);
		circles.emplace_back(10, 5, 0.397887535742484);
		circles.emplace_back(10, 6, 0.610221750405617);
		circles.emplace_back(10, 7, 0.4665126253617927);
		circles.emplace_back(10, 8, 0.6343051059404388);
		circles.emplace_back(10, 9, 0.5437243265798315);
		circles.emplace_back(10, 10, 0.3208837162004783);
	}
	result_expected = 11.57936863004565;
	timer.reset();
	result_actual = algorithm(a38, b38, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #38: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a39(1, 1);
	Point b39(9, 9);
	{
		circles.emplace_back(0, 0, 0.4211006044177338);
		circles.emplace_back(0, 1, 0.8181836337083951);
		circles.emplace_back(0, 2, 0.5067116476362571);
		circles.emplace_back(0, 3, 0.7822368783177808);
		circles.emplace_back(0, 4, 0.2874676623148844);
		circles.emplace_back(0, 5, 0.4402561472961679);
		circles.emplace_back(0, 6, 0.2432336332043633);
		circles.emplace_back(0, 7, 0.4427271767752245);
		circles.emplace_back(0, 8, 0.3914464044151827);
		circles.emplace_back(0, 9, 0.5900830123806372);
		circles.emplace_back(0, 10, 0.552492868504487);
		circles.emplace_back(1, 0, 0.4899416343541816);
		circles.emplace_back(1, 2, 0.6391939905239269);
		circles.emplace_back(1, 3, 0.6788180699804798);
		circles.emplace_back(1, 4, 0.5258878310909495);
		circles.emplace_back(1, 5, 0.415464313630946);
		circles.emplace_back(1, 6, 0.581315670046024);
		circles.emplace_back(1, 7, 0.6090450622374192);
		circles.emplace_back(1, 8, 0.6922887697583064);
		circles.emplace_back(1, 9, 0.2717244615079835);
		circles.emplace_back(1, 10, 0.1994492546422407);
		circles.emplace_back(2, 0, 0.369418745697476);
		circles.emplace_back(2, 1, 0.4498370209475979);
		circles.emplace_back(2, 2, 0.2739618412451819);
		circles.emplace_back(2, 3, 0.2809355283854529);
		circles.emplace_back(2, 4, 0.3822356920922175);
		circles.emplace_back(2, 5, 0.4248927626525983);
		circles.emplace_back(2, 6, 0.5504342519911006);
		circles.emplace_back(2, 7, 0.497199595416896);
		circles.emplace_back(2, 8, 0.6820597766200081);
		circles.emplace_back(2, 9, 0.4487562058260664);
		circles.emplace_back(2, 10, 0.3939922358142212);
		circles.emplace_back(3, 0, 0.6514681651024148);
		circles.emplace_back(3, 1, 0.7535273537272588);
		circles.emplace_back(3, 2, 0.4927872232859954);
		circles.emplace_back(3, 3, 0.418145972234197);
		circles.emplace_back(3, 4, 0.2114477746887133);
		circles.emplace_back(3, 5, 0.5064571203896776);
		circles.emplace_back(3, 6, 0.6525484161218628);
		circles.emplace_back(3, 7, 0.3707493602531031);
		circles.emplace_back(3, 8, 0.3925889494596049);
		circles.emplace_back(3, 9, 0.6163896668935195);
		circles.emplace_back(3, 10, 0.3215966176008805);
		circles.emplace_back(4, 0, 0.5084262878866866);
		circles.emplace_back(4, 1, 0.3075613003922626);
		circles.emplace_back(4, 2, 0.3086817151168361);
		circles.emplace_back(4, 3, 0.4455478345742449);
		circles.emplace_back(4, 4, 0.1848640891956165);
		circles.emplace_back(4, 5, 0.4475645593134686);
		circles.emplace_back(4, 6, 0.7142800443107262);
		circles.emplace_back(4, 7, 0.2970406263833865);
		circles.emplace_back(4, 8, 0.3560991888167336);
		circles.emplace_back(4, 9, 0.5111005515558645);
		circles.emplace_back(4, 10, 0.4753001043805852);
		circles.emplace_back(5, 0, 0.4622229212662205);
		circles.emplace_back(5, 1, 0.3559199339943007);
		circles.emplace_back(5, 2, 0.6458311061142012);
		circles.emplace_back(5, 3, 0.1285343166673556);
		circles.emplace_back(5, 4, 0.4793872702633962);
		circles.emplace_back(5, 5, 0.4445116141112521);
		circles.emplace_back(5, 6, 0.6191469033015892);
		circles.emplace_back(5, 7, 0.7450150622287764);
		circles.emplace_back(5, 8, 0.4203795386245474);
		circles.emplace_back(5, 9, 0.4834686677204445);
		circles.emplace_back(5, 10, 0.2830722599057481);
		circles.emplace_back(6, 0, 0.7537573576206341);
		circles.emplace_back(6, 1, 0.5554060347145423);
		circles.emplace_back(6, 2, 0.5402990770759061);
		circles.emplace_back(6, 3, 0.349130851845257);
		circles.emplace_back(6, 4, 0.4278062181780115);
		circles.emplace_back(6, 5, 0.2918640764197334);
		circles.emplace_back(6, 6, 0.3755459501640871);
		circles.emplace_back(6, 7, 0.2387973743258044);
		circles.emplace_back(6, 8, 0.5607137087965384);
		circles.emplace_back(6, 9, 0.4278209950542077);
		circles.emplace_back(6, 10, 0.3156512902351096);
		circles.emplace_back(7, 0, 0.7251601394964382);
		circles.emplace_back(7, 1, 0.6115706822136416);
		circles.emplace_back(7, 2, 0.3107665767660364);
		circles.emplace_back(7, 3, 0.4646869528340176);
		circles.emplace_back(7, 4, 0.3314196116058156);
		circles.emplace_back(7, 5, 0.5467182047897949);
		circles.emplace_back(7, 6, 0.5422639414435252);
		circles.emplace_back(7, 7, 0.1580777903320268);
		circles.emplace_back(7, 8, 0.7018478796584532);
		circles.emplace_back(7, 9, 0.5562636697897687);
		circles.emplace_back(7, 10, 0.4191238591214642);
		circles.emplace_back(8, 0, 0.3114419839577749);
		circles.emplace_back(8, 1, 0.3108340675709769);
		circles.emplace_back(8, 2, 0.4735265981638804);
		circles.emplace_back(8, 3, 0.4517275038873776);
		circles.emplace_back(8, 4, 0.3676735633285716);
		circles.emplace_back(8, 5, 0.4256406818283722);
		circles.emplace_back(8, 6, 0.2755391268292442);
		circles.emplace_back(8, 7, 0.3501226452877745);
		circles.emplace_back(8, 8, 0.5953921134816482);
		circles.emplace_back(8, 9, 0.2884958966402337);
		circles.emplace_back(8, 10, 0.4927261844510212);
		circles.emplace_back(9, 0, 0.4185182772343978);
		circles.emplace_back(9, 1, 0.2418846694054082);
		circles.emplace_back(9, 2, 0.3336467765970155);
		circles.emplace_back(9, 3, 0.6058903547236696);
		circles.emplace_back(9, 4, 0.3488026844104752);
		circles.emplace_back(9, 5, 0.4936647980706766);
		circles.emplace_back(9, 6, 0.6049984368262812);
		circles.emplace_back(9, 7, 0.2586264271521941);
		circles.emplace_back(9, 8, 0.3537099461769685);
		circles.emplace_back(9, 10, 0.6477738679619506);
		circles.emplace_back(10, 0, 0.5899641406489536);
		circles.emplace_back(10, 1, 0.4632906353333965);
		circles.emplace_back(10, 2, 0.4302598779788241);
		circles.emplace_back(10, 3, 0.3469495061086491);
		circles.emplace_back(10, 4, 0.5351513347355649);
		circles.emplace_back(10, 5, 0.3286495827371255);
		circles.emplace_back(10, 6, 0.2940964102512225);
		circles.emplace_back(10, 7, 0.1817862426163629);
		circles.emplace_back(10, 8, 0.5595086217625066);
		circles.emplace_back(10, 9, 0.2873338559875265);
		circles.emplace_back(10, 10, 0.275349404825829);
	}
	result_expected = 11.57936863004565;
	timer.reset();
	result_actual = algorithm(a39, b39, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #39: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a40(1, 1);
	Point b40(9, 9);
	{
		circles.emplace_back(0, 0, 0.4211006044177338);
		circles.emplace_back(0, 1, 0.8181836337083951);
		circles.emplace_back(0, 2, 0.5067116476362571);
		circles.emplace_back(0, 3, 0.7822368783177808);
		circles.emplace_back(0, 4, 0.2874676623148844);
		circles.emplace_back(0, 5, 0.4402561472961679);
		circles.emplace_back(0, 6, 0.2432336332043633);
		circles.emplace_back(0, 7, 0.4427271767752245);
		circles.emplace_back(0, 8, 0.3914464044151827);
		circles.emplace_back(0, 9, 0.5900830123806372);
		circles.emplace_back(0, 10, 0.552492868504487);
		circles.emplace_back(1, 0, 0.4899416343541816);
		circles.emplace_back(1, 2, 0.6391939905239269);
		circles.emplace_back(1, 3, 0.6788180699804798);
		circles.emplace_back(1, 4, 0.5258878310909495);
		circles.emplace_back(1, 5, 0.415464313630946);
		circles.emplace_back(1, 6, 0.581315670046024);
		circles.emplace_back(1, 7, 0.6090450622374192);
		circles.emplace_back(1, 8, 0.6922887697583064);
		circles.emplace_back(1, 9, 0.2717244615079835);
		circles.emplace_back(1, 10, 0.1994492546422407);
		circles.emplace_back(2, 0, 0.369418745697476);
		circles.emplace_back(2, 1, 0.4498370209475979);
		circles.emplace_back(2, 2, 0.2739618412451819);
		circles.emplace_back(2, 3, 0.2809355283854529);
		circles.emplace_back(2, 4, 0.3822356920922175);
		circles.emplace_back(2, 5, 0.4248927626525983);
		circles.emplace_back(2, 6, 0.5504342519911006);
		circles.emplace_back(2, 7, 0.497199595416896);
		circles.emplace_back(2, 8, 0.6820597766200081);
		circles.emplace_back(2, 9, 0.4487562058260664);
		circles.emplace_back(2, 10, 0.3939922358142212);
		circles.emplace_back(3, 0, 0.6514681651024148);
		circles.emplace_back(3, 1, 0.7535273537272588);
		circles.emplace_back(3, 2, 0.4927872232859954);
		circles.emplace_back(3, 3, 0.418145972234197);
		circles.emplace_back(3, 4, 0.2114477746887133);
		circles.emplace_back(3, 5, 0.5064571203896776);
		circles.emplace_back(3, 6, 0.6525484161218628);
		circles.emplace_back(3, 7, 0.3707493602531031);
		circles.emplace_back(3, 8, 0.3925889494596049);
		circles.emplace_back(3, 9, 0.6163896668935195);
		circles.emplace_back(3, 10, 0.3215966176008805);
		circles.emplace_back(4, 0, 0.5084262878866866);
		circles.emplace_back(4, 1, 0.3075613003922626);
		circles.emplace_back(4, 2, 0.3086817151168361);
		circles.emplace_back(4, 3, 0.4455478345742449);
		circles.emplace_back(4, 4, 0.1848640891956165);
		circles.emplace_back(4, 5, 0.4475645593134686);
		circles.emplace_back(4, 6, 0.7142800443107262);
		circles.emplace_back(4, 7, 0.2970406263833865);
		circles.emplace_back(4, 8, 0.3560991888167336);
		circles.emplace_back(4, 9, 0.5111005515558645);
		circles.emplace_back(4, 10, 0.4753001043805852);
		circles.emplace_back(5, 0, 0.4622229212662205);
		circles.emplace_back(5, 1, 0.3559199339943007);
		circles.emplace_back(5, 2, 0.6458311061142012);
		circles.emplace_back(5, 3, 0.1285343166673556);
		circles.emplace_back(5, 4, 0.4793872702633962);
		circles.emplace_back(5, 5, 0.4445116141112521);
		circles.emplace_back(5, 6, 0.6191469033015892);
		circles.emplace_back(5, 7, 0.7450150622287764);
		circles.emplace_back(5, 8, 0.4203795386245474);
		circles.emplace_back(5, 9, 0.4834686677204445);
		circles.emplace_back(5, 10, 0.2830722599057481);
		circles.emplace_back(6, 0, 0.7537573576206341);
		circles.emplace_back(6, 1, 0.5554060347145423);
		circles.emplace_back(6, 2, 0.5402990770759061);
		circles.emplace_back(6, 3, 0.349130851845257);
		circles.emplace_back(6, 4, 0.4278062181780115);
		circles.emplace_back(6, 5, 0.2918640764197334);
		circles.emplace_back(6, 6, 0.3755459501640871);
		circles.emplace_back(6, 7, 0.2387973743258044);
		circles.emplace_back(6, 8, 0.5607137087965384);
		circles.emplace_back(6, 9, 0.4278209950542077);
		circles.emplace_back(6, 10, 0.3156512902351096);
		circles.emplace_back(7, 0, 0.7251601394964382);
		circles.emplace_back(7, 1, 0.6115706822136416);
		circles.emplace_back(7, 2, 0.3107665767660364);
		circles.emplace_back(7, 3, 0.4646869528340176);
		circles.emplace_back(7, 4, 0.3314196116058156);
		circles.emplace_back(7, 5, 0.5467182047897949);
		circles.emplace_back(7, 6, 0.5422639414435252);
		circles.emplace_back(7, 7, 0.1580777903320268);
		circles.emplace_back(7, 8, 0.7018478796584532);
		circles.emplace_back(7, 9, 0.5562636697897687);
		circles.emplace_back(7, 10, 0.4191238591214642);
		circles.emplace_back(8, 0, 0.3114419839577749);
		circles.emplace_back(8, 1, 0.3108340675709769);
		circles.emplace_back(8, 2, 0.4735265981638804);
		circles.emplace_back(8, 3, 0.4517275038873776);
		circles.emplace_back(8, 4, 0.3676735633285716);
		circles.emplace_back(8, 5, 0.4256406818283722);
		circles.emplace_back(8, 6, 0.2755391268292442);
		circles.emplace_back(8, 7, 0.3501226452877745);
		circles.emplace_back(8, 8, 0.5953921134816482);
		circles.emplace_back(8, 9, 0.2884958966402337);
		circles.emplace_back(8, 10, 0.4927261844510212);
		circles.emplace_back(9, 0, 0.4185182772343978);
		circles.emplace_back(9, 1, 0.2418846694054082);
		circles.emplace_back(9, 2, 0.3336467765970155);
		circles.emplace_back(9, 3, 0.6058903547236696);
		circles.emplace_back(9, 4, 0.3488026844104752);
		circles.emplace_back(9, 5, 0.4936647980706766);
		circles.emplace_back(9, 6, 0.6049984368262812);
		circles.emplace_back(9, 7, 0.2586264271521941);
		circles.emplace_back(9, 8, 0.3537099461769685);
		circles.emplace_back(9, 10, 0.6477738679619506);
		circles.emplace_back(10, 0, 0.5899641406489536);
		circles.emplace_back(10, 1, 0.4632906353333965);
		circles.emplace_back(10, 2, 0.4302598779788241);
		circles.emplace_back(10, 3, 0.3469495061086491);
		circles.emplace_back(10, 4, 0.5351513347355649);
		circles.emplace_back(10, 5, 0.3286495827371255);
		circles.emplace_back(10, 6, 0.2940964102512225);
		circles.emplace_back(10, 7, 0.1817862426163629);
		circles.emplace_back(10, 8, 0.5595086217625066);
		circles.emplace_back(10, 9, 0.2873338559875265);
		circles.emplace_back(10, 10, 0.275349404825829);
	}
	result_expected = 11.66006079253472;
	timer.reset();
	result_actual = algorithm(a40, b40, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #40: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a41(1, 1);
	Point b41(9, 9);
	{
		circles.emplace_back(0, 0, 0.6130133426981047);
		circles.emplace_back(0, 1, 0.3305586705682799);
		circles.emplace_back(0, 2, 0.7512213256442919);
		circles.emplace_back(0, 3, 0.6166449088370427);
		circles.emplace_back(0, 4, 0.5170148262055591);
		circles.emplace_back(0, 5, 0.719342063809745);
		circles.emplace_back(0, 6, 0.572875134483911);
		circles.emplace_back(0, 7, 0.3638888461282477);
		circles.emplace_back(0, 8, 0.7077166746603325);
		circles.emplace_back(0, 9, 0.5996970831183717);
		circles.emplace_back(0, 10, 0.4411613732809201);
		circles.emplace_back(1, 0, 0.4904491461580619);
		circles.emplace_back(1, 2, 0.5379662257852033);
		circles.emplace_back(1, 3, 0.407500431756489);
		circles.emplace_back(1, 4, 0.5891714440891519);
		circles.emplace_back(1, 5, 0.445361310406588);
		circles.emplace_back(1, 6, 0.4335287555353716);
		circles.emplace_back(1, 7, 0.2254938947735354);
		circles.emplace_back(1, 8, 0.3425741110229865);
		circles.emplace_back(1, 9, 0.5661824162816629);
		circles.emplace_back(1, 10, 0.8628262476297095);
		circles.emplace_back(2, 0, 0.4093219366623089);
		circles.emplace_back(2, 1, 0.2865222385386005);
		circles.emplace_back(2, 2, 0.4471185585251078);
		circles.emplace_back(2, 3, 0.395543350582011);
		circles.emplace_back(2, 4, 0.3204052365152165);
		circles.emplace_back(2, 5, 0.4792392172152176);
		circles.emplace_back(2, 6, 0.3030507281189784);
		circles.emplace_back(2, 7, 0.4532255222322419);
		circles.emplace_back(2, 8, 0.481275160680525);
		circles.emplace_back(2, 9, 0.2904100770363584);
		circles.emplace_back(2, 10, 0.5200841286918149);
		circles.emplace_back(3, 0, 0.5049943617777899);
		circles.emplace_back(3, 1, 0.4189941729186102);
		circles.emplace_back(3, 2, 0.4925022881710902);
		circles.emplace_back(3, 3, 0.4332459304248914);
		circles.emplace_back(3, 4, 0.6115051293047145);
		circles.emplace_back(3, 5, 0.5122871820582077);
		circles.emplace_back(3, 6, 0.5831412492552772);
		circles.emplace_back(3, 7, 0.521956461458467);
		circles.emplace_back(3, 8, 0.7702714528189972);
		circles.emplace_back(3, 9, 0.408008827152662);
		circles.emplace_back(3, 10, 0.3666654631728306);
		circles.emplace_back(4, 0, 0.6638988367980346);
		circles.emplace_back(4, 1, 0.4654822227777913);
		circles.emplace_back(4, 2, 0.5225717001361773);
		circles.emplace_back(4, 3, 0.5729864003369585);
		circles.emplace_back(4, 4, 0.4379120247205719);
		circles.emplace_back(4, 5, 0.475435674120672);
		circles.emplace_back(4, 6, 0.3939605059800669);
		circles.emplace_back(4, 7, 0.7418780494714156);
		circles.emplace_back(4, 8, 0.4165323506807908);
		circles.emplace_back(4, 9, 0.4407156558008865);
		circles.emplace_back(4, 10, 0.399957160349004);
		circles.emplace_back(5, 0, 0.2508211558917537);
		circles.emplace_back(5, 1, 0.5388084387173876);
		circles.emplace_back(5, 2, 0.2462350878166035);
		circles.emplace_back(5, 3, 0.3082018247572705);
		circles.emplace_back(5, 4, 0.4145271472865715);
		circles.emplace_back(5, 5, 0.5040145903592929);
		circles.emplace_back(5, 6, 0.5202716057421639);
		circles.emplace_back(5, 7, 0.5737148792250082);
		circles.emplace_back(5, 8, 0.3342667469987646);
		circles.emplace_back(5, 9, 0.6768876010319218);
		circles.emplace_back(5, 10, 0.1036203927593306);
		circles.emplace_back(6, 0, 0.449504832434468);
		circles.emplace_back(6, 1, 0.3251282748067751);
		circles.emplace_back(6, 2, 0.6450120139634237);
		circles.emplace_back(6, 3, 0.4919891991885379);
		circles.emplace_back(6, 4, 0.6258871693862602);
		circles.emplace_back(6, 5, 0.4993306352058425);
		circles.emplace_back(6, 6, 0.5189788115909323);
		circles.emplace_back(6, 7, 0.4047605495201423);
		circles.emplace_back(6, 8, 0.5641391365556047);
		circles.emplace_back(6, 9, 0.5337159931892529);
		circles.emplace_back(6, 10, 0.6159425444668158);
		circles.emplace_back(7, 0, 0.3832461369456723);
		circles.emplace_back(7, 1, 0.3401154645485803);
		circles.emplace_back(7, 2, 0.4995471375295892);
		circles.emplace_back(7, 3, 0.7172018976649269);
		circles.emplace_back(7, 4, 0.571558405389078);
		circles.emplace_back(7, 5, 0.4634500282583758);
		circles.emplace_back(7, 6, 0.6827345315599814);
		circles.emplace_back(7, 7, 0.5404286946868524);
		circles.emplace_back(7, 8, 0.4832243190379813);
		circles.emplace_back(7, 9, 0.4879684445215389);
		circles.emplace_back(7, 10, 0.5726180514553562);
		circles.emplace_back(8, 0, 0.8171703388681635);
		circles.emplace_back(8, 1, 0.1066663193749264);
		circles.emplace_back(8, 2, 0.3789366072742268);
		circles.emplace_back(8, 3, 0.6474284120136872);
		circles.emplace_back(8, 4, 0.316250692284666);
		circles.emplace_back(8, 5, 0.352675469708629);
		circles.emplace_back(8, 6, 0.3527701602084562);
		circles.emplace_back(8, 7, 0.5345532799372449);
		circles.emplace_back(8, 8, 0.5036943921586499);
		circles.emplace_back(8, 9, 0.3970017872052267);
		circles.emplace_back(8, 10, 0.454829906928353);
		circles.emplace_back(9, 0, 0.4737330746138468);
		circles.emplace_back(9, 1, 0.5797996047651395);
		circles.emplace_back(9, 2, 0.4211867624195292);
		circles.emplace_back(9, 3, 0.3909281586064026);
		circles.emplace_back(9, 4, 0.5613114563981071);
		circles.emplace_back(9, 5, 0.5839842168381437);
		circles.emplace_back(9, 6, 0.404763066326268);
		circles.emplace_back(9, 7, 0.5781710191396996);
		circles.emplace_back(9, 8, 0.2036655023926869);
		circles.emplace_back(9, 10, 0.4080304644769058);
		circles.emplace_back(10, 0, 0.1719464448513463);
		circles.emplace_back(10, 1, 0.7307616078061983);
		circles.emplace_back(10, 2, 0.3579405697295442);
		circles.emplace_back(10, 3, 0.408352999552153);
		circles.emplace_back(10, 4, 0.3459448009030893);
		circles.emplace_back(10, 5, 0.246389219420962);
		circles.emplace_back(10, 6, 0.488214846351184);
		circles.emplace_back(10, 7, 0.4579153936123475);
		circles.emplace_back(10, 8, 0.4140094639034942);
		circles.emplace_back(10, 9, 0.3088294219924137);
		circles.emplace_back(10, 10, 0.6152185892919079);
	}
	result_expected = 15.92962469198705;
	timer.reset();
	result_actual = algorithm(a41, b41, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #41: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a42(1, 1);
	Point b42(9, 9);
	{
		circles.emplace_back(0, 0, 0.7284200792899355);
		circles.emplace_back(0, 1, 0.1563536468194797);
		circles.emplace_back(0, 2, 0.5723800918785855);
		circles.emplace_back(0, 3, 0.3877330504590645);
		circles.emplace_back(0, 4, 0.4433967292075977);
		circles.emplace_back(0, 5, 0.3420630906941369);
		circles.emplace_back(0, 6, 0.543758386443369);
		circles.emplace_back(0, 7, 0.7537940899142995);
		circles.emplace_back(0, 8, 0.292814072384499);
		circles.emplace_back(0, 9, 0.2451238966779783);
		circles.emplace_back(0, 10, 0.6270836542127654);
		circles.emplace_back(1, 0, 0.4598254766548052);
		circles.emplace_back(1, 2, 0.5498401481425389);
		circles.emplace_back(1, 3, 0.7836925455601885);
		circles.emplace_back(1, 4, 0.3475712825311348);
		circles.emplace_back(1, 5, 0.7558268768945708);
		circles.emplace_back(1, 6, 0.5803759975126013);
		circles.emplace_back(1, 7, 0.6357331047998741);
		circles.emplace_back(1, 8, 0.4195624827174469);
		circles.emplace_back(1, 9, 0.3347415298456326);
		circles.emplace_back(1, 10, 0.7859877921408042);
		circles.emplace_back(2, 0, 0.4341466230573133);
		circles.emplace_back(2, 1, 0.7745150127215311);
		circles.emplace_back(2, 2, 0.4841286109993234);
		circles.emplace_back(2, 3, 0.3708624006947502);
		circles.emplace_back(2, 4, 0.5945177122252062);
		circles.emplace_back(2, 5, 0.6145798372803256);
		circles.emplace_back(2, 6, 0.3782652829075232);
		circles.emplace_back(2, 7, 0.3734113927697763);
		circles.emplace_back(2, 8, 0.6786033169599249);
		circles.emplace_back(2, 9, 0.4073887255741283);
		circles.emplace_back(2, 10, 0.3888034334639087);
		circles.emplace_back(3, 0, 0.8531484802952036);
		circles.emplace_back(3, 1, 0.5466886717127636);
		circles.emplace_back(3, 2, 0.4876777863828465);
		circles.emplace_back(3, 3, 0.5421061016852036);
		circles.emplace_back(3, 4, 0.7734653964405879);
		circles.emplace_back(3, 5, 0.4019354452611879);
		circles.emplace_back(3, 6, 0.3813719407422468);
		circles.emplace_back(3, 7, 0.3013885909924284);
		circles.emplace_back(3, 8, 0.2709312120219692);
		circles.emplace_back(3, 9, 0.5798470727400854);
		circles.emplace_back(3, 10, 0.1177553321002051);
		circles.emplace_back(4, 0, 0.3017892699921503);
		circles.emplace_back(4, 1, 0.351740089408122);
		circles.emplace_back(4, 2, 0.2859762751730159);
		circles.emplace_back(4, 3, 0.4453526739729568);
		circles.emplace_back(4, 4, 0.5164950607577339);
		circles.emplace_back(4, 5, 0.3059324739268049);
		circles.emplace_back(4, 6, 0.6349997665034607);
		circles.emplace_back(4, 7, 0.2171465351013467);
		circles.emplace_back(4, 8, 0.2820466146105901);
		circles.emplace_back(4, 9, 0.4800147227710113);
		circles.emplace_back(4, 10, 0.09428514812607318);
		circles.emplace_back(5, 0, 0.1607555621070787);
		circles.emplace_back(5, 1, 0.3609481754014268);
		circles.emplace_back(5, 2, 0.1986021714052185);
		circles.emplace_back(5, 3, 0.2850749909179285);
		circles.emplace_back(5, 4, 0.4991986396489665);
		circles.emplace_back(5, 5, 0.4697071302914992);
		circles.emplace_back(5, 6, 0.5757106374716386);
		circles.emplace_back(5, 7, 0.6444131047697738);
		circles.emplace_back(5, 8, 0.4378699880791828);
		circles.emplace_back(5, 9, 0.5504282480338588);
		circles.emplace_back(5, 10, 0.2063213621964678);
		circles.emplace_back(6, 0, 0.5009379956172779);
		circles.emplace_back(6, 1, 0.4833501985995099);
		circles.emplace_back(6, 2, 0.4140876047546044);
		circles.emplace_back(6, 3, 0.6788443892961368);
		circles.emplace_back(6, 4, 0.5676685099722817);
		circles.emplace_back(6, 5, 0.6096782059175894);
		circles.emplace_back(6, 6, 0.3336111972341314);
		circles.emplace_back(6, 7, 0.2991053813835606);
		circles.emplace_back(6, 8, 0.504906666954048);
		circles.emplace_back(6, 9, 0.6377091984031722);
		circles.emplace_back(6, 10, 0.2148832436883822);
		circles.emplace_back(7, 0, 0.4664808738743886);
		circles.emplace_back(7, 1, 0.1563826778205112);
		circles.emplace_back(7, 2, 0.3431834657443687);
		circles.emplace_back(7, 3, 0.2238091720500961);
		circles.emplace_back(7, 4, 0.3928069663932547);
		circles.emplace_back(7, 5, 0.5117671529995277);
		circles.emplace_back(7, 6, 0.5591311841038987);
		circles.emplace_back(7, 7, 0.4975582957500592);
		circles.emplace_back(7, 8, 0.4046864516800269);
		circles.emplace_back(7, 9, 0.298675496620126);
		circles.emplace_back(7, 10, 0.3882381387753412);
		circles.emplace_back(8, 0, 0.4181111769983545);
		circles.emplace_back(8, 1, 0.3198193819960579);
		circles.emplace_back(8, 2, 0.4572894885437563);
		circles.emplace_back(8, 3, 0.1907973843393847);
		circles.emplace_back(8, 4, 0.4762366775656119);
		circles.emplace_back(8, 5, 0.5379820730304345);
		circles.emplace_back(8, 6, 0.4007210538955405);
		circles.emplace_back(8, 7, 0.3638718423200771);
		circles.emplace_back(8, 8, 0.3040236970642581);
		circles.emplace_back(8, 9, 0.7372795453062281);
		circles.emplace_back(8, 10, 0.4142432200955227);
		circles.emplace_back(9, 0, 0.4772928363410756);
		circles.emplace_back(9, 1, 0.7040925987297669);
		circles.emplace_back(9, 2, 0.5162964030867442);
		circles.emplace_back(9, 3, 0.3965132613899186);
		circles.emplace_back(9, 4, 0.1821195647818968);
		circles.emplace_back(9, 5, 0.5536113227019086);
		circles.emplace_back(9, 6, 0.7727711507817731);
		circles.emplace_back(9, 7, 0.295913030882366);
		circles.emplace_back(9, 8, 0.4571845109341666);
		circles.emplace_back(9, 10, 0.6112411868060007);
		circles.emplace_back(10, 0, 0.8594189468538388);
		circles.emplace_back(10, 1, 0.2451314800651744);
		circles.emplace_back(10, 2, 0.3093497906578704);
		circles.emplace_back(10, 3, 0.3051373748341575);
		circles.emplace_back(10, 4, 0.5075277952244505);
		circles.emplace_back(10, 5, 0.3471143658505753);
		circles.emplace_back(10, 6, 0.3930994375376031);
		circles.emplace_back(10, 7, 0.4301291123265401);
		circles.emplace_back(10, 8, 0.6589531741803512);
		circles.emplace_back(10, 9, 0.5155061451019719);
		circles.emplace_back(10, 10, 0.2650926255388185);
	}
	result_expected = 17.08855326005014;
	timer.reset();
	result_actual = algorithm(a42, b42, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #42: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();







	Point a43(1, 1);
	Point b43(9, 9);
	{circles.emplace_back(0, 0, 0.5322045298526064);
	circles.emplace_back(0, 1, 0.7971361027797684);
	circles.emplace_back(0, 2, 0.3227090566651896);
	circles.emplace_back(0, 3, 0.1393028291640803);
	circles.emplace_back(0, 4, 0.3084252137923613);
	circles.emplace_back(0, 5, 0.4177696447586641);
	circles.emplace_back(0, 6, 0.4586843908997252);
	circles.emplace_back(0, 7, 0.4583679211093112);
	circles.emplace_back(0, 8, 0.7003954446176067);
	circles.emplace_back(0, 9, 0.7297388499369845);
	circles.emplace_back(0, 10, 0.6536209467099979);
	circles.emplace_back(1, 0, 0.2467762074200436);
	circles.emplace_back(1, 2, 0.5094111226731911);
	circles.emplace_back(1, 3, 0.4269591331249103);
	circles.emplace_back(1, 4, 0.4675956760765985);
	circles.emplace_back(1, 5, 0.161513400147669);
	circles.emplace_back(1, 6, 0.4114133814582601);
	circles.emplace_back(1, 7, 0.5217380905291066);
	circles.emplace_back(1, 8, 0.5003515160875395);
	circles.emplace_back(1, 9, 0.7057955275056883);
	circles.emplace_back(1, 10, 0.2998718884075061);
	circles.emplace_back(2, 0, 0.6802857536589727);
	circles.emplace_back(2, 1, 0.5243174084695056);
	circles.emplace_back(2, 2, 0.321512781525962);
	circles.emplace_back(2, 3, 0.3347228331724182);
	circles.emplace_back(2, 4, 0.5509982807328925);
	circles.emplace_back(2, 5, 0.4939955066191032);
	circles.emplace_back(2, 6, 0.6260093032149597);
	circles.emplace_back(2, 7, 0.3254866034025326);
	circles.emplace_back(2, 8, 0.226140085584484);
	circles.emplace_back(2, 9, 0.3348405701341107);
	circles.emplace_back(2, 10, 0.4088239052100107);
	circles.emplace_back(3, 0, 0.3266901480266824);
	circles.emplace_back(3, 1, 0.7275494040688499);
	circles.emplace_back(3, 2, 0.5647565468447283);
	circles.emplace_back(3, 3, 0.3540167319355532);
	circles.emplace_back(3, 4, 0.3737190280342474);
	circles.emplace_back(3, 5, 0.4569922979688272);
	circles.emplace_back(3, 6, 0.551335342344828);
	circles.emplace_back(3, 7, 0.1037068572593853);
	circles.emplace_back(3, 8, 0.1372241547564045);
	circles.emplace_back(3, 9, 0.501790096401237);
	circles.emplace_back(3, 10, 0.3579627770232037);
	circles.emplace_back(4, 0, 0.328445819648914);
	circles.emplace_back(4, 1, 0.3242082156473771);
	circles.emplace_back(4, 2, 0.636345274723135);
	circles.emplace_back(4, 3, 0.5819167305948213);
	circles.emplace_back(4, 4, 0.4200520948274061);
	circles.emplace_back(4, 5, 0.6039167875656858);
	circles.emplace_back(4, 6, 0.7101907709380612);
	circles.emplace_back(4, 7, 0.7375824741320685);
	circles.emplace_back(4, 8, 0.2725315059302374);
	circles.emplace_back(4, 9, 0.386659137555398);
	circles.emplace_back(4, 10, 0.3631877396022901);
	circles.emplace_back(5, 0, 0.4879101895960047);
	circles.emplace_back(5, 1, 0.6667085711611435);
	circles.emplace_back(5, 2, 0.533683711127378);
	circles.emplace_back(5, 3, 0.6584967432310804);
	circles.emplace_back(5, 4, 0.3772396768676117);
	circles.emplace_back(5, 5, 0.5241937889484688);
	circles.emplace_back(5, 6, 0.3262333080405369);
	circles.emplace_back(5, 7, 0.2739473812049255);
	circles.emplace_back(5, 8, 0.3686172482790425);
	circles.emplace_back(5, 9, 0.2463118606014177);
	circles.emplace_back(5, 10, 0.6719049455830827);
	circles.emplace_back(6, 0, 0.3424313561758026);
	circles.emplace_back(6, 1, 0.3387298106448725);
	circles.emplace_back(6, 2, 0.4036158504663035);
	circles.emplace_back(6, 3, 0.6764394093537703);
	circles.emplace_back(6, 4, 0.6819439779734239);
	circles.emplace_back(6, 5, 0.5335811347933486);
	circles.emplace_back(6, 6, 0.4916122835827991);
	circles.emplace_back(6, 7, 0.3590654915431514);
	circles.emplace_back(6, 8, 0.6058991050114855);
	circles.emplace_back(6, 9, 0.4380353125976398);
	circles.emplace_back(6, 10, 0.5183221808401868);
	circles.emplace_back(7, 0, 0.2395239167148247);
	circles.emplace_back(7, 1, 0.5543425231939182);
	circles.emplace_back(7, 2, 0.6623524015070871);
	circles.emplace_back(7, 3, 0.539303031633608);
	circles.emplace_back(7, 4, 0.3748959550866857);
	circles.emplace_back(7, 5, 0.3366887623211369);
	circles.emplace_back(7, 6, 0.2988412565784529);
	circles.emplace_back(7, 7, 0.6057567040203139);
	circles.emplace_back(7, 8, 0.6743617233121767);
	circles.emplace_back(7, 9, 0.4266063499962911);
	circles.emplace_back(7, 10, 0.3517545500071719);
	circles.emplace_back(8, 0, 0.4413482923759147);
	circles.emplace_back(8, 1, 0.5700131727615371);
	circles.emplace_back(8, 2, 0.2996765030315146);
	circles.emplace_back(8, 3, 0.5935509781586006);
	circles.emplace_back(8, 4, 0.4133609025506302);
	circles.emplace_back(8, 5, 0.4718467653030529);
	circles.emplace_back(8, 6, 0.5544502563541754);
	circles.emplace_back(8, 7, 0.4506496560992673);
	circles.emplace_back(8, 8, 0.7138113745255396);
	circles.emplace_back(8, 9, 0.3850608365843072);
	circles.emplace_back(8, 10, 0.4075290294131264);
	circles.emplace_back(9, 0, 0.2718016996281221);
	circles.emplace_back(9, 1, 0.6161519425688311);
	circles.emplace_back(9, 2, 0.8177826468134298);
	circles.emplace_back(9, 3, 0.3032936300849542);
	circles.emplace_back(9, 4, 0.3822039948077872);
	circles.emplace_back(9, 5, 0.7231828328920528);
	circles.emplace_back(9, 6, 0.1573501190403476);
	circles.emplace_back(9, 7, 0.6289066960802302);
	circles.emplace_back(9, 8, 0.2764801549958065);
	circles.emplace_back(9, 10, 0.4718007988063618);
	circles.emplace_back(10, 0, 0.2432732649380341);
	circles.emplace_back(10, 1, 0.57521357384976);
	circles.emplace_back(10, 2, 0.4536536653758958);
	circles.emplace_back(10, 3, 0.4102085933787748);
	circles.emplace_back(10, 4, 0.5150002980837598);
	circles.emplace_back(10, 5, 0.4341666349908337);
	circles.emplace_back(10, 6, 0.2472382149891928);
	circles.emplace_back(10, 7, 0.6132103795884177);
	circles.emplace_back(10, 8, 0.5626134347403422);
	circles.emplace_back(10, 9, 0.5733980301534757);
	circles.emplace_back(10, 10, 0.753570216265507); }
	result_expected = 14.82031007417728;
	timer.reset();
	result_actual = algorithm(a43, b43, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #43: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a44(1, 1);
	Point b44(9, 9);
	{
		circles.emplace_back(0, 0, 0.2512180779827758);
		circles.emplace_back(0, 1, 0.4585793821373954);
		circles.emplace_back(0, 2, 0.3785658804466948);
		circles.emplace_back(0, 3, 0.51150851205457);
		circles.emplace_back(0, 4, 0.478593651833944);
		circles.emplace_back(0, 5, 0.6986795142525807);
		circles.emplace_back(0, 6, 0.3040989063447341);
		circles.emplace_back(0, 7, 0.536626270157285);
		circles.emplace_back(0, 8, 0.3569523297948763);
		circles.emplace_back(0, 9, 0.430244735092856);
		circles.emplace_back(0, 10, 0.7229644940933212);
		circles.emplace_back(1, 0, 0.3630200653569773);
		circles.emplace_back(1, 2, 0.5790517660556361);
		circles.emplace_back(1, 3, 0.5958200294757262);
		circles.emplace_back(1, 4, 0.4160851996159181);
		circles.emplace_back(1, 5, 0.1958611489506438);
		circles.emplace_back(1, 6, 0.5088921379996464);
		circles.emplace_back(1, 7, 0.7703837013104931);
		circles.emplace_back(1, 8, 0.3920286899199709);
		circles.emplace_back(1, 9, 0.4278139057802036);
		circles.emplace_back(1, 10, 0.6036521813599393);
		circles.emplace_back(2, 0, 0.2202462993795052);
		circles.emplace_back(2, 1, 0.2775961220031604);
		circles.emplace_back(2, 2, 0.7224464987637474);
		circles.emplace_back(2, 3, 0.2330861628754064);
		circles.emplace_back(2, 4, 0.3617542306194082);
		circles.emplace_back(2, 5, 0.4699339592596516);
		circles.emplace_back(2, 6, 0.4177587009267881);
		circles.emplace_back(2, 7, 0.5620067904470488);
		circles.emplace_back(2, 8, 0.5479230609023943);
		circles.emplace_back(2, 9, 0.2907942253863439);
		circles.emplace_back(2, 10, 0.3529519149335101);
		circles.emplace_back(3, 0, 0.4114790607942268);
		circles.emplace_back(3, 1, 0.2611255033174529);
		circles.emplace_back(3, 2, 0.5335681957891211);
		circles.emplace_back(3, 3, 0.3715663801180198);
		circles.emplace_back(3, 4, 0.4643500446109101);
		circles.emplace_back(3, 5, 0.5399590939516201);
		circles.emplace_back(3, 6, 0.6437185264891013);
		circles.emplace_back(3, 7, 0.7041105670155957);
		circles.emplace_back(3, 8, 0.4307396092219278);
		circles.emplace_back(3, 9, 0.6184185551712289);
		circles.emplace_back(3, 10, 0.1232348205288872);
		circles.emplace_back(4, 0, 0.5833077593939379);
		circles.emplace_back(4, 1, 0.3391170787392184);
		circles.emplace_back(4, 2, 0.3054978464031592);
		circles.emplace_back(4, 3, 0.3997376318788156);
		circles.emplace_back(4, 4, 0.4950848237844184);
		circles.emplace_back(4, 5, 0.4685888317180797);
		circles.emplace_back(4, 6, 0.4833469024160877);
		circles.emplace_back(4, 7, 0.5508559068432077);
		circles.emplace_back(4, 8, 0.5184281665133312);
		circles.emplace_back(4, 9, 0.588021836313419);
		circles.emplace_back(4, 10, 0.252108059101738);
		circles.emplace_back(5, 0, 0.5245028629666194);
		circles.emplace_back(5, 1, 0.2572318782331422);
		circles.emplace_back(5, 2, 0.5176281229360029);
		circles.emplace_back(5, 3, 0.4995571667561307);
		circles.emplace_back(5, 4, 0.4456753054400906);
		circles.emplace_back(5, 5, 0.6172630659537389);
		circles.emplace_back(5, 6, 0.5786351944087073);
		circles.emplace_back(5, 7, 0.4236743908608332);
		circles.emplace_back(5, 8, 0.3504013810073957);
		circles.emplace_back(5, 9, 0.6313693725736812);
		circles.emplace_back(5, 10, 0.6466673736227676);
		circles.emplace_back(6, 0, 0.3862697003642097);
		circles.emplace_back(6, 1, 0.3374617693712935);
		circles.emplace_back(6, 2, 0.3860536839114502);
		circles.emplace_back(6, 3, 0.2744630886940285);
		circles.emplace_back(6, 4, 0.6257880434626714);
		circles.emplace_back(6, 5, 0.3785093120997772);
		circles.emplace_back(6, 6, 0.2525410232366994);
		circles.emplace_back(6, 7, 0.6995530956191942);
		circles.emplace_back(6, 8, 0.2074192108819261);
		circles.emplace_back(6, 9, 0.6772120790323243);
		circles.emplace_back(6, 10, 0.5754626333015039);
		circles.emplace_back(7, 0, 0.702524638432078);
		circles.emplace_back(7, 1, 0.4386373866582289);
		circles.emplace_back(7, 2, 0.6180448721861467);
		circles.emplace_back(7, 3, 0.7222822458716109);
		circles.emplace_back(7, 4, 0.6314965468598529);
		circles.emplace_back(7, 5, 0.3282953864196315);
		circles.emplace_back(7, 6, 0.4953541671624407);
		circles.emplace_back(7, 7, 0.4465895387576893);
		circles.emplace_back(7, 8, 0.2584302714793011);
		circles.emplace_back(7, 9, 0.3173985831672326);
		circles.emplace_back(7, 10, 0.463321492052637);
		circles.emplace_back(8, 0, 0.3683857803465798);
		circles.emplace_back(8, 1, 0.2829018563730642);
		circles.emplace_back(8, 2, 0.6596835205564275);
		circles.emplace_back(8, 3, 0.2974502438446507);
		circles.emplace_back(8, 4, 0.3244866616325453);
		circles.emplace_back(8, 5, 0.3489598492858931);
		circles.emplace_back(8, 6, 0.4801262136781588);
		circles.emplace_back(8, 7, 0.4082009423291311);
		circles.emplace_back(8, 8, 0.4921673157485202);
		circles.emplace_back(8, 9, 0.3906941492808982);
		circles.emplace_back(8, 10, 0.3895051373401657);
		circles.emplace_back(9, 0, 0.7973999215057119);
		circles.emplace_back(9, 1, 0.439174524997361);
		circles.emplace_back(9, 2, 0.5721407918957994);
		circles.emplace_back(9, 3, 0.2831439018482342);
		circles.emplace_back(9, 4, 0.4980464584892615);
		circles.emplace_back(9, 5, 0.403231115383096);
		circles.emplace_back(9, 6, 0.3371476717991754);
		circles.emplace_back(9, 7, 0.6019586162874475);
		circles.emplace_back(9, 8, 0.4881433399161323);
		circles.emplace_back(9, 10, 0.5541575386421754);
		circles.emplace_back(10, 0, 0.2348262029467151);
		circles.emplace_back(10, 1, 0.4839349393034353);
		circles.emplace_back(10, 2, 0.3191758658504114);
		circles.emplace_back(10, 3, 0.7417356417747214);
		circles.emplace_back(10, 4, 0.436213916237466);
		circles.emplace_back(10, 5, 0.4841598173836246);
		circles.emplace_back(10, 6, 0.1498642911901698);
		circles.emplace_back(10, 7, 0.3824396240757778);
		circles.emplace_back(10, 8, 0.5077729946700856);
		circles.emplace_back(10, 9, 0.5915329106384888);
		circles.emplace_back(10, 10, 0.5258147045737133);
	}
	result_expected = 18.00769618225964;
	timer.reset();
	result_actual = algorithm(a44, b44, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #44: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a45(1, 1);
	Point b45(9, 9);
	{
		circles.emplace_back(0, 0, 0.3881591816665604);
		circles.emplace_back(0, 1, 0.3573497459990904);
		circles.emplace_back(0, 2, 0.3202827060827985);
		circles.emplace_back(0, 3, 0.4956933447858318);
		circles.emplace_back(0, 4, 0.4900398395257071);
		circles.emplace_back(0, 5, 0.3182200128911063);
		circles.emplace_back(0, 6, 0.6044123184168712);
		circles.emplace_back(0, 7, 0.50454935466405);
		circles.emplace_back(0, 8, 0.4605654710205271);
		circles.emplace_back(0, 9, 0.2868455205811187);
		circles.emplace_back(0, 10, 0.7731999783078208);
		circles.emplace_back(1, 0, 0.4549109725048766);
		circles.emplace_back(1, 2, 0.08700800493825227);
		circles.emplace_back(1, 3, 0.3799661620287225);
		circles.emplace_back(1, 4, 0.5358792081708088);
		circles.emplace_back(1, 5, 0.2762801609700545);
		circles.emplace_back(1, 6, 0.6993693200172856);
		circles.emplace_back(1, 7, 0.6266532205743715);
		circles.emplace_back(1, 8, 0.2536236854502931);
		circles.emplace_back(1, 9, 0.5936506734928116);
		circles.emplace_back(1, 10, 0.7059403269784524);
		circles.emplace_back(2, 0, 0.3609485300956294);
		circles.emplace_back(2, 1, 0.1269617934012786);
		circles.emplace_back(2, 2, 0.3356745581841096);
		circles.emplace_back(2, 3, 0.5396022380562498);
		circles.emplace_back(2, 4, 0.5307145726634189);
		circles.emplace_back(2, 5, 0.5767458593705669);
		circles.emplace_back(2, 6, 0.5731020992388949);
		circles.emplace_back(2, 7, 0.4679950240300968);
		circles.emplace_back(2, 8, 0.5883205136982724);
		circles.emplace_back(2, 9, 0.5468010805780068);
		circles.emplace_back(2, 10, 0.328120195842348);
		circles.emplace_back(3, 0, 0.3706780587555841);
		circles.emplace_back(3, 1, 0.07878917462658137);
		circles.emplace_back(3, 2, 0.5063791373977438);
		circles.emplace_back(3, 3, 0.5452141785761341);
		circles.emplace_back(3, 4, 0.5364079511957243);
		circles.emplace_back(3, 5, 0.7910299430368468);
		circles.emplace_back(3, 6, 0.5805414941394701);
		circles.emplace_back(3, 7, 0.4641780633246526);
		circles.emplace_back(3, 8, 0.5836585649522021);
		circles.emplace_back(3, 9, 0.6877826203359291);
		circles.emplace_back(3, 10, 0.2865973873296753);
		circles.emplace_back(4, 0, 0.4858982426812872);
		circles.emplace_back(4, 1, 0.357508225296624);
		circles.emplace_back(4, 2, 0.07989720690529793);
		circles.emplace_back(4, 3, 0.8047215014928951);
		circles.emplace_back(4, 4, 0.2715356148546562);
		circles.emplace_back(4, 5, 0.8060191137017682);
		circles.emplace_back(4, 6, 0.4605746247572824);
		circles.emplace_back(4, 7, 0.360876332432963);
		circles.emplace_back(4, 8, 0.4657311500748619);
		circles.emplace_back(4, 9, 0.589233849872835);
		circles.emplace_back(4, 10, 0.2651933776913211);
		circles.emplace_back(5, 0, 0.1501642380142584);
		circles.emplace_back(5, 1, 0.3844598944997415);
		circles.emplace_back(5, 2, 0.2239142612786963);
		circles.emplace_back(5, 3, 0.3723471489502117);
		circles.emplace_back(5, 4, 0.5787341764429584);
		circles.emplace_back(5, 5, 0.3581584116211161);
		circles.emplace_back(5, 6, 0.5171473401831462);
		circles.emplace_back(5, 7, 0.2117183363763615);
		circles.emplace_back(5, 8, 0.4523681320482865);
		circles.emplace_back(5, 9, 0.4707506611710414);
		circles.emplace_back(5, 10, 0.1919433881761506);
		circles.emplace_back(6, 0, 0.5944125250680372);
		circles.emplace_back(6, 1, 0.1898722285637632);
		circles.emplace_back(6, 2, 0.1851973155280575);
		circles.emplace_back(6, 3, 0.457951348205097);
		circles.emplace_back(6, 4, 0.4313788975356146);
		circles.emplace_back(6, 5, 0.3893975299084559);
		circles.emplace_back(6, 6, 0.4961935136234388);
		circles.emplace_back(6, 7, 0.4304163241060451);
		circles.emplace_back(6, 8, 0.4555415813578292);
		circles.emplace_back(6, 9, 0.7258155284682288);
		circles.emplace_back(6, 10, 0.500640052347444);
		circles.emplace_back(7, 0, 0.1505042876349762);
		circles.emplace_back(7, 1, 0.8132669343380258);
		circles.emplace_back(7, 2, 0.1072733208769932);
		circles.emplace_back(7, 3, 0.5265130154555663);
		circles.emplace_back(7, 4, 0.5101189729990437);
		circles.emplace_back(7, 5, 0.5407917671604082);
		circles.emplace_back(7, 6, 0.669053471297957);
		circles.emplace_back(7, 7, 0.4107568399747833);
		circles.emplace_back(7, 8, 0.3343359588878229);
		circles.emplace_back(7, 9, 0.4912375035462901);
		circles.emplace_back(7, 10, 0.3328635622048751);
		circles.emplace_back(8, 0, 0.566825820109807);
		circles.emplace_back(8, 1, 0.3245789380045608);
		circles.emplace_back(8, 2, 0.3278352779103443);
		circles.emplace_back(8, 3, 0.5096804326632991);
		circles.emplace_back(8, 4, 0.4324990486493334);
		circles.emplace_back(8, 5, 0.3156631740974262);
		circles.emplace_back(8, 6, 0.448986970516853);
		circles.emplace_back(8, 7, 0.4742741041118279);
		circles.emplace_back(8, 8, 0.1385937958722934);
		circles.emplace_back(8, 9, 0.4498311464907601);
		circles.emplace_back(8, 10, 0.3607871801359579);
		circles.emplace_back(9, 0, 0.4895363936433568);
		circles.emplace_back(9, 1, 0.5892023259541019);
		circles.emplace_back(9, 2, 0.5209053821163252);
		circles.emplace_back(9, 3, 0.4626311341999099);
		circles.emplace_back(9, 4, 0.5087392147863283);
		circles.emplace_back(9, 5, 0.2940771508729085);
		circles.emplace_back(9, 6, 0.2916834750445559);
		circles.emplace_back(9, 7, 0.5615335364593192);
		circles.emplace_back(9, 8, 0.3338475657859817);
		circles.emplace_back(9, 10, 0.3437897218158468);
		circles.emplace_back(10, 0, 0.4377002935158089);
		circles.emplace_back(10, 1, 0.2807833521394059);
		circles.emplace_back(10, 2, 0.658012205385603);
		circles.emplace_back(10, 3, 0.2682875580852851);
		circles.emplace_back(10, 4, 0.6204823744716123);
		circles.emplace_back(10, 5, 0.3785595305962488);
		circles.emplace_back(10, 6, 0.6703670161077753);
		circles.emplace_back(10, 7, 0.3694748135050759);
		circles.emplace_back(10, 8, 0.3434195055859163);
		circles.emplace_back(10, 9, 0.5421326654730364);
		circles.emplace_back(10, 10, 0.3512560550356283);
	}
	result_expected = 14.29493392936035;
	timer.reset();
	result_actual = algorithm(a45, b45, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #45: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a46(1, 1);
	Point b46(9, 9);
	{
		circles.emplace_back(0, 0, 0.468441280326806);
		circles.emplace_back(0, 1, 0.2933784947963431);
		circles.emplace_back(0, 2, 0.7732775923563168);
		circles.emplace_back(0, 3, 0.7360152920940891);
		circles.emplace_back(0, 4, 0.4579648306360468);
		circles.emplace_back(0, 5, 0.5211841273354366);
		circles.emplace_back(0, 6, 0.4305219239322469);
		circles.emplace_back(0, 7, 0.3754340358311311);
		circles.emplace_back(0, 8, 0.400912295258604);
		circles.emplace_back(0, 9, 0.3640923102619126);
		circles.emplace_back(0, 10, 0.5438555226428434);
		circles.emplace_back(1, 0, 0.4710210466990247);
		circles.emplace_back(1, 2, 0.4651637801667675);
		circles.emplace_back(1, 3, 0.3633804044919088);
		circles.emplace_back(1, 4, 0.4675259108422324);
		circles.emplace_back(1, 5, 0.4132003378355876);
		circles.emplace_back(1, 6, 0.5356854203855619);
		circles.emplace_back(1, 7, 0.2801797443302348);
		circles.emplace_back(1, 8, 0.7865446184528991);
		circles.emplace_back(1, 9, 0.4005616633454337);
		circles.emplace_back(1, 10, 0.3943755713989958);
		circles.emplace_back(2, 0, 0.362675344501622);
		circles.emplace_back(2, 1, 0.8425294681219384);
		circles.emplace_back(2, 2, 0.3682906940812245);
		circles.emplace_back(2, 3, 0.3083094380563125);
		circles.emplace_back(2, 4, 0.2677977946819737);
		circles.emplace_back(2, 5, 0.3945077978773042);
		circles.emplace_back(2, 6, 0.5039038809249178);
		circles.emplace_back(2, 7, 0.2170071409782395);
		circles.emplace_back(2, 8, 0.3905323415296152);
		circles.emplace_back(2, 9, 0.3803056212840601);
		circles.emplace_back(2, 10, 0.3784130055690184);
		circles.emplace_back(3, 0, 0.3593502204632387);
		circles.emplace_back(3, 1, 0.3039701582165435);
		circles.emplace_back(3, 2, 0.294147725100629);
		circles.emplace_back(3, 3, 0.4710444187978282);
		circles.emplace_back(3, 4, 0.6307715778937563);
		circles.emplace_back(3, 5, 0.5632268014596775);
		circles.emplace_back(3, 6, 0.346093704435043);
		circles.emplace_back(3, 7, 0.4156379662686959);
		circles.emplace_back(3, 8, 0.3113438546424732);
		circles.emplace_back(3, 9, 0.4763528560521081);
		circles.emplace_back(3, 10, 0.2189349354011938);
		circles.emplace_back(4, 0, 0.4468506017932668);
		circles.emplace_back(4, 1, 0.5553912484785541);
		circles.emplace_back(4, 2, 0.495361766894348);
		circles.emplace_back(4, 3, 0.4881774852750823);
		circles.emplace_back(4, 4, 0.6742896881187335);
		circles.emplace_back(4, 5, 0.1832497674738988);
		circles.emplace_back(4, 6, 0.3304998585255817);
		circles.emplace_back(4, 7, 0.6207359601510688);
		circles.emplace_back(4, 8, 0.162700985209085);
		circles.emplace_back(4, 9, 0.6658009214093908);
		circles.emplace_back(4, 10, 0.2408835421549156);
		circles.emplace_back(5, 0, 0.5179632900981233);
		circles.emplace_back(5, 1, 0.3463363260263577);
		circles.emplace_back(5, 2, 0.6424038506811485);
		circles.emplace_back(5, 3, 0.5046287101926282);
		circles.emplace_back(5, 4, 0.7186414518160745);
		circles.emplace_back(5, 5, 0.3556259798118844);
		circles.emplace_back(5, 6, 0.6628508927067741);
		circles.emplace_back(5, 7, 0.2215973182814196);
		circles.emplace_back(5, 8, 0.4275581287918612);
		circles.emplace_back(5, 9, 0.4842807028675452);
		circles.emplace_back(5, 10, 0.5939715858316049);
		circles.emplace_back(6, 0, 0.3518861548276618);
		circles.emplace_back(6, 1, 0.4852943089557811);
		circles.emplace_back(6, 2, 0.4749484768370166);
		circles.emplace_back(6, 3, 0.1815101107349619);
		circles.emplace_back(6, 4, 0.4431827980326489);
		circles.emplace_back(6, 5, 0.5448478198377416);
		circles.emplace_back(6, 6, 0.4515509344870224);
		circles.emplace_back(6, 7, 0.2079011693364009);
		circles.emplace_back(6, 8, 0.5501137604238465);
		circles.emplace_back(6, 9, 0.570717801223509);
		circles.emplace_back(6, 10, 0.4764244729885831);
		circles.emplace_back(7, 0, 0.3365693012019619);
		circles.emplace_back(7, 1, 0.4987098208861425);
		circles.emplace_back(7, 2, 0.7260751153109595);
		circles.emplace_back(7, 3, 0.5603910546982661);
		circles.emplace_back(7, 4, 0.3833766374504193);
		circles.emplace_back(7, 5, 0.4991135441930964);
		circles.emplace_back(7, 6, 0.1636436943663284);
		circles.emplace_back(7, 7, 0.4038836954394355);
		circles.emplace_back(7, 8, 0.505844092159532);
		circles.emplace_back(7, 9, 0.3596539880381897);
		circles.emplace_back(7, 10, 0.4859178258804604);
		circles.emplace_back(8, 0, 0.3972516402835026);
		circles.emplace_back(8, 1, 0.450770991272293);
		circles.emplace_back(8, 2, 0.7054135975660756);
		circles.emplace_back(8, 3, 0.5903403752250597);
		circles.emplace_back(8, 4, 0.4583702268311753);
		circles.emplace_back(8, 5, 0.25087813900318);
		circles.emplace_back(8, 6, 0.1544122874038294);
		circles.emplace_back(8, 7, 0.3650669458089396);
		circles.emplace_back(8, 8, 0.3356804359937087);
		circles.emplace_back(8, 9, 0.7110993217444047);
		circles.emplace_back(8, 10, 0.2545337111921981);
		circles.emplace_back(9, 0, 0.2509409767342731);
		circles.emplace_back(9, 1, 0.3547831302741543);
		circles.emplace_back(9, 2, 0.3751462494721636);
		circles.emplace_back(9, 3, 0.4343187186168507);
		circles.emplace_back(9, 4, 0.3353047779528424);
		circles.emplace_back(9, 5, 0.2367129795486107);
		circles.emplace_back(9, 6, 0.5129719346528873);
		circles.emplace_back(9, 7, 0.4707509999396279);
		circles.emplace_back(9, 8, 0.693271502922289);
		circles.emplace_back(9, 10, 0.3660170743474737);
		circles.emplace_back(10, 0, 0.4197575086494907);
		circles.emplace_back(10, 1, 0.2271599180297926);
		circles.emplace_back(10, 2, 0.642083058762364);
		circles.emplace_back(10, 3, 0.4367632266366854);
		circles.emplace_back(10, 4, 0.5670474756276235);
		circles.emplace_back(10, 5, 0.6643655278952793);
		circles.emplace_back(10, 6, 0.7241789539111778);
		circles.emplace_back(10, 7, 0.4546029580989852);
		circles.emplace_back(10, 8, 0.3966584039619193);
		circles.emplace_back(10, 9, 0.3781907837139443);
		circles.emplace_back(10, 10, 0.58460108328145);
	}
	result_expected = 14.78523138291016;
	timer.reset();
	result_actual = algorithm(a46, b46, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #46: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();
	




	Point a47(1, 1);
	Point b47(9, 9);
	{
		circles.emplace_back(0, 0, 0.2230141759151593);
		circles.emplace_back(0, 1, 0.4979860551422461);
		circles.emplace_back(0, 2, 0.366465933364816);
		circles.emplace_back(0, 3, 0.4583594509167597);
		circles.emplace_back(0, 4, 0.4918485360452905);
		circles.emplace_back(0, 5, 0.1593359501799569);
		circles.emplace_back(0, 6, 0.4786501004593446);
		circles.emplace_back(0, 7, 0.3333838301477954);
		circles.emplace_back(0, 8, 0.3963084940100088);
		circles.emplace_back(0, 9, 0.3339023735141382);
		circles.emplace_back(0, 10, 0.5511950538726523);
		circles.emplace_back(1, 0, 0.3046863612486049);
		circles.emplace_back(1, 2, 0.3644790431717411);
		circles.emplace_back(1, 3, 0.6110208144178614);
		circles.emplace_back(1, 4, 0.4817761647747829);
		circles.emplace_back(1, 5, 0.3853600865928456);
		circles.emplace_back(1, 6, 0.6215391405159607);
		circles.emplace_back(1, 7, 0.5333188459044322);
		circles.emplace_back(1, 8, 0.5455155511619523);
		circles.emplace_back(1, 9, 0.290038423310034);
		circles.emplace_back(1, 10, 0.2687778199324384);
		circles.emplace_back(2, 0, 0.4503904411336407);
		circles.emplace_back(2, 1, 0.7063224098877982);
		circles.emplace_back(2, 2, 0.456440573441796);
		circles.emplace_back(2, 3, 0.5655399929964915);
		circles.emplace_back(2, 4, 0.5496187273180112);
		circles.emplace_back(2, 5, 0.5264755361946299);
		circles.emplace_back(2, 6, 0.6206278715981171);
		circles.emplace_back(2, 7, 0.5922269372502341);
		circles.emplace_back(2, 8, 0.4547721771290525);
		circles.emplace_back(2, 9, 0.5275730307446792);
		circles.emplace_back(2, 10, 0.5115960701135919);
		circles.emplace_back(3, 0, 0.6224764719838276);
		circles.emplace_back(3, 1, 0.4329992376035079);
		circles.emplace_back(3, 2, 0.6059741941513493);
		circles.emplace_back(3, 3, 0.4808285617036745);
		circles.emplace_back(3, 4, 0.4826478215167299);
		circles.emplace_back(3, 5, 0.6008463965496048);
		circles.emplace_back(3, 6, 0.5558586090104655);
		circles.emplace_back(3, 7, 0.6324355396209285);
		circles.emplace_back(3, 8, 0.4267361659789458);
		circles.emplace_back(3, 9, 0.3699246864533052);
		circles.emplace_back(3, 10, 0.4030274094315245);
		circles.emplace_back(4, 0, 0.4695040953112766);
		circles.emplace_back(4, 1, 0.804841879592277);
		circles.emplace_back(4, 2, 0.2228496258845553);
		circles.emplace_back(4, 3, 0.5025717380689457);
		circles.emplace_back(4, 4, 0.3222842535702511);
		circles.emplace_back(4, 5, 0.2533194564515724);
		circles.emplace_back(4, 6, 0.2600795984035358);
		circles.emplace_back(4, 7, 0.6035333906533197);
		circles.emplace_back(4, 8, 0.5738359451992437);
		circles.emplace_back(4, 9, 0.3847311238059774);
		circles.emplace_back(4, 10, 0.3082776689669117);
		circles.emplace_back(5, 0, 0.2336826480226591);
		circles.emplace_back(5, 1, 0.5487619171617553);
		circles.emplace_back(5, 2, 0.5057301428401842);
		circles.emplace_back(5, 3, 0.2308218378340825);
		circles.emplace_back(5, 4, 0.8075382956536487);
		circles.emplace_back(5, 5, 0.2806515802396461);
		circles.emplace_back(5, 6, 0.2409987969556823);
		circles.emplace_back(5, 7, 0.131088731973432);
		circles.emplace_back(5, 8, 0.4107548306928948);
		circles.emplace_back(5, 9, 0.423860794189386);
		circles.emplace_back(5, 10, 0.4913660675520077);
		circles.emplace_back(6, 0, 0.2891357339685783);
		circles.emplace_back(6, 1, 0.2640018564881757);
		circles.emplace_back(6, 2, 0.5252525903983042);
		circles.emplace_back(6, 3, 0.5042299973079934);
		circles.emplace_back(6, 4, 0.5224065484246239);
		circles.emplace_back(6, 5, 0.6194606646196916);
		circles.emplace_back(6, 6, 0.2215238320408389);
		circles.emplace_back(6, 7, 0.3844097409630194);
		circles.emplace_back(6, 8, 0.6110852058744057);
		circles.emplace_back(6, 9, 0.5930630044313148);
		circles.emplace_back(6, 10, 0.5777428117347881);
		circles.emplace_back(7, 0, 0.5235523035982623);
		circles.emplace_back(7, 1, 0.2787235041847452);
		circles.emplace_back(7, 2, 0.3855970400618389);
		circles.emplace_back(7, 3, 0.2327227866975591);
		circles.emplace_back(7, 4, 0.6762189664179459);
		circles.emplace_back(7, 5, 0.3687668874626979);
		circles.emplace_back(7, 6, 0.2958054949762299);
		circles.emplace_back(7, 7, 0.3668564514024183);
		circles.emplace_back(7, 8, 0.6607764000305906);
		circles.emplace_back(7, 9, 0.4076037624618039);
		circles.emplace_back(7, 10, 0.3786009839968756);
		circles.emplace_back(8, 0, 0.5580363477347419);
		circles.emplace_back(8, 1, 0.6132174652302638);
		circles.emplace_back(8, 2, 0.4947632524883374);
		circles.emplace_back(8, 3, 0.2515235328348354);
		circles.emplace_back(8, 4, 0.4412862126482651);
		circles.emplace_back(8, 5, 0.3720367012778297);
		circles.emplace_back(8, 6, 0.6108863888075575);
		circles.emplace_back(8, 7, 0.8025652851210907);
		circles.emplace_back(8, 8, 0.3377282633213326);
		circles.emplace_back(8, 9, 0.4222855016821995);
		circles.emplace_back(8, 10, 0.7840957395499571);
		circles.emplace_back(9, 0, 0.402487396937795);
		circles.emplace_back(9, 1, 0.1685114198131487);
		circles.emplace_back(9, 2, 0.3769319774815812);
		circles.emplace_back(9, 3, 0.605388476117514);
		circles.emplace_back(9, 4, 0.5747541188495233);
		circles.emplace_back(9, 5, 0.6193254652200266);
		circles.emplace_back(9, 6, 0.4236505080247298);
		circles.emplace_back(9, 7, 0.33367787708994);
		circles.emplace_back(9, 8, 0.2262090654345229);
		circles.emplace_back(9, 10, 0.4711261433316394);
		circles.emplace_back(10, 0, 0.2151659792521969);
		circles.emplace_back(10, 1, 0.5811082696309313);
		circles.emplace_back(10, 2, 0.5916186723159625);
		circles.emplace_back(10, 3, 0.6626961937872693);
		circles.emplace_back(10, 4, 0.3312777094775811);
		circles.emplace_back(10, 5, 0.4192684083944186);
		circles.emplace_back(10, 6, 0.5952078406931832);
		circles.emplace_back(10, 7, 0.6006673247320578);
		circles.emplace_back(10, 8, 0.490688062668778);
		circles.emplace_back(10, 9, 0.4969282919308171);
		circles.emplace_back(10, 10, 0.5823127693729475);
	}
	result_expected = 18.5922239229683;
	timer.reset();
	result_actual = algorithm(a47, b47, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #47: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();
	*/


	/*

	Point a48(1, 1);
	Point b48(9, 9);
	{
		circles.emplace_back(0, 0, 0.5826281229732558);
		circles.emplace_back(0, 1, 0.54076074922923);
		circles.emplace_back(0, 2, 0.209924416593276);
		circles.emplace_back(0, 3, 0.42427597430069);
		circles.emplace_back(0, 4, 0.3489429016364738);
		circles.emplace_back(0, 5, 0.5033338142791762);
		circles.emplace_back(0, 6, 0.6138184679439291);
		circles.emplace_back(0, 7, 0.6497084955917671);
		circles.emplace_back(0, 8, 0.4289064853219315);
		circles.emplace_back(0, 9, 0.604712313436903);
		circles.emplace_back(0, 10, 0.6199544496601447);
		circles.emplace_back(1, 0, 0.4052442920627072);
		circles.emplace_back(1, 2, 0.496859932760708);
		circles.emplace_back(1, 3, 0.5679656760999933);
		circles.emplace_back(1, 4, 0.2655392499407753);
		circles.emplace_back(1, 5, 0.2989118232624605);
		circles.emplace_back(1, 6, 0.5038921969709917);
		circles.emplace_back(1, 7, 0.5956547562265768);
		circles.emplace_back(1, 8, 0.3983716454124078);
		circles.emplace_back(1, 9, 0.629247819003649);
		circles.emplace_back(1, 10, 0.6007527229143307);
		circles.emplace_back(2, 0, 0.3211135706165805);
		circles.emplace_back(2, 1, 0.5668447425356135);
		circles.emplace_back(2, 2, 0.3532782363938168);
		circles.emplace_back(2, 3, 0.5175999826518819);
		circles.emplace_back(2, 4, 0.5564107246929779);
		circles.emplace_back(2, 5, 0.355846856511198);
		circles.emplace_back(2, 6, 0.4964914043666795);
		circles.emplace_back(2, 7, 0.416210948000662);
		circles.emplace_back(2, 8, 0.8151155257830396);
		circles.emplace_back(2, 9, 0.5591858276864513);
		circles.emplace_back(2, 10, 0.5579283557133748);
		circles.emplace_back(3, 0, 0.5802765006897971);
		circles.emplace_back(3, 1, 0.4379937838995829);
		circles.emplace_back(3, 2, 0.4291617754613981);
		circles.emplace_back(3, 3, 0.6135153466137125);
		circles.emplace_back(3, 4, 0.4594077800167724);
		circles.emplace_back(3, 5, 0.4997583000222221);
		circles.emplace_back(3, 6, 0.2939132896950468);
		circles.emplace_back(3, 7, 0.370763563667424);
		circles.emplace_back(3, 8, 0.4324784680036828);
		circles.emplace_back(3, 9, 0.2249990418786183);
		circles.emplace_back(3, 10, 0.3831620596116408);
		circles.emplace_back(4, 0, 0.3779610184254125);
		circles.emplace_back(4, 1, 0.5059280120534823);
		circles.emplace_back(4, 2, 0.3914180072257295);
		circles.emplace_back(4, 3, 0.3529809402069077);
		circles.emplace_back(4, 4, 0.2409816294210032);
		circles.emplace_back(4, 5, 0.5126507851062342);
		circles.emplace_back(4, 6, 0.2484937746310606);
		circles.emplace_back(4, 7, 0.5502104561543092);
		circles.emplace_back(4, 8, 0.2508364917011932);
		circles.emplace_back(4, 9, 0.5270961832953617);
		circles.emplace_back(4, 10, 0.4297007417539134);
		circles.emplace_back(5, 0, 0.5071487432112917);
		circles.emplace_back(5, 1, 0.3750923338579014);
		circles.emplace_back(5, 2, 0.3622046611038968);
		circles.emplace_back(5, 3, 0.4864080511266365);
		circles.emplace_back(5, 4, 0.5071399271255359);
		circles.emplace_back(5, 5, 0.3162821625592187);
		circles.emplace_back(5, 6, 0.4638047040207312);
		circles.emplace_back(5, 7, 0.2215832034358755);
		circles.emplace_back(5, 8, 0.5116859400412067);
		circles.emplace_back(5, 9, 0.5904330945806577);
		circles.emplace_back(5, 10, 0.6680957386968657);
		circles.emplace_back(6, 0, 0.6514253583038225);
		circles.emplace_back(6, 1, 0.4897067744052037);
		circles.emplace_back(6, 2, 0.5288363763364031);
		circles.emplace_back(6, 3, 0.3378419806016609);
		circles.emplace_back(6, 4, 0.5730533225694671);
		circles.emplace_back(6, 5, 0.6395741743734106);
		circles.emplace_back(6, 6, 0.3561845909105614);
		circles.emplace_back(6, 7, 0.2429022191790864);
		circles.emplace_back(6, 8, 0.4663732260698452);
		circles.emplace_back(6, 9, 0.4445437647169456);
		circles.emplace_back(6, 10, 0.2482010525884107);
		circles.emplace_back(7, 0, 0.4007205405039713);
		circles.emplace_back(7, 1, 0.40825088492129);
		circles.emplace_back(7, 2, 0.1522106172284111);
		circles.emplace_back(7, 3, 0.5218863888876513);
		circles.emplace_back(7, 4, 0.2424029874382541);
		circles.emplace_back(7, 5, 0.4271138523006812);
		circles.emplace_back(7, 6, 0.6186132546281442);
		circles.emplace_back(7, 7, 0.3615073100896552);
		circles.emplace_back(7, 8, 0.4200051572872326);
		circles.emplace_back(7, 9, 0.4761081567266956);
		circles.emplace_back(7, 10, 0.307611091970466);
		circles.emplace_back(8, 0, 0.7334525662707164);
		circles.emplace_back(8, 1, 0.3206557369558141);
		circles.emplace_back(8, 2, 0.3529347278410569);
		circles.emplace_back(8, 3, 0.3861603155499324);
		circles.emplace_back(8, 4, 0.1930810918333009);
		circles.emplace_back(8, 5, 0.2031409756047651);
		circles.emplace_back(8, 6, 0.6444905096897855);
		circles.emplace_back(8, 7, 0.5061131993075833);
		circles.emplace_back(8, 8, 0.3366873375372961);
		circles.emplace_back(8, 9, 0.5225750948069617);
		circles.emplace_back(8, 10, 0.524439261504449);
		circles.emplace_back(9, 0, 0.413165858737193);
		circles.emplace_back(9, 1, 0.3017087900312617);
		circles.emplace_back(9, 2, 0.4587816362036392);
		circles.emplace_back(9, 3, 0.3818370459834113);
		circles.emplace_back(9, 4, 0.4735794422915205);
		circles.emplace_back(9, 5, 0.6683006788836792);
		circles.emplace_back(9, 6, 0.5140107466606423);
		circles.emplace_back(9, 7, 0.3089374050730839);
		circles.emplace_back(9, 8, 0.3592997602885589);
		circles.emplace_back(9, 10, 0.3654028711142018);
		circles.emplace_back(10, 0, 0.3956174009246752);
		circles.emplace_back(10, 1, 0.3263012232491747);
		circles.emplace_back(10, 2, 0.3821003513177857);
		circles.emplace_back(10, 3, 0.3344239532249048);
		circles.emplace_back(10, 4, 0.6493255617795511);
		circles.emplace_back(10, 5, 0.2733362782979384);
		circles.emplace_back(10, 6, 0.5173739861464127);
		circles.emplace_back(10, 7, 0.5536675007315353);
		circles.emplace_back(10, 8, 0.4587032777024433);
		circles.emplace_back(10, 9, 0.4423914795974269);
		circles.emplace_back(10, 10, 0.4081976091256365);
	}
	result_expected = 12.09686652400611;
	timer.reset();
	result_actual = algorithm(a48, b48, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #48: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a49(1, 1);
	Point b49(9, 9);
	{
		circles.emplace_back(0, 0, 0.576625535194762);
		circles.emplace_back(0, 1, 0.3764737180201337);
		circles.emplace_back(0, 2, 0.5845307938987389);
		circles.emplace_back(0, 3, 0.4902957170968875);
		circles.emplace_back(0, 4, 0.08726416875142604);
		circles.emplace_back(0, 5, 0.6032871455652639);
		circles.emplace_back(0, 6, 0.1651118586072698);
		circles.emplace_back(0, 7, 0.6285271757980808);
		circles.emplace_back(0, 8, 0.6254264361457899);
		circles.emplace_back(0, 9, 0.579578826832585);
		circles.emplace_back(0, 10, 0.497294282563962);
		circles.emplace_back(1, 0, 0.3055204737698659);
		circles.emplace_back(1, 2, 0.4854773142607882);
		circles.emplace_back(1, 3, 0.4061378796352074);
		circles.emplace_back(1, 4, 0.5316026343265549);
		circles.emplace_back(1, 5, 0.3530824137618765);
		circles.emplace_back(1, 6, 0.4413159291492775);
		circles.emplace_back(1, 7, 0.5590120582608505);
		circles.emplace_back(1, 8, 0.4296691179508343);
		circles.emplace_back(1, 9, 0.3670052416389808);
		circles.emplace_back(1, 10, 0.600879950565286);
		circles.emplace_back(2, 0, 0.4143734761280939);
		circles.emplace_back(2, 1, 0.5002809362718835);
		circles.emplace_back(2, 2, 0.4958972127875313);
		circles.emplace_back(2, 3, 0.6432671739952639);
		circles.emplace_back(2, 4, 0.4489702659426257);
		circles.emplace_back(2, 5, 0.3258573416853324);
		circles.emplace_back(2, 6, 0.5446615960216149);
		circles.emplace_back(2, 7, 0.2415992901893332);
		circles.emplace_back(2, 8, 0.5317891773534938);
		circles.emplace_back(2, 9, 0.6574813744286075);
		circles.emplace_back(2, 10, 0.2832491149893031);
		circles.emplace_back(3, 0, 0.524752842192538);
		circles.emplace_back(3, 1, 0.3725541121093556);
		circles.emplace_back(3, 2, 0.3066112883621827);
		circles.emplace_back(3, 3, 0.5013088270789012);
		circles.emplace_back(3, 4, 0.6810823698760942);
		circles.emplace_back(3, 5, 0.2426855967147276);
		circles.emplace_back(3, 6, 0.5115966642508283);
		circles.emplace_back(3, 7, 0.5993624398251995);
		circles.emplace_back(3, 8, 0.1572607419686392);
		circles.emplace_back(3, 9, 0.2343461925862357);
		circles.emplace_back(3, 10, 0.3071242105448618);
		circles.emplace_back(4, 0, 0.3571270648157224);
		circles.emplace_back(4, 1, 0.5553616755874827);
		circles.emplace_back(4, 2, 0.6731968437088653);
		circles.emplace_back(4, 3, 0.4747182516613975);
		circles.emplace_back(4, 4, 0.7696114090969786);
		circles.emplace_back(4, 5, 0.2813094432698562);
		circles.emplace_back(4, 6, 0.7504891617922113);
		circles.emplace_back(4, 7, 0.5024209037655964);
		circles.emplace_back(4, 8, 0.4916104040807113);
		circles.emplace_back(4, 9, 0.3478207675041631);
		circles.emplace_back(4, 10, 0.3901186489267275);
		circles.emplace_back(5, 0, 0.4317769380519166);
		circles.emplace_back(5, 1, 0.481223271950148);
		circles.emplace_back(5, 2, 0.2849639027612283);
		circles.emplace_back(5, 3, 0.3162638577399775);
		circles.emplace_back(5, 4, 0.420248331525363);
		circles.emplace_back(5, 5, 0.4830200295662507);
		circles.emplace_back(5, 6, 0.4614599050255492);
		circles.emplace_back(5, 7, 0.5372364890528842);
		circles.emplace_back(5, 8, 0.5971835052827373);
		circles.emplace_back(5, 9, 0.2414814298739657);
		circles.emplace_back(5, 10, 0.2698510888265446);
		circles.emplace_back(6, 0, 0.3111674270359799);
		circles.emplace_back(6, 1, 0.3414662502938882);
		circles.emplace_back(6, 2, 0.4853373408084735);
		circles.emplace_back(6, 3, 0.3786616717698053);
		circles.emplace_back(6, 4, 0.4091537118656561);
		circles.emplace_back(6, 5, 0.458969340682961);
		circles.emplace_back(6, 6, 0.3734285617014393);
		circles.emplace_back(6, 7, 0.604675606568344);
		circles.emplace_back(6, 8, 0.5414914498804136);
		circles.emplace_back(6, 9, 0.4879378345096483);
		circles.emplace_back(6, 10, 0.2427170771872625);
		circles.emplace_back(7, 0, 0.4084566005738452);
		circles.emplace_back(7, 1, 0.5626196612371132);
		circles.emplace_back(7, 2, 0.6104270620504394);
		circles.emplace_back(7, 3, 0.3490697486093268);
		circles.emplace_back(7, 4, 0.4662353228079155);
		circles.emplace_back(7, 5, 0.4204000650672242);
		circles.emplace_back(7, 6, 0.3979203015798703);
		circles.emplace_back(7, 7, 0.5414404429262504);
		circles.emplace_back(7, 8, 0.6212887984933332);
		circles.emplace_back(7, 9, 0.2653578021330759);
		circles.emplace_back(7, 10, 0.569251142651774);
		circles.emplace_back(8, 0, 0.5600755991181359);
		circles.emplace_back(8, 1, 0.4679369910852983);
		circles.emplace_back(8, 2, 0.4855080949841067);
		circles.emplace_back(8, 3, 0.2889555368805304);
		circles.emplace_back(8, 4, 0.4993682320928201);
		circles.emplace_back(8, 5, 0.5712815718026831);
		circles.emplace_back(8, 6, 0.6823938456131146);
		circles.emplace_back(8, 7, 0.3841785362223163);
		circles.emplace_back(8, 8, 0.5259853740921244);
		circles.emplace_back(8, 9, 0.07581187665928155);
		circles.emplace_back(8, 10, 0.6539591706125065);
		circles.emplace_back(9, 0, 0.2082607187563554);
		circles.emplace_back(9, 1, 0.2928939535981044);
		circles.emplace_back(9, 2, 0.4060030509950593);
		circles.emplace_back(9, 3, 0.2998838738305494);
		circles.emplace_back(9, 4, 0.329129301966168);
		circles.emplace_back(9, 5, 0.4399101117393002);
		circles.emplace_back(9, 6, 0.6120313815074041);
		circles.emplace_back(9, 7, 0.315003856527619);
		circles.emplace_back(9, 8, 0.5706189435208217);
		circles.emplace_back(9, 10, 0.3213969561969861);
		circles.emplace_back(10, 0, 0.3637318157823756);
		circles.emplace_back(10, 1, 0.2864424650324509);
		circles.emplace_back(10, 2, 0.4848472295561805);
		circles.emplace_back(10, 3, 0.351735752611421);
		circles.emplace_back(10, 4, 0.6459226693259552);
		circles.emplace_back(10, 5, 0.5600777758983895);
		circles.emplace_back(10, 6, 0.4837698504561558);
		circles.emplace_back(10, 7, 0.4091955534880981);
		circles.emplace_back(10, 8, 0.4582225200952962);
		circles.emplace_back(10, 9, 0.5919708185596392);
		circles.emplace_back(10, 10, 0.2080404641339555);
	}
	result_expected = 14.89225860499741;
	timer.reset();
	result_actual = algorithm(a49, b49, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #49: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a50(1, 1);
	Point b50(9, 9);
	{
		circles.emplace_back(0, 0, 0.2888262646039948);
		circles.emplace_back(0, 1, 0.2724842905299738);
		circles.emplace_back(0, 2, 0.4503797354875132);
		circles.emplace_back(0, 3, 0.4613002468133345);
		circles.emplace_back(0, 4, 0.5450001489138231);
		circles.emplace_back(0, 5, 0.6509715170832351);
		circles.emplace_back(0, 6, 0.5839848798466846);
		circles.emplace_back(0, 7, 0.1880221313098445);
		circles.emplace_back(0, 8, 0.4142267679562792);
		circles.emplace_back(0, 9, 0.478401807253249);
		circles.emplace_back(0, 10, 0.5219498506514355);
		circles.emplace_back(1, 0, 0.5230347328120842);
		circles.emplace_back(1, 2, 0.4588663607602939);
		circles.emplace_back(1, 3, 0.3109824841143563);
		circles.emplace_back(1, 4, 0.6214434654219075);
		circles.emplace_back(1, 5, 0.1908509621629491);
		circles.emplace_back(1, 6, 0.3223666602512821);
		circles.emplace_back(1, 7, 0.5955634183483198);
		circles.emplace_back(1, 8, 0.3282476703403517);
		circles.emplace_back(1, 9, 0.5829263266408816);
		circles.emplace_back(1, 10, 0.7366481471573934);
		circles.emplace_back(2, 0, 0.262032047775574);
		circles.emplace_back(2, 1, 0.6660763879073783);
		circles.emplace_back(2, 2, 0.5909719182411208);
		circles.emplace_back(2, 3, 0.4722627414157614);
		circles.emplace_back(2, 4, 0.7420755843864754);
		circles.emplace_back(2, 5, 0.2202303020982072);
		circles.emplace_back(2, 6, 0.1244470894569531);
		circles.emplace_back(2, 7, 0.3719509310787544);
		circles.emplace_back(2, 8, 0.5174354088725522);
		circles.emplace_back(2, 9, 0.4312125810189172);
		circles.emplace_back(2, 10, 0.4903568165609613);
		circles.emplace_back(3, 0, 0.6582223387202247);
		circles.emplace_back(3, 1, 0.5507786526577547);
		circles.emplace_back(3, 2, 0.4639305370626971);
		circles.emplace_back(3, 3, 0.4634787503862753);
		circles.emplace_back(3, 4, 0.3555847253417596);
		circles.emplace_back(3, 5, 0.6023119674297049);
		circles.emplace_back(3, 6, 0.4681082245660946);
		circles.emplace_back(3, 7, 0.825144954607822);
		circles.emplace_back(3, 8, 0.6180464317789301);
		circles.emplace_back(3, 9, 0.4852624821709469);
		circles.emplace_back(3, 10, 0.3955349749652669);
		circles.emplace_back(4, 0, 0.5987033315235749);
		circles.emplace_back(4, 1, 0.402517257607542);
		circles.emplace_back(4, 2, 0.3633509476901963);
		circles.emplace_back(4, 3, 0.5897748694522306);
		circles.emplace_back(4, 4, 0.4597837353358045);
		circles.emplace_back(4, 5, 0.6787327775498851);
		circles.emplace_back(4, 6, 0.3433820686535909);
		circles.emplace_back(4, 7, 0.3139621491311118);
		circles.emplace_back(4, 8, 0.4494937729323283);
		circles.emplace_back(4, 9, 0.5163270953809842);
		circles.emplace_back(4, 10, 0.6660770231159404);
		circles.emplace_back(5, 0, 0.4323075626743957);
		circles.emplace_back(5, 1, 0.5686692921677604);
		circles.emplace_back(5, 2, 0.6396790353348478);
		circles.emplace_back(5, 3, 0.348273169551976);
		circles.emplace_back(5, 4, 0.4109406514791772);
		circles.emplace_back(5, 5, 0.3813045576447621);
		circles.emplace_back(5, 6, 0.4911567710107192);
		circles.emplace_back(5, 7, 0.6796159413876012);
		circles.emplace_back(5, 8, 0.3537129723234102);
		circles.emplace_back(5, 9, 0.5052871139952912);
		circles.emplace_back(5, 10, 0.1933858917793259);
		circles.emplace_back(6, 0, 0.3268679290311411);
		circles.emplace_back(6, 1, 0.6385872575221583);
		circles.emplace_back(6, 2, 0.3185623366618529);
		circles.emplace_back(6, 3, 0.3511659066891298);
		circles.emplace_back(6, 4, 0.4489601494045928);
		circles.emplace_back(6, 5, 0.5702375125838444);
		circles.emplace_back(6, 6, 0.4588526701787486);
		circles.emplace_back(6, 7, 0.5836601858725771);
		circles.emplace_back(6, 8, 0.5759105029748752);
		circles.emplace_back(6, 9, 0.3144850513665006);
		circles.emplace_back(6, 10, 0.2450565539533272);
		circles.emplace_back(7, 0, 0.2274843394523486);
		circles.emplace_back(7, 1, 0.6547344182850793);
		circles.emplace_back(7, 2, 0.3301954687340185);
		circles.emplace_back(7, 3, 0.3984520355472341);
		circles.emplace_back(7, 4, 0.6013180339476093);
		circles.emplace_back(7, 5, 0.5154726839857176);
		circles.emplace_back(7, 6, 0.4642615507123992);
		circles.emplace_back(7, 7, 0.2918300714576617);
		circles.emplace_back(7, 8, 0.2726652461802587);
		circles.emplace_back(7, 9, 0.4604614683659747);
		circles.emplace_back(7, 10, 0.425297122146003);
		circles.emplace_back(8, 0, 0.1046825153985992);
		circles.emplace_back(8, 1, 0.4173879546811804);
		circles.emplace_back(8, 2, 0.2299695263849571);
		circles.emplace_back(8, 3, 0.5016668318537995);
		circles.emplace_back(8, 4, 0.4125697940820828);
		circles.emplace_back(8, 5, 0.6126382685964927);
		circles.emplace_back(8, 6, 0.3473275942029431);
		circles.emplace_back(8, 7, 0.339476875285618);
		circles.emplace_back(8, 8, 0.5887932704994455);
		circles.emplace_back(8, 9, 0.653813994093798);
		circles.emplace_back(8, 10, 0.396674971212633);
		circles.emplace_back(9, 0, 0.6461516546783969);
		circles.emplace_back(9, 1, 0.2464972947025671);
		circles.emplace_back(9, 2, 0.4361626382684335);
		circles.emplace_back(9, 3, 0.6364482895703986);
		circles.emplace_back(9, 4, 0.235221376712434);
		circles.emplace_back(9, 5, 0.5993259420851246);
		circles.emplace_back(9, 6, 0.5916588505497202);
		circles.emplace_back(9, 7, 0.6017374712275341);
		circles.emplace_back(9, 8, 0.4779455876676366);
		circles.emplace_back(9, 10, 0.3687594391638413);
		circles.emplace_back(10, 0, 0.7217803016072138);
		circles.emplace_back(10, 1, 0.4986338724615052);
		circles.emplace_back(10, 2, 0.5773976460797712);
		circles.emplace_back(10, 3, 0.5162552768597379);
		circles.emplace_back(10, 4, 0.6168069997569546);
		circles.emplace_back(10, 5, 0.5436956159071996);
		circles.emplace_back(10, 6, 0.5306351328967139);
		circles.emplace_back(10, 7, 0.7283190112793818);
		circles.emplace_back(10, 8, 0.4022690448677167);
		circles.emplace_back(10, 9, 0.451655110088177);
		circles.emplace_back(10, 10, 0.2945811991347);
	}
	result_expected = 18.50681881132256;
	timer.reset();
	result_actual = algorithm(a50, b50, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #50: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a51(1, 1);
	Point b51(9, 9);
	{
		circles.emplace_back(0, 0, 0.4326297519961372);
		circles.emplace_back(0, 1, 0.503167819767259);
		circles.emplace_back(0, 2, 0.2244937564479187);
		circles.emplace_back(0, 3, 0.6212418510345742);
		circles.emplace_back(0, 4, 0.4733453378314152);
		circles.emplace_back(0, 5, 0.3665956191485747);
		circles.emplace_back(0, 6, 0.5450088438810781);
		circles.emplace_back(0, 7, 0.6778841727180406);
		circles.emplace_back(0, 8, 0.5237122001359239);
		circles.emplace_back(0, 9, 0.7333787159761413);
		circles.emplace_back(0, 10, 0.3279976307647303);
		circles.emplace_back(1, 0, 0.3178004863439128);
		circles.emplace_back(1, 2, 0.6641049135709182);
		circles.emplace_back(1, 3, 0.2993688653921708);
		circles.emplace_back(1, 4, 0.2321836144896224);
		circles.emplace_back(1, 5, 0.6172834497643634);
		circles.emplace_back(1, 6, 0.4036204343894497);
		circles.emplace_back(1, 7, 0.5570082461228594);
		circles.emplace_back(1, 8, 0.3860099884914234);
		circles.emplace_back(1, 9, 0.3444370916811749);
		circles.emplace_back(1, 10, 0.2733520262176171);
		circles.emplace_back(2, 0, 0.3577928393846377);
		circles.emplace_back(2, 1, 0.2304252867819741);
		circles.emplace_back(2, 2, 0.5754487843019888);
		circles.emplace_back(2, 3, 0.469467873335816);
		circles.emplace_back(2, 4, 0.5862592452904209);
		circles.emplace_back(2, 5, 0.4317862159805372);
		circles.emplace_back(2, 6, 0.423947153496556);
		circles.emplace_back(2, 7, 0.4742193814599887);
		circles.emplace_back(2, 8, 0.7861199367558583);
		circles.emplace_back(2, 9, 0.3680026748450473);
		circles.emplace_back(2, 10, 0.2990709264529869);
		circles.emplace_back(3, 0, 0.7330041660228744);
		circles.emplace_back(3, 1, 0.3291719509055838);
		circles.emplace_back(3, 2, 0.4410499613033608);
		circles.emplace_back(3, 3, 0.4578737168340012);
		circles.emplace_back(3, 4, 0.4156087279552594);
		circles.emplace_back(3, 5, 0.3676040179794654);
		circles.emplace_back(3, 6, 0.6189731669845059);
		circles.emplace_back(3, 7, 0.4676897474331781);
		circles.emplace_back(3, 8, 0.4397558169672265);
		circles.emplace_back(3, 9, 0.5603271277388557);
		circles.emplace_back(3, 10, 0.2605087592499331);
		circles.emplace_back(4, 0, 0.244085510331206);
		circles.emplace_back(4, 1, 0.08508148232940584);
		circles.emplace_back(4, 2, 0.3139535333728418);
		circles.emplace_back(4, 3, 0.5254483507247641);
		circles.emplace_back(4, 4, 0.4800223645521328);
		circles.emplace_back(4, 5, 0.5756668111542239);
		circles.emplace_back(4, 6, 0.3290491929044947);
		circles.emplace_back(4, 7, 0.3238696563290432);
		circles.emplace_back(4, 8, 0.4318550712196156);
		circles.emplace_back(4, 9, 0.3592493541771546);
		circles.emplace_back(4, 10, 0.6922846480971202);
		circles.emplace_back(5, 0, 0.307359637808986);
		circles.emplace_back(5, 1, 0.1777912662131712);
		circles.emplace_back(5, 2, 0.2612392390379682);
		circles.emplace_back(5, 3, 0.6051093408605084);
		circles.emplace_back(5, 4, 0.4553548357682302);
		circles.emplace_back(5, 5, 0.5144368703244254);
		circles.emplace_back(5, 6, 0.5416649710619822);
		circles.emplace_back(5, 7, 0.4895743671571836);
		circles.emplace_back(5, 8, 0.3597238891990855);
		circles.emplace_back(5, 9, 0.4070524369133636);
		circles.emplace_back(5, 10, 0.5331739215413108);
		circles.emplace_back(6, 0, 0.1619286684086546);
		circles.emplace_back(6, 1, 0.6607172425137833);
		circles.emplace_back(6, 2, 0.7591454370645806);
		circles.emplace_back(6, 3, 0.5882125035161152);
		circles.emplace_back(6, 4, 0.4146136604016646);
		circles.emplace_back(6, 5, 0.3374090400757268);
		circles.emplace_back(6, 6, 0.6170234822435304);
		circles.emplace_back(6, 7, 0.5135110350558534);
		circles.emplace_back(6, 8, 0.4972812996944412);
		circles.emplace_back(6, 9, 0.6057562082307413);
		circles.emplace_back(6, 10, 0.2749334844527766);
		circles.emplace_back(7, 0, 0.2199982900405303);
		circles.emplace_back(7, 1, 0.6374605875229463);
		circles.emplace_back(7, 2, 0.5273997248383239);
		circles.emplace_back(7, 3, 0.396411753888242);
		circles.emplace_back(7, 4, 0.3662707364419475);
		circles.emplace_back(7, 5, 0.2914975112071261);
		circles.emplace_back(7, 6, 0.4823330763028935);
		circles.emplace_back(7, 7, 0.5174700340954587);
		circles.emplace_back(7, 8, 0.6237414621049538);
		circles.emplace_back(7, 9, 0.3663934230571613);
		circles.emplace_back(7, 10, 0.4085629021050408);
		circles.emplace_back(8, 0, 0.7472424746258184);
		circles.emplace_back(8, 1, 0.5415937880286946);
		circles.emplace_back(8, 2, 0.4031668567797169);
		circles.emplace_back(8, 3, 0.5618868268327787);
		circles.emplace_back(8, 4, 0.1317185411928221);
		circles.emplace_back(8, 5, 0.6396645691478625);
		circles.emplace_back(8, 6, 0.4623637813841924);
		circles.emplace_back(8, 7, 0.3989134797127917);
		circles.emplace_back(8, 8, 0.5961868633283302);
		circles.emplace_back(8, 9, 0.6073821826139465);
		circles.emplace_back(8, 10, 0.8023412925889716);
		circles.emplace_back(9, 0, 0.3364497016416862);
		circles.emplace_back(9, 1, 0.6320150195388123);
		circles.emplace_back(9, 2, 0.6368842035764828);
		circles.emplace_back(9, 3, 0.3909497417276725);
		circles.emplace_back(9, 4, 0.4903799397172406);
		circles.emplace_back(9, 5, 0.2433902599615976);
		circles.emplace_back(9, 6, 0.6684397684643045);
		circles.emplace_back(9, 7, 0.5412383021553978);
		circles.emplace_back(9, 8, 0.547162829269655);
		circles.emplace_back(9, 10, 0.4196461665211245);
		circles.emplace_back(10, 0, 0.5763016257667913);
		circles.emplace_back(10, 1, 0.6118089731549844);
		circles.emplace_back(10, 2, 0.5710699633928016);
		circles.emplace_back(10, 3, 0.3488002505851909);
		circles.emplace_back(10, 4, 0.2731128743151203);
		circles.emplace_back(10, 5, 0.1624440213432536);
		circles.emplace_back(10, 6, 0.6002918499754741);
		circles.emplace_back(10, 7, 0.5379274881212041);
		circles.emplace_back(10, 8, 0.6609933890635148);
		circles.emplace_back(10, 9, 0.5056318595772609);
		circles.emplace_back(10, 10, 0.3350360562326387);
	}
	result_expected = 16.87019067321377;
	timer.reset();
	result_actual = algorithm(a51, b51, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #51: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a52(1, 1);
	Point b52(9, 9);
	{
		circles.emplace_back(0, 0, 0.3559947923524305);
		circles.emplace_back(0, 1, 0.2074309343704954);
		circles.emplace_back(0, 2, 0.5446163633605465);
		circles.emplace_back(0, 3, 0.3707425407366827);
		circles.emplace_back(0, 4, 0.5647814239142462);
		circles.emplace_back(0, 5, 0.3741019647801295);
		circles.emplace_back(0, 6, 0.5385946247493848);
		circles.emplace_back(0, 7, 0.2795411729486659);
		circles.emplace_back(0, 8, 0.2535103385103866);
		circles.emplace_back(0, 9, 0.5767471133032813);
		circles.emplace_back(0, 10, 0.2856881437590346);
		circles.emplace_back(1, 0, 0.3930764402495697);
		circles.emplace_back(1, 2, 0.2428154720691964);
		circles.emplace_back(1, 3, 0.7042263671988621);
		circles.emplace_back(1, 4, 0.5643124572699889);
		circles.emplace_back(1, 5, 0.4898243424715474);
		circles.emplace_back(1, 6, 0.5736699633998796);
		circles.emplace_back(1, 7, 0.5748789312550798);
		circles.emplace_back(1, 8, 0.6235702054342255);
		circles.emplace_back(1, 9, 0.4400264739291742);
		circles.emplace_back(1, 10, 0.2469003143487498);
		circles.emplace_back(2, 0, 0.5583127785706893);
		circles.emplace_back(2, 1, 0.5632926355814561);
		circles.emplace_back(2, 2, 0.2113662929506972);
		circles.emplace_back(2, 3, 0.6289114874554798);
		circles.emplace_back(2, 4, 0.2407488888362422);
		circles.emplace_back(2, 5, 0.4943545436253771);
		circles.emplace_back(2, 6, 0.3885125789092854);
		circles.emplace_back(2, 7, 0.5892479411093517);
		circles.emplace_back(2, 8, 0.5620451741153374);
		circles.emplace_back(2, 9, 0.5198876529699191);
		circles.emplace_back(2, 10, 0.3096550767542794);
		circles.emplace_back(3, 0, 0.08561560220550746);
		circles.emplace_back(3, 1, 0.3025250921258703);
		circles.emplace_back(3, 2, 0.3280174309154972);
		circles.emplace_back(3, 3, 0.3731573290424421);
		circles.emplace_back(3, 4, 0.5619897763011977);
		circles.emplace_back(3, 5, 0.4477359470212832);
		circles.emplace_back(3, 6, 0.3367483425652608);
		circles.emplace_back(3, 7, 0.2174516954692081);
		circles.emplace_back(3, 8, 0.2754339952720329);
		circles.emplace_back(3, 9, 0.4092618776718154);
		circles.emplace_back(3, 10, 0.4816225422313437);
		circles.emplace_back(4, 0, 0.5273015598999337);
		circles.emplace_back(4, 1, 0.5172548024682327);
		circles.emplace_back(4, 2, 0.5297165334457531);
		circles.emplace_back(4, 3, 0.386777002341114);
		circles.emplace_back(4, 4, 0.4695557249011472);
		circles.emplace_back(4, 5, 0.7441174753708765);
		circles.emplace_back(4, 6, 0.5500404374906793);
		circles.emplace_back(4, 7, 0.3100240798434242);
		circles.emplace_back(4, 8, 0.3115199937717989);
		circles.emplace_back(4, 9, 0.3847476857481524);
		circles.emplace_back(4, 10, 0.6672280375147238);
		circles.emplace_back(5, 0, 0.3025805201148614);
		circles.emplace_back(5, 1, 0.6250709400745108);
		circles.emplace_back(5, 2, 0.6378440973116085);
		circles.emplace_back(5, 3, 0.2606094440678134);
		circles.emplace_back(5, 4, 0.2740698983659968);
		circles.emplace_back(5, 5, 0.129636864666827);
		circles.emplace_back(5, 6, 0.6268269008724019);
		circles.emplace_back(5, 7, 0.6148118563229218);
		circles.emplace_back(5, 8, 0.5034234985476359);
		circles.emplace_back(5, 9, 0.3771709402324632);
		circles.emplace_back(5, 10, 0.4270472869975492);
		circles.emplace_back(6, 0, 0.1175256753573194);
		circles.emplace_back(6, 1, 0.486304629757069);
		circles.emplace_back(6, 2, 0.432241543312557);
		circles.emplace_back(6, 3, 0.5310828561661765);
		circles.emplace_back(6, 4, 0.5602003049338237);
		circles.emplace_back(6, 5, 0.4596813801443204);
		circles.emplace_back(6, 6, 0.5503647738369182);
		circles.emplace_back(6, 7, 0.367743966425769);
		circles.emplace_back(6, 8, 0.4197946397820487);
		circles.emplace_back(6, 9, 0.4941728083183989);
		circles.emplace_back(6, 10, 0.407704162155278);
		circles.emplace_back(7, 0, 0.4404160185484216);
		circles.emplace_back(7, 1, 0.6497072413796559);
		circles.emplace_back(7, 2, 0.5947935722535476);
		circles.emplace_back(7, 3, 0.3852625635685399);
		circles.emplace_back(7, 4, 0.2003626786870882);
		circles.emplace_back(7, 5, 0.658011201233603);
		circles.emplace_back(7, 6, 0.6007219956954941);
		circles.emplace_back(7, 7, 0.760691240360029);
		circles.emplace_back(7, 8, 0.4206150385318324);
		circles.emplace_back(7, 9, 0.4011186916613951);
		circles.emplace_back(7, 10, 0.3247165720677003);
		circles.emplace_back(8, 0, 0.4108411313267424);
		circles.emplace_back(8, 1, 0.386071712966077);
		circles.emplace_back(8, 2, 0.6710002040723339);
		circles.emplace_back(8, 3, 0.5228059058776126);
		circles.emplace_back(8, 4, 0.07818130881059915);
		circles.emplace_back(8, 5, 0.4654348752228543);
		circles.emplace_back(8, 6, 0.4040834747487679);
		circles.emplace_back(8, 7, 0.6348770916229114);
		circles.emplace_back(8, 8, 0.7042096232296898);
		circles.emplace_back(8, 9, 0.3806072295410559);
		circles.emplace_back(8, 10, 0.4899570981273427);
		circles.emplace_back(9, 0, 0.4867875301977619);
		circles.emplace_back(9, 1, 0.3829805351095274);
		circles.emplace_back(9, 2, 0.4391749213216826);
		circles.emplace_back(9, 3, 0.6080038275802507);
		circles.emplace_back(9, 4, 0.3946251827990636);
		circles.emplace_back(9, 5, 0.5378751346142963);
		circles.emplace_back(9, 6, 0.245601384784095);
		circles.emplace_back(9, 7, 0.6700885636964813);
		circles.emplace_back(9, 8, 0.5617422623327002);
		circles.emplace_back(9, 10, 0.5747383485781029);
		circles.emplace_back(10, 0, 0.6567571281222626);
		circles.emplace_back(10, 1, 0.2974260300630703);
		circles.emplace_back(10, 2, 0.5091873623197898);
		circles.emplace_back(10, 3, 0.3145083350362256);
		circles.emplace_back(10, 4, 0.4974104561610147);
		circles.emplace_back(10, 5, 0.409753136546351);
		circles.emplace_back(10, 6, 0.3301610233029351);
		circles.emplace_back(10, 7, 0.2584630652563646);
		circles.emplace_back(10, 8, 0.4013041305122897);
		circles.emplace_back(10, 9, 0.6549310300732031);
		circles.emplace_back(10, 10, 0.6091197367524728);
	}
	result_expected = 14.19105265712948;
	timer.reset();
	result_actual = algorithm(a52, b52, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #52: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a53(1, 1);
	Point b53(9, 9);
	{
		circles.emplace_back(0, 0, 0.389209093269892);
		circles.emplace_back(0, 1, 0.1934429672313854);
		circles.emplace_back(0, 2, 0.3571018329123035);
		circles.emplace_back(0, 3, 0.3961533864727244);
		circles.emplace_back(0, 4, 0.4605375129031017);
		circles.emplace_back(0, 5, 0.6792173719732091);
		circles.emplace_back(0, 6, 0.3115250684553757);
		circles.emplace_back(0, 7, 0.2772611275082454);
		circles.emplace_back(0, 8, 0.3792721023084596);
		circles.emplace_back(0, 9, 0.4559878126485273);
		circles.emplace_back(0, 10, 0.5042187744984403);
		circles.emplace_back(1, 0, 0.3311507025500759);
		circles.emplace_back(1, 2, 0.6322346559958533);
		circles.emplace_back(1, 3, 0.7127552295802161);
		circles.emplace_back(1, 4, 0.3845303040230647);
		circles.emplace_back(1, 5, 0.3131861958419904);
		circles.emplace_back(1, 6, 0.4614525043638423);
		circles.emplace_back(1, 7, 0.5335423831595107);
		circles.emplace_back(1, 8, 0.668761813477613);
		circles.emplace_back(1, 9, 0.5571092245867476);
		circles.emplace_back(1, 10, 0.3407332207309082);
		circles.emplace_back(2, 0, 0.4701111390022561);
		circles.emplace_back(2, 1, 0.4029754385584965);
		circles.emplace_back(2, 2, 0.4351585678523406);
		circles.emplace_back(2, 3, 0.4567315158667042);
		circles.emplace_back(2, 4, 0.4996406906051561);
		circles.emplace_back(2, 5, 0.5631031574914231);
		circles.emplace_back(2, 6, 0.3672132329782471);
		circles.emplace_back(2, 7, 0.2476333200233057);
		circles.emplace_back(2, 8, 0.5329917195020243);
		circles.emplace_back(2, 9, 0.4204863418126479);
		circles.emplace_back(2, 10, 0.3195839594816789);
		circles.emplace_back(3, 0, 0.3025820524664596);
		circles.emplace_back(3, 1, 0.3891814929200336);
		circles.emplace_back(3, 2, 0.3509699946502223);
		circles.emplace_back(3, 3, 0.4840781604638323);
		circles.emplace_back(3, 4, 0.2749720785068348);
		circles.emplace_back(3, 5, 0.5016948989359662);
		circles.emplace_back(3, 6, 0.3156766765052453);
		circles.emplace_back(3, 7, 0.677963301516138);
		circles.emplace_back(3, 8, 0.4127343540312722);
		circles.emplace_back(3, 9, 0.5722564191324636);
		circles.emplace_back(3, 10, 0.7915851185331121);
		circles.emplace_back(4, 0, 0.555453717126511);
		circles.emplace_back(4, 1, 0.6587392575340345);
		circles.emplace_back(4, 2, 0.4376880387542769);
		circles.emplace_back(4, 3, 0.4800385233247653);
		circles.emplace_back(4, 4, 0.4713458645856008);
		circles.emplace_back(4, 5, 0.4244416096480563);
		circles.emplace_back(4, 6, 0.6654780943645164);
		circles.emplace_back(4, 7, 0.571307553187944);
		circles.emplace_back(4, 8, 0.2874270153930411);
		circles.emplace_back(4, 9, 0.489892880176194);
		circles.emplace_back(4, 10, 0.5436860590009018);
		circles.emplace_back(5, 0, 0.2933330059284344);
		circles.emplace_back(5, 1, 0.4622823841637);
		circles.emplace_back(5, 2, 0.2332455826224759);
		circles.emplace_back(5, 3, 0.2808082648320123);
		circles.emplace_back(5, 4, 0.7227731781313196);
		circles.emplace_back(5, 5, 0.3151256950339302);
		circles.emplace_back(5, 6, 0.3428748562233522);
		circles.emplace_back(5, 7, 0.5812295633135364);
		circles.emplace_back(5, 8, 0.3864809159422293);
		circles.emplace_back(5, 9, 0.5042781855678186);
		circles.emplace_back(5, 10, 0.6152422354789451);
		circles.emplace_back(6, 0, 0.4118859228445217);
		circles.emplace_back(6, 1, 0.2315353533485904);
		circles.emplace_back(6, 2, 0.4109210481634363);
		circles.emplace_back(6, 3, 0.5916266071842983);
		circles.emplace_back(6, 4, 0.5257629639236256);
		circles.emplace_back(6, 5, 0.2919533379608765);
		circles.emplace_back(6, 6, 0.4687463089590892);
		circles.emplace_back(6, 7, 0.4368473549606278);
		circles.emplace_back(6, 8, 0.3578554318053648);
		circles.emplace_back(6, 9, 0.5302055442938581);
		circles.emplace_back(6, 10, 0.4301311442395672);
		circles.emplace_back(7, 0, 0.5131046912865713);
		circles.emplace_back(7, 1, 0.3592126066563651);
		circles.emplace_back(7, 2, 0.4816622745478525);
		circles.emplace_back(7, 3, 0.6094606343423947);
		circles.emplace_back(7, 4, 0.3520621770294383);
		circles.emplace_back(7, 5, 0.3846946512116119);
		circles.emplace_back(7, 6, 0.2800939468899742);
		circles.emplace_back(7, 7, 0.3942239550640806);
		circles.emplace_back(7, 8, 0.5782964284764602);
		circles.emplace_back(7, 9, 0.5000648959307);
		circles.emplace_back(7, 10, 0.692351271235384);
		circles.emplace_back(8, 0, 0.164509006566368);
		circles.emplace_back(8, 1, 0.3872390118660405);
		circles.emplace_back(8, 2, 0.5240430616540834);
		circles.emplace_back(8, 3, 0.5403501125285401);
		circles.emplace_back(8, 4, 0.6115204797824845);
		circles.emplace_back(8, 5, 0.4307355254190042);
		circles.emplace_back(8, 6, 0.4709444197593257);
		circles.emplace_back(8, 7, 0.5384860415244475);
		circles.emplace_back(8, 8, 0.4957463603233918);
		circles.emplace_back(8, 9, 0.7133468688698485);
		circles.emplace_back(8, 10, 0.6095298898173496);
		circles.emplace_back(9, 0, 0.5246035730699077);
		circles.emplace_back(9, 1, 0.3353978698840365);
		circles.emplace_back(9, 2, 0.3525177004979923);
		circles.emplace_back(9, 3, 0.3036920747486874);
		circles.emplace_back(9, 4, 0.6126450918847695);
		circles.emplace_back(9, 5, 0.465747845149599);
		circles.emplace_back(9, 6, 0.5057370816590264);
		circles.emplace_back(9, 7, 0.6506022334797308);
		circles.emplace_back(9, 8, 0.4451044658431783);
		circles.emplace_back(9, 10, 0.3599925542017445);
		circles.emplace_back(10, 0, 0.5178163088159635);
		circles.emplace_back(10, 1, 0.4819431910989806);
		circles.emplace_back(10, 2, 0.1734103467548266);
		circles.emplace_back(10, 3, 0.2522619504248723);
		circles.emplace_back(10, 4, 0.5914089330704883);
		circles.emplace_back(10, 5, 0.3438531865132973);
		circles.emplace_back(10, 6, 0.3443641586462036);
		circles.emplace_back(10, 7, 0.2534033639123663);
		circles.emplace_back(10, 8, 0.133897967194207);
		circles.emplace_back(10, 9, 0.4212056576041505);
		circles.emplace_back(10, 10, 0.4207577735418453);
	}
	result_expected = 14.24584306958688;
	timer.reset();
	result_actual = algorithm(a53, b53, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #53: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a54(1, 1);
	Point b54(9, 9);
	{
		circles.emplace_back(0, 0, 0.4001636303728446);
		circles.emplace_back(0, 1, 0.2837752801598981);
		circles.emplace_back(0, 2, 0.7218499638838693);
		circles.emplace_back(0, 3, 0.314295874745585);
		circles.emplace_back(0, 4, 0.7283946575364098);
		circles.emplace_back(0, 5, 0.3696381791727617);
		circles.emplace_back(0, 6, 0.2864380466518924);
		circles.emplace_back(0, 7, 0.4589480076218024);
		circles.emplace_back(0, 8, 0.6109074290608987);
		circles.emplace_back(0, 9, 0.40492817920167);
		circles.emplace_back(0, 10, 0.7394620266510173);
		circles.emplace_back(1, 0, 0.3028553178766742);
		circles.emplace_back(1, 2, 0.3505994459381327);
		circles.emplace_back(1, 3, 0.5715369600104168);
		circles.emplace_back(1, 4, 0.4471277392236516);
		circles.emplace_back(1, 5, 0.6469169773394242);
		circles.emplace_back(1, 6, 0.6694806054001674);
		circles.emplace_back(1, 7, 0.795404510688968);
		circles.emplace_back(1, 8, 0.4976892069680616);
		circles.emplace_back(1, 9, 0.4081812972435728);
		circles.emplace_back(1, 10, 0.3842225173255429);
		circles.emplace_back(2, 0, 0.3672344616847112);
		circles.emplace_back(2, 1, 0.6698690498946235);
		circles.emplace_back(2, 2, 0.4361665290081874);
		circles.emplace_back(2, 3, 0.5088562581455335);
		circles.emplace_back(2, 4, 0.4114516043337062);
		circles.emplace_back(2, 5, 0.6049898330820724);
		circles.emplace_back(2, 6, 0.4602363525191322);
		circles.emplace_back(2, 7, 0.6752435622503981);
		circles.emplace_back(2, 8, 0.7565265978919342);
		circles.emplace_back(2, 9, 0.5484413518337533);
		circles.emplace_back(2, 10, 0.2961550519103184);
		circles.emplace_back(3, 0, 0.3119464508956298);
		circles.emplace_back(3, 1, 0.6097928640665486);
		circles.emplace_back(3, 2, 0.3761088543338701);
		circles.emplace_back(3, 3, 0.6899473788449541);
		circles.emplace_back(3, 4, 0.3721202986082062);
		circles.emplace_back(3, 5, 0.5898806690471247);
		circles.emplace_back(3, 6, 0.2713872018037364);
		circles.emplace_back(3, 7, 0.527188103296794);
		circles.emplace_back(3, 8, 0.3510553370928391);
		circles.emplace_back(3, 9, 0.5198933930369094);
		circles.emplace_back(3, 10, 0.568405966158025);
		circles.emplace_back(4, 0, 0.48584625183139);
		circles.emplace_back(4, 1, 0.483991596638225);
		circles.emplace_back(4, 2, 0.7344509872840718);
		circles.emplace_back(4, 3, 0.5270904651610181);
		circles.emplace_back(4, 4, 0.5608090333873406);
		circles.emplace_back(4, 5, 0.5648322850232944);
		circles.emplace_back(4, 6, 0.4037256186129525);
		circles.emplace_back(4, 7, 0.4556837350828573);
		circles.emplace_back(4, 8, 0.3382104525575414);
		circles.emplace_back(4, 9, 0.4763806039234623);
		circles.emplace_back(4, 10, 0.3275945014553144);
		circles.emplace_back(5, 0, 0.3463544408557936);
		circles.emplace_back(5, 1, 0.2476896103704348);
		circles.emplace_back(5, 2, 0.4727250028168782);
		circles.emplace_back(5, 3, 0.7030349173815921);
		circles.emplace_back(5, 4, 0.3395157237304374);
		circles.emplace_back(5, 5, 0.37070369257126);
		circles.emplace_back(5, 6, 0.6043978703906759);
		circles.emplace_back(5, 7, 0.4178864221321419);
		circles.emplace_back(5, 8, 0.3824799864320084);
		circles.emplace_back(5, 9, 0.4330206454033032);
		circles.emplace_back(5, 10, 0.3269326634472236);
		circles.emplace_back(6, 0, 0.3741052401484922);
		circles.emplace_back(6, 1, 0.4980746158165857);
		circles.emplace_back(6, 2, 0.2595165388891473);
		circles.emplace_back(6, 3, 0.6834444733103737);
		circles.emplace_back(6, 4, 0.5936358466045931);
		circles.emplace_back(6, 5, 0.5288436430273578);
		circles.emplace_back(6, 6, 0.1194026176119223);
		circles.emplace_back(6, 7, 0.5018590297317133);
		circles.emplace_back(6, 8, 0.8100247369380668);
		circles.emplace_back(6, 9, 0.1724603411508724);
		circles.emplace_back(6, 10, 0.5400070389965549);
		circles.emplace_back(7, 0, 0.3974151422968134);
		circles.emplace_back(7, 1, 0.2989013838814571);
		circles.emplace_back(7, 2, 0.2739757603732869);
		circles.emplace_back(7, 3, 0.4172362990910187);
		circles.emplace_back(7, 4, 0.62106557933148);
		circles.emplace_back(7, 5, 0.65045138199348);
		circles.emplace_back(7, 6, 0.4905282006366178);
		circles.emplace_back(7, 7, 0.5008413458475843);
		circles.emplace_back(7, 8, 0.5444013843080029);
		circles.emplace_back(7, 9, 0.3370067796902731);
		circles.emplace_back(7, 10, 0.5941386217949912);
		circles.emplace_back(8, 0, 0.582613379904069);
		circles.emplace_back(8, 1, 0.5217246297514065);
		circles.emplace_back(8, 2, 0.3788785987766459);
		circles.emplace_back(8, 3, 0.5282169912708923);
		circles.emplace_back(8, 4, 0.4656343428650871);
		circles.emplace_back(8, 5, 0.4198946086456999);
		circles.emplace_back(8, 6, 0.36155654147733);
		circles.emplace_back(8, 7, 0.1834045692114159);
		circles.emplace_back(8, 8, 0.5427070930832997);
		circles.emplace_back(8, 9, 0.356572463340126);
		circles.emplace_back(8, 10, 0.5074008849682287);
		circles.emplace_back(9, 0, 0.3083771311445161);
		circles.emplace_back(9, 1, 0.6620902689406648);
		circles.emplace_back(9, 2, 0.3374892519554123);
		circles.emplace_back(9, 3, 0.154951563407667);
		circles.emplace_back(9, 4, 0.4212341281352565);
		circles.emplace_back(9, 5, 0.3086628396296874);
		circles.emplace_back(9, 6, 0.4333624522900208);
		circles.emplace_back(9, 7, 0.5489794374676421);
		circles.emplace_back(9, 8, 0.2370987844420597);
		circles.emplace_back(9, 10, 0.5786433434346691);
		circles.emplace_back(10, 0, 0.2870859032263979);
		circles.emplace_back(10, 1, 0.494404751365073);
		circles.emplace_back(10, 2, 0.777554132672958);
		circles.emplace_back(10, 3, 0.4759888135129586);
		circles.emplace_back(10, 4, 0.4918181836372241);
		circles.emplace_back(10, 5, 0.2772077773930505);
		circles.emplace_back(10, 6, 0.2775399864418432);
		circles.emplace_back(10, 7, 0.6085983911762014);
		circles.emplace_back(10, 8, 0.4305944287916645);
		circles.emplace_back(10, 9, 0.3054566479520872);
		circles.emplace_back(10, 10, 0.2553358505247161);
	}
	result_expected = 15.00537306513809;
	timer.reset();
	result_actual = algorithm(a54, b54, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #54: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a55(1, 1);
	Point b55(9, 9);
	{
		circles.emplace_back(0, 0, 0.5124466266715899);
		circles.emplace_back(0, 1, 0.5180865842616186);
		circles.emplace_back(0, 2, 0.2735773750813678);
		circles.emplace_back(0, 3, 0.361254768515937);
		circles.emplace_back(0, 4, 0.5817714674631134);
		circles.emplace_back(0, 5, 0.43513709732797);
		circles.emplace_back(0, 6, 0.3029910574899986);
		circles.emplace_back(0, 7, 0.3706731079844758);
		circles.emplace_back(0, 8, 0.2334419340128079);
		circles.emplace_back(0, 9, 0.396691045886837);
		circles.emplace_back(0, 10, 0.5622432750882581);
		circles.emplace_back(1, 0, 0.2370212831301615);
		circles.emplace_back(1, 2, 0.2836304830620065);
		circles.emplace_back(1, 3, 0.343751704855822);
		circles.emplace_back(1, 4, 0.5197506710188463);
		circles.emplace_back(1, 5, 0.3703604149399325);
		circles.emplace_back(1, 6, 0.5649150584125892);
		circles.emplace_back(1, 7, 0.4999845500802621);
		circles.emplace_back(1, 8, 0.6322897211881354);
		circles.emplace_back(1, 9, 0.5571699288440868);
		circles.emplace_back(1, 10, 0.4619358292082325);
		circles.emplace_back(2, 0, 0.5835946997394785);
		circles.emplace_back(2, 1, 0.4223526912974194);
		circles.emplace_back(2, 2, 0.5869710898725315);
		circles.emplace_back(2, 3, 0.2937316157156601);
		circles.emplace_back(2, 4, 0.5151027932530269);
		circles.emplace_back(2, 5, 0.5474957813741639);
		circles.emplace_back(2, 6, 0.4014114753110334);
		circles.emplace_back(2, 7, 0.4208810026058927);
		circles.emplace_back(2, 8, 0.2116443076869473);
		circles.emplace_back(2, 9, 0.4148044578032568);
		circles.emplace_back(2, 10, 0.4314353848574683);
		circles.emplace_back(3, 0, 0.5055731397354976);
		circles.emplace_back(3, 1, 0.7084173116600141);
		circles.emplace_back(3, 2, 0.4436009728582576);
		circles.emplace_back(3, 3, 0.5381651882780716);
		circles.emplace_back(3, 4, 0.6027332304278389);
		circles.emplace_back(3, 5, 0.5979036567499861);
		circles.emplace_back(3, 6, 0.2295190717326477);
		circles.emplace_back(3, 7, 0.623118610563688);
		circles.emplace_back(3, 8, 0.5103277072543279);
		circles.emplace_back(3, 9, 0.5274886063998565);
		circles.emplace_back(3, 10, 0.5130708870710805);
		circles.emplace_back(4, 0, 0.4233869545860216);
		circles.emplace_back(4, 1, 0.2569740953156724);
		circles.emplace_back(4, 2, 0.4461039023241028);
		circles.emplace_back(4, 3, 0.5058310210006312);
		circles.emplace_back(4, 4, 0.3573992612538859);
		circles.emplace_back(4, 5, 0.5549805630231276);
		circles.emplace_back(4, 6, 0.240519268414937);
		circles.emplace_back(4, 7, 0.5773628146620468);
		circles.emplace_back(4, 8, 0.6368974071694538);
		circles.emplace_back(4, 9, 0.3969401603797451);
		circles.emplace_back(4, 10, 0.7519073521485552);
		circles.emplace_back(5, 0, 0.3560118052409962);
		circles.emplace_back(5, 1, 0.5107471397845075);
		circles.emplace_back(5, 2, 0.2240047447616234);
		circles.emplace_back(5, 3, 0.5133071034913882);
		circles.emplace_back(5, 4, 0.4466913704993203);
		circles.emplace_back(5, 5, 0.2562100500566885);
		circles.emplace_back(5, 6, 0.3439635941991582);
		circles.emplace_back(5, 7, 0.4986105913063511);
		circles.emplace_back(5, 8, 0.5187855608062818);
		circles.emplace_back(5, 9, 0.2833014826057479);
		circles.emplace_back(5, 10, 0.6272517081582919);
		circles.emplace_back(6, 0, 0.8236982572590932);
		circles.emplace_back(6, 1, 0.4672941186698154);
		circles.emplace_back(6, 2, 0.5678593833697959);
		circles.emplace_back(6, 3, 0.4590127958217636);
		circles.emplace_back(6, 4, 0.4903476072242483);
		circles.emplace_back(6, 5, 0.4003446857677773);
		circles.emplace_back(6, 6, 0.4789490847615525);
		circles.emplace_back(6, 7, 0.4753419518703594);
		circles.emplace_back(6, 8, 0.6135403401916847);
		circles.emplace_back(6, 9, 0.4561971974791958);
		circles.emplace_back(6, 10, 0.7162290283245966);
		circles.emplace_back(7, 0, 0.2618330197641626);
		circles.emplace_back(7, 1, 0.3227929146727547);
		circles.emplace_back(7, 2, 0.4028654649155214);
		circles.emplace_back(7, 3, 0.5229024248896167);
		circles.emplace_back(7, 4, 0.4425556425238028);
		circles.emplace_back(7, 5, 0.4781355526065454);
		circles.emplace_back(7, 6, 0.623480944451876);
		circles.emplace_back(7, 7, 0.2898798522306606);
		circles.emplace_back(7, 8, 0.3375870010117069);
		circles.emplace_back(7, 9, 0.191364680766128);
		circles.emplace_back(7, 10, 0.2405236947583035);
		circles.emplace_back(8, 0, 0.3167777902213856);
		circles.emplace_back(8, 1, 0.5172232397133484);
		circles.emplace_back(8, 2, 0.3931938096648082);
		circles.emplace_back(8, 3, 0.2820455213310197);
		circles.emplace_back(8, 4, 0.7453780934913083);
		circles.emplace_back(8, 5, 0.230995580018498);
		circles.emplace_back(8, 6, 0.3369278499623761);
		circles.emplace_back(8, 7, 0.4430103085236624);
		circles.emplace_back(8, 8, 0.3311734015820548);
		circles.emplace_back(8, 9, 0.5396161210024729);
		circles.emplace_back(8, 10, 0.3792858663713559);
		circles.emplace_back(9, 0, 0.3448765390785411);
		circles.emplace_back(9, 1, 0.5686234866036102);
		circles.emplace_back(9, 2, 0.4279783277073875);
		circles.emplace_back(9, 3, 0.2289972690632567);
		circles.emplace_back(9, 4, 0.4465470011578873);
		circles.emplace_back(9, 5, 0.8357475383905694);
		circles.emplace_back(9, 6, 0.3273372069234028);
		circles.emplace_back(9, 7, 0.3037964425748214);
		circles.emplace_back(9, 8, 0.3098106828751042);
		circles.emplace_back(9, 10, 0.6736773871583864);
		circles.emplace_back(10, 0, 0.3247941704699769);
		circles.emplace_back(10, 1, 0.1864408122142777);
		circles.emplace_back(10, 2, 0.4724018543260172);
		circles.emplace_back(10, 3, 0.5667966636596248);
		circles.emplace_back(10, 4, 0.2882115859771147);
		circles.emplace_back(10, 5, 0.6203773479675874);
		circles.emplace_back(10, 6, 0.5318013371201232);
		circles.emplace_back(10, 7, 0.5390908968402073);
		circles.emplace_back(10, 8, 0.2846820151666179);
		circles.emplace_back(10, 9, 0.6356825059046969);
		circles.emplace_back(10, 10, 0.5929049614118412);
	}
	result_expected = 13.19286880988421;
	timer.reset();
	result_actual = algorithm(a55, b55, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #55: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a56(1, 1);
	Point b56(9, 9);
	{
		circles.emplace_back(0, 0, 0.2323335489956662);
		circles.emplace_back(0, 1, 0.7206771396333351);
		circles.emplace_back(0, 2, 0.4459006070857868);
		circles.emplace_back(0, 3, 0.482684210431762);
		circles.emplace_back(0, 4, 0.3817329884273931);
		circles.emplace_back(0, 5, 0.582001374126412);
		circles.emplace_back(0, 6, 0.2064056539675221);
		circles.emplace_back(0, 7, 0.5849640525178984);
		circles.emplace_back(0, 8, 0.354665399598889);
		circles.emplace_back(0, 9, 0.4016751673305407);
		circles.emplace_back(0, 10, 0.1749115843093023);
		circles.emplace_back(1, 0, 0.4984429606469348);
		circles.emplace_back(1, 2, 0.3681186307920143);
		circles.emplace_back(1, 3, 0.5338729901472107);
		circles.emplace_back(1, 4, 0.4647559625795111);
		circles.emplace_back(1, 5, 0.5710801194654778);
		circles.emplace_back(1, 6, 0.3504719792632386);
		circles.emplace_back(1, 7, 0.1620410114759579);
		circles.emplace_back(1, 8, 0.2315821088617668);
		circles.emplace_back(1, 9, 0.4139748198213056);
		circles.emplace_back(1, 10, 0.4632369138998911);
		circles.emplace_back(2, 0, 0.5193194614956155);
		circles.emplace_back(2, 1, 0.1840446652611717);
		circles.emplace_back(2, 2, 0.3478630407946184);
		circles.emplace_back(2, 3, 0.3483837353764102);
		circles.emplace_back(2, 4, 0.6493946824455633);
		circles.emplace_back(2, 5, 0.759163599810563);
		circles.emplace_back(2, 6, 0.4853562192292884);
		circles.emplace_back(2, 7, 0.6168791738105938);
		circles.emplace_back(2, 8, 0.2859058669069782);
		circles.emplace_back(2, 9, 0.4529516478767618);
		circles.emplace_back(2, 10, 0.4020472067641094);
		circles.emplace_back(3, 0, 0.6440599239198491);
		circles.emplace_back(3, 1, 0.2785314835840836);
		circles.emplace_back(3, 2, 0.4469401910668239);
		circles.emplace_back(3, 3, 0.6996084143640473);
		circles.emplace_back(3, 4, 0.3874671176774427);
		circles.emplace_back(3, 5, 0.4438803905854001);
		circles.emplace_back(3, 6, 0.5212285736342892);
		circles.emplace_back(3, 7, 0.4140071443514898);
		circles.emplace_back(3, 8, 0.5927667344687506);
		circles.emplace_back(3, 9, 0.2693126362049952);
		circles.emplace_back(3, 10, 0.1946818563854322);
		circles.emplace_back(4, 0, 0.5719631099374964);
		circles.emplace_back(4, 1, 0.4033809487475082);
		circles.emplace_back(4, 2, 0.547814947203733);
		circles.emplace_back(4, 3, 0.2829020080855116);
		circles.emplace_back(4, 4, 0.6487731422530487);
		circles.emplace_back(4, 5, 0.5394554151920602);
		circles.emplace_back(4, 6, 0.5720559045905247);
		circles.emplace_back(4, 7, 0.5145975343650206);
		circles.emplace_back(4, 8, 0.6306280848802999);
		circles.emplace_back(4, 9, 0.5617874913616105);
		circles.emplace_back(4, 10, 0.3657458069035783);
		circles.emplace_back(5, 0, 0.3969765441259369);
		circles.emplace_back(5, 1, 0.2345468758838251);
		circles.emplace_back(5, 2, 0.486340397852473);
		circles.emplace_back(5, 3, 0.4804262209916487);
		circles.emplace_back(5, 4, 0.4707882534479722);
		circles.emplace_back(5, 5, 0.4890528173418716);
		circles.emplace_back(5, 6, 0.3649683159543201);
		circles.emplace_back(5, 7, 0.7358142202952876);
		circles.emplace_back(5, 8, 0.6456379269948229);
		circles.emplace_back(5, 9, 0.4287170323776081);
		circles.emplace_back(5, 10, 0.2979774228064343);
		circles.emplace_back(6, 0, 0.3318263106280938);
		circles.emplace_back(6, 1, 0.5562002569204196);
		circles.emplace_back(6, 2, 0.4056941096903756);
		circles.emplace_back(6, 3, 0.4941478640539572);
		circles.emplace_back(6, 4, 0.4104070434579626);
		circles.emplace_back(6, 5, 0.4299561792751774);
		circles.emplace_back(6, 6, 0.5713749355869367);
		circles.emplace_back(6, 7, 0.5438416640041396);
		circles.emplace_back(6, 8, 0.6952873166883364);
		circles.emplace_back(6, 9, 0.5070781279122457);
		circles.emplace_back(6, 10, 0.6312817135127261);
		circles.emplace_back(7, 0, 0.220821573282592);
		circles.emplace_back(7, 1, 0.2877973629394546);
		circles.emplace_back(7, 2, 0.2030887258937582);
		circles.emplace_back(7, 3, 0.5263301710831001);
		circles.emplace_back(7, 4, 0.3784058539895341);
		circles.emplace_back(7, 5, 0.5468594253296032);
		circles.emplace_back(7, 6, 0.4549179143970832);
		circles.emplace_back(7, 7, 0.6435839546145871);
		circles.emplace_back(7, 8, 0.2555840023560449);
		circles.emplace_back(7, 9, 0.3312851207563653);
		circles.emplace_back(7, 10, 0.2409835191210732);
		circles.emplace_back(8, 0, 0.3096262111561373);
		circles.emplace_back(8, 1, 0.5587184089003131);
		circles.emplace_back(8, 2, 0.4325024906778708);
		circles.emplace_back(8, 3, 0.315920254192315);
		circles.emplace_back(8, 4, 0.3696733580203727);
		circles.emplace_back(8, 5, 0.8344569560838863);
		circles.emplace_back(8, 6, 0.5758377393940464);
		circles.emplace_back(8, 7, 0.3505821635713801);
		circles.emplace_back(8, 8, 0.5055560398148372);
		circles.emplace_back(8, 9, 0.4994815534679219);
		circles.emplace_back(8, 10, 0.4184766598278656);
		circles.emplace_back(9, 0, 0.117943499959074);
		circles.emplace_back(9, 1, 0.3956922729732469);
		circles.emplace_back(9, 2, 0.4427176103694364);
		circles.emplace_back(9, 3, 0.2222307468065992);
		circles.emplace_back(9, 4, 0.5155230412026867);
		circles.emplace_back(9, 5, 0.4701777777867391);
		circles.emplace_back(9, 6, 0.4656294460175558);
		circles.emplace_back(9, 7, 0.6292329978430643);
		circles.emplace_back(9, 8, 0.3649568442022428);
		circles.emplace_back(9, 10, 0.5641184979351237);
		circles.emplace_back(10, 0, 0.5762266372097656);
		circles.emplace_back(10, 1, 0.5186884014168754);
		circles.emplace_back(10, 2, 0.3793444363167509);
		circles.emplace_back(10, 3, 0.322330307518132);
		circles.emplace_back(10, 4, 0.5024063034681603);
		circles.emplace_back(10, 5, 0.4728041127556935);
		circles.emplace_back(10, 6, 0.3389934442704544);
		circles.emplace_back(10, 7, 0.5585309055866673);
		circles.emplace_back(10, 8, 0.3402563296956941);
		circles.emplace_back(10, 9, 0.3300243171164766);
		circles.emplace_back(10, 10, 0.2661876605590806);
	}
	result_expected = 15.10205565552759;
	timer.reset();
	result_actual = algorithm(a56, b56, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #56: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a57(1, 1);
	Point b57(9, 9);
	{
		circles.emplace_back(0, 0, 0.1221488981740549);
		circles.emplace_back(0, 1, 0.6029445263324306);
		circles.emplace_back(0, 2, 0.4536947805667296);
		circles.emplace_back(0, 3, 0.3396035473560914);
		circles.emplace_back(0, 4, 0.3758750678272918);
		circles.emplace_back(0, 5, 0.6858187270117924);
		circles.emplace_back(0, 6, 0.2942820882657542);
		circles.emplace_back(0, 7, 0.4390001779189333);
		circles.emplace_back(0, 8, 0.7370808306382969);
		circles.emplace_back(0, 9, 0.6133428237168118);
		circles.emplace_back(0, 10, 0.5732725702458993);
		circles.emplace_back(1, 0, 0.3608076154952869);
		circles.emplace_back(1, 2, 0.3862288807751611);
		circles.emplace_back(1, 3, 0.2834937394363806);
		circles.emplace_back(1, 4, 0.2668759146938101);
		circles.emplace_back(1, 5, 0.6952387297293171);
		circles.emplace_back(1, 6, 0.395401022513397);
		circles.emplace_back(1, 7, 0.1752443383214995);
		circles.emplace_back(1, 8, 0.417658468731679);
		circles.emplace_back(1, 9, 0.6055494505679234);
		circles.emplace_back(1, 10, 0.6800681897671893);
		circles.emplace_back(2, 0, 0.7347572733415291);
		circles.emplace_back(2, 1, 0.5522312266984954);
		circles.emplace_back(2, 2, 0.3000724596669898);
		circles.emplace_back(2, 3, 0.4272276531206444);
		circles.emplace_back(2, 4, 0.2059147714404389);
		circles.emplace_back(2, 5, 0.6331175059312955);
		circles.emplace_back(2, 6, 0.2376493192976341);
		circles.emplace_back(2, 7, 0.6030324143590405);
		circles.emplace_back(2, 8, 0.4208093561930582);
		circles.emplace_back(2, 9, 0.3229253100464121);
		circles.emplace_back(2, 10, 0.357086038752459);
		circles.emplace_back(3, 0, 0.393037788500078);
		circles.emplace_back(3, 1, 0.5158205079613253);
		circles.emplace_back(3, 2, 0.3889493797207251);
		circles.emplace_back(3, 3, 0.6712570782518014);
		circles.emplace_back(3, 4, 0.2781901733251289);
		circles.emplace_back(3, 5, 0.3889022615505383);
		circles.emplace_back(3, 6, 0.4263279309729114);
		circles.emplace_back(3, 7, 0.5164827903499827);
		circles.emplace_back(3, 8, 0.299683006410487);
		circles.emplace_back(3, 9, 0.4637067413656041);
		circles.emplace_back(3, 10, 0.1278790809446946);
		circles.emplace_back(4, 0, 0.1978052988415584);
		circles.emplace_back(4, 1, 0.5158049096586182);
		circles.emplace_back(4, 2, 0.6761686340672896);
		circles.emplace_back(4, 3, 0.3787419611820951);
		circles.emplace_back(4, 4, 0.2207878151675686);
		circles.emplace_back(4, 5, 0.6039050213294104);
		circles.emplace_back(4, 6, 0.5491755987284704);
		circles.emplace_back(4, 7, 0.3039475184166804);
		circles.emplace_back(4, 8, 0.3504623923217878);
		circles.emplace_back(4, 9, 0.2106005155714229);
		circles.emplace_back(4, 10, 0.5709496144903824);
		circles.emplace_back(5, 0, 0.6470440028468146);
		circles.emplace_back(5, 1, 0.5880511162569746);
		circles.emplace_back(5, 2, 0.6033513094531372);
		circles.emplace_back(5, 3, 0.4427642657188698);
		circles.emplace_back(5, 4, 0.6079021439189091);
		circles.emplace_back(5, 5, 0.3060857347911224);
		circles.emplace_back(5, 6, 0.2265269574942067);
		circles.emplace_back(5, 7, 0.4116229646606371);
		circles.emplace_back(5, 8, 0.6178250136086717);
		circles.emplace_back(5, 9, 0.3325507240137085);
		circles.emplace_back(5, 10, 0.3150907336967066);
		circles.emplace_back(6, 0, 0.6535231115994975);
		circles.emplace_back(6, 1, 0.5800875772023574);
		circles.emplace_back(6, 2, 0.624674792191945);
		circles.emplace_back(6, 3, 0.5690259010763838);
		circles.emplace_back(6, 4, 0.422931192512624);
		circles.emplace_back(6, 5, 0.3540309315780177);
		circles.emplace_back(6, 6, 0.4229958211770281);
		circles.emplace_back(6, 7, 0.4416291686939076);
		circles.emplace_back(6, 8, 0.6340938142267987);
		circles.emplace_back(6, 9, 0.4108362309867516);
		circles.emplace_back(6, 10, 0.4263242453103885);
		circles.emplace_back(7, 0, 0.4447963361861184);
		circles.emplace_back(7, 1, 0.4898096770746633);
		circles.emplace_back(7, 2, 0.4391033003339544);
		circles.emplace_back(7, 3, 0.3782298678299412);
		circles.emplace_back(7, 4, 0.4244251257972791);
		circles.emplace_back(7, 5, 0.5232874850509688);
		circles.emplace_back(7, 6, 0.4283589359605685);
		circles.emplace_back(7, 7, 0.3056771147763356);
		circles.emplace_back(7, 8, 0.3090602019103244);
		circles.emplace_back(7, 9, 0.2687147934688255);
		circles.emplace_back(7, 10, 0.2086198939243331);
		circles.emplace_back(8, 0, 0.6004337263992056);
		circles.emplace_back(8, 1, 0.5849053780781105);
		circles.emplace_back(8, 2, 0.2261627941159531);
		circles.emplace_back(8, 3, 0.4741355657810345);
		circles.emplace_back(8, 4, 0.1838778860634193);
		circles.emplace_back(8, 5, 0.5003280115546659);
		circles.emplace_back(8, 6, 0.5364520379109308);
		circles.emplace_back(8, 7, 0.3694353418657556);
		circles.emplace_back(8, 8, 0.8458287866553291);
		circles.emplace_back(8, 9, 0.2529805853264406);
		circles.emplace_back(8, 10, 0.331604095059447);
		circles.emplace_back(9, 0, 0.6658056620741263);
		circles.emplace_back(9, 1, 0.7980256344890222);
		circles.emplace_back(9, 2, 0.06266447764355688);
		circles.emplace_back(9, 3, 0.3765041527105495);
		circles.emplace_back(9, 4, 0.7063217541435733);
		circles.emplace_back(9, 5, 0.5328800907125696);
		circles.emplace_back(9, 6, 0.2830609190510586);
		circles.emplace_back(9, 7, 0.3673995501128957);
		circles.emplace_back(9, 8, 0.2475590594345703);
		circles.emplace_back(9, 10, 0.7281271502142772);
		circles.emplace_back(10, 0, 0.2554541369201616);
		circles.emplace_back(10, 1, 0.402859251271002);
		circles.emplace_back(10, 2, 0.6761093462118879);
		circles.emplace_back(10, 3, 0.2879994580289349);
		circles.emplace_back(10, 4, 0.3575716874795035);
		circles.emplace_back(10, 5, 0.6928192551014944);
		circles.emplace_back(10, 6, 0.2280265104258433);
		circles.emplace_back(10, 7, 0.3615500632440671);
		circles.emplace_back(10, 8, 0.1506669753463939);
		circles.emplace_back(10, 9, 0.6213389430893584);
		circles.emplace_back(10, 10, 0.1893270639935508);
	}
	result_expected = 12.62404327521149;
	timer.reset();
	result_actual = algorithm(a57, b57, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #57: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a58(1, 1);
	Point b58(9, 9);
	{
		circles.emplace_back(0, 0, 0.2287486104061827);
		circles.emplace_back(0, 1, 0.3779689605580643);
		circles.emplace_back(0, 2, 0.8286933644441887);
		circles.emplace_back(0, 3, 0.5056703105801716);
		circles.emplace_back(0, 4, 0.4949759684270247);
		circles.emplace_back(0, 5, 0.817624053102918);
		circles.emplace_back(0, 6, 0.7284264587564394);
		circles.emplace_back(0, 7, 0.2793432088801637);
		circles.emplace_back(0, 8, 0.3845422969898209);
		circles.emplace_back(0, 9, 0.5432551949517801);
		circles.emplace_back(0, 10, 0.5249902161536738);
		circles.emplace_back(1, 0, 0.481674923398532);
		circles.emplace_back(1, 2, 0.373853550455533);
		circles.emplace_back(1, 3, 0.3952631295891478);
		circles.emplace_back(1, 4, 0.4475947749568149);
		circles.emplace_back(1, 5, 0.3590060627320781);
		circles.emplace_back(1, 6, 0.5548514192691073);
		circles.emplace_back(1, 7, 0.1159948590444401);
		circles.emplace_back(1, 8, 0.5658944568363949);
		circles.emplace_back(1, 9, 0.4603376053506508);
		circles.emplace_back(1, 10, 0.5693517088657245);
		circles.emplace_back(2, 0, 0.4519042884232476);
		circles.emplace_back(2, 1, 0.5031347394688055);
		circles.emplace_back(2, 2, 0.4647845128783956);
		circles.emplace_back(2, 3, 0.5049061560770497);
		circles.emplace_back(2, 4, 0.5758300579385832);
		circles.emplace_back(2, 5, 0.6123851666925475);
		circles.emplace_back(2, 6, 0.2369590308750048);
		circles.emplace_back(2, 7, 0.4928126830374822);
		circles.emplace_back(2, 8, 0.5325155624421313);
		circles.emplace_back(2, 9, 0.6314831961644813);
		circles.emplace_back(2, 10, 0.3884086771169677);
		circles.emplace_back(3, 0, 0.4988990885904059);
		circles.emplace_back(3, 1, 0.5604961584554985);
		circles.emplace_back(3, 2, 0.3823139845160767);
		circles.emplace_back(3, 3, 0.5732339173788205);
		circles.emplace_back(3, 4, 0.4477051771944389);
		circles.emplace_back(3, 5, 0.393478558701463);
		circles.emplace_back(3, 6, 0.6300511100096627);
		circles.emplace_back(3, 7, 0.496010528714396);
		circles.emplace_back(3, 8, 0.3706883253296837);
		circles.emplace_back(3, 9, 0.2943374141352251);
		circles.emplace_back(3, 10, 0.267983232694678);
		circles.emplace_back(4, 0, 0.6601416502380744);
		circles.emplace_back(4, 1, 0.4190774854039773);
		circles.emplace_back(4, 2, 0.02485408347565681);
		circles.emplace_back(4, 3, 0.2435516920639202);
		circles.emplace_back(4, 4, 0.6347645214060321);
		circles.emplace_back(4, 5, 0.432000627159141);
		circles.emplace_back(4, 6, 0.504322590236552);
		circles.emplace_back(4, 7, 0.4912240422097966);
		circles.emplace_back(4, 8, 0.568336907797493);
		circles.emplace_back(4, 9, 0.4005106165772304);
		circles.emplace_back(4, 10, 0.4601477672578766);
		circles.emplace_back(5, 0, 0.2878285244805738);
		circles.emplace_back(5, 1, 0.4270282143959775);
		circles.emplace_back(5, 2, 0.3181345322867855);
		circles.emplace_back(5, 3, 0.6235605887370184);
		circles.emplace_back(5, 4, 0.2959744776366278);
		circles.emplace_back(5, 5, 0.5860402863705531);
		circles.emplace_back(5, 6, 0.7585714194690808);
		circles.emplace_back(5, 7, 0.2735756897600368);
		circles.emplace_back(5, 8, 0.211183685506694);
		circles.emplace_back(5, 9, 0.3519828973570838);
		circles.emplace_back(5, 10, 0.5711634812643751);
		circles.emplace_back(6, 0, 0.4823160733329132);
		circles.emplace_back(6, 1, 0.478357662144117);
		circles.emplace_back(6, 2, 0.444428925239481);
		circles.emplace_back(6, 3, 0.5347657076781616);
		circles.emplace_back(6, 4, 0.6648300049128011);
		circles.emplace_back(6, 5, 0.493205874483101);
		circles.emplace_back(6, 6, 0.6147742154309526);
		circles.emplace_back(6, 7, 0.3606389419874176);
		circles.emplace_back(6, 8, 0.3865250944392756);
		circles.emplace_back(6, 9, 0.5542599024949595);
		circles.emplace_back(6, 10, 0.5305271316552534);
		circles.emplace_back(7, 0, 0.5849913846468553);
		circles.emplace_back(7, 1, 0.5313445658655837);
		circles.emplace_back(7, 2, 0.2810985368443653);
		circles.emplace_back(7, 3, 0.5031527942279354);
		circles.emplace_back(7, 4, 0.3417935346951708);
		circles.emplace_back(7, 5, 0.1838107141898945);
		circles.emplace_back(7, 6, 0.7644088140456006);
		circles.emplace_back(7, 7, 0.5875970058375969);
		circles.emplace_back(7, 8, 0.4564915686612949);
		circles.emplace_back(7, 9, 0.7280605499865487);
		circles.emplace_back(7, 10, 0.163507989118807);
		circles.emplace_back(8, 0, 0.3316148648271337);
		circles.emplace_back(8, 1, 0.4512441569706425);
		circles.emplace_back(8, 2, 0.3169986314373091);
		circles.emplace_back(8, 3, 0.5169514457462355);
		circles.emplace_back(8, 4, 0.4030290659749881);
		circles.emplace_back(8, 5, 0.4023077178513631);
		circles.emplace_back(8, 6, 0.7146920838626102);
		circles.emplace_back(8, 7, 0.4818515439284965);
		circles.emplace_back(8, 8, 0.2730428887763992);
		circles.emplace_back(8, 9, 0.4401951087405905);
		circles.emplace_back(8, 10, 0.6651328067528084);
		circles.emplace_back(9, 0, 0.4675324051408097);
		circles.emplace_back(9, 1, 0.3837328732246533);
		circles.emplace_back(9, 2, 0.4332327551906928);
		circles.emplace_back(9, 3, 0.7904918682994321);
		circles.emplace_back(9, 4, 0.5791456349892542);
		circles.emplace_back(9, 5, 0.5778461830923334);
		circles.emplace_back(9, 6, 0.4451412172755226);
		circles.emplace_back(9, 7, 0.7719910874264314);
		circles.emplace_back(9, 8, 0.4368719833670184);
		circles.emplace_back(9, 10, 0.5190276567125692);
		circles.emplace_back(10, 0, 0.3072641934966668);
		circles.emplace_back(10, 1, 0.6165168033214286);
		circles.emplace_back(10, 2, 0.7863339421106502);
		circles.emplace_back(10, 3, 0.4806015452602878);
		circles.emplace_back(10, 4, 0.3960709621896967);
		circles.emplace_back(10, 5, 0.2621008324669674);
		circles.emplace_back(10, 6, 0.3658442801563069);
		circles.emplace_back(10, 7, 0.7310329385334625);
		circles.emplace_back(10, 8, 0.4565572604304179);
		circles.emplace_back(10, 9, 0.6253936131717637);
		circles.emplace_back(10, 10, 0.5461155161960051);
	}
	result_expected = -1.0;
	timer.reset();
	result_actual = algorithm(a58, b58, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #58: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a59(1, 1);
	Point b59(9, 9);
	{
		circles.emplace_back(0, 0, 0.5941938782343641);
		circles.emplace_back(0, 1, 0.3621696004411206);
		circles.emplace_back(0, 2, 0.3442545376019552);
		circles.emplace_back(0, 3, 0.4080553288338706);
		circles.emplace_back(0, 4, 0.5125591587508097);
		circles.emplace_back(0, 5, 0.5518780234968289);
		circles.emplace_back(0, 6, 0.6185844713123515);
		circles.emplace_back(0, 7, 0.7742729042423889);
		circles.emplace_back(0, 8, 0.3914568154374137);
		circles.emplace_back(0, 9, 0.335022291331552);
		circles.emplace_back(0, 10, 0.702525460277684);
		circles.emplace_back(1, 0, 0.4599212213186547);
		circles.emplace_back(1, 2, 0.5524983003968372);
		circles.emplace_back(1, 3, 0.5045565150445327);
		circles.emplace_back(1, 4, 0.6511526254238561);
		circles.emplace_back(1, 5, 0.5585002743406221);
		circles.emplace_back(1, 6, 0.3743133457610384);
		circles.emplace_back(1, 7, 0.3493172215064987);
		circles.emplace_back(1, 8, 0.4747832446591929);
		circles.emplace_back(1, 9, 0.3282462331233546);
		circles.emplace_back(1, 10, 0.6487145144725218);
		circles.emplace_back(2, 0, 0.6059398572659119);
		circles.emplace_back(2, 1, 0.3040280224056914);
		circles.emplace_back(2, 2, 0.194731540675275);
		circles.emplace_back(2, 3, 0.5304164385655895);
		circles.emplace_back(2, 4, 0.3410487299552187);
		circles.emplace_back(2, 5, 0.6187095466302708);
		circles.emplace_back(2, 6, 0.5353009483544156);
		circles.emplace_back(2, 7, 0.5084347449475899);
		circles.emplace_back(2, 8, 0.5043453871970996);
		circles.emplace_back(2, 9, 0.5437729333760216);
		circles.emplace_back(2, 10, 0.6609684885246679);
		circles.emplace_back(3, 0, 0.4772896686801686);
		circles.emplace_back(3, 1, 0.3432204330107197);
		circles.emplace_back(3, 2, 0.4653136587934568);
		circles.emplace_back(3, 3, 0.4614003847120329);
		circles.emplace_back(3, 4, 0.1361393537605181);
		circles.emplace_back(3, 5, 0.6195137817179784);
		circles.emplace_back(3, 6, 0.3698475786717608);
		circles.emplace_back(3, 7, 0.4286088992608711);
		circles.emplace_back(3, 8, 0.3939678414026275);
		circles.emplace_back(3, 9, 0.7190483493497595);
		circles.emplace_back(3, 10, 0.1599481354700401);
		circles.emplace_back(4, 0, 0.424982118490152);
		circles.emplace_back(4, 1, 0.408952745818533);
		circles.emplace_back(4, 2, 0.5945621825521812);
		circles.emplace_back(4, 3, 0.549375752848573);
		circles.emplace_back(4, 4, 0.7112746753497049);
		circles.emplace_back(4, 5, 0.3401376174995676);
		circles.emplace_back(4, 6, 0.3326640249928459);
		circles.emplace_back(4, 7, 0.5908244177000597);
		circles.emplace_back(4, 8, 0.2001844095764682);
		circles.emplace_back(4, 9, 0.539533993997611);
		circles.emplace_back(4, 10, 0.4854373212670907);
		circles.emplace_back(5, 0, 0.3394104496808723);
		circles.emplace_back(5, 1, 0.2511399653507396);
		circles.emplace_back(5, 2, 0.3627781382063404);
		circles.emplace_back(5, 3, 0.4573176583042368);
		circles.emplace_back(5, 4, 0.2050284582423046);
		circles.emplace_back(5, 5, 0.5719243264524266);
		circles.emplace_back(5, 6, 0.526467464142479);
		circles.emplace_back(5, 7, 0.4878686442738399);
		circles.emplace_back(5, 8, 0.3966994871618226);
		circles.emplace_back(5, 9, 0.6427592889172956);
		circles.emplace_back(5, 10, 0.1903016502270475);
		circles.emplace_back(6, 0, 0.32108122499194);
		circles.emplace_back(6, 1, 0.1120363465743139);
		circles.emplace_back(6, 2, 0.1284758711932227);
		circles.emplace_back(6, 3, 0.4921534400666132);
		circles.emplace_back(6, 4, 0.4018214378273114);
		circles.emplace_back(6, 5, 0.7749511325033381);
		circles.emplace_back(6, 6, 0.5943956617964431);
		circles.emplace_back(6, 7, 0.6141941307345405);
		circles.emplace_back(6, 8, 0.4900516031077131);
		circles.emplace_back(6, 9, 0.3747299338923767);
		circles.emplace_back(6, 10, 0.1915481044678017);
		circles.emplace_back(7, 0, 0.5081987485522405);
		circles.emplace_back(7, 1, 0.6334499530261383);
		circles.emplace_back(7, 2, 0.3095997271360829);
		circles.emplace_back(7, 3, 0.4268487208290025);
		circles.emplace_back(7, 4, 0.5581559123704209);
		circles.emplace_back(7, 5, 0.5890536980470642);
		circles.emplace_back(7, 6, 0.387912458111532);
		circles.emplace_back(7, 7, 0.483863270538859);
		circles.emplace_back(7, 8, 0.3083073843503371);
		circles.emplace_back(7, 9, 0.5345505308127031);
		circles.emplace_back(7, 10, 0.690071311709471);
		circles.emplace_back(8, 0, 0.6097828489495442);
		circles.emplace_back(8, 1, 0.3347423082450405);
		circles.emplace_back(8, 2, 0.359843567549251);
		circles.emplace_back(8, 3, 0.6443241688655689);
		circles.emplace_back(8, 4, 0.53423492226284);
		circles.emplace_back(8, 5, 0.08867113518062979);
		circles.emplace_back(8, 6, 0.3795147269731388);
		circles.emplace_back(8, 7, 0.5195492510916665);
		circles.emplace_back(8, 8, 0.3355553001863882);
		circles.emplace_back(8, 9, 0.2895042369375005);
		circles.emplace_back(8, 10, 0.1568115466972813);
		circles.emplace_back(9, 0, 0.4881579525070265);
		circles.emplace_back(9, 1, 0.2201460460899398);
		circles.emplace_back(9, 2, 0.2958602067315951);
		circles.emplace_back(9, 3, 0.3797824371373281);
		circles.emplace_back(9, 4, 0.3622398593695834);
		circles.emplace_back(9, 5, 0.630544324661605);
		circles.emplace_back(9, 6, 0.5326288474956528);
		circles.emplace_back(9, 7, 0.5801853729179128);
		circles.emplace_back(9, 8, 0.2560749571071937);
		circles.emplace_back(9, 10, 0.6478271870641038);
		circles.emplace_back(10, 0, 0.7022138476604596);
		circles.emplace_back(10, 1, 0.3357950217789039);
		circles.emplace_back(10, 2, 0.4781380248488858);
		circles.emplace_back(10, 3, 0.3039772935910151);
		circles.emplace_back(10, 4, 0.2580801444360986);
		circles.emplace_back(10, 5, 0.3467333109816536);
		circles.emplace_back(10, 6, 0.3057202174561098);
		circles.emplace_back(10, 7, 0.5698345738230273);
		circles.emplace_back(10, 8, 0.5687309745931998);
		circles.emplace_back(10, 9, 0.226448431215249);
		circles.emplace_back(10, 10, 0.2452928350539878);
	}
	result_expected = 14.4160590052208;
	timer.reset();
	result_actual = algorithm(a59, b59, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #59: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a60(1, 1);
	Point b60(9, 9);
	{
		circles.emplace_back(0, 0, 0.3342588242841885);
		circles.emplace_back(0, 1, 0.8502396127441898);
		circles.emplace_back(0, 2, 0.4979672780027613);
		circles.emplace_back(0, 3, 0.5317382800625637);
		circles.emplace_back(0, 4, 0.3401282435981557);
		circles.emplace_back(0, 5, 0.4954607971245423);
		circles.emplace_back(0, 6, 0.2360463306074962);
		circles.emplace_back(0, 7, 0.7695732017280533);
		circles.emplace_back(0, 8, 0.4927989051444456);
		circles.emplace_back(0, 9, 0.4780468428740278);
		circles.emplace_back(0, 10, 0.2458459684392437);
		circles.emplace_back(1, 0, 0.3692888281540945);
		circles.emplace_back(1, 2, 0.5066501672146841);
		circles.emplace_back(1, 3, 0.2593934428179637);
		circles.emplace_back(1, 4, 0.5187532249605283);
		circles.emplace_back(1, 5, 0.1819334858329966);
		circles.emplace_back(1, 6, 0.2053410206688568);
		circles.emplace_back(1, 7, 0.5766401557484642);
		circles.emplace_back(1, 8, 0.3559779790928587);
		circles.emplace_back(1, 9, 0.1850623066769913);
		circles.emplace_back(1, 10, 0.4414023740915581);
		circles.emplace_back(2, 0, 0.4398505822056905);
		circles.emplace_back(2, 1, 0.4005475841229781);
		circles.emplace_back(2, 2, 0.5231791225494816);
		circles.emplace_back(2, 3, 0.3507902764482423);
		circles.emplace_back(2, 4, 0.5164972277591005);
		circles.emplace_back(2, 5, 0.5683249341091141);
		circles.emplace_back(2, 6, 0.4557955472962931);
		circles.emplace_back(2, 7, 0.6080250772414729);
		circles.emplace_back(2, 8, 0.6313760537886992);
		circles.emplace_back(2, 9, 0.6186749677872285);
		circles.emplace_back(2, 10, 0.4162322462769225);
		circles.emplace_back(3, 0, 0.2975415241671726);
		circles.emplace_back(3, 1, 0.2600757157662884);
		circles.emplace_back(3, 2, 0.3554046099772677);
		circles.emplace_back(3, 3, 0.234287393395789);
		circles.emplace_back(3, 4, 0.3668747982708737);
		circles.emplace_back(3, 5, 0.2441264890367165);
		circles.emplace_back(3, 6, 0.4986011504894122);
		circles.emplace_back(3, 7, 0.5258973156334832);
		circles.emplace_back(3, 8, 0.3773074866039678);
		circles.emplace_back(3, 9, 0.5059538820991293);
		circles.emplace_back(3, 10, 0.3179940605303272);
		circles.emplace_back(4, 0, 0.602914325078018);
		circles.emplace_back(4, 1, 0.6176024923799559);
		circles.emplace_back(4, 2, 0.6917619373882189);
		circles.emplace_back(4, 3, 0.5684652466094121);
		circles.emplace_back(4, 4, 0.5061267384560778);
		circles.emplace_back(4, 5, 0.1964468826306984);
		circles.emplace_back(4, 6, 0.6204712195554748);
		circles.emplace_back(4, 7, 0.6183327419450506);
		circles.emplace_back(4, 8, 0.2146460841642693);
		circles.emplace_back(4, 9, 0.4792316733626649);
		circles.emplace_back(4, 10, 0.566836491250433);
		circles.emplace_back(5, 0, 0.111032835370861);
		circles.emplace_back(5, 1, 0.6347864968003705);
		circles.emplace_back(5, 2, 0.2847925522131845);
		circles.emplace_back(5, 3, 0.6568690764019266);
		circles.emplace_back(5, 4, 0.3508256377419457);
		circles.emplace_back(5, 5, 0.6215612991945818);
		circles.emplace_back(5, 6, 0.3077365386066958);
		circles.emplace_back(5, 7, 0.3036889109993353);
		circles.emplace_back(5, 8, 0.1531490858411416);
		circles.emplace_back(5, 9, 0.6359217719407751);
		circles.emplace_back(5, 10, 0.4819795814109966);
		circles.emplace_back(6, 0, 0.2619312813738361);
		circles.emplace_back(6, 1, 0.2502463837852701);
		circles.emplace_back(6, 2, 0.3908631104277447);
		circles.emplace_back(6, 3, 0.2511200940934941);
		circles.emplace_back(6, 4, 0.4288332499796524);
		circles.emplace_back(6, 5, 0.4926918819313869);
		circles.emplace_back(6, 6, 0.489522569370456);
		circles.emplace_back(6, 7, 0.4612734273774549);
		circles.emplace_back(6, 8, 0.4701247686753049);
		circles.emplace_back(6, 9, 0.3374403932830319);
		circles.emplace_back(6, 10, 0.5083947948412969);
		circles.emplace_back(7, 0, 0.641992279398255);
		circles.emplace_back(7, 1, 0.5988494795048609);
		circles.emplace_back(7, 2, 0.6630249473964795);
		circles.emplace_back(7, 3, 0.228789343801327);
		circles.emplace_back(7, 4, 0.5908980433596298);
		circles.emplace_back(7, 5, 0.2852402029791847);
		circles.emplace_back(7, 6, 0.3025279817869886);
		circles.emplace_back(7, 7, 0.06965539113152772);
		circles.emplace_back(7, 8, 0.6276480926899239);
		circles.emplace_back(7, 9, 0.3257741138571873);
		circles.emplace_back(7, 10, 0.3349509708350524);
		circles.emplace_back(8, 0, 0.5248986241640523);
		circles.emplace_back(8, 1, 0.4328640036983415);
		circles.emplace_back(8, 2, 0.6495326044270768);
		circles.emplace_back(8, 3, 0.5256074921926484);
		circles.emplace_back(8, 4, 0.558315324713476);
		circles.emplace_back(8, 5, 0.7376457157311961);
		circles.emplace_back(8, 6, 0.4899908352876082);
		circles.emplace_back(8, 7, 0.3561647306894883);
		circles.emplace_back(8, 8, 0.7592686386080458);
		circles.emplace_back(8, 9, 0.5792966288281605);
		circles.emplace_back(8, 10, 0.5003619736293331);
		circles.emplace_back(9, 0, 0.4349584197392687);
		circles.emplace_back(9, 1, 0.4122320327209308);
		circles.emplace_back(9, 2, 0.3888846388785168);
		circles.emplace_back(9, 3, 0.5406211190158501);
		circles.emplace_back(9, 4, 0.5282062202459201);
		circles.emplace_back(9, 5, 0.5833249395014718);
		circles.emplace_back(9, 6, 0.6262641102774068);
		circles.emplace_back(9, 7, 0.5143339166650548);
		circles.emplace_back(9, 8, 0.5027445370098576);
		circles.emplace_back(9, 10, 0.2769655890064314);
		circles.emplace_back(10, 0, 0.5281837860820815);
		circles.emplace_back(10, 1, 0.3834148582303896);
		circles.emplace_back(10, 2, 0.4209137726342305);
		circles.emplace_back(10, 3, 0.4657660284312442);
		circles.emplace_back(10, 4, 0.1851056356681511);
		circles.emplace_back(10, 5, 0.4389402700820937);
		circles.emplace_back(10, 6, 0.6782170189311728);
		circles.emplace_back(10, 7, 0.6467943291412667);
		circles.emplace_back(10, 8, 0.6123596398858353);
		circles.emplace_back(10, 9, 0.6561409890884533);
		circles.emplace_back(10, 10, 0.5243771858280525);
	}
	result_expected = 14.26744422635388;
	timer.reset();
	result_actual = algorithm(a60, b60, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #60: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a61(1, 1);
	Point b61(9, 9);
	{
		circles.emplace_back(0, 0, 0.627328981203027);
		circles.emplace_back(0, 1, 0.5312595137162134);
		circles.emplace_back(0, 2, 0.5116997258970514);
		circles.emplace_back(0, 3, 0.3584175677737221);
		circles.emplace_back(0, 4, 0.2932304754154756);
		circles.emplace_back(0, 5, 0.4258043664274737);
		circles.emplace_back(0, 6, 0.1914781157160178);
		circles.emplace_back(0, 7, 0.4383908476447687);
		circles.emplace_back(0, 8, 0.4630550728412345);
		circles.emplace_back(0, 9, 0.2905912992311642);
		circles.emplace_back(0, 10, 0.3667984565952793);
		circles.emplace_back(1, 0, 0.4963815381517633);
		circles.emplace_back(1, 2, 0.5810357618378476);
		circles.emplace_back(1, 3, 0.7355639404384419);
		circles.emplace_back(1, 4, 0.5674051352078094);
		circles.emplace_back(1, 5, 0.6994068607455119);
		circles.emplace_back(1, 6, 0.2520554025890305);
		circles.emplace_back(1, 7, 0.4632219181163236);
		circles.emplace_back(1, 8, 0.529230740130879);
		circles.emplace_back(1, 9, 0.6468410620233044);
		circles.emplace_back(1, 10, 0.3717370591359213);
		circles.emplace_back(2, 0, 0.08391627024393529);
		circles.emplace_back(2, 1, 0.3450918626273051);
		circles.emplace_back(2, 2, 0.4449881676351651);
		circles.emplace_back(2, 3, 0.0547765189083293);
		circles.emplace_back(2, 4, 0.4848557923687622);
		circles.emplace_back(2, 5, 0.496439584926702);
		circles.emplace_back(2, 6, 0.249428173690103);
		circles.emplace_back(2, 7, 0.414641999755986);
		circles.emplace_back(2, 8, 0.6184493227628991);
		circles.emplace_back(2, 9, 0.2942896560067311);
		circles.emplace_back(2, 10, 0.5157616756623611);
		circles.emplace_back(3, 0, 0.2977660444797948);
		circles.emplace_back(3, 1, 0.3256089650793001);
		circles.emplace_back(3, 2, 0.3074573548743501);
		circles.emplace_back(3, 3, 0.5493779347976669);
		circles.emplace_back(3, 4, 0.4253546028630808);
		circles.emplace_back(3, 5, 0.4596392485080287);
		circles.emplace_back(3, 6, 0.4062220413470641);
		circles.emplace_back(3, 7, 0.5948713820194825);
		circles.emplace_back(3, 8, 0.4459383012028411);
		circles.emplace_back(3, 9, 0.5263372254325077);
		circles.emplace_back(3, 10, 0.1995463943341747);
		circles.emplace_back(4, 0, 0.5557315593352541);
		circles.emplace_back(4, 1, 0.5517908993409947);
		circles.emplace_back(4, 2, 0.5059285065857694);
		circles.emplace_back(4, 3, 0.6939753376180305);
		circles.emplace_back(4, 4, 0.5849314987426624);
		circles.emplace_back(4, 5, 0.2623399351956323);
		circles.emplace_back(4, 6, 0.4724642337067053);
		circles.emplace_back(4, 7, 0.1523396531352773);
		circles.emplace_back(4, 8, 0.5370395386358723);
		circles.emplace_back(4, 9, 0.3276945567922667);
		circles.emplace_back(4, 10, 0.4763039896963164);
		circles.emplace_back(5, 0, 0.3803892817581072);
		circles.emplace_back(5, 1, 0.5224795777117833);
		circles.emplace_back(5, 2, 0.6554155417950823);
		circles.emplace_back(5, 3, 0.3053096462739631);
		circles.emplace_back(5, 4, 0.5194813115755096);
		circles.emplace_back(5, 5, 0.4545647663762793);
		circles.emplace_back(5, 6, 0.2136525045381859);
		circles.emplace_back(5, 7, 0.3903751491336152);
		circles.emplace_back(5, 8, 0.2734476536745206);
		circles.emplace_back(5, 9, 0.5299296356504782);
		circles.emplace_back(5, 10, 0.8137732905568554);
		circles.emplace_back(6, 0, 0.4709172406001016);
		circles.emplace_back(6, 1, 0.4477674054214731);
		circles.emplace_back(6, 2, 0.5329856635769828);
		circles.emplace_back(6, 3, 0.3256105586187914);
		circles.emplace_back(6, 4, 0.285952119785361);
		circles.emplace_back(6, 5, 0.5291689012432471);
		circles.emplace_back(6, 6, 0.50502527912613);
		circles.emplace_back(6, 7, 0.3284505502553657);
		circles.emplace_back(6, 8, 0.1063830402446911);
		circles.emplace_back(6, 9, 0.6837864509085193);
		circles.emplace_back(6, 10, 0.368599303602241);
		circles.emplace_back(7, 0, 0.5508890467928722);
		circles.emplace_back(7, 1, 0.2741238451329991);
		circles.emplace_back(7, 2, 0.7019967653090134);
		circles.emplace_back(7, 3, 0.4477928295498714);
		circles.emplace_back(7, 4, 0.6026795138837769);
		circles.emplace_back(7, 5, 0.5636834398610517);
		circles.emplace_back(7, 6, 0.5680600697407499);
		circles.emplace_back(7, 7, 0.4750245371600613);
		circles.emplace_back(7, 8, 0.5516984335379674);
		circles.emplace_back(7, 9, 0.3318362022517249);
		circles.emplace_back(7, 10, 0.5826909046852961);
		circles.emplace_back(8, 0, 0.5249944481765851);
		circles.emplace_back(8, 1, 0.4491528236540034);
		circles.emplace_back(8, 2, 0.5710033301962539);
		circles.emplace_back(8, 3, 0.6166836140910164);
		circles.emplace_back(8, 4, 0.5664051173022017);
		circles.emplace_back(8, 5, 0.2561549450503662);
		circles.emplace_back(8, 6, 0.4319701268104836);
		circles.emplace_back(8, 7, 0.3237175211543217);
		circles.emplace_back(8, 8, 0.2720812611049041);
		circles.emplace_back(8, 9, 0.5747891959967092);
		circles.emplace_back(8, 10, 0.431564223091118);
		circles.emplace_back(9, 0, 0.4904667916009202);
		circles.emplace_back(9, 1, 0.27811282442417);
		circles.emplace_back(9, 2, 0.5367961942451075);
		circles.emplace_back(9, 3, 0.4109197380719706);
		circles.emplace_back(9, 4, 0.4521399844670668);
		circles.emplace_back(9, 5, 0.5326464842772111);
		circles.emplace_back(9, 6, 0.4529990465613082);
		circles.emplace_back(9, 7, 0.5599523764802142);
		circles.emplace_back(9, 8, 0.7515742903808131);
		circles.emplace_back(9, 10, 0.5249505912652239);
		circles.emplace_back(10, 0, 0.4765968057559803);
		circles.emplace_back(10, 1, 0.4736704638926312);
		circles.emplace_back(10, 2, 0.5700094573432579);
		circles.emplace_back(10, 3, 0.6353785484796389);
		circles.emplace_back(10, 4, 0.4834501152159646);
		circles.emplace_back(10, 5, 0.655946919391863);
		circles.emplace_back(10, 6, 0.6076664040097967);
		circles.emplace_back(10, 7, 0.3968556279083714);
		circles.emplace_back(10, 8, 0.8224840409355237);
		circles.emplace_back(10, 9, 0.2363771657226607);
		circles.emplace_back(10, 10, 0.3422555204713717);
	}
	result_expected = 12.48615110926782;
	timer.reset();
	result_actual = algorithm(a61, b61, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #61: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a62(1, 1);
	Point b62(9, 9);
	{
		circles.emplace_back(0, 0, 0.4085142243420705);
		circles.emplace_back(0, 1, 0.4393330910475924);
		circles.emplace_back(0, 2, 0.4158479769481346);
		circles.emplace_back(0, 3, 0.3435396565357223);
		circles.emplace_back(0, 4, 0.6921025467803702);
		circles.emplace_back(0, 5, 0.426353422855027);
		circles.emplace_back(0, 6, 0.5064422636060044);
		circles.emplace_back(0, 7, 0.3720767975086346);
		circles.emplace_back(0, 8, 0.4317917473381385);
		circles.emplace_back(0, 9, 0.2021272373618558);
		circles.emplace_back(0, 10, 0.5813047953648492);
		circles.emplace_back(1, 0, 0.6402674274751916);
		circles.emplace_back(1, 2, 0.2880064876517281);
		circles.emplace_back(1, 3, 0.373584361304529);
		circles.emplace_back(1, 4, 0.6000938611803576);
		circles.emplace_back(1, 5, 0.5638315800810233);
		circles.emplace_back(1, 6, 0.2259039427852258);
		circles.emplace_back(1, 7, 0.3838660166831687);
		circles.emplace_back(1, 8, 0.4256438669515774);
		circles.emplace_back(1, 9, 0.2818405768135562);
		circles.emplace_back(1, 10, 0.3491262426367029);
		circles.emplace_back(2, 0, 0.1990557777928188);
		circles.emplace_back(2, 1, 0.4974638706771657);
		circles.emplace_back(2, 2, 0.4734284527832642);
		circles.emplace_back(2, 3, 0.3794513508444652);
		circles.emplace_back(2, 4, 0.7369027157546952);
		circles.emplace_back(2, 5, 0.3776970551116392);
		circles.emplace_back(2, 6, 0.6493080700049176);
		circles.emplace_back(2, 7, 0.4729673811933026);
		circles.emplace_back(2, 8, 0.5906617305474355);
		circles.emplace_back(2, 9, 0.3351661379216239);
		circles.emplace_back(2, 10, 0.146216918178834);
		circles.emplace_back(3, 0, 0.8133953515207395);
		circles.emplace_back(3, 1, 0.5511760705383494);
		circles.emplace_back(3, 2, 0.4831297193421051);
		circles.emplace_back(3, 3, 0.5024176029721275);
		circles.emplace_back(3, 4, 0.5731853751232847);
		circles.emplace_back(3, 5, 0.5803270395146682);
		circles.emplace_back(3, 6, 0.5363745673326775);
		circles.emplace_back(3, 7, 0.5423780217999592);
		circles.emplace_back(3, 8, 0.2830112896626815);
		circles.emplace_back(3, 9, 0.4389758912147954);
		circles.emplace_back(3, 10, 0.4032688402337953);
		circles.emplace_back(4, 0, 0.5487562271067873);
		circles.emplace_back(4, 1, 0.4002887235721573);
		circles.emplace_back(4, 2, 0.622522911359556);
		circles.emplace_back(4, 3, 0.7784012469230219);
		circles.emplace_back(4, 4, 0.5498149771476164);
		circles.emplace_back(4, 5, 0.4173415999626741);
		circles.emplace_back(4, 6, 0.4072086871834472);
		circles.emplace_back(4, 7, 0.3514311444712803);
		circles.emplace_back(4, 8, 0.4003909742692485);
		circles.emplace_back(4, 9, 0.2998420780291781);
		circles.emplace_back(4, 10, 0.1602825644658878);
		circles.emplace_back(5, 0, 0.4977745732991025);
		circles.emplace_back(5, 1, 0.4845437906915322);
		circles.emplace_back(5, 2, 0.4961489319568499);
		circles.emplace_back(5, 3, 0.5171632920624688);
		circles.emplace_back(5, 4, 0.5667512298328802);
		circles.emplace_back(5, 5, 0.5180094817886128);
		circles.emplace_back(5, 6, 0.5081693673273548);
		circles.emplace_back(5, 7, 0.4787168539362028);
		circles.emplace_back(5, 8, 0.3328173766611144);
		circles.emplace_back(5, 9, 0.378583886870183);
		circles.emplace_back(5, 10, 0.364369275025092);
		circles.emplace_back(6, 0, 0.8317764886887744);
		circles.emplace_back(6, 1, 0.5255096901906654);
		circles.emplace_back(6, 2, 0.4425606174627319);
		circles.emplace_back(6, 3, 0.4855569226434454);
		circles.emplace_back(6, 4, 0.54602989659179);
		circles.emplace_back(6, 5, 0.303725045803003);
		circles.emplace_back(6, 6, 0.5553487330907956);
		circles.emplace_back(6, 7, 0.3840650833910331);
		circles.emplace_back(6, 8, 0.350398634118028);
		circles.emplace_back(6, 9, 0.5899612405104563);
		circles.emplace_back(6, 10, 0.514395104558207);
		circles.emplace_back(7, 0, 0.3869566024979577);
		circles.emplace_back(7, 1, 0.2420346959726885);
		circles.emplace_back(7, 2, 0.4301436531124637);
		circles.emplace_back(7, 3, 0.5925364647293463);
		circles.emplace_back(7, 4, 0.223878401122056);
		circles.emplace_back(7, 5, 0.6310592846246436);
		circles.emplace_back(7, 6, 0.694662841851823);
		circles.emplace_back(7, 7, 0.47990614681039);
		circles.emplace_back(7, 8, 0.4701889177551493);
		circles.emplace_back(7, 9, 0.4741687673376873);
		circles.emplace_back(7, 10, 0.4862480795709416);
		circles.emplace_back(8, 0, 0.5725205101305618);
		circles.emplace_back(8, 1, 0.6859839871292933);
		circles.emplace_back(8, 2, 0.3002328207017854);
		circles.emplace_back(8, 3, 0.570301826368086);
		circles.emplace_back(8, 4, 0.3856700534233823);
		circles.emplace_back(8, 5, 0.2416461566230282);
		circles.emplace_back(8, 6, 0.4810097626643255);
		circles.emplace_back(8, 7, 0.3933201397536322);
		circles.emplace_back(8, 8, 0.7202402156079187);
		circles.emplace_back(8, 9, 0.4705424401676282);
		circles.emplace_back(8, 10, 0.2501040720613673);
		circles.emplace_back(9, 0, 0.6050240223063156);
		circles.emplace_back(9, 1, 0.4600868640700355);
		circles.emplace_back(9, 2, 0.6394955096533522);
		circles.emplace_back(9, 3, 0.4232910956488922);
		circles.emplace_back(9, 4, 0.3498267068294808);
		circles.emplace_back(9, 5, 0.6285914704436436);
		circles.emplace_back(9, 6, 0.1776533238356933);
		circles.emplace_back(9, 7, 0.3233339426340535);
		circles.emplace_back(9, 8, 0.643261879007332);
		circles.emplace_back(9, 10, 0.2825209738919511);
		circles.emplace_back(10, 0, 0.5543821947416291);
		circles.emplace_back(10, 1, 0.2624175667064264);
		circles.emplace_back(10, 2, 0.6989978375611826);
		circles.emplace_back(10, 3, 0.4713173318887129);
		circles.emplace_back(10, 4, 0.3468082915758714);
		circles.emplace_back(10, 5, 0.385325035569258);
		circles.emplace_back(10, 6, 0.3220625919057056);
		circles.emplace_back(10, 7, 0.2399417584994808);
		circles.emplace_back(10, 8, 0.5876325821271166);
		circles.emplace_back(10, 9, 0.3264809879707172);
		circles.emplace_back(10, 10, 0.3339048973051831);
	}
	result_expected = 17.23251095722748;
	timer.reset();
	result_actual = algorithm(a62, b62, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #62: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a63(1, 1);
	Point b63(9, 9);
	{
		circles.emplace_back(0, 0, 0.3033986501628533);
		circles.emplace_back(0, 1, 0.4338442116742954);
		circles.emplace_back(0, 2, 0.3839872782351449);
		circles.emplace_back(0, 3, 0.3449162275297567);
		circles.emplace_back(0, 4, 0.471064198971726);
		circles.emplace_back(0, 5, 0.5469573193928227);
		circles.emplace_back(0, 6, 0.2637758082943037);
		circles.emplace_back(0, 7, 0.5400386850116774);
		circles.emplace_back(0, 8, 0.4489446934545412);
		circles.emplace_back(0, 9, 0.225396292260848);
		circles.emplace_back(0, 10, 0.2970035472186282);
		circles.emplace_back(1, 0, 0.4930838485015556);
		circles.emplace_back(1, 2, 0.5979895068565383);
		circles.emplace_back(1, 3, 0.5796544564655051);
		circles.emplace_back(1, 4, 0.5838147382484749);
		circles.emplace_back(1, 5, 0.475387558224611);
		circles.emplace_back(1, 6, 0.2765837729210034);
		circles.emplace_back(1, 7, 0.3908512063091621);
		circles.emplace_back(1, 8, 0.266595293325372);
		circles.emplace_back(1, 9, 0.3744256385369226);
		circles.emplace_back(1, 10, 0.5453457491705194);
		circles.emplace_back(2, 0, 0.2433125706156716);
		circles.emplace_back(2, 1, 0.4858443751232698);
		circles.emplace_back(2, 2, 0.488015558081679);
		circles.emplace_back(2, 3, 0.7623538676882162);
		circles.emplace_back(2, 4, 0.6718002166366205);
		circles.emplace_back(2, 5, 0.3217881665797904);
		circles.emplace_back(2, 6, 0.509729027445428);
		circles.emplace_back(2, 7, 0.3469284733990207);
		circles.emplace_back(2, 8, 0.31401389145758);
		circles.emplace_back(2, 9, 0.6748608279274776);
		circles.emplace_back(2, 10, 0.3711405343143269);
		circles.emplace_back(3, 0, 0.3400932498509064);
		circles.emplace_back(3, 1, 0.2089923009043559);
		circles.emplace_back(3, 2, 0.5881776412250473);
		circles.emplace_back(3, 3, 0.4565368161303922);
		circles.emplace_back(3, 4, 0.7398413324961438);
		circles.emplace_back(3, 5, 0.4320374259492382);
		circles.emplace_back(3, 6, 0.6651253423886373);
		circles.emplace_back(3, 7, 0.35571227024775);
		circles.emplace_back(3, 8, 0.2393311094725504);
		circles.emplace_back(3, 9, 0.3067872766172513);
		circles.emplace_back(3, 10, 0.4851946407230571);
		circles.emplace_back(4, 0, 0.5704753015888855);
		circles.emplace_back(4, 1, 0.3461367098847404);
		circles.emplace_back(4, 2, 0.385062083392404);
		circles.emplace_back(4, 3, 0.171179925953038);
		circles.emplace_back(4, 4, 0.6404906078008935);
		circles.emplace_back(4, 5, 0.4106781795853749);
		circles.emplace_back(4, 6, 0.3351089261239394);
		circles.emplace_back(4, 7, 0.5108711627544835);
		circles.emplace_back(4, 8, 0.504082401911728);
		circles.emplace_back(4, 9, 0.5419563444564118);
		circles.emplace_back(4, 10, 0.2288698004325852);
		circles.emplace_back(5, 0, 0.08636297278571874);
		circles.emplace_back(5, 1, 0.3596235724864528);
		circles.emplace_back(5, 2, 0.4387173611903563);
		circles.emplace_back(5, 3, 0.2688981216168031);
		circles.emplace_back(5, 4, 0.6141059042187408);
		circles.emplace_back(5, 5, 0.4431357812834903);
		circles.emplace_back(5, 6, 0.6141719555715098);
		circles.emplace_back(5, 7, 0.4455486660590395);
		circles.emplace_back(5, 8, 0.3488248887704685);
		circles.emplace_back(5, 9, 0.4877254984108731);
		circles.emplace_back(5, 10, 0.3423943482572213);
		circles.emplace_back(6, 0, 0.2650659501319751);
		circles.emplace_back(6, 1, 0.2544298862339929);
		circles.emplace_back(6, 2, 0.2804809749824926);
		circles.emplace_back(6, 3, 0.304525868059136);
		circles.emplace_back(6, 4, 0.3391960466047749);
		circles.emplace_back(6, 5, 0.6950437165098264);
		circles.emplace_back(6, 6, 0.4824551532743498);
		circles.emplace_back(6, 7, 0.3629082527244463);
		circles.emplace_back(6, 8, 0.5769468385493383);
		circles.emplace_back(6, 9, 0.7492720791371539);
		circles.emplace_back(6, 10, 0.3273595143808052);
		circles.emplace_back(7, 0, 0.4412716372171417);
		circles.emplace_back(7, 1, 0.669121710746549);
		circles.emplace_back(7, 2, 0.4008407603250816);
		circles.emplace_back(7, 3, 0.6645938633708283);
		circles.emplace_back(7, 4, 0.3391022294992581);
		circles.emplace_back(7, 5, 0.3062516785925254);
		circles.emplace_back(7, 6, 0.6087250274838879);
		circles.emplace_back(7, 7, 0.5622370519442483);
		circles.emplace_back(7, 8, 0.4583146738121286);
		circles.emplace_back(7, 9, 0.6205509545048699);
		circles.emplace_back(7, 10, 0.609896211256273);
		circles.emplace_back(8, 0, 0.4356236385880038);
		circles.emplace_back(8, 1, 0.4703541014576331);
		circles.emplace_back(8, 2, 0.6925209518289194);
		circles.emplace_back(8, 3, 0.657810475048609);
		circles.emplace_back(8, 4, 0.5171314862323925);
		circles.emplace_back(8, 5, 0.3018528690794482);
		circles.emplace_back(8, 6, 0.5128277262439951);
		circles.emplace_back(8, 7, 0.5497647720621899);
		circles.emplace_back(8, 8, 0.4328052974073216);
		circles.emplace_back(8, 9, 0.4669669844442979);
		circles.emplace_back(8, 10, 0.6400778546696528);
		circles.emplace_back(9, 0, 0.3462449898244813);
		circles.emplace_back(9, 1, 0.4014410868985578);
		circles.emplace_back(9, 2, 0.4245172197232023);
		circles.emplace_back(9, 3, 0.3451177516719326);
		circles.emplace_back(9, 4, 0.535391282220371);
		circles.emplace_back(9, 5, 0.5217565919039771);
		circles.emplace_back(9, 6, 0.388059912272729);
		circles.emplace_back(9, 7, 0.3824814233696088);
		circles.emplace_back(9, 8, 0.5457055890234187);
		circles.emplace_back(9, 10, 0.4632726196898147);
		circles.emplace_back(10, 0, 0.4670124529162422);
		circles.emplace_back(10, 1, 0.4796116588404402);
		circles.emplace_back(10, 2, 0.3601263429271057);
		circles.emplace_back(10, 3, 0.2265303327469155);
		circles.emplace_back(10, 4, 0.466958461725153);
		circles.emplace_back(10, 5, 0.38447965902742);
		circles.emplace_back(10, 6, 0.5345953640760853);
		circles.emplace_back(10, 7, 0.3882694714469835);
		circles.emplace_back(10, 8, 0.2272576513001695);
		circles.emplace_back(10, 9, 0.2622281031450256);
		circles.emplace_back(10, 10, 0.2742419420974329);
	}
	result_expected = 12.68562333073604;
	timer.reset();
	result_actual = algorithm(a63, b63, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #63: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	*/

	Point a64(1, 1);
	Point b64(9, 9);
	{
		circles.emplace_back(0, 0, 0.09719251419883221);
		circles.emplace_back(0, 1, 0.2240853775525466);
		circles.emplace_back(0, 2, 0.5814626525854691);
		circles.emplace_back(0, 3, 0.5703091056318953);
		circles.emplace_back(0, 4, 0.5359397751046344);
		circles.emplace_back(0, 5, 0.5170268779853359);
		circles.emplace_back(0, 6, 0.5808168923249468);
		circles.emplace_back(0, 7, 0.6509470793651416);
		circles.emplace_back(0, 8, 0.4149004391161725);
		circles.emplace_back(0, 9, 0.4673511974746361);
		circles.emplace_back(0, 10, 0.5564157098298892);
		circles.emplace_back(1, 0, 0.4489989285590127);
		circles.emplace_back(1, 2, 0.5134845346910879);
		circles.emplace_back(1, 3, 0.6060898015508428);
		circles.emplace_back(1, 4, 0.1608621114632115);
		circles.emplace_back(1, 5, 0.6399033910827711);
		circles.emplace_back(1, 6, 0.5344808439491316);
		circles.emplace_back(1, 7, 0.3800448771798983);
		circles.emplace_back(1, 8, 0.354372476390563);
		circles.emplace_back(1, 9, 0.3528398969443515);
		circles.emplace_back(1, 10, 0.7871257503284141);
		circles.emplace_back(2, 0, 0.6538523210445418);
		circles.emplace_back(2, 1, 0.2986852479865774);
		circles.emplace_back(2, 2, 0.3082407753216103);
		circles.emplace_back(2, 3, 0.364508023741655);
		circles.emplace_back(2, 4, 0.4962244153255597);
		circles.emplace_back(2, 5, 0.4343680627411231);
		circles.emplace_back(2, 6, 0.3847956490935758);
		circles.emplace_back(2, 7, 0.4309345432324335);
		circles.emplace_back(2, 8, 0.4284971909830347);
		circles.emplace_back(2, 9, 0.3321483166655526);
		circles.emplace_back(2, 10, 0.5690730168716982);
		circles.emplace_back(3, 0, 0.684881957131438);
		circles.emplace_back(3, 1, 0.4636074785375968);
		circles.emplace_back(3, 2, 0.4588921691989526);
		circles.emplace_back(3, 3, 0.5908840225310996);
		circles.emplace_back(3, 4, 0.3131592807127163);
		circles.emplace_back(3, 5, 0.6136246463516727);
		circles.emplace_back(3, 6, 0.3488569846143946);
		circles.emplace_back(3, 7, 0.597513412241824);
		circles.emplace_back(3, 8, 0.5019064313499256);
		circles.emplace_back(3, 9, 0.5939620264107361);
		circles.emplace_back(3, 10, 0.2208422109251842);
		circles.emplace_back(4, 0, 0.5699426790000871);
		circles.emplace_back(4, 1, 0.3200537011725828);
		circles.emplace_back(4, 2, 0.1023930276045576);
		circles.emplace_back(4, 3, 0.3318636962911114);
		circles.emplace_back(4, 4, 0.5341903946595267);
		circles.emplace_back(4, 5, 0.4408671672223136);
		circles.emplace_back(4, 6, 0.6009969365084543);
		circles.emplace_back(4, 7, 0.6079764429247007);
		circles.emplace_back(4, 8, 0.4708947294624522);
		circles.emplace_back(4, 9, 0.5172050391091033);
		circles.emplace_back(4, 10, 0.3791594056645408);
		circles.emplace_back(5, 0, 0.2428707984974608);
		circles.emplace_back(5, 1, 0.4762631590710953);
		circles.emplace_back(5, 2, 0.1761099441675469);
		circles.emplace_back(5, 3, 0.625752629362978);
		circles.emplace_back(5, 4, 0.4048670850461349);
		circles.emplace_back(5, 5, 0.3775143590988591);
		circles.emplace_back(5, 6, 0.5483621501130983);
		circles.emplace_back(5, 7, 0.488620206923224);
		circles.emplace_back(5, 8, 0.4429336653789505);
		circles.emplace_back(5, 9, 0.555937287141569);
		circles.emplace_back(5, 10, 0.398618725198321);
		circles.emplace_back(6, 0, 0.3494916934752837);
		circles.emplace_back(6, 1, 0.3323534469818696);
		circles.emplace_back(6, 2, 0.4806924523087218);
		circles.emplace_back(6, 3, 0.2717636358691379);
		circles.emplace_back(6, 4, 0.5924518382409587);
		circles.emplace_back(6, 5, 0.3506638234248385);
		circles.emplace_back(6, 6, 0.6064803722547367);
		circles.emplace_back(6, 7, 0.3210937819210812);
		circles.emplace_back(6, 8, 0.6940895103150978);
		circles.emplace_back(6, 9, 0.5244950532680377);
		circles.emplace_back(6, 10, 0.5382022177102044);
		circles.emplace_back(7, 0, 0.4339659691555425);
		circles.emplace_back(7, 1, 0.6134513119468465);
		circles.emplace_back(7, 2, 0.4379320764681324);
		circles.emplace_back(7, 3, 0.3157376445131376);
		circles.emplace_back(7, 4, 0.6205298195360228);
		circles.emplace_back(7, 5, 0.3099248793208971);
		circles.emplace_back(7, 6, 0.743024768284522);
		circles.emplace_back(7, 7, 0.4219648131402209);
		circles.emplace_back(7, 8, 0.3811716188443824);
		circles.emplace_back(7, 9, 0.5671768708387389);
		circles.emplace_back(7, 10, 0.3630716306855902);
		circles.emplace_back(8, 0, 0.4671475957380608);
		circles.emplace_back(8, 1, 0.4182941018370911);
		circles.emplace_back(8, 2, 0.3512706428999081);
		circles.emplace_back(8, 3, 0.3293019212549552);
		circles.emplace_back(8, 4, 0.2528149706544354);
		circles.emplace_back(8, 5, 0.308057174901478);
		circles.emplace_back(8, 6, 0.4810886131832376);
		circles.emplace_back(8, 7, 0.1415812195977196);
		circles.emplace_back(8, 8, 0.4682576044695452);
		circles.emplace_back(8, 9, 0.2977045762119815);
		circles.emplace_back(8, 10, 0.7391843114281073);
		circles.emplace_back(9, 0, 0.2937654312467202);
		circles.emplace_back(9, 1, 0.722766621527262);
		circles.emplace_back(9, 2, 0.5441014733863995);
		circles.emplace_back(9, 3, 0.501189117715694);
		circles.emplace_back(9, 4, 0.7543282290687784);
		circles.emplace_back(9, 5, 0.2667395609663799);
		circles.emplace_back(9, 6, 0.2591079986421391);
		circles.emplace_back(9, 7, 0.5118986882502213);
		circles.emplace_back(9, 8, 0.6428869321709498);
		circles.emplace_back(9, 10, 0.3047785212518647);
		circles.emplace_back(10, 0, 0.2774137214524671);
		circles.emplace_back(10, 1, 0.2861640686402097);
		circles.emplace_back(10, 2, 0.2932518223067745);
		circles.emplace_back(10, 3, 0.6539054922061041);
		circles.emplace_back(10, 4, 0.7124580587027595);
		circles.emplace_back(10, 5, 0.4627124946797266);
		circles.emplace_back(10, 6, 0.4436238977825269);
		circles.emplace_back(10, 7, 0.4500198745401576);
		circles.emplace_back(10, 8, 0.5160616223467513);
		circles.emplace_back(10, 9, 0.3890228806296364);
		circles.emplace_back(10, 10, 0.3445660648634657);
	
	}
	result_expected = 13.79929264205633;
	timer.reset();
	result_actual = algorithm(a64, b64, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #64: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





	Point a65(1, 1);
	Point b65(9, 9);
	{
		circles.emplace_back(0, 0, 0.7557231868850067);
		circles.emplace_back(0, 1, 0.5073935045627876);
		circles.emplace_back(0, 2, 0.5653809949988499);
		circles.emplace_back(0, 3, 0.3253727666800841);
		circles.emplace_back(0, 4, 0.1726359603228047);
		circles.emplace_back(0, 5, 0.4868995004100725);
		circles.emplace_back(0, 6, 0.2262393238255754);
		circles.emplace_back(0, 7, 0.4094630496343598);
		circles.emplace_back(0, 8, 0.5113318204181269);
		circles.emplace_back(0, 9, 0.4008162679849193);
		circles.emplace_back(0, 10, 0.5870066214585676);
		circles.emplace_back(1, 0, 0.5194220673060045);
		circles.emplace_back(1, 2, 0.7220137567492202);
		circles.emplace_back(1, 3, 0.6718964260770007);
		circles.emplace_back(1, 4, 0.4343921488383785);
		circles.emplace_back(1, 5, 0.4623160218587145);
		circles.emplace_back(1, 6, 0.3390575799392536);
		circles.emplace_back(1, 7, 0.5619695893255994);
		circles.emplace_back(1, 8, 0.2884295992786065);
		circles.emplace_back(1, 9, 0.4359055429464206);
		circles.emplace_back(1, 10, 0.242547566187568);
		circles.emplace_back(2, 0, 0.4819643408758565);
		circles.emplace_back(2, 1, 0.3143057117471471);
		circles.emplace_back(2, 2, 0.5463825041195377);
		circles.emplace_back(2, 3, 0.389929289300926);
		circles.emplace_back(2, 4, 0.5150161425350234);
		circles.emplace_back(2, 5, 0.4121185716474429);
		circles.emplace_back(2, 6, 0.3782552767312154);
		circles.emplace_back(2, 7, 0.6209046402247622);
		circles.emplace_back(2, 8, 0.4682861824287101);
		circles.emplace_back(2, 9, 0.2626905990997329);
		circles.emplace_back(2, 10, 0.4070074213435873);
		circles.emplace_back(3, 0, 0.2886940340744331);
		circles.emplace_back(3, 1, 0.3191161601571366);
		circles.emplace_back(3, 2, 0.2575612247223034);
		circles.emplace_back(3, 3, 0.5951548166340217);
		circles.emplace_back(3, 4, 0.420790804666467);
		circles.emplace_back(3, 5, 0.6711440094513819);
		circles.emplace_back(3, 6, 0.4912842529127374);
		circles.emplace_back(3, 7, 0.662326225801371);
		circles.emplace_back(3, 8, 0.262332786549814);
		circles.emplace_back(3, 9, 0.2860055583296344);
		circles.emplace_back(3, 10, 0.5441549126291647);
		circles.emplace_back(4, 0, 0.3699923004722223);
		circles.emplace_back(4, 1, 0.3052160845370963);
		circles.emplace_back(4, 2, 0.506247126753442);
		circles.emplace_back(4, 3, 0.5334915956715122);
		circles.emplace_back(4, 4, 0.4114680221071467);
		circles.emplace_back(4, 5, 0.3560760307358578);
		circles.emplace_back(4, 6, 0.435074061783962);
		circles.emplace_back(4, 7, 0.1615972824627533);
		circles.emplace_back(4, 8, 0.4478135809069499);
		circles.emplace_back(4, 9, 0.5462603290798143);
		circles.emplace_back(4, 10, 0.4885602102382108);
		circles.emplace_back(5, 0, 0.4385256553301587);
		circles.emplace_back(5, 1, 0.580258692218922);
		circles.emplace_back(5, 2, 0.4369193873601034);
		circles.emplace_back(5, 3, 0.2859433288453146);
		circles.emplace_back(5, 4, 0.6077768992865458);
		circles.emplace_back(5, 5, 0.3997753504430875);
		circles.emplace_back(5, 6, 0.5223388367565348);
		circles.emplace_back(5, 7, 0.3936314319027588);
		circles.emplace_back(5, 8, 0.3530481903115287);
		circles.emplace_back(5, 9, 0.704424020438455);
		circles.emplace_back(5, 10, 0.38463923886884);
		circles.emplace_back(6, 0, 0.4885450764326378);
		circles.emplace_back(6, 1, 0.4141638711327687);
		circles.emplace_back(6, 2, 0.5250982664292678);
		circles.emplace_back(6, 3, 0.2029679802479222);
		circles.emplace_back(6, 4, 0.1564205848379061);
		circles.emplace_back(6, 5, 0.2903103145072237);
		circles.emplace_back(6, 6, 0.2502928184112534);
		circles.emplace_back(6, 7, 0.4703083544271067);
		circles.emplace_back(6, 8, 0.5906992050586268);
		circles.emplace_back(6, 9, 0.5587004740023985);
		circles.emplace_back(6, 10, 0.4905200760578736);
		circles.emplace_back(7, 0, 0.6210308314533904);
		circles.emplace_back(7, 1, 0.507627208228223);
		circles.emplace_back(7, 2, 0.686793122277595);
		circles.emplace_back(7, 3, 0.573000050126575);
		circles.emplace_back(7, 4, 0.7223115149186924);
		circles.emplace_back(7, 5, 0.4431919238297269);
		circles.emplace_back(7, 6, 0.4661917768651619);
		circles.emplace_back(7, 7, 0.4072487413650379);
		circles.emplace_back(7, 8, 0.6325427864911034);
		circles.emplace_back(7, 9, 0.64751871235203);
		circles.emplace_back(7, 10, 0.7463483134517446);
		circles.emplace_back(8, 0, 0.6121899569174275);
		circles.emplace_back(8, 1, 0.4798611379461363);
		circles.emplace_back(8, 2, 0.4423538754461333);
		circles.emplace_back(8, 3, 0.1961962666595355);
		circles.emplace_back(8, 4, 0.7454155642306431);
		circles.emplace_back(8, 5, 0.4639171906979754);
		circles.emplace_back(8, 6, 0.4572585035813972);
		circles.emplace_back(8, 7, 0.2718388183275238);
		circles.emplace_back(8, 8, 0.4252191824605688);
		circles.emplace_back(8, 9, 0.5340129028307273);
		circles.emplace_back(8, 10, 0.3101382612017914);
		circles.emplace_back(9, 0, 0.4184164732927456);
		circles.emplace_back(9, 1, 0.4860283113783225);
		circles.emplace_back(9, 2, 0.6467309636296704);
		circles.emplace_back(9, 3, 0.3477341093821451);
		circles.emplace_back(9, 4, 0.1842794226715341);
		circles.emplace_back(9, 5, 0.5578598977765068);
		circles.emplace_back(9, 6, 0.3561813756125048);
		circles.emplace_back(9, 7, 0.3116989659843966);
		circles.emplace_back(9, 8, 0.4755895946407691);
		circles.emplace_back(9, 10, 0.4104243393754586);
		circles.emplace_back(10, 0, 0.2399902240606025);
		circles.emplace_back(10, 1, 0.5458853033138439);
		circles.emplace_back(10, 2, 0.2294773927191272);
		circles.emplace_back(10, 3, 0.5525029262294993);
		circles.emplace_back(10, 4, 0.3141556340502575);
		circles.emplace_back(10, 5, 0.4104686832753942);
		circles.emplace_back(10, 6, 0.5338781215483323);
		circles.emplace_back(10, 7, 0.4272237196331843);
		circles.emplace_back(10, 8, 0.3398959149839356);
		circles.emplace_back(10, 9, 0.1185322300298139);
		circles.emplace_back(10, 10, 0.4721731001744047);
	}
	result_expected = 12.3813487017205;
	timer.reset();
	result_actual = algorithm(a65, b65, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #65: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a66(1, 1);
	Point b66(9, 9);
	{
		circles.emplace_back(0, 0, 0.193860868527554);
		circles.emplace_back(0, 1, 0.4756148926215246);
		circles.emplace_back(0, 2, 0.3607370401499793);
		circles.emplace_back(0, 3, 0.3207604628289119);
		circles.emplace_back(0, 4, 0.5367823634063825);
		circles.emplace_back(0, 5, 0.277109428611584);
		circles.emplace_back(0, 6, 0.5337035302771255);
		circles.emplace_back(0, 7, 0.5776806472102179);
		circles.emplace_back(0, 8, 0.4921712277224287);
		circles.emplace_back(0, 9, 0.4991441275225952);
		circles.emplace_back(0, 10, 0.4377287222770974);
		circles.emplace_back(1, 0, 0.4504215702647343);
		circles.emplace_back(1, 2, 0.6331451467936858);
		circles.emplace_back(1, 3, 0.6015182313742116);
		circles.emplace_back(1, 4, 0.5594644658965989);
		circles.emplace_back(1, 5, 0.4810284914681688);
		circles.emplace_back(1, 6, 0.5038995342096314);
		circles.emplace_back(1, 7, 0.6127497016685083);
		circles.emplace_back(1, 8, 0.1051815989194438);
		circles.emplace_back(1, 9, 0.3366435636067763);
		circles.emplace_back(1, 10, 0.3434990357374773);
		circles.emplace_back(2, 0, 0.2545014889212325);
		circles.emplace_back(2, 1, 0.8002450448228046);
		circles.emplace_back(2, 2, 0.3436000710586086);
		circles.emplace_back(2, 3, 0.4899424707284197);
		circles.emplace_back(2, 4, 0.679874989693053);
		circles.emplace_back(2, 5, 0.6204248479334638);
		circles.emplace_back(2, 6, 0.4931963555747643);
		circles.emplace_back(2, 7, 0.4051262110238895);
		circles.emplace_back(2, 8, 0.5286956911208108);
		circles.emplace_back(2, 9, 0.4706681460840627);
		circles.emplace_back(2, 10, 0.09727442956063896);
		circles.emplace_back(3, 0, 0.3113309973618015);
		circles.emplace_back(3, 1, 0.3529160029487684);
		circles.emplace_back(3, 2, 0.1769570807693526);
		circles.emplace_back(3, 3, 0.5217282768571749);
		circles.emplace_back(3, 4, 0.4798571932828053);
		circles.emplace_back(3, 5, 0.2152602770598605);
		circles.emplace_back(3, 6, 0.5068776448024437);
		circles.emplace_back(3, 7, 0.3760668410221115);
		circles.emplace_back(3, 8, 0.5624334765365347);
		circles.emplace_back(3, 9, 0.3142370145069435);
		circles.emplace_back(3, 10, 0.4845244674710557);
		circles.emplace_back(4, 0, 0.2871567011112347);
		circles.emplace_back(4, 1, 0.6060239679878577);
		circles.emplace_back(4, 2, 0.2386432600440457);
		circles.emplace_back(4, 3, 0.7153665371937677);
		circles.emplace_back(4, 4, 0.3352694349596277);
		circles.emplace_back(4, 5, 0.441658798023127);
		circles.emplace_back(4, 6, 0.4046861841576174);
		circles.emplace_back(4, 7, 0.4866988616762682);
		circles.emplace_back(4, 8, 0.3805586699629203);
		circles.emplace_back(4, 9, 0.2879131104564294);
		circles.emplace_back(4, 10, 0.6788468525977805);
		circles.emplace_back(5, 0, 0.2593050655676052);
		circles.emplace_back(5, 1, 0.1580918213585392);
		circles.emplace_back(5, 2, 0.4596595039358362);
		circles.emplace_back(5, 3, 0.3396111834095791);
		circles.emplace_back(5, 4, 0.6159559256164356);
		circles.emplace_back(5, 5, 0.3695615180069581);
		circles.emplace_back(5, 6, 0.6227189108496531);
		circles.emplace_back(5, 7, 0.3811930914642289);
		circles.emplace_back(5, 8, 0.5823688433272763);
		circles.emplace_back(5, 9, 0.4498017156729475);
		circles.emplace_back(5, 10, 0.3850349137326702);
		circles.emplace_back(6, 0, 0.6123748204903677);
		circles.emplace_back(6, 1, 0.7862532551167533);
		circles.emplace_back(6, 2, 0.5362334978068247);
		circles.emplace_back(6, 3, 0.4649964991724118);
		circles.emplace_back(6, 4, 0.353589462605305);
		circles.emplace_back(6, 5, 0.5700669799698517);
		circles.emplace_back(6, 6, 0.3193655638257041);
		circles.emplace_back(6, 7, 0.2275342492153868);
		circles.emplace_back(6, 8, 0.2853706653462723);
		circles.emplace_back(6, 9, 0.2231085045961663);
		circles.emplace_back(6, 10, 0.5024744048947468);
		circles.emplace_back(7, 0, 0.4286149702733382);
		circles.emplace_back(7, 1, 0.7512945262016728);
		circles.emplace_back(7, 2, 0.1485702060861513);
		circles.emplace_back(7, 3, 0.4485891672084108);
		circles.emplace_back(7, 4, 0.3587597595294937);
		circles.emplace_back(7, 5, 0.6685386746423319);
		circles.emplace_back(7, 6, 0.3311775120673701);
		circles.emplace_back(7, 7, 0.4429062027717009);
		circles.emplace_back(7, 8, 0.3262105088448152);
		circles.emplace_back(7, 9, 0.4491835416527465);
		circles.emplace_back(7, 10, 0.6210389983607456);
		circles.emplace_back(8, 0, 0.348758307681419);
		circles.emplace_back(8, 1, 0.4703698461642489);
		circles.emplace_back(8, 2, 0.4853808167623356);
		circles.emplace_back(8, 3, 0.39933242413681);
		circles.emplace_back(8, 4, 0.3852636479074135);
		circles.emplace_back(8, 5, 0.5461395144229755);
		circles.emplace_back(8, 6, 0.70151409257669);
		circles.emplace_back(8, 7, 0.5414517045719549);
		circles.emplace_back(8, 8, 0.6047793725738302);
		circles.emplace_back(8, 9, 0.06978218795266002);
		circles.emplace_back(8, 10, 0.5264766968088225);
		circles.emplace_back(9, 0, 0.5432398210046813);
		circles.emplace_back(9, 1, 0.2982849147403613);
		circles.emplace_back(9, 2, 0.7669317263877019);
		circles.emplace_back(9, 3, 0.5891917118104174);
		circles.emplace_back(9, 4, 0.6259326685918495);
		circles.emplace_back(9, 5, 0.2068199796834961);
		circles.emplace_back(9, 6, 0.5133768660714849);
		circles.emplace_back(9, 7, 0.6904991816030815);
		circles.emplace_back(9, 8, 0.4854388414649293);
		circles.emplace_back(9, 10, 0.6671022206777707);
		circles.emplace_back(10, 0, 0.5092433489626274);
		circles.emplace_back(10, 1, 0.4545355064095929);
		circles.emplace_back(10, 2, 0.3015803553862497);
		circles.emplace_back(10, 3, 0.3694496022770181);
		circles.emplace_back(10, 4, 0.4771994890412316);
		circles.emplace_back(10, 5, 0.2127300246851519);
		circles.emplace_back(10, 6, 0.1729193079052493);
		circles.emplace_back(10, 7, 0.5561324510956183);
		circles.emplace_back(10, 8, 0.6253101762151345);
		circles.emplace_back(10, 9, 0.4235437826486304);
		circles.emplace_back(10, 10, 0.5927954760147258);
	}
	result_expected = 14.18746350918706;
	timer.reset();
	result_actual = algorithm(a66, b66, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #66: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a67(1, 1);
	Point b67(9, 9);
	{
		circles.emplace_back(0, 0, 0.4382801940897479);
		circles.emplace_back(0, 1, 0.4651643177261576);
		circles.emplace_back(0, 2, 0.4810754913138225);
		circles.emplace_back(0, 3, 0.4321998513070867);
		circles.emplace_back(0, 4, 0.6594677843386307);
		circles.emplace_back(0, 5, 0.6259007170563563);
		circles.emplace_back(0, 6, 0.3156596710206941);
		circles.emplace_back(0, 7, 0.1451091126305983);
		circles.emplace_back(0, 8, 0.5841068143257871);
		circles.emplace_back(0, 9, 0.4547573903342709);
		circles.emplace_back(0, 10, 0.5395819834666327);
		circles.emplace_back(1, 0, 0.6619060362456366);
		circles.emplace_back(1, 2, 0.2387663167202845);
		circles.emplace_back(1, 3, 0.5447693202411755);
		circles.emplace_back(1, 4, 0.6410367512376979);
		circles.emplace_back(1, 5, 0.5865108434809372);
		circles.emplace_back(1, 6, 0.4845482526579872);
		circles.emplace_back(1, 7, 0.5802396474173293);
		circles.emplace_back(1, 8, 0.5794516648398712);
		circles.emplace_back(1, 9, 0.4628484858898446);
		circles.emplace_back(1, 10, 0.5486426875228062);
		circles.emplace_back(2, 0, 0.440609299368225);
		circles.emplace_back(2, 1, 0.485304677230306);
		circles.emplace_back(2, 2, 0.5262768679065629);
		circles.emplace_back(2, 3, 0.2931876542279497);
		circles.emplace_back(2, 4, 0.6533500568708405);
		circles.emplace_back(2, 5, 0.5175580858485773);
		circles.emplace_back(2, 6, 0.4056010070024058);
		circles.emplace_back(2, 7, 0.3495587039971724);
		circles.emplace_back(2, 8, 0.5365060578798875);
		circles.emplace_back(2, 9, 0.6818348021479324);
		circles.emplace_back(2, 10, 0.3912981313420459);
		circles.emplace_back(3, 0, 0.5962131446460261);
		circles.emplace_back(3, 1, 0.3215087389340624);
		circles.emplace_back(3, 2, 0.5624618086265399);
		circles.emplace_back(3, 3, 0.4355787149397656);
		circles.emplace_back(3, 4, 0.3082139663631097);
		circles.emplace_back(3, 5, 0.4968902140622958);
		circles.emplace_back(3, 6, 0.2715058033587411);
		circles.emplace_back(3, 7, 0.6999084503157064);
		circles.emplace_back(3, 8, 0.4565584549913183);
		circles.emplace_back(3, 9, 0.4635200911900028);
		circles.emplace_back(3, 10, 0.1679260320262983);
		circles.emplace_back(4, 0, 0.4156161586521193);
		circles.emplace_back(4, 1, 0.3854364928090945);
		circles.emplace_back(4, 2, 0.5419907260453328);
		circles.emplace_back(4, 3, 0.6499693074496463);
		circles.emplace_back(4, 4, 0.3732126374496147);
		circles.emplace_back(4, 5, 0.4455435468116775);
		circles.emplace_back(4, 6, 0.4227759135654196);
		circles.emplace_back(4, 7, 0.4739322166191414);
		circles.emplace_back(4, 8, 0.7060454456834122);
		circles.emplace_back(4, 9, 0.4115733444923535);
		circles.emplace_back(4, 10, 0.4997880168026313);
		circles.emplace_back(5, 0, 0.602415515226312);
		circles.emplace_back(5, 1, 0.483914626459591);
		circles.emplace_back(5, 2, 0.4620152371237054);
		circles.emplace_back(5, 3, 0.3779585333308205);
		circles.emplace_back(5, 4, 0.6351957096951082);
		circles.emplace_back(5, 5, 0.6822743671713397);
		circles.emplace_back(5, 6, 0.5493812505388632);
		circles.emplace_back(5, 7, 0.695467099151574);
		circles.emplace_back(5, 8, 0.2258388267131522);
		circles.emplace_back(5, 9, 0.5426455971552059);
		circles.emplace_back(5, 10, 0.4389878234127536);
		circles.emplace_back(6, 0, 0.4512439301004633);
		circles.emplace_back(6, 1, 0.3371813702629879);
		circles.emplace_back(6, 2, 0.5898645228473469);
		circles.emplace_back(6, 3, 0.4444172330433503);
		circles.emplace_back(6, 4, 0.4783707007532939);
		circles.emplace_back(6, 5, 0.8388034661533311);
		circles.emplace_back(6, 6, 0.2217921004397795);
		circles.emplace_back(6, 7, 0.3377837086329237);
		circles.emplace_back(6, 8, 0.4540048608323559);
		circles.emplace_back(6, 9, 0.3996191940503195);
		circles.emplace_back(6, 10, 0.4371094460366294);
		circles.emplace_back(7, 0, 0.6629292320692911);
		circles.emplace_back(7, 1, 0.3864523891126737);
		circles.emplace_back(7, 2, 0.5787091070087627);
		circles.emplace_back(7, 3, 0.516824183310382);
		circles.emplace_back(7, 4, 0.329674026207067);
		circles.emplace_back(7, 5, 0.570013984828256);
		circles.emplace_back(7, 6, 0.567519938503392);
		circles.emplace_back(7, 7, 0.4251127286581323);
		circles.emplace_back(7, 8, 0.4172467306489125);
		circles.emplace_back(7, 9, 0.4482296965783462);
		circles.emplace_back(7, 10, 0.386556496960111);
		circles.emplace_back(8, 0, 0.4451235138578341);
		circles.emplace_back(8, 1, 0.2650192650267854);
		circles.emplace_back(8, 2, 0.2761469887336716);
		circles.emplace_back(8, 3, 0.7896907477872446);
		circles.emplace_back(8, 4, 0.5153661462245509);
		circles.emplace_back(8, 5, 0.5786713797831907);
		circles.emplace_back(8, 6, 0.3222372453426942);
		circles.emplace_back(8, 7, 0.2792130829067901);
		circles.emplace_back(8, 8, 0.6823115062667057);
		circles.emplace_back(8, 9, 0.5299098944524303);
		circles.emplace_back(8, 10, 0.3005857115378603);
		circles.emplace_back(9, 0, 0.2847507777856663);
		circles.emplace_back(9, 1, 0.3348277828423306);
		circles.emplace_back(9, 2, 0.5778676234418526);
		circles.emplace_back(9, 3, 0.3739798724418506);
		circles.emplace_back(9, 4, 0.6091786359669641);
		circles.emplace_back(9, 5, 0.3360774458153173);
		circles.emplace_back(9, 6, 0.6903069893131032);
		circles.emplace_back(9, 7, 0.4185212695738301);
		circles.emplace_back(9, 8, 0.6946468211011961);
		circles.emplace_back(9, 10, 0.3185001562116668);
		circles.emplace_back(10, 0, 0.5927533235633745);
		circles.emplace_back(10, 1, 0.3903857547556981);
		circles.emplace_back(10, 2, 0.211850876477547);
		circles.emplace_back(10, 3, 0.6575066138757393);
		circles.emplace_back(10, 4, 0.4236828549066559);
		circles.emplace_back(10, 5, 0.5853571815183386);
		circles.emplace_back(10, 6, 0.4256689320551231);
		circles.emplace_back(10, 7, 0.7895083426265046);
		circles.emplace_back(10, 8, 0.3238903850549832);
		circles.emplace_back(10, 9, 0.4317595340078696);
		circles.emplace_back(10, 10, 0.4402910989942029);
	}
	result_expected = 16.40714706620832;
	timer.reset();
	result_actual = algorithm(a67, b67, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #67: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a68(1, 1);
	Point b68(9, 9);
	{
		circles.emplace_back(0, 0, 0.3899084129137918);
		circles.emplace_back(0, 1, 0.6381616519996897);
		circles.emplace_back(0, 2, 0.3074124933918938);
		circles.emplace_back(0, 3, 0.2769660516874864);
		circles.emplace_back(0, 4, 0.4766781019745394);
		circles.emplace_back(0, 5, 0.357375380792655);
		circles.emplace_back(0, 6, 0.521235441765748);
		circles.emplace_back(0, 7, 0.3874897972913459);
		circles.emplace_back(0, 8, 0.4551444914890453);
		circles.emplace_back(0, 9, 0.5791600218275562);
		circles.emplace_back(0, 10, 0.4501249035587534);
		circles.emplace_back(1, 0, 0.5565616327570752);
		circles.emplace_back(1, 2, 0.4696140027372167);
		circles.emplace_back(1, 3, 0.4152301766211167);
		circles.emplace_back(1, 4, 0.3717304244404658);
		circles.emplace_back(1, 5, 0.39613228936214);
		circles.emplace_back(1, 6, 0.57745686925482);
		circles.emplace_back(1, 7, 0.523527711094357);
		circles.emplace_back(1, 8, 0.2837538877269253);
		circles.emplace_back(1, 9, 0.4848692647414282);
		circles.emplace_back(1, 10, 0.1112775469897315);
		circles.emplace_back(2, 0, 0.4932925563538447);
		circles.emplace_back(2, 1, 0.3503972682869061);
		circles.emplace_back(2, 2, 0.3558643424184993);
		circles.emplace_back(2, 3, 0.4447960619581863);
		circles.emplace_back(2, 4, 0.4611881969729438);
		circles.emplace_back(2, 5, 0.2665838239481673);
		circles.emplace_back(2, 6, 0.4857082988368347);
		circles.emplace_back(2, 7, 0.1280652954010293);
		circles.emplace_back(2, 8, 0.3866068467730656);
		circles.emplace_back(2, 9, 0.3805777244037017);
		circles.emplace_back(2, 10, 0.5880577978910878);
		circles.emplace_back(3, 0, 0.3076492064399645);
		circles.emplace_back(3, 1, 0.464279312104918);
		circles.emplace_back(3, 2, 0.3656271176179871);
		circles.emplace_back(3, 3, 0.4648194729583338);
		circles.emplace_back(3, 4, 0.3973869922338054);
		circles.emplace_back(3, 5, 0.602314542629756);
		circles.emplace_back(3, 6, 0.6812556337332353);
		circles.emplace_back(3, 7, 0.5180761964293197);
		circles.emplace_back(3, 8, 0.4153681856347248);
		circles.emplace_back(3, 9, 0.3437938696006313);
		circles.emplace_back(3, 10, 0.5148273264756426);
		circles.emplace_back(4, 0, 0.3758805367397144);
		circles.emplace_back(4, 1, 0.452743690344505);
		circles.emplace_back(4, 2, 0.1600449316436425);
		circles.emplace_back(4, 3, 0.1440100520616397);
		circles.emplace_back(4, 4, 0.2350404029013589);
		circles.emplace_back(4, 5, 0.4899977535707876);
		circles.emplace_back(4, 6, 0.6937202880391851);
		circles.emplace_back(4, 7, 0.5107622856041416);
		circles.emplace_back(4, 8, 0.3740218765335158);
		circles.emplace_back(4, 9, 0.3263058761833236);
		circles.emplace_back(4, 10, 0.2798057195032015);
		circles.emplace_back(5, 0, 0.4474683750187978);
		circles.emplace_back(5, 1, 0.4390942313941196);
		circles.emplace_back(5, 2, 0.4376036603702232);
		circles.emplace_back(5, 3, 0.5226832164684311);
		circles.emplace_back(5, 4, 0.545847232430242);
		circles.emplace_back(5, 5, 0.2568421404110268);
		circles.emplace_back(5, 6, 0.5289915947942063);
		circles.emplace_back(5, 7, 0.1573736548656598);
		circles.emplace_back(5, 8, 0.6092594630783423);
		circles.emplace_back(5, 9, 0.1761700702132657);
		circles.emplace_back(5, 10, 0.4971007772488519);
		circles.emplace_back(6, 0, 0.4730841594049707);
		circles.emplace_back(6, 1, 0.5790379317244515);
		circles.emplace_back(6, 2, 0.2929238631622866);
		circles.emplace_back(6, 3, 0.2680445748148486);
		circles.emplace_back(6, 4, 0.4271851543569937);
		circles.emplace_back(6, 5, 0.5754667665576562);
		circles.emplace_back(6, 6, 0.1602545068832114);
		circles.emplace_back(6, 7, 0.5265812215162441);
		circles.emplace_back(6, 8, 0.2277421018341556);
		circles.emplace_back(6, 9, 0.3440338006010279);
		circles.emplace_back(6, 10, 0.4378490912960842);
		circles.emplace_back(7, 0, 0.5021123534766957);
		circles.emplace_back(7, 1, 0.21272692757193);
		circles.emplace_back(7, 2, 0.6475814506178722);
		circles.emplace_back(7, 3, 0.5831539531471207);
		circles.emplace_back(7, 4, 0.52714248157572);
		circles.emplace_back(7, 5, 0.3040341342100873);
		circles.emplace_back(7, 6, 0.594981033517979);
		circles.emplace_back(7, 7, 0.3377150080399587);
		circles.emplace_back(7, 8, 0.133824401604943);
		circles.emplace_back(7, 9, 0.6644266020739451);
		circles.emplace_back(7, 10, 0.3469555202638731);
		circles.emplace_back(8, 0, 0.3117602699669078);
		circles.emplace_back(8, 1, 0.30421554192435);
		circles.emplace_back(8, 2, 0.4355360774556175);
		circles.emplace_back(8, 3, 0.1896757272770628);
		circles.emplace_back(8, 4, 0.7201495583401992);
		circles.emplace_back(8, 5, 0.3398702486185357);
		circles.emplace_back(8, 6, 0.2850433483952656);
		circles.emplace_back(8, 7, 0.3167549453442916);
		circles.emplace_back(8, 8, 0.4728163925232365);
		circles.emplace_back(8, 9, 0.3663930081529543);
		circles.emplace_back(8, 10, 0.2411631079623476);
		circles.emplace_back(9, 0, 0.410267006023787);
		circles.emplace_back(9, 1, 0.4728270738618448);
		circles.emplace_back(9, 2, 0.5385776075301691);
		circles.emplace_back(9, 3, 0.6425585050368682);
		circles.emplace_back(9, 4, 0.6614127855515107);
		circles.emplace_back(9, 5, 0.4251819552155212);
		circles.emplace_back(9, 6, 0.4617572319461032);
		circles.emplace_back(9, 7, 0.3818103825906292);
		circles.emplace_back(9, 8, 0.6214601462474093);
		circles.emplace_back(9, 10, 0.5094838979886844);
		circles.emplace_back(10, 0, 0.6949904999462887);
		circles.emplace_back(10, 1, 0.5705662034684792);
		circles.emplace_back(10, 2, 0.5235823154216632);
		circles.emplace_back(10, 3, 0.5195989166619256);
		circles.emplace_back(10, 4, 0.5517084360821173);
		circles.emplace_back(10, 5, 0.6044936636695638);
		circles.emplace_back(10, 6, 0.5662197017809376);
		circles.emplace_back(10, 7, 0.6234340108232572);
		circles.emplace_back(10, 8, 0.3634473810670897);
		circles.emplace_back(10, 9, 0.7561639931285754);
		circles.emplace_back(10, 10, 0.3985901493346318);
	}
	result_expected = 11.53106892553423;
	timer.reset();
	result_actual = algorithm(a68, b68, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #68: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a69(1, 1);
	Point b69(9, 9);
	{
		circles.emplace_back(0, 0, 0.5459571846993639);
		circles.emplace_back(0, 1, 0.3222928394330665);
		circles.emplace_back(0, 2, 0.6739899439970031);
		circles.emplace_back(0, 3, 0.5989726288011298);
		circles.emplace_back(0, 4, 0.7285846541868523);
		circles.emplace_back(0, 5, 0.7676592646865174);
		circles.emplace_back(0, 6, 0.4153434664243832);
		circles.emplace_back(0, 7, 0.2863893665140494);
		circles.emplace_back(0, 8, 0.1680602413835004);
		circles.emplace_back(0, 9, 0.2330307819647714);
		circles.emplace_back(0, 10, 0.2919780718395487);
		circles.emplace_back(1, 0, 0.4563114108284935);
		circles.emplace_back(1, 2, 0.1879519566195086);
		circles.emplace_back(1, 3, 0.6182878481922671);
		circles.emplace_back(1, 4, 0.7558808837318792);
		circles.emplace_back(1, 5, 0.5810126360272988);
		circles.emplace_back(1, 6, 0.4458907679887488);
		circles.emplace_back(1, 7, 0.2032448497368023);
		circles.emplace_back(1, 8, 0.4036793759325519);
		circles.emplace_back(1, 9, 0.4651971837272867);
		circles.emplace_back(1, 10, 0.6296765583800151);
		circles.emplace_back(2, 0, 0.3680236375657842);
		circles.emplace_back(2, 1, 0.5277277983957901);
		circles.emplace_back(2, 2, 0.5975253417855129);
		circles.emplace_back(2, 3, 0.4453762700082734);
		circles.emplace_back(2, 4, 0.4358879999024793);
		circles.emplace_back(2, 5, 0.4919982904801145);
		circles.emplace_back(2, 6, 0.6886628607055172);
		circles.emplace_back(2, 7, 0.5505392364459112);
		circles.emplace_back(2, 8, 0.5041640723822638);
		circles.emplace_back(2, 9, 0.4609016817295923);
		circles.emplace_back(2, 10, 0.1364787075435743);
		circles.emplace_back(3, 0, 0.3356547021539882);
		circles.emplace_back(3, 1, 0.178871685708873);
		circles.emplace_back(3, 2, 0.559162980155088);
		circles.emplace_back(3, 3, 0.1090162573149428);
		circles.emplace_back(3, 4, 0.3069765295134857);
		circles.emplace_back(3, 5, 0.4786916508106515);
		circles.emplace_back(3, 6, 0.6908765480155125);
		circles.emplace_back(3, 7, 0.1858629219001159);
		circles.emplace_back(3, 8, 0.1738400933565572);
		circles.emplace_back(3, 9, 0.1238939814968035);
		circles.emplace_back(3, 10, 0.595865965099074);
		circles.emplace_back(4, 0, 0.6485432164510712);
		circles.emplace_back(4, 1, 0.3935963629977777);
		circles.emplace_back(4, 2, 0.6758520546136424);
		circles.emplace_back(4, 3, 0.1714735795045272);
		circles.emplace_back(4, 4, 0.3605602632975206);
		circles.emplace_back(4, 5, 0.3772881717653945);
		circles.emplace_back(4, 6, 0.6427677077008411);
		circles.emplace_back(4, 7, 0.5379047459224239);
		circles.emplace_back(4, 8, 0.4277107333531603);
		circles.emplace_back(4, 9, 0.5091936740325763);
		circles.emplace_back(4, 10, 0.5172322741476819);
		circles.emplace_back(5, 0, 0.4752517514163628);
		circles.emplace_back(5, 1, 0.2792982250219211);
		circles.emplace_back(5, 2, 0.5833619897486642);
		circles.emplace_back(5, 3, 0.3612485558493063);
		circles.emplace_back(5, 4, 0.4103224287042394);
		circles.emplace_back(5, 5, 0.5608700806042179);
		circles.emplace_back(5, 6, 0.3102660364704207);
		circles.emplace_back(5, 7, 0.8043387333629652);
		circles.emplace_back(5, 8, 0.4813984569394961);
		circles.emplace_back(5, 9, 0.3791026402032003);
		circles.emplace_back(5, 10, 0.4966975488932803);
		circles.emplace_back(6, 0, 0.4703632135642692);
		circles.emplace_back(6, 1, 0.3590483499923721);
		circles.emplace_back(6, 2, 0.2894599331310019);
		circles.emplace_back(6, 3, 0.3520292858825996);
		circles.emplace_back(6, 4, 0.3986754148034379);
		circles.emplace_back(6, 5, 0.5511201322311535);
		circles.emplace_back(6, 6, 0.6672508068149909);
		circles.emplace_back(6, 7, 0.3239694250049069);
		circles.emplace_back(6, 8, 0.3752374895615503);
		circles.emplace_back(6, 9, 0.2700387018034234);
		circles.emplace_back(6, 10, 0.55270949320402);
		circles.emplace_back(7, 0, 0.2169331445591524);
		circles.emplace_back(7, 1, 0.139321984606795);
		circles.emplace_back(7, 2, 0.2905328814173117);
		circles.emplace_back(7, 3, 0.4107246126746759);
		circles.emplace_back(7, 4, 0.4961563931079581);
		circles.emplace_back(7, 5, 0.5814244386507198);
		circles.emplace_back(7, 6, 0.4759171566227451);
		circles.emplace_back(7, 7, 0.39584161543753);
		circles.emplace_back(7, 8, 0.430676846508868);
		circles.emplace_back(7, 9, 0.198011917504482);
		circles.emplace_back(7, 10, 0.4010531015926972);
		circles.emplace_back(8, 0, 0.5631636604433879);
		circles.emplace_back(8, 1, 0.678307052445598);
		circles.emplace_back(8, 2, 0.5187324867350981);
		circles.emplace_back(8, 3, 0.5501154924044386);
		circles.emplace_back(8, 4, 0.6157759317895397);
		circles.emplace_back(8, 5, 0.6657247624592856);
		circles.emplace_back(8, 6, 0.471710621821694);
		circles.emplace_back(8, 7, 0.5172881078207865);
		circles.emplace_back(8, 8, 0.5293183926260099);
		circles.emplace_back(8, 9, 0.4668054514797404);
		circles.emplace_back(8, 10, 0.6025535558117553);
		circles.emplace_back(9, 0, 0.3885142175713554);
		circles.emplace_back(9, 1, 0.2443319765618071);
		circles.emplace_back(9, 2, 0.232322024856694);
		circles.emplace_back(9, 3, 0.1126935644773766);
		circles.emplace_back(9, 4, 0.5324267581338062);
		circles.emplace_back(9, 5, 0.3670032165711746);
		circles.emplace_back(9, 6, 0.2741367128910497);
		circles.emplace_back(9, 7, 0.432691188971512);
		circles.emplace_back(9, 8, 0.2785831960150972);
		circles.emplace_back(9, 10, 0.5689323113998398);
		circles.emplace_back(10, 0, 0.5570101528661325);
		circles.emplace_back(10, 1, 0.3961243959842249);
		circles.emplace_back(10, 2, 0.611130078532733);
		circles.emplace_back(10, 3, 0.3265496294712648);
		circles.emplace_back(10, 4, 0.6011526585789397);
		circles.emplace_back(10, 5, 0.6296886753989384);
		circles.emplace_back(10, 6, 0.2560222720960155);
		circles.emplace_back(10, 7, 0.4908056502928957);
		circles.emplace_back(10, 8, 0.6486426773713901);
		circles.emplace_back(10, 9, 0.4251330754486844);
		circles.emplace_back(10, 10, 0.4899218879872933);
	}
	result_expected = 16.87284178933973;
	timer.reset();
	result_actual = algorithm(a69, b69, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #69: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a70(1, 1);
	Point b70(9, 9);
	{
		circles.emplace_back(0, 0, 0.4277593433624133);
		circles.emplace_back(0, 1, 0.2968374346615746);
		circles.emplace_back(0, 2, 0.5086571753723547);
		circles.emplace_back(0, 3, 0.5489018956432119);
		circles.emplace_back(0, 4, 0.3206899845739826);
		circles.emplace_back(0, 5, 0.5519007659750059);
		circles.emplace_back(0, 6, 0.6733939955709501);
		circles.emplace_back(0, 7, 0.4650794234359636);
		circles.emplace_back(0, 8, 0.674357410124503);
		circles.emplace_back(0, 9, 0.4055731364758685);
		circles.emplace_back(0, 10, 0.5906038452638313);
		circles.emplace_back(1, 0, 0.4093037469545379);
		circles.emplace_back(1, 2, 0.5120357079198584);
		circles.emplace_back(1, 3, 0.4883088479982689);
		circles.emplace_back(1, 4, 0.5652041076449678);
		circles.emplace_back(1, 5, 0.4680239647859707);
		circles.emplace_back(1, 6, 0.4059453464811668);
		circles.emplace_back(1, 7, 0.7019054335774854);
		circles.emplace_back(1, 8, 0.6512599625391885);
		circles.emplace_back(1, 9, 0.4324613617965952);
		circles.emplace_back(1, 10, 0.4317087413510308);
		circles.emplace_back(2, 0, 0.4847502394812181);
		circles.emplace_back(2, 1, 0.5930610465584323);
		circles.emplace_back(2, 2, 0.528211459913291);
		circles.emplace_back(2, 3, 0.3874542589997872);
		circles.emplace_back(2, 4, 0.3128091947408393);
		circles.emplace_back(2, 5, 0.5074090507579967);
		circles.emplace_back(2, 6, 0.8634007564047351);
		circles.emplace_back(2, 7, 0.4681936582317576);
		circles.emplace_back(2, 8, 0.4894827681826427);
		circles.emplace_back(2, 9, 0.5727412557927891);
		circles.emplace_back(2, 10, 0.5235231496626511);
		circles.emplace_back(3, 0, 0.4360979690914973);
		circles.emplace_back(3, 1, 0.6274541129590944);
		circles.emplace_back(3, 2, 0.2407150045735761);
		circles.emplace_back(3, 3, 0.3910810524830595);
		circles.emplace_back(3, 4, 0.2772968092700466);
		circles.emplace_back(3, 5, 0.6756543985800817);
		circles.emplace_back(3, 6, 0.3358781124232337);
		circles.emplace_back(3, 7, 0.4181561928475275);
		circles.emplace_back(3, 8, 0.3858261380111799);
		circles.emplace_back(3, 9, 0.2944703304441645);
		circles.emplace_back(3, 10, 0.4590502147329971);
		circles.emplace_back(4, 0, 0.5300351022044196);
		circles.emplace_back(4, 1, 0.3653494475176558);
		circles.emplace_back(4, 2, 0.4323188568698242);
		circles.emplace_back(4, 3, 0.1600400521187112);
		circles.emplace_back(4, 4, 0.3880142912501469);
		circles.emplace_back(4, 5, 0.4892773918574675);
		circles.emplace_back(4, 6, 0.3067140636267141);
		circles.emplace_back(4, 7, 0.4953236930770799);
		circles.emplace_back(4, 8, 0.5895101132104174);
		circles.emplace_back(4, 9, 0.1099108533700928);
		circles.emplace_back(4, 10, 0.5429512559669092);
		circles.emplace_back(5, 0, 0.3363086941419169);
		circles.emplace_back(5, 1, 0.5335983146214858);
		circles.emplace_back(5, 2, 0.3572324465727433);
		circles.emplace_back(5, 3, 0.5735332281561568);
		circles.emplace_back(5, 4, 0.243809197540395);
		circles.emplace_back(5, 5, 0.330108273611404);
		circles.emplace_back(5, 6, 0.3179714595666155);
		circles.emplace_back(5, 7, 0.1514637205051258);
		circles.emplace_back(5, 8, 0.4743569663492962);
		circles.emplace_back(5, 9, 0.4803969256812706);
		circles.emplace_back(5, 10, 0.3355672329431399);
		circles.emplace_back(6, 0, 0.580533063900657);
		circles.emplace_back(6, 1, 0.5339733571512625);
		circles.emplace_back(6, 2, 0.4079273769864812);
		circles.emplace_back(6, 3, 0.4216559761902317);
		circles.emplace_back(6, 4, 0.2157210118370131);
		circles.emplace_back(6, 5, 0.3450272301910445);
		circles.emplace_back(6, 6, 0.3667772051179781);
		circles.emplace_back(6, 7, 0.5197060215985402);
		circles.emplace_back(6, 8, 0.5368417599471286);
		circles.emplace_back(6, 9, 0.2418037970317528);
		circles.emplace_back(6, 10, 0.6062014473835006);
		circles.emplace_back(7, 0, 0.5114265156676993);
		circles.emplace_back(7, 1, 0.54855615303386);
		circles.emplace_back(7, 2, 0.7604094057111069);
		circles.emplace_back(7, 3, 0.5193752765888348);
		circles.emplace_back(7, 4, 0.406574548012577);
		circles.emplace_back(7, 5, 0.3098760796012357);
		circles.emplace_back(7, 6, 0.3386372633976862);
		circles.emplace_back(7, 7, 0.3544413643190637);
		circles.emplace_back(7, 8, 0.4067857177695259);
		circles.emplace_back(7, 9, 0.6462860538857057);
		circles.emplace_back(7, 10, 0.2914190965471789);
		circles.emplace_back(8, 0, 0.7159869317198172);
		circles.emplace_back(8, 1, 0.384053137502633);
		circles.emplace_back(8, 2, 0.3476069853873923);
		circles.emplace_back(8, 3, 0.177487748558633);
		circles.emplace_back(8, 4, 0.6350754877785221);
		circles.emplace_back(8, 5, 0.5644798746099695);
		circles.emplace_back(8, 6, 0.4047271359013394);
		circles.emplace_back(8, 7, 0.4228757149307057);
		circles.emplace_back(8, 8, 0.5359582551056519);
		circles.emplace_back(8, 9, 0.2579298302298412);
		circles.emplace_back(8, 10, 0.3883252640487626);
		circles.emplace_back(9, 0, 0.4168746159179136);
		circles.emplace_back(9, 1, 0.3775902832159773);
		circles.emplace_back(9, 2, 0.3242020556470379);
		circles.emplace_back(9, 3, 0.4227109573082998);
		circles.emplace_back(9, 4, 0.2460806066868827);
		circles.emplace_back(9, 5, 0.4980762493098154);
		circles.emplace_back(9, 6, 0.5163535061990842);
		circles.emplace_back(9, 7, 0.7579071515472605);
		circles.emplace_back(9, 8, 0.2821507249725982);
		circles.emplace_back(9, 10, 0.2401709465542808);
		circles.emplace_back(10, 0, 0.6917952326824889);
		circles.emplace_back(10, 1, 0.3930998380528763);
		circles.emplace_back(10, 2, 0.4888951762346551);
		circles.emplace_back(10, 3, 0.3859594598645344);
		circles.emplace_back(10, 4, 0.631787010258995);
		circles.emplace_back(10, 5, 0.5545799580635503);
		circles.emplace_back(10, 6, 0.2643305563135073);
		circles.emplace_back(10, 7, 0.5788420291850344);
		circles.emplace_back(10, 8, 0.5599554048618302);
		circles.emplace_back(10, 9, 0.6813024848001078);
		circles.emplace_back(10, 10, 0.3833190115867183);
	}
	result_expected = 14.64100426808216;
	timer.reset();
	result_actual = algorithm(a70, b70, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #70: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a71(1, 1);
	Point b71(9, 9);
	{
		circles.emplace_back(0, 0, 0.7609486002707854);
		circles.emplace_back(0, 1, 0.4004602771019563);
		circles.emplace_back(0, 2, 0.2211876929970458);
		circles.emplace_back(0, 3, 0.3564183366252109);
		circles.emplace_back(0, 4, 0.5041080629685893);
		circles.emplace_back(0, 5, 0.4664347236743197);
		circles.emplace_back(0, 6, 0.1912896159337834);
		circles.emplace_back(0, 7, 0.2705680093495175);
		circles.emplace_back(0, 8, 0.4624971769982948);
		circles.emplace_back(0, 9, 0.4193234562641009);
		circles.emplace_back(0, 10, 0.7049566899659112);
		circles.emplace_back(1, 0, 0.4272361636860296);
		circles.emplace_back(1, 2, 0.4250941852340475);
		circles.emplace_back(1, 3, 0.3897446179529652);
		circles.emplace_back(1, 4, 0.4191095865564421);
		circles.emplace_back(1, 5, 0.3436524997232482);
		circles.emplace_back(1, 6, 0.2960621144855395);
		circles.emplace_back(1, 7, 0.2005000371253118);
		circles.emplace_back(1, 8, 0.4047612318070605);
		circles.emplace_back(1, 9, 0.6327521313680335);
		circles.emplace_back(1, 10, 0.2811867637792602);
		circles.emplace_back(2, 0, 0.2823589188745245);
		circles.emplace_back(2, 1, 0.393904013489373);
		circles.emplace_back(2, 2, 0.6274553715018555);
		circles.emplace_back(2, 3, 0.3084943801397458);
		circles.emplace_back(2, 4, 0.5232399739092216);
		circles.emplace_back(2, 5, 0.1058891755761579);
		circles.emplace_back(2, 6, 0.3649084546370432);
		circles.emplace_back(2, 7, 0.3611740218708291);
		circles.emplace_back(2, 8, 0.3414169849595055);
		circles.emplace_back(2, 9, 0.8064234002726153);
		circles.emplace_back(2, 10, 0.09631019707303494);
		circles.emplace_back(3, 0, 0.5509296093368903);
		circles.emplace_back(3, 1, 0.4233728106832131);
		circles.emplace_back(3, 2, 0.6023075775476172);
		circles.emplace_back(3, 3, 0.5379495945526287);
		circles.emplace_back(3, 4, 0.2098866632441059);
		circles.emplace_back(3, 5, 0.4169268270721659);
		circles.emplace_back(3, 6, 0.5250427621649578);
		circles.emplace_back(3, 7, 0.3290793574182316);
		circles.emplace_back(3, 8, 0.2291787304216996);
		circles.emplace_back(3, 9, 0.2202608063584194);
		circles.emplace_back(3, 10, 0.5064283182146028);
		circles.emplace_back(4, 0, 0.5122503832681105);
		circles.emplace_back(4, 1, 0.4223384971031919);
		circles.emplace_back(4, 2, 0.3574682334205135);
		circles.emplace_back(4, 3, 0.1992772511439398);
		circles.emplace_back(4, 4, 0.201732167112641);
		circles.emplace_back(4, 5, 0.3416185897076502);
		circles.emplace_back(4, 6, 0.3812520596897229);
		circles.emplace_back(4, 7, 0.8463737272890285);
		circles.emplace_back(4, 8, 0.4556441490305587);
		circles.emplace_back(4, 9, 0.4253670631209388);
		circles.emplace_back(4, 10, 0.3933958945563063);
		circles.emplace_back(5, 0, 0.3507977809058502);
		circles.emplace_back(5, 1, 0.5174229993252083);
		circles.emplace_back(5, 2, 0.2045825764769688);
		circles.emplace_back(5, 3, 0.4236336342757568);
		circles.emplace_back(5, 4, 0.5507422087015584);
		circles.emplace_back(5, 5, 0.1422508411807939);
		circles.emplace_back(5, 6, 0.6467742564389481);
		circles.emplace_back(5, 7, 0.3575425283750519);
		circles.emplace_back(5, 8, 0.5519466518657282);
		circles.emplace_back(5, 9, 0.274069410818629);
		circles.emplace_back(5, 10, 0.4652512479806319);
		circles.emplace_back(6, 0, 0.2540846835589036);
		circles.emplace_back(6, 1, 0.8208738656016067);
		circles.emplace_back(6, 2, 0.4888051551533863);
		circles.emplace_back(6, 3, 0.3719669526675716);
		circles.emplace_back(6, 4, 0.4434220051160082);
		circles.emplace_back(6, 5, 0.2917531761573627);
		circles.emplace_back(6, 6, 0.1694302669493482);
		circles.emplace_back(6, 7, 0.302042954438366);
		circles.emplace_back(6, 8, 0.6456295758252963);
		circles.emplace_back(6, 9, 0.3906161253573373);
		circles.emplace_back(6, 10, 0.3284846574766561);
		circles.emplace_back(7, 0, 0.2880976328859106);
		circles.emplace_back(7, 1, 0.500932472362183);
		circles.emplace_back(7, 2, 0.329449302633293);
		circles.emplace_back(7, 3, 0.4436838666675612);
		circles.emplace_back(7, 4, 0.8125044640386477);
		circles.emplace_back(7, 5, 0.4520910192048177);
		circles.emplace_back(7, 6, 0.5735893645556643);
		circles.emplace_back(7, 7, 0.4222379107726738);
		circles.emplace_back(7, 8, 0.4157050086418166);
		circles.emplace_back(7, 9, 0.5695594800403342);
		circles.emplace_back(7, 10, 0.6354852418648079);
		circles.emplace_back(8, 0, 0.5595060675172135);
		circles.emplace_back(8, 1, 0.4887015879387036);
		circles.emplace_back(8, 2, 0.4600431866711006);
		circles.emplace_back(8, 3, 0.2979525340022519);
		circles.emplace_back(8, 4, 0.6076125987572595);
		circles.emplace_back(8, 5, 0.3278546469518915);
		circles.emplace_back(8, 6, 0.2490791054209694);
		circles.emplace_back(8, 7, 0.6200450911419466);
		circles.emplace_back(8, 8, 0.4196484106360003);
		circles.emplace_back(8, 9, 0.4801098052645102);
		circles.emplace_back(8, 10, 0.6782648410415276);
		circles.emplace_back(9, 0, 0.328668783721514);
		circles.emplace_back(9, 1, 0.5850836512399837);
		circles.emplace_back(9, 2, 0.4567795953014865);
		circles.emplace_back(9, 3, 0.2077610781183466);
		circles.emplace_back(9, 4, 0.1490624594734982);
		circles.emplace_back(9, 5, 0.4220162457553669);
		circles.emplace_back(9, 6, 0.1440048881107941);
		circles.emplace_back(9, 7, 0.3646924599772319);
		circles.emplace_back(9, 8, 0.4772710879566148);
		circles.emplace_back(9, 10, 0.4418813691241666);
		circles.emplace_back(10, 0, 0.5880210066447035);
		circles.emplace_back(10, 1, 0.4280719050904736);
		circles.emplace_back(10, 2, 0.4477360925870016);
		circles.emplace_back(10, 3, 0.3522468562005088);
		circles.emplace_back(10, 4, 0.5833535265410319);
		circles.emplace_back(10, 5, 0.490873360983096);
		circles.emplace_back(10, 6, 0.5991278701694682);
		circles.emplace_back(10, 7, 0.6133195494068786);
		circles.emplace_back(10, 8, 0.3420687644043937);
		circles.emplace_back(10, 9, 0.5898779956391081);
		circles.emplace_back(10, 10, 0.691545497928746);
	}
	result_expected = 12.29113239713847;
	timer.reset();
	result_actual = algorithm(a71, b71, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #71: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	


	//=====================================================================
	/*
	Point a8(0.0, 0.0);
	Point b8(2.0, 2.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0 + g_pi / 2.0;

	result_actual = algorithm(a8, b8, circles);

	std::cout << "test  #s8: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a9(0.0, 0.0);
	Point b9(2.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 2.0;

	result_actual = algorithm(a9, b9, circles);

	std::cout << "test  #s9: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a10(0.0, 0.0);
	Point b10(3.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 3.0;

	result_actual = algorithm(a10, b10, circles);

	std::cout << "test  #s10: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a11(0.0, 0.0);
	Point b11(4.0, 0.0);
	circles.emplace_back(1.0, 1.0, 1.0);
	result_expected = 4.0;

	result_actual = algorithm(a11, b11, circles);

	std::cout << "test  #s11: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a12(0.0, 0.0);
	Point b12(4.0, 0.0);
	circles.emplace_back(2.0, 2.0, 2.0);
	result_expected = 4.0;

	result_actual = algorithm(a12, b12, circles);

	std::cout << "test  #s12: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a13(0.0, 0.0);
	Point b13(4.0, 0.0);
	circles.emplace_back(2.0, 4.0, 4.0);
	result_expected = 4.0;

	result_actual = algorithm(a13, b13, circles);

	std::cout << "test  #s13: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a14(0.0, 0.0);
	Point b14(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 8.0;

	result_actual = algorithm(a14, b14, circles);

	std::cout << "test  #s14: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a15(-2.0, 0.0);
	Point b15(8.0, 0.0);
	circles.emplace_back(4.0, 4.0, 4.0);
	result_expected = 10.0;

	result_actual = algorithm(a15, b15, circles);

	std::cout << "test  #s15: " <<
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

	std::cout << "test  #s16: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();
	*/
}

void test_filter_tangents(void (*algorithm)(Tangents_t&, const std::vector<Circle>&)) {
	std::cout << "test_filter_tangents:\n";

	std::vector<Circle> circles;
	Tangents_t actual;
	Tangents_t expected;

	Circle c11(Point(0.0, 0.0), 2.0);
	Circle c12(Point(4.0, 4.0), 2.0);
	circles.push_back(c11);
	circles.push_back(c12);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c11,
		c12
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c11,
		c12
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c11,
		c12
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c11,
		c12
	);

	expected = actual;

	algorithm(actual, circles);
	std::cout << "test  #1: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c21(Point(0.0, 0.0), 2.0);
	Circle c22(Point(4.0, 4.0), 2.0);
	Circle c23(Point(0.0, 0.0), 2.0);
	Circle c24(Point(4.0, 4.0), 2.0);
	Circle c25(Point(0.0, 0.0), 1.0);
	Circle c26(Point(4.0, 4.0), 1.0);
	Circle c27(Point(1.0, 1.0), 0.5);
	Circle c28(Point(1.0, -1.0), 0.5);
	Circle c29(Point(-1.0, -1.0), 0.5);
	Circle c210(Point(-1.0, 1.0), 0.5);
	Circle c211(Point(5.0, 5.0), 0.5);
	Circle c212(Point(5.0, 3.0), 0.5);
	Circle c213(Point(3.0, 3.0), 0.5);
	Circle c214(Point(3.0, 5.0), 0.5);


	circles.push_back(c21);
	circles.push_back(c22);
	circles.push_back(c23);
	circles.push_back(c24);
	circles.push_back(c25);
	circles.push_back(c26);
	circles.push_back(c27);
	circles.push_back(c28);
	circles.push_back(c29);
	circles.push_back(c210);
	circles.push_back(c211);
	circles.push_back(c212);
	circles.push_back(c213);
	circles.push_back(c214);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c21,
		c22
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c21,
		c22
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c21,
		c22
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c21,
		c22
	);

	expected = actual;

	algorithm(actual, circles);
	std::cout << "test  #2: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c31(Point(0.0, 0.0), 2.0);
	Circle c32(Point(4.0, 4.0), 2.0);
	Circle c33(Point(1.0, 4.0), 0.5);
	circles.push_back(c31);
	circles.push_back(c32);
	circles.push_back(c33);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c31,
		c32
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c31,
		c32
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c31,
		c32
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c31,
		c32
	);

	expected.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c31,
		c32
	);
	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c31,
		c32
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c31,
		c32
	);


	algorithm(actual, circles);
	std::cout << "test  #3: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c41(Point(0.0, 0.0), 2.0);
	Circle c42(Point(4.0, 4.0), 2.0);
	Circle c43(Point(1.0, 4.0), 1.0);
	circles.push_back(c41);
	circles.push_back(c42);
	circles.push_back(c43);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c41,
		c42
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c41,
		c42
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c41,
		c42
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c41,
		c42
	);

	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c41,
		c42
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c41,
		c42
	);


	algorithm(actual, circles);
	std::cout << "test  #4: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c51(Point(0.0, 0.0), 2.0);
	Circle c52(Point(4.0, 4.0), 2.0);
	Circle c53(Point(3.0, 5.0), 1.0);
	circles.push_back(c51);
	circles.push_back(c52);
	circles.push_back(c53);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c51,
		c52
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c51,
		c52
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c51,
		c52
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c51,
		c52
	);

	expected.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c51,
		c52
	);
	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c51,
		c52
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c51,
		c52
	);


	algorithm(actual, circles);
	std::cout << "test  #5: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c61(Point(0.0, 0.0), 2.0);
	Circle c62(Point(4.0, 4.0), 2.0);
	Circle c63(Point(3.0, 5.0), 2.0);
	circles.push_back(c61);
	circles.push_back(c62);
	circles.push_back(c63);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c61,
		c62
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c61,
		c62
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c61,
		c62
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c61,
		c62
	);

	expected.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c61,
		c62
	);
	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c61,
		c62
	);


	algorithm(actual, circles);
	std::cout << "test  #6: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c71(Point(0.0, 0.0), 2.0);
	Circle c72(Point(4.0, 4.0), 2.0);
	Circle c73(Point(2.0, 2.0), 0.5);
	circles.push_back(c71);
	circles.push_back(c72);
	circles.push_back(c73);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c71,
		c72
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c71,
		c72
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c71,
		c72
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c71,
		c72
	);

	expected.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c71,
		c72
	);
	expected.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c71,
		c72
	);


	algorithm(actual, circles);
	std::cout << "test  #7: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c81(Point(0.0, 0.0), 2.0);
	Circle c82(Point(4.0, 4.0), 2.0);
	Circle c83(Point(2.0, 2.0), 3.0);
	circles.push_back(c81);
	circles.push_back(c82);
	circles.push_back(c83);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c81,
		c82
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c81,
		c82
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c81,
		c82
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c81,
		c82
	);

	algorithm(actual, circles);
	std::cout << "test  #8: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
	circles.clear();


	Circle c91(Point(0.0, 0.0), 2.0);
	Circle c92(Point(4.0, 4.0), 2.0);
	Circle c93(Point(5.0, 5.0), 5.0);
	circles.push_back(c91);
	circles.push_back(c92);
	circles.push_back(c93);

	actual.emplace(
		Point(2.0, 0.0),
		Point(2.0, 4.0),
		c91,
		c92
	);
	actual.emplace(
		Point(0.0, 2.0),
		Point(4.0, 2.0),
		c91,
		c92
	);
	actual.emplace(
		Point(std::sqrt(2.0), -std::sqrt(2.0)),
		Point(4.0 + std::sqrt(2.0), 4.0 - std::sqrt(2.0)),
		c91,
		c92
	);
	actual.emplace(
		Point(-std::sqrt(2.0), std::sqrt(2.0)),
		Point(4.0 - std::sqrt(2.0), 4.0 + std::sqrt(2.0)),
		c91,
		c92
	);

	algorithm(actual, circles);
	std::cout << "test  #9: " << (actual == expected ? "ok" : "FAILED") << '\n';
	actual.clear();
	expected.clear();
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
    test_there_is_collision_between_tangent_and_circle(there_is555555555555555ςόξ78888σσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσσ34γψ0 ψ._collision_between_tangent_and_circle);
    test_there_is_collision_between_arc_and_circle(there_is_collision_between_arc_and_circle);
    test_filter_tangents(filter_tangents);
    test_filter_arcs(filter_arcs);
    test_double_hash();
    test_get_graph(get_graph);
*/

    test_tiptoe_through_the_circles(tiptoe_through_the_circles);
	//test_filter_tangents(filter_tangents_advanced);
	std::cout << "threads: " << std::thread::hardware_concurrency() << '\n';

	/*const std::vector<Circle> circles({
		Circle(0.0,0.0,1.0),
		Circle(0.0,0.0,2.0),
		Circle(0.0,0.0,3.0),
		Circle(0.0,0.0,4.0),
		Circle(0.0,0.0,5.0),
		});

	const double r = 2.5;

	const auto boundary = std::lower_bound(
		circles.cbegin(),
		circles.cend(),
		r,
		[](const Circle& circle, double value)->bool {
			return circle.r < value;
		}
		);

 	return 0;*/
}

/*
const std::vector<Circle> circles({
		Circle(0.0,0.0,1.0),
		Circle(0.0,0.0,2.0),
		Circle(0.0,0.0,3.0),
		Circle(0.0,0.0,4.0),
		Circle(0.0,0.0,5.0),
	});

const double r = 2.5;
//const Circle r(0.0, 0.0, 2.5);
const auto boundary = std::lower_bound(
	circles.cbegin(),
	circles.cend(),
	r,
	[](const Circle& circle, double value)->bool {
		return circle.r < value;
	}
);
*/