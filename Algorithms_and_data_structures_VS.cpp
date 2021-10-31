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




	// HERE !!!!!!!!!!!!!!!!!
	timer.reset();
	result_actual = algorithm(a26, b26, circles);
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #26: " <<
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