#include <iomanip>
#include <iostream>

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


double g_copy{ 0.0 };
double g_tangents_reserve{ 0.0 };
double g_add_tangents{ 0.0 };
double g_filter_tangents{ 0.0 };
double g_add_and_filter_tangents{ 0.0 };
double g_filter_tangents_preparation{ 0.0 };
double g_filter_tangents_filtering{ 0.0 };
double g_get_points_on_circles{ 0.0 };
double g_arcs_size{ 0.0 };
double g_arc_reserve{ 0.0 };
double g_add_arcs{ 0.0 };
double g_filter_arcs{ 0.0 };
double g_graph_reserve{ 0.0 };
double g_add_nodes_to_graph{ 0.0 };
double g_connect_nodes_of_graph{ 0.0 };
double g_merge_neighbors_for_similar_nodes{ 0.0 };
double g_graph{ 0.0 };
double g_dijkstra{ 0.0 };
double g_time{ 0.0 };

#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>


/*
The shortest path consists of tangents and arcs. 
The idea is to build a graph, and then to find the shortest path
using Dijkstra algorithm.
Nodes in the graph - points. 
All the points are on circumeferences of circles. 
Weight of edge (edge cost) is either the length 
of straight line between two points in case these points are 
the ends of the tangent, or the length of the arc in case 
these points are on the circumeference of the same circle.

Every pair of two circles is considered. For every pair all four tangents
are found. Then these for tangents are filtered, because some of them can
be covered with other circles. Then all points of tangents left are added
to the graph. After that for both of the circles in the pair 
for every two points on it arcs are found, then filtered and added to the graph. 
Code requires refactoring.

Version where all tangents between all circles are found, then all these tangents
are filtered, then for every circle all arcs are found, and then all arcs are filtered,
then points of tangents and arcs are added to the graph and connected - works to slow, 
but is much easier to understand:

----The first step is to find all the tangents between every two circles.
----Two or four tangents between every two circles.
----The second step is to remove all tangents that can not exist because some
----of the circles can cover the path of the tangent (collision between tangent and circle).
----The third step is to find all the arcs between points on every circle.
----The fourth step is to remove all arcs that also can not exist because some
----of the circles can cover the curve of the arc (collision between arc and circle).
----The fifth step is to connect all the points according to what tangents and
----arcs the belong to.
----The sixth step is to find the shortest path in this graph using Dijkstra algorithm.

Start point and finish point are considered as the circles with zero radius 
Straight line between start and finish point is also considered as tangent.

Time complexity of slow algorithm: O(n^4) 
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

Time complexity of this algorithm:
Number of pairs circle-circle:                   n * (n - 1) / 2,                 O(n^2)
Number of tangents:                              4 * n * (n - 1) / 2,             O(n^2)
Number of points on each circle:                 4 * (n - 1) = m                  O(n)
Number of arcs on each circle:                   m * (m - 1)                      O(m^2) = O(n^2)
Number of arcs:                                  n * m * (m - 1)                  O(n^3)
Number of points:                                n * m = k                        O(n^2)
Number of circles to filter tangents:            < n - 2. Proportionally to the length of the tangent
												 for short tangents << n 
Number of circles to filter arcs :               << n                             O(n)
												 depends on how many circles intersect the circle arc belongs to
Filtering tangents:                                                               for short O(n^2), for long still O(n^3)
Filtering arcs:                                                                   << O(n^4)
												 depends on topology of circls - proportionally to how many other circles intersect some circle on average
Complexity of Dijkstra algorithm 
with priority queue for k nodes:                               O(k*log(Edges)) => O(n^2 * log(Edges)) -> works 1.5-2 times faster than without priority queue 

*/


const double g_pi = atan(1.0) * 4.0;

constexpr double g_epsilon = 1e-8;


// Data structures =====================================================================

// some prototypes for data structures
struct Tangent;
struct Point;
struct Circle;
struct Double_hash;
struct Point_hash;
struct Circle_hash;
struct Greater_pair_vertex_distance;

// type for length
using Length_t = double;
// type for coordinate (same as Length_t, just to make code more readable)
using Coordinate_t = Length_t;
// type for angle (same as Length_t, just to make code more readable)
using Angle_t = double;
// hashing length
using Length_t_hash = Double_hash;
// to store tangents
using Tangents_t = std::vector<Tangent>;
// to filter tangents fast
using Pair_x_interval = std::pair<Coordinate_t, Coordinate_t>;
using Pair_circle_interval = std::pair<std::vector<Circle>::const_iterator, std::vector<Circle>::const_iterator>;
// to store points
using Points_t = std::unordered_set<Point, Point_hash>;
// to store points according to circle they belong to
using Points_on_circles_t = std::unordered_map<Circle, std::vector<Point>, Circle_hash>;
// to store circles
using Circles_t = std::unordered_set<Circle, Circle_hash>;
// to store potentially colliding circles relatively to all arcs of certain circle
using Colliding_circles_with_arc_t = std::unordered_map<Circle, Circles_t, Circle_hash>;
// node type for graph
using Vertex_t = Point;
// hashing node
using Vertex_t_hash = Point_hash;
// to store neighbors for the node in the graph with the cost (distance) of the edges
using Vertices_t = std::unordered_multimap<Vertex_t, Length_t, Vertex_t_hash>;
// to store shortest distances - for Dijkstra algorithm
using Distances_t = std::unordered_map<Vertex_t, Length_t, Vertex_t_hash>;;
// to store graph - for Dijkstra algorithm
using Graph_t = std::unordered_map<Vertex_t, Vertices_t, Vertex_t_hash>;
// to store vertex and its distance in priority queue for Dijkstra algorithm
using Pair_vertex_distance_t = std::pair<Vertex_t, Length_t>;
// queue - it is needed for Dijkstra algorithm (breadth first search)
using Queue_t = std::priority_queue<Pair_vertex_distance_t, std::vector<Pair_vertex_distance_t>, Greater_pair_vertex_distance>;


// Types ===============================================================================

// compares two double number with certain epsilon
bool are_equal(Length_t a, Length_t b, Length_t epsilon = g_epsilon) {
	return a > b ? a - b < epsilon : b - a < epsilon;
}

// computes hash for double. This is needed for data structures
struct Double_hash {
	std::size_t operator()(Length_t obj) const noexcept {
		// completely wrong, but it only creates more nodes in graph
		return std::hash<Length_t>{}(obj);
	}
	static std::size_t call(Length_t obj) noexcept {
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
Length_t get_distance(const Point& p1, const Point& p2) {
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
	Length_t m_length;
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
Angle_t get_angle_with_x_axis(const Point& left_side, const Point& center) {
	if (are_equal(left_side.x, center.x)) {
		if (left_side.y < center.y)
			return 3.0 * g_pi / 2.0;
		return g_pi / 2.0;
	}

	const Angle_t angle = atan((left_side.y - center.y) / (left_side.x - center.x));

	if (left_side.x < center.x)
		return angle + g_pi;

	if (left_side.y < center.y)
		return angle + 2.0 * g_pi;

	return angle;
}

// returns the length of arc
Length_t get_arc_length(const Point& a, const Point& b, const Circle& circle) {

	const Angle_t angle_a = get_angle_with_x_axis(a, circle.ctr);
	const Angle_t angle_b = get_angle_with_x_axis(b, circle.ctr);

	// angles from 0 to 2*pi are considered
	const Angle_t delta_angle =
		angle_a > angle_b ? angle_a - angle_b :
		2.0 * g_pi + angle_a - angle_b;

	return circle.r * delta_angle;
}

// arc on the circle. 
// Consists of two points. Also has length and includes its owner (circle)
struct Arc {
	Point m_a;
	Point m_b;
	Length_t m_length;
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

// prototype for compare class for priority queue for Dijkstra algorithm
struct Greater_pair_vertex_distance;


// compare class for priority queue for Dijkstra algorithm
struct Greater_pair_vertex_distance {
	bool operator()(const Pair_vertex_distance_t& left, const Pair_vertex_distance_t& right) const noexcept {
		return left.second > right.second;
	}
};
// to store interval of doubles in hash table
struct Pair_x_interval_hash {
	std::size_t operator()(const Pair_x_interval& obj) const noexcept {
		const std::size_t x = Double_hash::call(obj.first);
		const std::size_t y = Double_hash::call(obj.second);
		return (x + y) * (x + y + 1) / 2 + y;							        // Cantor's pair
	}
	static std::size_t call(const Pair_x_interval& obj) noexcept {
		static const Pair_x_interval_hash instance;								// singleton
		return instance(obj);
	}
};


// 3 data structures:
// 1 - all circles sorted by their left end
// 2 - all x-coordinates where each of the circles starts or ends - sorted
// 3 - all intervals on x-axis with circles covering each interval - sorted
// All of these is needed to filter tangents faster - this reduces the amount of 
// cirlces to be considered as potentially colliding ones with tangent
struct Filter_tangent_tools {
	std::vector<Circle> m_circles_sorted_by_left_point_x;
	std::vector<Coordinate_t> m_ranges_x_sorted;
	std::unordered_map<Pair_x_interval, Circles_t, Pair_x_interval_hash> m_circles_on_ranges;

	Filter_tangent_tools() {}
};

// Logic to build a graph ==============================================================

// returns true if (x_1 <= a <= x_2) or (x_2 <= a <= x_1) 
bool is_between(Length_t a, Length_t x_1, Length_t x_2) {
	return (x_1 < a && a < x_2) ||
		   (x_2 < a && a < x_1) ||
		   are_equal(a, x_1) ||
		   are_equal(a, x_2);
}

// returns distance between the center of the circle and the line tangent lays on
Length_t get_distance(const Circle& circle, const Tangent& tangent) {
	// see distance between point and line
	const Length_t numerator = std::abs(
		(tangent.m_b.x - tangent.m_a.x) * (tangent.m_a.y - circle.ctr.y) -
		(tangent.m_a.x - circle.ctr.x) * (tangent.m_b.y - tangent.m_a.y)
	);
	const Length_t distance = get_distance(tangent.m_a, tangent.m_b);

	return numerator / distance;
}

// returns true if the projection of point on the line(point_1, point_2) lays between point_1 and point_2
bool is_point_between_points(const Point& point, const Point& point_1, const Point& point_2) {
	if (are_equal(point_1.x, point_2.x))
		return is_between(point.y, point_1.y, point_2.y);

	const Length_t distance = get_distance(point_1, point_2);

	const double k = ((point_2.y - point_1.y) * (point.x - point_1.x) -
		(point_2.x - point_1.x) * (point.y - point_1.y)) /
		(distance * distance);

	const Coordinate_t x_n = point.x - k * (point_2.y - point_1.y);

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

// returns true if at least one circle from the group covers tangent or its part
bool there_is_collision_between_tangent_and_group_of_circles(const Tangent& tangent, const std::vector<Circle>& circles) {
	for (const auto& circle : circles) {
		if (circle != *tangent.m_circle_a && circle != *tangent.m_circle_b) {
			if (there_is_collision_between_tangent_and_circle(tangent, circle))
				return true;
		}
	}
	return false;
}

// returns true if at least one circle from the group covers tangent or its part
bool there_is_collision_between_tangent_and_group_of_circles(
	const Tangent& tangent,
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

// returns true if at least one circle from the group covers tangent or its part
bool there_is_collision_between_tangent_and_group_of_circles(const Tangent& tangent, const Circles_t& circles) {
	for (const auto& circle : circles) {
		if (circle != *tangent.m_circle_a && circle != *tangent.m_circle_b) {
			if (there_is_collision_between_tangent_and_circle(tangent, circle))
				return true;
		}
	}
	return false;
}

// returns pair of values between which target value is
Pair_x_interval get_interval(Coordinate_t value_to_find, const std::vector<Coordinate_t>& sorted_values) {
	const auto right = std::upper_bound(
		sorted_values.cbegin(),
		sorted_values.cend(),
		value_to_find,
		[](Coordinate_t value_to_find, Coordinate_t value) {
			return value > value_to_find || are_equal(value, value_to_find);
		}
	);
	const auto left =
		(right == sorted_values.cbegin()) ?
		sorted_values.cbegin() :
		right - 1u;

	return Pair_x_interval(*left, *right);
}

using Pair_circle_interval = std::pair<std::vector<Circle>::const_iterator, std::vector<Circle>::const_iterator>;


// returns pair of circles (iterators) of sorted vector of circles.
// The first circle has x-coordinate of its left side smaller, than value, 
// the second circle has x-coordinate of its left side not greater, than value
Pair_circle_interval get_interval(Coordinate_t value_to_find, const std::vector<Circle>& sorted_circles) {
	const auto right = std::upper_bound(
		sorted_circles.cbegin(),
		sorted_circles.cend(),
		value_to_find,
		[](Coordinate_t value_to_find, const Circle& circle) {
			return  (value_to_find < circle.ctr.x - circle.r)  ||
				are_equal(circle.ctr.x - circle.r, value_to_find);
		}
	);
	const auto left =
		(right == sorted_circles.cbegin()) ?
		sorted_circles.cbegin() :
		right - 1u;

	return Pair_circle_interval(left, right);
}

// returns three data structures for fast tangent filtering
Filter_tangent_tools get_filter_tangents_tools(const std::vector<Circle>& circles) {
	


	// vector with circles, but all circles are sorted
	// by their left side. For example, the first circle is circle
	// with the smallest coordinate of its left side, the smallest (center - radius)
	std::vector<Circle> circles_sorted_by_left_end = [&]()->std::vector<Circle> {
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

	// sorted vector with x coordinates, where each circle x-projection starts or ends
	// every two consequetive values is an x-coordinate interval with 
	// the same amount of x-projection of circles 
	std::vector<Coordinate_t> ranges_x_sorted = [&]()->std::vector<Coordinate_t> {
		std::vector<Coordinate_t> local_copy;
		local_copy.reserve(circles.size() * 2u);
		for (const auto& circle : circles) {
			local_copy.push_back(circle.ctr.x - circle.r);
			local_copy.push_back(circle.ctr.x + circle.r);
		}
		std::sort(
			local_copy.begin(),
			local_copy.end(),
			[](Coordinate_t x_1, Coordinate_t x_2)->bool {
				return x_1 < x_2;
			}
		);
		return local_copy;
	}();

	// contains all circles for each interval of x-coordinate
	std::unordered_map<Pair_x_interval, Circles_t, Pair_x_interval_hash> circles_on_ranges_x;
	circles_on_ranges_x.reserve(circles.size() * 2u - 1u);
	for (auto x = ranges_x_sorted.cbegin(); x < ranges_x_sorted.cend() - 1u; ++x) {
		const Coordinate_t left  = *x;
		const Coordinate_t right = *(x + 1);
		const Pair_x_interval range(left, right);
		circles_on_ranges_x.insert(std::make_pair(range, Circles_t()));

		for (const auto& circle : circles) {
			const Coordinate_t left_part  = circle.ctr.x - circle.r;
			const Coordinate_t right_part = circle.ctr.x + circle.r;
			if ((left_part < right || are_equal(left_part, right)) &&
				(right_part > left || are_equal(right_part, left)))
				circles_on_ranges_x.at(range).insert(circle);
		}
	}
	circles_on_ranges_x.insert(std::make_pair(std::make_pair(*ranges_x_sorted.cbegin(), *ranges_x_sorted.cbegin()), Circles_t()));

	Filter_tangent_tools tools;
	tools.m_circles_sorted_by_left_point_x = std::move(circles_sorted_by_left_end);
	tools.m_ranges_x_sorted				   = std::move(ranges_x_sorted);
	tools.m_circles_on_ranges			   = std::move(circles_on_ranges_x);

	return tools;
}


// returns true if arc can not exist because circle covers it (or its part)
bool there_is_collision_between_arc_and_circle(const Arc& arc, const Circle& circle) {

	const Length_t distance = get_distance(arc.m_owner->ctr, circle.ctr);


	if (distance > arc.m_owner->r + circle.r ||               // arc and circle not intersect 
		arc.m_owner->r > distance + circle.r ||               // circle is deep inside arc and does not touch arc 
		are_equal(arc.m_owner->r, distance + circle.r))       // circle is inside arc, but touches it
		return false;


	// circle covers circumference of arc's owner -> there might be collision

	const Angle_t angle_b = get_angle_with_x_axis(arc.m_b, arc.m_owner->ctr);
	const Angle_t angle = get_angle_with_x_axis(circle.ctr, arc.m_owner->ctr);
	const Angle_t angle_a = get_angle_with_x_axis(arc.m_a, arc.m_owner->ctr);

	// considering angles only from 0 to 2*pi
	const Angle_t angle_a_rotated = angle_a > angle_b ?
		angle_a - angle_b : 2.0 * g_pi + angle_a - angle_b;
	const Angle_t angle_b_rotated = 0.0;
	const Angle_t angle_rotated = angle > angle_b ?
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

// returns all possible tangents between these two circles
Tangents_t get_tangents(const Circle& circle_1, const Circle& circle_2) {

	// circles have common center - no tangents
	if (circle_1.ctr == circle_2.ctr)
		return {};

	// one circle is inside another one or have only one common point - no tangents
	const Length_t distance_between_circles = get_distance(circle_1.ctr, circle_2.ctr);
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

	const Length_t r_a = circle_a.r;
	const Length_t r_b = circle_b.r;
	const Coordinate_t xo_a = circle_a.ctr.x;
	const Coordinate_t yo_a = circle_a.ctr.y;
	const Coordinate_t xo_b = circle_b.ctr.x;
	const Coordinate_t yo_b = circle_b.ctr.y;


	const Angle_t angle_sum_outer = std::asin((r_b - r_a) / distance_between_circles) +
		std::asin((xo_b - xo_a) / distance_between_circles);
	const Angle_t angle_subtraction_outer = std::asin((r_b - r_a) / distance_between_circles) -
		std::asin((xo_b - xo_a) / distance_between_circles);
	const Angle_t angle_sum_inner = std::asin((-r_b - r_a) / distance_between_circles) +
		std::asin((xo_b - xo_a) / distance_between_circles);
	const Angle_t angle_subtraction_inner = std::asin((-r_b - r_a) / distance_between_circles) -
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
	tangents.emplace_back(A_outer_1, B_outer_1, circle_a, circle_b);


	const Point A_outer_2(
		xo_a - r_a * std::cos(angle_subtraction_outer),
		yo_a - r_a * std::sin(angle_subtraction_outer)
	);
	const Point B_outer_2(
		xo_b - r_b * std::cos(angle_subtraction_outer),
		yo_b - r_b * std::sin(angle_subtraction_outer)
	);
	tangents.emplace_back(A_outer_2, B_outer_2, circle_a, circle_b);
	

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
	tangents.emplace_back(A_inner_1, B_inner_1, circle_a, circle_b);


	const Point A_inner_2(
		xo_a - r_a * std::cos(angle_subtraction_inner),
		yo_a - r_a * std::sin(angle_subtraction_inner)
	);
	const Point B_inner_2(
		xo_b + r_b * std::cos(angle_subtraction_inner),
		yo_b + r_b * std::sin(angle_subtraction_inner)
	);
	tangents.emplace_back(A_inner_2, B_inner_2, circle_a, circle_b);


	return tangents;
}


// returns true if tangent is covered by some circle. 
// Decides which circles should be considered using 'tools'.
// This is the logic of filtering tangent faster 
// than just using brute force method
bool is_tangent_existing(
	const Tangent& tangent, 
	const Filter_tangent_tools& tools
) {

	const Coordinate_t left_end_of_tangent =
		(tangent.m_a.x < tangent.m_b.x) ?
		 tangent.m_a.x :
		 tangent.m_b.x;

	const Coordinate_t right_end_of_tangent =
		(tangent.m_a.x > tangent.m_b.x) ?
		 tangent.m_a.x :
		 tangent.m_b.x; 

	const auto begin_for_circles_to_consider = get_interval(
		left_end_of_tangent, 
		tools.m_circles_sorted_by_left_point_x
	).first;

	const auto end_for_circles_to_consider = get_interval(
		right_end_of_tangent, 
		tools.m_circles_sorted_by_left_point_x
	).second;

	if (
		there_is_collision_between_tangent_and_group_of_circles(
			tangent, 
			begin_for_circles_to_consider, 
			end_for_circles_to_consider
		)
	)
		return false;
		
	const auto interval_for_circles_covering_left_end = get_interval(
		left_end_of_tangent, 
		tools.m_ranges_x_sorted
	);

	const Circles_t& circles_covering_left_end = 
		tools.m_circles_on_ranges.at(interval_for_circles_covering_left_end);

	if (
		there_is_collision_between_tangent_and_group_of_circles(
			tangent, 
			circles_covering_left_end
		)
	)
		return false;

	return true;
}

// adds one tangent to graph
void add_tangent_to_graph(const Tangent& tangent, Graph_t& graph) {
	if (graph.find(tangent.m_a) == graph.cend())
		graph.emplace(std::make_pair(tangent.m_a, Vertices_t()));
	graph.at(tangent.m_a).emplace(std::make_pair(tangent.m_b, tangent.m_length));

	if (graph.find(tangent.m_b) == graph.cend())
		graph.emplace(std::make_pair(tangent.m_b, Vertices_t()));
	graph.at(tangent.m_b).emplace(std::make_pair(tangent.m_a, tangent.m_length));
}

// adds both ends of tangent to storage where all points have its own circle as a key
void add_tangent_to_points_on_circles(const Tangent& tangent, Points_on_circles_t& points_on_circles) {
	points_on_circles.at(*tangent.m_circle_a).push_back(tangent.m_a);
	points_on_circles.at(*tangent.m_circle_b).push_back(tangent.m_b);
}

// creates all arcs between this point and all other points on this circle,
// filters all arcs (removes arcs which are covered by other circles) 
// and adds to graph 
void create_arcs_for_this_point_filter_and_add_to_graph(
	Graph_t& graph,
	const Point& point,
	const Circle& circle,
	const Points_on_circles_t& points_on_circles,
	const Colliding_circles_with_arc_t& colliding_circles
) {
	for (auto another_point = points_on_circles.at(circle).cbegin();
		 another_point != points_on_circles.at(circle).cend();
		 ++another_point
		) {

		if (Point_hash::call(*another_point) != Point_hash::call(point)) {

			bool is_arc_existing{ true };
			const Arc ab(*another_point, point, circle);
			for (const auto& colliding_circle : colliding_circles.at(circle)) {
				if (there_is_collision_between_arc_and_circle(ab, colliding_circle)) {
					is_arc_existing = false;
					break;
				}
			}

			if (is_arc_existing) {
				graph.at(ab.m_a).emplace(std::make_pair(ab.m_b, ab.m_length));
				graph.at(ab.m_b).emplace(std::make_pair(ab.m_a, ab.m_length));
			}

			is_arc_existing = true;
			const Arc ba(point, *another_point, circle);
			for (const auto& colliding_circle : colliding_circles.at(circle)) {
				if (there_is_collision_between_arc_and_circle(ba, colliding_circle)) {
					is_arc_existing = false;
					break;
				}
			}

			if (is_arc_existing) {
				graph.at(ba.m_a).emplace(std::make_pair(ba.m_b, ba.m_length));
				graph.at(ba.m_b).emplace(std::make_pair(ba.m_a, ba.m_length));
			}
		}
	}
}

// adds to graph all tangents and arcs which can exist between these two circles
void create_tangents_filter_add_to_graph_create_arcs_filter_add_to_graph_for_this_pair_of_circles(
	const Circle& circle_1,
	const Circle& circle_2,
	const Filter_tangent_tools& tools,
	const Colliding_circles_with_arc_t& colliding_circles_with_arc,
	Points_on_circles_t& points_on_circles,
	Graph_t& graph
) {
	const auto tangents = get_tangents(circle_1, circle_2);

	for (auto tangent = tangents.cbegin(); tangent != tangents.cend(); ++tangent) {
		if (is_tangent_existing(*tangent, tools)) {
			add_tangent_to_graph(
				*tangent, 
				graph
			);
			add_tangent_to_points_on_circles(
				*tangent, 
				points_on_circles
			);
			create_arcs_for_this_point_filter_and_add_to_graph(
				graph,
				tangent->m_a,
				*tangent->m_circle_a,
				points_on_circles,
				colliding_circles_with_arc
			);

			create_arcs_for_this_point_filter_and_add_to_graph(
				graph,
				tangent->m_b,
				*tangent->m_circle_b,
				points_on_circles,
				colliding_circles_with_arc
			);

		}
	}
}

// returns vector of circles with added start and finish points as circles with zero radius
std::vector<Circle> add_start_and_finish_to_circles(const Point& a, const Point& b, const std::vector<Circle>& circles) {
	auto local_copy = circles;
	local_copy.emplace_back(a, 0.0);
	local_copy.emplace_back(b, 0.0);
	return local_copy;
}

// returns hash table with empty vectors of points with circle as a key
Points_on_circles_t get_points_on_circles(const std::vector<Circle>& circles) {
	Points_on_circles_t points_on_circles;

	for (const auto& circle : circles) {
		points_on_circles.emplace(std::make_pair(circle, std::vector<Point>()));
		points_on_circles.at(circle).reserve(4u * circles.size());
	}

	return points_on_circles;
}

// returns graph for this entire task
Graph_t get_graph(const Point& a, const Point& b, const std::vector <Circle>& circles) {
	
	// for each circle gathers covering it circles - needed to filter arcs faster
	// This reduces the amount of circles to be considered as potentially colliding with arc
	const auto colliding_circles_with_each_circle = get_colliding_circles_with_arc(circles);
	
	// to filter tangents faster
	const auto tools_to_filter_tangents_faster = get_filter_tangents_tools(circles);
	
	// graph
	Graph_t graph;

	// all circles with start and finish points as circles with zero radius
	const auto circles_copy = add_start_and_finish_to_circles(a, b, circles);
	
	// all points binded to their own circles
	// It is needed to generate arcs on each circle
	auto points_on_circles = get_points_on_circles(circles_copy);

	// considering every two circles (including start and finish points)
	// finding all tangents between every two of them, filtering tangents,
	// finding all arcs for each circle, filtering arcs, then adding tangents
	// and arcs to graph
	for (auto circle_1 = circles_copy.cbegin(); circle_1 != circles_copy.cend(); ++circle_1) {
		for (auto circle_2 = circle_1 + 1u; circle_2 != circles_copy.cend(); ++circle_2) {
			create_tangents_filter_add_to_graph_create_arcs_filter_add_to_graph_for_this_pair_of_circles(
				*circle_1,
				*circle_2,
				tools_to_filter_tangents_faster,
				colliding_circles_with_each_circle,
				points_on_circles,
				graph
			);
		}
	}

		
	return graph;
}

// Logic to find the shortest path =====================================================

// calculates distance which can not be exceeded during passing through this graph 
Length_t get_unreachable_maximum(const Graph_t& graph) {
	Length_t maximum = 0.0;
	for (const auto& [vertex, neighbors] : graph)
		for (const auto& [neighbor, distance] : neighbors)
			maximum += distance;

	return maximum * 10.0;
}

// dijkstra algorithm
Length_t dijkstra_tiptoe_priority_queue(const Graph_t& graph, const Vertex_t& start, const Vertex_t& finish) {
	// modification for this particular task: 
	// if there is no tangent to start and/or finish point(s), 
	// it is (they are) not included in the graph 
	if (graph.find(start) == graph.cend() || graph.find(finish) == graph.cend())
		return -1.0;

	const Length_t maximum = get_unreachable_maximum(graph);

	Distances_t distances;
	for (const auto& [vertex, _] : graph)
		distances.insert(std::pair<Vertex_t, Length_t>(vertex, maximum));

	distances.at(start) = 0.0;

	Queue_t queue;
	queue.push(std::make_pair(start, 0.0));

	while (!queue.empty()) {
		const auto vertex = queue.top();
		queue.pop();

		for (const auto& [neighbor, edge_weight] : graph.at(vertex.first)) {
			if (distances.at(vertex.first) + edge_weight < distances.at(neighbor)) {
				distances.at(neighbor) = distances.at(vertex.first) + edge_weight;
				queue.push(std::make_pair(neighbor, distances.at(neighbor)));
			}
		}
	}
	return are_equal(distances.at(finish), maximum) ? -1.0 : distances.at(finish);
}


Length_t tiptoe_through_the_circles(Point a, Point b, const std::vector<Circle>& circles) {
	if (!circles.size())
		return get_distance(a, b);
	Timer timer;
	const auto graph = get_graph(a, b, circles);
	g_graph += timer.elapsed();
	std::cout << "graph = \t\t" << timer.elapsed() << '\n';
	timer.reset();
	const Length_t result = dijkstra_tiptoe_priority_queue(graph, a, b);  // 3.00 c, 2.92 c, 2.64 c, 2.24 c, 2.43 c
	g_dijkstra += timer.elapsed();
	std::cout << "dijkstra = \t\t" << timer.elapsed() << '\n';
	return result;
}

void test_tiptoe_through_the_circles(double (*algorithm)(Point, Point, const std::vector<Circle>&), bool medium_tests = true, bool big_tests = true) {
	std::cout << "test_tiptoe_through_the_circles:\n";
	std::cout << std::setprecision(16);
	bool verbose = false;
	Timer timer;

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

	timer.reset();
	result_actual = algorithm(a1, b1, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

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

	timer.reset();
	result_actual = algorithm(a2, b2, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


	std::cout << "test  #2: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	Point a3(3.0, 0.0);
	Point b3(0.0, 4.0);
	result_expected = 5.0;

	timer.reset();
	result_actual = algorithm(a3, b3, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


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

	timer.reset();
	result_actual = algorithm(a4, b4, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


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

	timer.reset();
	result_actual = algorithm(a5, b5, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';

	std::cout << "test  #5: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();

	if (medium_tests) {

	Point a101(-2.000298425089568, 3.749468164518476);
	Point b101(3.086806660052389, -0.3613790776580572);
	{
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
	}
	result_expected = 11.92280589779663;

	timer.reset();
	result_actual = algorithm(a101, b101, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


	std::cout << "test #101: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a102(-3.407654467504472, 3.147248836234212);
	Point b102(2.705999904777855, 3.699559176340699);
	{
		circles.emplace_back(-1.30285874241963, 0.8287367434240878, 0.530179562070407);
		circles.emplace_back(0.2471824758686125, 0.7799994270317256, 0.6663304635090753);
		circles.emplace_back(-1.101479020435363, -4.487210686784238, 1.410582280461676);
		circles.emplace_back(3.88571459101513, -3.412391173187643, 0.6502192210173234);
		circles.emplace_back(4.726873098406941, -1.342303913552314, 1.657216931018047);
		circles.emplace_back(-1.269799352157861, -3.634526326786727, 0.973153028753586);
		circles.emplace_back(0.4688428458757699, -1.447940340731293, 1.362857049121521);
		circles.emplace_back(-4.142232874874026, 4.053193016443402, 1.090474483394064);
		circles.emplace_back(-0.665865947958082, -0.5710750375874341, 1.393810525978915);
		circles.emplace_back(-0.3010314446873963, 3.41557213338092, 0.6971190973417833);
		circles.emplace_back(0.7474921573884785, -0.1814590045250952, 0.866015613800846);
		circles.emplace_back(4.864786283578724, 3.911350185517222, 0.314354850933887);
		circles.emplace_back(1.462721249554306, -3.371791888494045, 1.037379816430621);
		circles.emplace_back(1.335364214610308, -4.874243072699755, 1.229946907353587);
		circles.emplace_back(-4.885504718404263, -0.3796107158996165, 0.8128225376596674);
		circles.emplace_back(0.8149511343799531, 2.465207225177437, 1.655936161824502);
		circles.emplace_back(1.745450051967055, -4.240099035669118, 0.4329816699726507);
		circles.emplace_back(-4.588022690732032, -3.351922880392522, 1.110670110140927);
		circles.emplace_back(-3.348182335030288, 0.3222733712755144, 1.126149553409777);
		circles.emplace_back(3.6525839404203, -3.75478619011119, 0.3934334217337891);
		circles.emplace_back(1.620937928091735, -3.810074597131461, 1.28613714587409);
		circles.emplace_back(-4.632382008712739, -2.361299640033394, 1.01725264058914);
		circles.emplace_back(1.363912706729025, -0.242021472658962, 1.483084296458401);
		circles.emplace_back(1.039441938046366, 1.396577029954642, 1.320589729840867);
		circles.emplace_back(0.9662505495361984, 2.610473644454032, 0.9059697396354749);
		circles.emplace_back(-0.398722521495074, -3.776384780649096, 1.646404349780641);
		circles.emplace_back(-2.431198118720204, 1.864345411304384, 1.154134194389917);
		circles.emplace_back(0.8307247818447649, 4.856850083451718, 1.160799118387513);
		circles.emplace_back(0.3084717760793865, 3.935077183414251, 0.9556073350133374);
		circles.emplace_back(-0.7161020743660629, -3.431405855808407, 0.9973933143308386);
		circles.emplace_back(1.377752122934908, -1.147998997475952, 0.9697838012361898);
		circles.emplace_back(3.029059844557196, -3.059125759173185, 0.9414152079029008);
		circles.emplace_back(-3.500768181402236, 1.475147877354175, 1.136812465195544);
		circles.emplace_back(0.7417685096152127, 4.147131664212793, 1.287765949568711);
		circles.emplace_back(2.605612331535667, 2.726441326085478, 0.4900807911762967);
		circles.emplace_back(-4.764735193457454, -0.6831309315748513, 0.5852376333205029);
		circles.emplace_back(3.543099730741233, -0.7590041006915271, 0.9550120615633204);
		circles.emplace_back(-2.269698667805642, -3.257478496525437, 1.286685339524411);
	}
	result_expected = 8.322402159494233;

	timer.reset();
	result_actual = algorithm(a102, b102, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


	std::cout << "test #102: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a103(-3.997427604626864, -1.515199078246951);
	Point b103(3.198281688150018, -3.065876862034202);
	{
		circles.emplace_back(3.557604493107647, 3.867830077651888, 1.030572976008989);
		circles.emplace_back(0.3106679976917803, 1.224292393308133, 1.620719462144188);
		circles.emplace_back(3.365572250913829, -1.614064283203334, 0.8567804944934323);
		circles.emplace_back(0.9754285705275834, 2.762684689369053, 1.323656560271047);
		circles.emplace_back(-2.325451376382262, -0.7308800308965147, 1.229702988662757);
		circles.emplace_back(4.640441599767655, 2.783511255402118, 1.209928478603251);
		circles.emplace_back(-4.860883622895926, 4.509994906838983, 0.8191822316264733);
		circles.emplace_back(2.104613536503166, -3.114207384642214, 0.6794940257677808);
		circles.emplace_back(1.453441588673741, 1.047918784897774, 1.498832579585724);
		circles.emplace_back(4.889070063363761, 0.7866096054203808, 0.8136321776779368);
		circles.emplace_back(0.4971474525518715, 0.1595791964791715, 0.9921046027680859);
		circles.emplace_back(3.100865294691175, 1.710938645992428, 1.554040239774622);
		circles.emplace_back(2.177390793804079, 3.555218770634383, 0.5587449659360573);
		circles.emplace_back(0.9745319443754852, 4.87836503656581, 0.584624522854574);
		circles.emplace_back(-2.51545489532873, 2.131190632935613, 0.7320754967397078);
		circles.emplace_back(-2.91006131330505, -1.824561392422765, 0.8878201520303264);
		circles.emplace_back(-0.0245307176373899, -0.06309976102784276, 1.473306463914923);
		circles.emplace_back(-3.294679143000394, -2.33975627226755, 0.5851729606511071);
		circles.emplace_back(2.127076659817249, -3.471106796059757, 1.039518678723834);
		circles.emplace_back(-0.808675664011389, 2.676039135549217, 1.477393430122174);
		circles.emplace_back(-1.577002701815218, 0.1705852220766246, 0.7247626618249341);
		circles.emplace_back(1.891746211331338, -1.293708186130971, 0.9340535740600898);
		circles.emplace_back(2.329095259774476, -4.66777608031407, 1.306965305260382);
		circles.emplace_back(-0.07975043961778283, 0.9276478760875762, 1.07899610272143);
		circles.emplace_back(2.575321330223233, -4.96448376448825, 1.348764146747999);
		circles.emplace_back(3.179673447739333, 0.460352182853967, 0.7118611411424354);
		circles.emplace_back(4.141850408632308, -4.479051327798516, 1.245506560965441);
		circles.emplace_back(1.011652981396765, -2.672652842011303, 1.136409211927093);
		circles.emplace_back(-0.203328465577215, 1.243171512614936, 1.175955860014073);
		circles.emplace_back(-2.300232730340213, -3.929088155273348, 0.7782384827500208);
		circles.emplace_back(-1.774262094404548, -4.467276011127979, 1.232746140169911);
		circles.emplace_back(4.765123135875911, 1.400947116781026, 1.102941637975164);
		circles.emplace_back(-2.487805287819356, -1.241520328912884, 1.072573971538804);
		circles.emplace_back(-1.388290675822645, -1.663666644599289, 0.8356419522548094);
		circles.emplace_back(-4.934534800704569, 1.168844036292285, 0.5481304534478113);
		circles.emplace_back(-1.331368770916015, -1.749335105996579, 0.5924912515329197);
		circles.emplace_back(-3.201877891551703, 3.711077345069498, 0.4332969914888963);
	}
	result_expected = 15.30354281541973;

	timer.reset();
	result_actual = algorithm(a103, b103, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #103: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a104(-2.709975998383015, -2.927324889227748);
	Point b104(3.553547830786556, 0.887513155117631);
	{
		circles.emplace_back(-2.950063014868647, 1.884566603694111, 0.7483262516791001);
		circles.emplace_back(4.066753948573023, 4.994499206077307, 0.7857669603778049);
		circles.emplace_back(-3.496747396420687, -3.7948301830329, 1.028303389227949);
		circles.emplace_back(4.439268202986568, -0.881743838544935, 0.8674092678586021);
		circles.emplace_back(-0.6081845401786268, -0.09549257578328252, 1.189688349771313);
		circles.emplace_back(0.4560813377611339, -2.976281202863902, 1.259551885467954);
		circles.emplace_back(1.828885574359447, 1.633974330034107, 1.318896803050302);
		circles.emplace_back(4.642659353557974, 1.222652427386492, 0.4448513247771188);
		circles.emplace_back(-0.8169213798828423, 2.31358302058652, 0.7574518236564471);
		circles.emplace_back(-2.282275080215186, -4.900783228222281, 1.229359040758572);
		circles.emplace_back(-0.754333829972893, 4.80168596142903, 1.937195614934899);
		circles.emplace_back(-4.154334843624383, -2.252448096405715, 0.8445095428498461);
		circles.emplace_back(-3.59642370371148, 2.991978952195495, 0.8343890750547871);
		circles.emplace_back(3.980647881980985, -3.499987141694874, 1.034540772461332);
		circles.emplace_back(-0.8793349168263376, -0.8813574467785656, 0.6480490271700545);
		circles.emplace_back(-3.034271274227649, 4.742475536186248, 1.672473843325861);
		circles.emplace_back(-3.906930543016642, 0.3742258599959314, 0.7806028403108939);
		circles.emplace_back(-1.410101933870465, 3.506097311619669, 0.7869696190813555);
		circles.emplace_back(0.8640920440666378, -3.164510957431048, 0.7770069469930604);
		circles.emplace_back(-1.008218701463193, -3.919875978026539, 0.8524389942875131);
		circles.emplace_back(-3.090661989990622, 3.19630021462217, 1.027961988397874);
		circles.emplace_back(-4.701415447052568, 0.9079258213751018, 1.132606390188448);
		circles.emplace_back(-0.6268407520838082, 3.569510628003627, 1.152721118484624);
		circles.emplace_back(-2.876672341953963, 1.313453612383455, 1.536306867352687);
		circles.emplace_back(-4.553983679506928, 4.501471596304327, 1.094521731347777);
		circles.emplace_back(-2.645026759710163, 2.345773342531174, 0.2747199862031266);
		circles.emplace_back(3.826906129252166, -4.078291624318808, 1.047551223752089);
		circles.emplace_back(0.6289238599129021, -2.321385687682778, 1.254851599200629);
		circles.emplace_back(0.6083335331641138, -1.947785706724972, 0.4066078685456886);
		circles.emplace_back(-4.544567649718374, -2.635457545984536, 1.740445029432885);
		circles.emplace_back(3.765714119654149, -2.037564206402749, 1.985838226159103);
		circles.emplace_back(-1.765085987281054, -4.417275080922991, 0.4932114630704745);
		circles.emplace_back(3.494860471691936, 3.023366371635348, 1.186214180127718);
		circles.emplace_back(2.62451613554731, 2.284094567876309, 1.154218422877602);
		circles.emplace_back(1.793548024725169, 4.432136111427099, 1.179498620075174);
		circles.emplace_back(4.575769056100398, -1.053683294449002, 0.589142377465032);
	}
	result_expected = 7.334158457725674;

	timer.reset();
	result_actual = algorithm(a104, b104, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';


	std::cout << "test #104: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a105(-3.635850071441382, -1.707838160917163);
	Point b105(3.225729187484831, -3.731068959459662);
	{
		circles.emplace_back(-2.172349265310913, -4.312638265546411, 1.62847022137139);
		circles.emplace_back(-3.251324312295765, 3.024977508466691, 1.006659239414148);
		circles.emplace_back(3.637937649618834, 4.060053557623178, 0.8732667149277403);
		circles.emplace_back(4.811804678756744, 4.428744667675346, 0.4516330526908859);
		circles.emplace_back(4.416278486605734, 1.352452842984349, 0.714944051974453);
		circles.emplace_back(-1.22567999875173, 2.559542327653617, 1.142633220250718);
		circles.emplace_back(-2.177871100138873, 0.7937727472744882, 1.045165789104067);
		circles.emplace_back(3.344518186058849, 3.993602136615664, 0.4264995498815551);
		circles.emplace_back(0.921063965652138, -0.5790386837907135, 1.156766482698731);
		circles.emplace_back(0.1134811411611736, 0.4602193762548268, 0.7278252524556592);
		circles.emplace_back(4.993396101053804, 2.318652442190796, 0.866486543812789);
		circles.emplace_back(2.595831828657538, 0.3986851195804775, 1.002486866037361);
		circles.emplace_back(3.329654696863145, 0.2089616400189698, 1.085207979683764);
		circles.emplace_back(0.2665597503073514, -4.376659172121435, 1.248254531226121);
		circles.emplace_back(-4.269504493568093, -2.887603340204805, 0.8081363016972318);
		circles.emplace_back(-3.727511854376644, 2.229292679112405, 0.8958557239500805);
		circles.emplace_back(1.403461408335716, 1.856387832667679, 0.899793473794125);
		circles.emplace_back(-4.312943706754595, -2.758783565368503, 1.210711433016695);
		circles.emplace_back(-3.788679798599333, -4.44476853357628, 0.7298135299934074);
		circles.emplace_back(2.303906555753201, 0.1294856634922326, 1.049753972818144);
		circles.emplace_back(1.065239182207733, -0.9015985322184861, 1.010105170565657);
		circles.emplace_back(3.794587932061404, -0.0316125969402492, 1.232426405441947);
		circles.emplace_back(-2.560433770995587, 0.03433564445003867, 1.590572742163204);
		circles.emplace_back(4.362058562692255, -4.262583756353706, 0.8871584382141008);
		circles.emplace_back(2.560200097505003, -2.513917081523687, 0.9597599253756924);
		circles.emplace_back(-1.18431092472747, 1.874940593261272, 1.037790907477029);
		circles.emplace_back(-3.289215608965605, -0.5597211443819106, 1.03949162249919);
		circles.emplace_back(1.100471892859787, 0.7013138406910002, 0.8913894849130883);
		circles.emplace_back(-2.562659548129886, 1.166707787197083, 0.9890011354116722);
		circles.emplace_back(1.123671128880233, -0.3434864873997867, 1.014716182765551);
		circles.emplace_back(-2.424579623620957, -4.67492381343618, 0.7381832631072029);
		circles.emplace_back(4.844337666872889, 1.852975010406226, 0.9774605584098025);
		circles.emplace_back(-3.246333498973399, -0.440637010615319, 0.8315434388117864);
	}
	result_expected = 7.153651710189512;

	timer.reset();
	result_actual = algorithm(a105, b105, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #105: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a106(-3.806075710337609, 1.89314285106957);
	Point b106(2.823465475346893, 0.6947441343218088);
	{
		circles.emplace_back(-1.487007515970618, -3.636514747049659, 1.378336590179242);
		circles.emplace_back(4.604606928769499, -0.9670934011228383, 1.337590606580488);
		circles.emplace_back(-0.6413868186064065, -3.263172011356801, 0.6536694864975288);
		circles.emplace_back(4.08762063132599, -0.6203083717264235, 1.570809294632636);
		circles.emplace_back(-4.718081376049668, 0.8639877312816679, 1.277732460410334);
		circles.emplace_back(1.611659659538418, 0.6839933129958808, 1.02595785993617);
		circles.emplace_back(-3.429730639327317, -4.764917611610144, 1.293171008047648);
		circles.emplace_back(-1.789634290616959, 4.580585265066475, 0.4211253763874993);
		circles.emplace_back(-1.278693641070276, 1.365974305663258, 0.8646221168572082);
		circles.emplace_back(2.421991492155939, -3.54448574827984, 0.562016074056737);
		circles.emplace_back(-3.170185287017375, -3.745377499144524, 0.9593169114785268);
		circles.emplace_back(4.690455116797239, 3.755388220306486, 1.017115278518759);
		circles.emplace_back(-1.716391651425511, -3.896268715616316, 0.8916572986403479);
		circles.emplace_back(-2.140160703565925, 4.71750172553584, 0.7185603062389418);
		circles.emplace_back(-1.898068182636052, 3.668581985402852, 1.433890634519048);
		circles.emplace_back(-3.679107513744384, -2.736895855050534, 0.5346276107477024);
		circles.emplace_back(1.118140399921685, 4.287933481391519, 0.2652485858416185);
		circles.emplace_back(-0.9775195480324328, -4.431587008293718, 1.13941081261728);
		circles.emplace_back(3.881567774806172, -4.873110812623054, 1.042913610371761);
		circles.emplace_back(-4.791327000129968, -0.8185662771575153, 1.06661907818634);
		circles.emplace_back(3.399634819943458, -2.502565255854279, 0.8702758067985996);
		circles.emplace_back(-3.652468065265566, -0.05714984377846122, 0.8956625730032101);
		circles.emplace_back(1.684219429735094, -4.26147933350876, 0.4190042947186157);
		circles.emplace_back(0.05791309056803584, 2.848477449733764, 0.8149268253939226);
		circles.emplace_back(2.254610501695424, -2.526281292084605, 1.782579440600239);
		circles.emplace_back(-0.7322466210462153, 4.369078690651804, 1.350699957297183);
		circles.emplace_back(-1.059887388255447, -3.286094118375331, 0.6479401203570887);
		circles.emplace_back(-1.082781322766095, 4.063333340454847, 1.137783875060268);
		circles.emplace_back(3.888888482470065, -3.910718022380024, 0.7647841801634058);
		circles.emplace_back(2.880052400287241, -0.8016869961284101, 0.8688743811333551);
		circles.emplace_back(2.583332213107497, 2.856716669630259, 1.456345337699167);
		circles.emplace_back(-0.3836916503496468, -1.052711259108037, 1.369756105099805);
		circles.emplace_back(0.7532451837323606, -2.941087109502405, 1.418256589979864);
		circles.emplace_back(-0.544276253785938, 2.926542225759476, 1.206182789686136);
		circles.emplace_back(-3.931496397126466, -1.565212875138968, 1.194239807245322);
		circles.emplace_back(2.41542198928073, -4.388786798808724, 0.4602720604976639);
	}
	result_expected = 7.627044361490151;

	timer.reset();
	result_actual = algorithm(a106, b106, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #106: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a107(-3.994156218599528, 3.651317762210965);
	Point b107(2.656247851904482, -0.3339756336063147);
	{
		circles.emplace_back(-4.961015267763287, -3.020499234553427, 1.156193189905025);
		circles.emplace_back(-3.460494556929916, 2.288062821608037, 1.342849821108393);
		circles.emplace_back(3.30658309860155, -1.929743520449847, 1.352735911798663);
		circles.emplace_back(3.598702971357852, -1.267938970122486, 0.7776984652271494);
		circles.emplace_back(0.8530579530633986, -2.440140985418111, 1.105056527326815);
		circles.emplace_back(-2.318604153115302, 4.945078541059047, 1.520960688148625);
		circles.emplace_back(4.555986330378801, 2.449849543627352, 1.041340431920253);
		circles.emplace_back(-2.293816080782562, -1.247918528970331, 1.337413972825743);
		circles.emplace_back(-2.863754348363727, 1.198901298921555, 1.21705346989911);
		circles.emplace_back(4.802035733591765, 2.71822813199833, 0.8757757635088637);
		circles.emplace_back(-1.186044726055115, -0.7187193096615374, 1.344755692942999);
		circles.emplace_back(0.1237120083533227, -3.160318227019161, 1.618283297889866);
		circles.emplace_back(4.65088170254603, 0.3372001345269382, 1.010443842108361);
		circles.emplace_back(0.2147435653023422, -1.620019364636391, 1.417986944993026);
		circles.emplace_back(-4.637374214362353, 1.029957642313093, 1.214000490284525);
		circles.emplace_back(3.204292596783489, -4.753993113990873, 0.9310709906974807);
		circles.emplace_back(0.3570672334171832, -0.8245236915536225, 0.6685512657044455);
		circles.emplace_back(3.623093522619456, 1.309451155830175, 1.10941307072062);
		circles.emplace_back(-1.681109319906682, 0.3566460474394262, 1.432436211197637);
		circles.emplace_back(2.730563280638307, -4.268121847417206, 1.64515471199993);
		circles.emplace_back(2.984236257616431, 3.137213669251651, 1.578556021372788);
		circles.emplace_back(-4.164985355455428, -1.043032433371991, 1.056516380910762);
		circles.emplace_back(-1.707513600122184, 0.2360611385665834, 0.4915960874175653);
		circles.emplace_back(2.522499912884086, 4.107723238412291, 1.462488874257542);
		circles.emplace_back(-3.386080653872341, -3.637444388587028, 0.8115609667031094);
		circles.emplace_back(3.737156062852591, 2.81941230641678, 1.150868826475926);
		circles.emplace_back(4.982428562361747, -3.402751407120377, 0.799669081880711);
		circles.emplace_back(-4.972983787301928, -2.199285195674747, 0.9368795439833775);
		circles.emplace_back(-4.038273950573057, -4.020454690326005, 1.277462141658179);
		circles.emplace_back(0.691416256595403, -4.914940858725458, 0.8694759629433975);
		circles.emplace_back(0.5460460693575442, 1.590209703426808, 0.6514990615425631);
		circles.emplace_back(3.08989443583414, -4.187778613995761, 1.538806894910522);
		circles.emplace_back(-0.5542949098162353, -2.119783072266728, 1.15781256610062);
		circles.emplace_back(4.731385929044336, -0.3345837234519422, 1.421376418718137);
		circles.emplace_back(-0.06903081899508834, 3.40898723108694, 0.9193596974713727);
		circles.emplace_back(-0.3905102727003396, 4.798762102145702, 0.9384848754154518);
		circles.emplace_back(1.4079489861615, 1.515481618698686, 1.878035243204795);
	}
	result_expected = -1;

	timer.reset();
	result_actual = algorithm(a107, b107, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #107: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a108(-3.842293019872159, 2.634805621579289);
	Point b108(2.948530243244022, -2.969537680968642);
	{
		circles.emplace_back(4.800060500856489, -2.769076095428318, 0.612027670466341);
		circles.emplace_back(2.143677512649447, 3.09743870748207, 1.144586207414977);
		circles.emplace_back(-0.1174558443017304, -2.729489270132035, 1.388914105226286);
		circles.emplace_back(4.037538461852819, 4.741430913563818, 0.7302489153807983);
		circles.emplace_back(3.447112904395908, 3.06453492725268, 1.265148527012206);
		circles.emplace_back(1.372100582811981, -2.968499262351543, 1.397312464076094);
		circles.emplace_back(-3.063152946997434, 2.316741265822202, 0.5088786368491128);
		circles.emplace_back(-3.651449109893292, 4.360161812510341, 0.9515042101731523);
		circles.emplace_back(0.5959581560455263, -2.854800724890083, 1.030221959599294);
		circles.emplace_back(0.41722476715222, 1.88856542808935, 0.5242541298968717);
		circles.emplace_back(-0.1987671968527138, 4.837727744597942, 0.6136385093675926);
		circles.emplace_back(2.434763864148408, -1.435959490481764, 1.440011637262069);
		circles.emplace_back(-1.967424473259598, -0.304118765052408, 0.7217969851801171);
		circles.emplace_back(-2.231765554752201, 2.560424122493714, 1.547646264615469);
		circles.emplace_back(0.8942719246260822, -1.407989680301398, 0.7925897703738882);
		circles.emplace_back(4.369155403692275, 4.74420984974131, 1.165419510169886);
		circles.emplace_back(-0.2803131588734686, -0.1243739738129079, 0.5312254466349259);
		circles.emplace_back(-2.710396086331457, 1.296885132323951, 0.8013198447180911);
		circles.emplace_back(-1.493043799418956, 3.995767694432288, 1.453038471122272);
		circles.emplace_back(-2.219464562367648, -0.5050775804556906, 1.227545057213865);
		circles.emplace_back(-2.008175163064152, 3.405292222741991, 0.8973041026154532);
		circles.emplace_back(-4.250826442148536, 4.6137327211909, 0.5970958064077422);
		circles.emplace_back(-0.6838735868223011, -2.269028581213206, 1.445432600122876);
		circles.emplace_back(3.707793850917369, 4.730483905877918, 0.8793114332249388);
		circles.emplace_back(0.746495274361223, -3.419997075106949, 0.3759401548886672);
		circles.emplace_back(-4.82955522602424, -2.396970160771161, 0.9472337760729714);
		circles.emplace_back(-2.012256172019988, -4.540991063695401, 1.211054954235442);
		circles.emplace_back(-0.5028827185742557, 3.548290205653757, 0.6604269187664613);
		circles.emplace_back(-4.431067204568535, -1.144184318836778, 1.993215213180519);
		circles.emplace_back(-2.803406359162182, 4.083264607470483, 1.339810488256626);
		circles.emplace_back(-2.692494571674615, -2.672724619042128, 1.211551947263069);
		circles.emplace_back(3.429674666840583, 1.775458285119385, 1.113681306852959);
		circles.emplace_back(1.72795053338632, 1.198111160192639, 0.7162226975196972);
		circles.emplace_back(1.653703341726214, -3.973159447778016, 1.213902891124599);
		circles.emplace_back(-2.723697100300342, 0.9562341240234673, 1.349673356045969);
		circles.emplace_back(-3.499284663703293, 0.7024105894379318, 1.43145093943458);
		circles.emplace_back(-0.09652691660448909, 4.979894401039928, 1.024272157787345);
	}
	result_expected = 17.9340243222033;

	timer.reset();
	result_actual = algorithm(a108, b108, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #108: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a109(-3.624325111042708, 0.3301214743405581);
	Point b109(2.534309422131628, -0.8213437106460333);
	{
		circles.emplace_back(0.1737918495200574, 1.353599282447249, 0.8211046288022771);
		circles.emplace_back(1.420561133418232, -4.932794135529548, 1.745380455884151);
		circles.emplace_back(-0.1875047688372433, -3.692304089199752, 1.333657399681397);
		circles.emplace_back(-1.217915553133935, -2.780239454004914, 1.183362578763626);
		circles.emplace_back(-4.472020009998232, 1.771241708192974, 0.8958710223669185);
		circles.emplace_back(-1.93344310624525, 4.470786636229604, 0.7795052475994453);
		circles.emplace_back(-1.951006634626538, -3.509446566458791, 0.9920243581989779);
		circles.emplace_back(-2.439732530619949, -3.915922094602138, 1.267377028125338);
		circles.emplace_back(0.2201833645813167, -1.107538871001452, 0.7801937480689958);
		circles.emplace_back(2.84212363185361, 3.612434805836529, 0.996934520243667);
		circles.emplace_back(-2.332276033703238, 4.798295742366463, 1.25741214568261);
		circles.emplace_back(0.6725956522859633, -0.02931400435045362, 1.195305484603159);
		circles.emplace_back(0.1150967064313591, -3.260517369490117, 1.162196114216931);
		circles.emplace_back(-1.912277236115187, 4.83408093219623, 0.9640152934705838);
		circles.emplace_back(-4.869277647230774, -3.772874695714563, 0.7295387240359559);
		circles.emplace_back(-4.859073178377002, 1.196784439962357, 1.482311439397745);
		circles.emplace_back(0.8455130900256336, 4.62644848274067, 0.5744968177052214);
		circles.emplace_back(-2.689951870124787, 3.120251649525017, 0.9978873358806595);
		circles.emplace_back(-0.4570777365006506, -0.236642153467983, 1.393121414654888);
		circles.emplace_back(4.354271406773478, -0.1356455986388028, 0.8949224021984263);
		circles.emplace_back(4.93155027506873, -0.5576842906884849, 0.7019959039287641);
		circles.emplace_back(-0.4264213959686458, -3.034776041749865, 0.6713476121192797);
		circles.emplace_back(-1.531041024718434, 4.753950575832278, 1.427295110956766);
		circles.emplace_back(-1.439915949013084, 1.288618620019406, 0.9914253736613318);
		circles.emplace_back(1.257690645288676, -3.03121269447729, 1.092364261788316);
		circles.emplace_back(-1.613923858385533, -1.603781415615231, 0.9935997945955023);
		circles.emplace_back(1.530581412371248, 0.7002033502794802, 1.376840305724181);
		circles.emplace_back(2.127052575815469, -4.75731291109696, 0.9267459627008064);
		circles.emplace_back(3.437658005859703, -1.874321398790926, 1.131809555948712);
		circles.emplace_back(-4.45585855981335, 4.873488831799477, 1.16254987034481);
		circles.emplace_back(4.574506252538413, 1.50629247771576, 0.9436147296102717);
		circles.emplace_back(0.706705164629966, 1.589192727115005, 1.209895489527844);
		circles.emplace_back(-2.609723696950823, -2.294159994926304, 0.9499273851746692);
		circles.emplace_back(3.557514587882906, -0.9335584496147931, 0.7839173634303733);
		circles.emplace_back(-4.934118513483554, 3.400663074571639, 1.263045862247236);
		circles.emplace_back(-1.857179112266749, -2.650614941958338, 1.512766116089187);
	}
	result_expected = 10.03281998056108;

	timer.reset();
	result_actual = algorithm(a109, b109, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #109: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a110(-3.957887265365571, -0.1224720757454634);
	Point b110(3.844673836138099, -0.7752236481755972);
	{
		circles.emplace_back(-1.023787858430296, 4.609296193812042, 1.000921175279655);
		circles.emplace_back(-3.473772031720728, 3.204521618317813, 1.403745111147873);
		circles.emplace_back(4.675325218122452, -4.256850506644696, 1.371446319227107);
		circles.emplace_back(-1.112776070367545, 2.193837685044855, 0.8023837413405999);
		circles.emplace_back(1.919966095592827, -4.210789201315492, 1.575252636731602);
		circles.emplace_back(-4.45762196322903, 0.6989294174127281, 0.590300395223312);
		circles.emplace_back(4.929418235551566, -4.419254704844207, 1.565798383322544);
		circles.emplace_back(-0.3428244474343956, 1.460260429885238, 0.5709864446660503);
		circles.emplace_back(-1.076654384378344, 1.272477938327938, 0.5980895802611484);
		circles.emplace_back(-2.231282850261778, -1.660742566455156, 0.7437057663453742);
		circles.emplace_back(1.796254094224423, -1.050222280900925, 1.562432074476965);
		circles.emplace_back(4.628667824435979, 4.005039667245001, 0.7953843138879164);
		circles.emplace_back(-0.8013699785806239, 2.836169565562159, 0.3065716600278392);
		circles.emplace_back(3.534181884024292, 2.983391981106251, 0.8168374585686251);
		circles.emplace_back(-4.985497810412198, -0.5106893996708095, 0.7624087845208123);
		circles.emplace_back(-0.8146217721514404, -4.875866083893925, 1.246728653251193);
		circles.emplace_back(1.471266967710108, 3.012286222074181, 1.204997801431455);
		circles.emplace_back(1.182158889714628, 3.195380873512477, 1.065207661758177);
		circles.emplace_back(1.457460212986916, -4.337449769955128, 0.9065016667591407);
		circles.emplace_back(1.566132560838014, -0.6907127820886672, 1.332418783358298);
		circles.emplace_back(3.807753303553909, 3.065051960293204, 0.8436714159557596);
		circles.emplace_back(-1.924876437988132, 1.973704907577485, 0.6824991895584389);
		circles.emplace_back(4.091794386040419, 2.279062152374536, 1.611755694565363);
		circles.emplace_back(4.758215483743697, 2.497784995939583, 0.9288046778878196);
		circles.emplace_back(2.564609681721777, 2.979928015265614, 1.628019053512253);
		circles.emplace_back(2.048497463110834, 0.006893097888678312, 0.6984048348618671);
		circles.emplace_back(1.151123445015401, -4.252543288748711, 1.011758657475002);
		circles.emplace_back(-1.941350183915347, 2.19330366468057, 1.280881787813269);
		circles.emplace_back(-3.604051081929356, -4.348154773470014, 1.342357492283918);
		circles.emplace_back(0.50122449407354, -2.106018338818103, 1.135646412777714);
		circles.emplace_back(-1.038053624797612, 2.746043347287923, 1.259998094779439);
		circles.emplace_back(2.990944583434612, 1.39535398920998, 0.7408530531218275);
		circles.emplace_back(-3.742861899081618, 2.460155209992081, 1.322684266068973);
		circles.emplace_back(-0.6894341832958162, 0.767316750716418, 1.373048491100781);
		circles.emplace_back(-3.140586104709655, -3.00104635534808, 1.505679166619666);
		circles.emplace_back(3.264811814296991, -2.725181805435568, 0.767433102033101);
		circles.emplace_back(-2.6579455495812, 2.417800279799849, 1.062866629124619);
		circles.emplace_back(-1.241386474575847, 3.755200940649956, 0.4115418082801625);
		circles.emplace_back(-2.369556308258325, 3.845233127940446, 1.201378462580033);
		circles.emplace_back(3.466352086979896, 0.5330808251164854, 0.8577696377178654);
	}
	result_expected = 21.08387333978086;

	timer.reset();
	result_actual = algorithm(a110, b110, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #110: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a111(-3.778286985587329, 1.665761696174741);
	Point b111(3.000821185763925, -0.5783965792506933);
	{
		circles.emplace_back(-1.586767940316349, -1.341976930852979, 1.152185937599279);
		circles.emplace_back(0.8331040502525866, 1.921679403167218, 0.9906797478673979);
		circles.emplace_back(1.020244664978236, -3.83379117352888, 1.107271489244886);
		circles.emplace_back(-0.380810599308461, 2.809819595422596, 1.012329998402856);
		circles.emplace_back(-0.5673651420511305, -0.1355355768464506, 1.498860548832454);
		circles.emplace_back(3.246456861961633, -2.971411275211722, 1.132521335384808);
		circles.emplace_back(-1.514008736703545, 4.363292010966688, 0.8554082969436422);
		circles.emplace_back(4.819205163512379, -0.3483669576235116, 0.120994374784641);
		circles.emplace_back(3.799145042430609, 3.340866670478135, 1.252107114461251);
		circles.emplace_back(-0.6110934796743095, 4.55259365728125, 1.341276135458611);
		circles.emplace_back(-0.01140121603384614, 1.117933376226574, 0.8505436957115307);
		circles.emplace_back(-4.832457413431257, 2.611711367499083, 0.598264801944606);
		circles.emplace_back(3.209127511363477, 3.45462003024295, 1.017223991383798);
		circles.emplace_back(-1.302984214853495, 4.127881412860006, 0.9274222470587119);
		circles.emplace_back(4.911519607994705, -0.2954593789763749, 1.506362700718455);
		circles.emplace_back(-3.384786315727979, -4.51331578893587, 0.9106262852670625);
		circles.emplace_back(-3.828228290658444, 3.468013049568981, 1.005500867008231);
		circles.emplace_back(0.2121535665355623, 0.06109649548307061, 1.605620528408326);
		circles.emplace_back(3.696402760688215, -3.610689782071859, 1.427832731674425);
		circles.emplace_back(2.608762786258012, 0.9764757729135454, 0.7861644897377118);
		circles.emplace_back(4.808297285344452, -2.883600515779108, 1.531602287502028);
		circles.emplace_back(2.57912544766441, -1.805591818410903, 1.106534710410051);
		circles.emplace_back(3.506650968920439, 2.694870859850198, 0.8540001900168135);
		circles.emplace_back(-1.477260503452271, -3.097311204764992, 1.416692044003867);
		circles.emplace_back(2.693440502043813, 3.189887313637882, 0.6943412147695198);
		circles.emplace_back(-1.236604636069387, -0.8707136218436062, 0.8657954630209133);
		circles.emplace_back(-2.734226633328944, -1.373477268498391, 0.8386011458234861);
		circles.emplace_back(0.240143605042249, 4.869102945085615, 1.313496217108332);
		circles.emplace_back(-0.5294514284469187, 4.646339456085116, 1.14817972315941);
		circles.emplace_back(0.471520668361336, 1.561169500928372, 1.21074036906939);
		circles.emplace_back(-4.619446240831167, -1.526615924667567, 0.817499138158746);
		circles.emplace_back(-2.962018253747374, 3.415034285280854, 1.022676137485541);
		circles.emplace_back(4.140454905573279, 0.9941078047268093, 1.561679592053406);
		circles.emplace_back(-2.002699908334762, -4.18872895417735, 1.413001133804209);
		circles.emplace_back(-0.3195854718796909, 2.537749928887933, 1.081243219575845);
	}
	result_expected = 16.4982449792727;

	timer.reset();
	result_actual = algorithm(a111, b111, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #111: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a112(-3.886600207071751, 3.536135198548436);
	Point b112(2.825044752564281, 2.059943312779069);
	{
		circles.emplace_back(4.090649371501058, 1.129560677800328, 1.41444650220219);
		circles.emplace_back(-4.369590764399618, 2.005102902185172, 1.505405834014527);
		circles.emplace_back(-1.863438833970577, 3.048947465140373, 0.7372024840908125);
		circles.emplace_back(1.345455416012555, 4.046367814298719, 0.4859903990989551);
		circles.emplace_back(-4.709182141814381, -3.872407933231443, 1.826821110979654);
		circles.emplace_back(1.976839250419289, 3.100044305901974, 0.8721217418788001);
		circles.emplace_back(2.001420713495463, -4.126920111011714, 1.189887355011888);
		circles.emplace_back(3.892503429669887, -0.8544628159143031, 0.9355325443437322);
		circles.emplace_back(-1.444350781384856, 4.446395805571228, 1.14152400533203);
		circles.emplace_back(4.738652782980353, -2.248249270487577, 1.097342800418846);
		circles.emplace_back(0.745977524202317, -1.070444311480969, 0.9026324975537136);
		circles.emplace_back(4.148181707132608, 3.643945080693811, 0.9394440170144661);
		circles.emplace_back(0.1477462588809431, 0.3888312005437911, 0.211791336000897);
		circles.emplace_back(4.16559329489246, 3.509789395611733, 0.6223500898806378);
		circles.emplace_back(0.07646080804988742, 3.389329568017274, 1.137529882160015);
		circles.emplace_back(4.942609381396323, 0.05388913443312049, 1.141814658953808);
		circles.emplace_back(4.663680901285261, 3.878408803138882, 0.6194687202805653);
		circles.emplace_back(-2.042110522743315, 1.087408557068557, 1.281319435383193);
		circles.emplace_back(-0.04468989791348577, 3.335877594072372, 1.383028748561628);
		circles.emplace_back(4.932245307136327, -3.439496720675379, 1.347030179924332);
		circles.emplace_back(2.244687543716282, -2.461852168198675, 1.799559581861831);
		circles.emplace_back(4.497456422541291, -3.339878518600017, 0.7934966998873278);
		circles.emplace_back(3.755228004883975, -2.048523507546633, 0.7393237893702462);
		circles.emplace_back(-0.7177388924174011, -0.8456738875247538, 0.6497404193272813);
		circles.emplace_back(2.153315546456724, -2.18336581485346, 0.623927764664404);
		circles.emplace_back(0.7530766609124839, -1.941048305016011, 0.6887042711721733);
		circles.emplace_back(0.6418829713948071, -0.2400369965471327, 1.088069795421325);
		circles.emplace_back(4.814483204390854, -2.524593842681497, 1.445113565237261);
		circles.emplace_back(1.848733259830624, 1.599616918247193, 0.709618197265081);
		circles.emplace_back(-4.598882005084306, -3.293605863582343, 1.310239093122072);
		circles.emplace_back(-4.899797800462693, -3.701658046338707, 1.1919449420413);
		circles.emplace_back(4.77560613071546, 1.245286522898823, 1.484885749989189);
		circles.emplace_back(-4.922421609517187, -1.926180601585656, 1.197997606988065);
		circles.emplace_back(1.813097696285695, -1.517654198687524, 0.8481727830367163);
		circles.emplace_back(2.809954502154142, -4.379936794284731, 1.148414532816969);
		circles.emplace_back(1.328011841978878, 2.472296545747668, 0.934825280145742);
		circles.emplace_back(4.557398355100304, -2.140970204491168, 0.8945636878488584);
		circles.emplace_back(-3.097327046561986, -2.75104597909376, 1.193407430988736);
		circles.emplace_back(-2.033231954555959, -4.752657397184521, 1.055836292891763);
	}
	result_expected = 9.490896110376527;

	timer.reset();
	result_actual = algorithm(a112, b112, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #112: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a113(-2.384485750924796, 1.846013085916638);
	Point b113(3.58218847727403, -0.8975841905921698);
	{
		circles.emplace_back(0.6452524452470243, -0.2932859188877046, 0.4769902931759133);
		circles.emplace_back(-0.2261845930479467, 0.6116839381866157, 1.07840628165286);
		circles.emplace_back(-1.461701497901231, -2.168619751464576, 1.547667612251826);
		circles.emplace_back(2.59259992511943, -2.201123333070427, 0.7240157784661277);
		circles.emplace_back(0.9883743873797357, 4.134033678565174, 0.4503847904736176);
		circles.emplace_back(3.058827186468989, -3.334230959881097, 0.8838424903107807);
		circles.emplace_back(1.457269589882344, -4.517676669638604, 0.8855303011136129);
		circles.emplace_back(-3.858303038869053, -2.673915138002485, 1.517387032345868);
		circles.emplace_back(-4.194508099462837, 2.294823850970715, 0.6921270827529952);
		circles.emplace_back(-1.293774240184575, -4.013421393465251, 1.183439767104574);
		circles.emplace_back(-3.665408890228719, -1.161907000932842, 1.05224686244037);
		circles.emplace_back(2.519571629818529, -2.277233877684921, 1.153740646340884);
		circles.emplace_back(-0.4546324140392244, 0.3558038990013301, 1.170658845524303);
		circles.emplace_back(4.063677105586976, 0.6756995362229645, 0.7764410141156985);
		circles.emplace_back(-4.316406787838787, 2.295371133368462, 1.176130235823803);
		circles.emplace_back(0.8536506886593997, -0.7850964809767902, 1.026387975481339);
		circles.emplace_back(-2.028883832972497, -2.541224232409149, 0.7920600229641422);
		circles.emplace_back(-0.1739666261710227, -0.6877949996851385, 0.9054750055307522);
		circles.emplace_back(-1.87537889694795, -4.610115841496736, 0.7453354869736358);
		circles.emplace_back(3.853649522643536, 4.152632441837341, 1.345808260072954);
		circles.emplace_back(-2.317499078344554, 3.961596672888845, 1.547494245297275);
		circles.emplace_back(4.536616222467273, -2.010763471480459, 0.439377154991962);
		circles.emplace_back(2.284668108914047, 2.700232218485326, 0.5326584013877436);
		circles.emplace_back(-1.395044692326337, -2.3619180242531, 0.9223538358928635);
		circles.emplace_back(-1.314696546178311, -1.369172988925129, 0.9278115680208429);
		circles.emplace_back(0.01572318142279983, -0.3036204515956342, 0.7684186022961512);
		circles.emplace_back(-3.437225085217506, 4.994199622888118, 0.2532126511679962);
		circles.emplace_back(4.779262647498399, -3.478434684220701, 1.922827083221637);
		circles.emplace_back(-3.554060033056885, -4.576189739163965, 0.9203624757239595);
		circles.emplace_back(-3.73275222023949, 2.367553773801774, 0.4438248454360291);
		circles.emplace_back(-0.4762693797238171, 4.833651513326913, 1.54885619294364);
		circles.emplace_back(-4.325314376037568, -3.414376622531563, 0.7568338798126205);
		circles.emplace_back(4.594797973986715, -4.814323575701565, 1.226825510733761);
		circles.emplace_back(3.757159824017435, 1.120277314912528, 0.642789587075822);
		circles.emplace_back(1.768194090109318, 0.4052579519338906, 1.115497983177193);
		circles.emplace_back(2.147477038670331, -3.988874147180468, 1.18673536775168);
	}
	result_expected = 7.378431860720976;

	timer.reset();
	result_actual = algorithm(a113, b113, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #113: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a114(-3.308218527119607, 1.641663821414113);
	Point b114(3.264070787932724, 2.801618719473481);
	{
		circles.emplace_back(-4.440482484642416, -3.967216664459556, 1.335643888660706);
		circles.emplace_back(-4.773840468842536, 3.049637128133327, 1.259069639001973);
		circles.emplace_back(-1.915365650784224, -0.1027044677175581, 0.8301262769615277);
		circles.emplace_back(0.2630449621938169, -2.083918375428766, 0.7387645485112443);
		circles.emplace_back(-3.993561223614961, 3.862728506792337, 1.054014280554838);
		circles.emplace_back(1.567390051204711, -3.534439748618752, 1.699625922902487);
		circles.emplace_back(2.141680305358022, -3.563416691031307, 0.704856976144947);
		circles.emplace_back(1.187604481820017, 4.017227261792868, 1.646109217102639);
		circles.emplace_back(0.2589922654442489, 1.481811713892967, 0.9474222279386594);
		circles.emplace_back(-1.89361923141405, 1.264821996446699, 1.247041591978632);
		circles.emplace_back(3.663623274769634, -4.199135263916105, 0.3795721782604232);
		circles.emplace_back(-0.9136800398118794, 4.917349510360509, 1.007093764585443);
		circles.emplace_back(-1.563781502190977, -3.751248845364898, 1.294714573421516);
		circles.emplace_back(0.7989016943611205, -4.655136980582029, 1.231607451359741);
		circles.emplace_back(3.328089180868119, -3.397420074325055, 1.303675701026805);
		circles.emplace_back(3.596685260999948, 0.976239365991205, 0.4130391742801294);
		circles.emplace_back(-0.450538641307503, -1.016263363417238, 0.475993456901051);
		circles.emplace_back(-1.337244303431362, 4.467850911896676, 1.060972507926635);
		circles.emplace_back(-3.339500159490854, 3.993858054745942, 1.182377683487721);
		circles.emplace_back(4.81475890846923, 2.19938246300444, 1.483345235302113);
		circles.emplace_back(3.290597607847303, 4.365122749004513, 1.243547903024592);
		circles.emplace_back(-0.1598992547951639, 0.5801733280532062, 0.9896537770284339);
		circles.emplace_back(-4.839506570715457, -3.848533395212144, 1.100899439980276);
		circles.emplace_back(0.9834271599538624, -0.07264700019732118, 1.043975575990044);
		circles.emplace_back(4.167316721286625, -4.450624024029821, 1.389620105014183);
		circles.emplace_back(-4.546669551637024, -4.887529511470348, 0.6751417505322024);
		circles.emplace_back(-3.227694251108915, 4.98839519219473, 0.4929439638974145);
		circles.emplace_back(-0.7631442206911743, 4.282769651617855, 0.8599535709014162);
		circles.emplace_back(2.177039009984583, 4.768203890416771, 0.6677521523321047);
		circles.emplace_back(3.584600987378508, -4.384393387008458, 1.413891001115553);
		circles.emplace_back(-0.8861366030760109, -4.125411610584706, 0.8666916351066902);
		circles.emplace_back(-1.740203520748764, 4.430850076023489, 1.277881245524622);
		circles.emplace_back(3.405469788704067, -0.8860585954971611, 0.7581048502353951);
		circles.emplace_back(-0.9394759987480938, -2.715837478172034, 1.297610278544016);
		circles.emplace_back(-3.882228198926896, -0.3970880270935595, 1.685504365130328);
	}
	result_expected = 6.921533943700562;

	timer.reset();
	result_actual = algorithm(a114, b114, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #114: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a115(-2.774441487621516, 0.1904862392693758);
	Point b115(2.229377178009599, 3.552666941657662);
	{
		circles.emplace_back(2.722399698104709, -0.2442470542155206, 0.8360957747558131);
		circles.emplace_back(-4.603641161229461, 2.543660204391927, 1.781839247304015);
		circles.emplace_back(4.789332828950137, 4.319605745840818, 1.079362446558662);
		circles.emplace_back(-0.4256975906901062, -4.379955141339451, 1.23456104749348);
		circles.emplace_back(2.754898590501398, -4.640898609068245, 1.556872656592168);
		circles.emplace_back(3.200037481728941, -1.998412602115422, 1.788971285591833);
		circles.emplace_back(-3.47500265808776, -2.517079513054341, 0.8017711113439873);
		circles.emplace_back(-3.340083083603531, 2.862795817200094, 0.4694785850355401);
		circles.emplace_back(-0.4705192311666906, 1.920335206668824, 0.9588517053751274);
		circles.emplace_back(-2.834873006213456, 3.606978834141046, 1.07708973151166);
		circles.emplace_back(-2.152693632524461, -4.603569305036217, 1.385648474260233);
		circles.emplace_back(-2.603241468314081, 3.889260350260884, 0.5206609107786789);
		circles.emplace_back(-1.920673151034862, -3.549755353014916, 0.5385276786284521);
		circles.emplace_back(-4.225846908520907, -1.354273895267397, 0.6041065141325817);
		circles.emplace_back(-3.508149294648319, -2.713205029722303, 0.9534400252858176);
		circles.emplace_back(4.300752675626427, 1.69651749311015, 1.068628586339764);
		circles.emplace_back(4.530863470863551, 0.7635371317155659, 1.039389386516996);
		circles.emplace_back(1.711415548343211, -1.852765067014843, 0.9877928463509306);
		circles.emplace_back(4.354906228836626, 3.767026683781296, 1.258024888136424);
		circles.emplace_back(3.404936406295747, 0.6286538881249726, 1.132017222349532);
		circles.emplace_back(-4.628996967803687, -1.583189892116934, 1.199096415541135);
		circles.emplace_back(-2.471320724580437, -0.8834205544553697, 1.00612699186895);
		circles.emplace_back(-0.4198684706352651, -3.075798612553626, 0.4523896015016362);
		circles.emplace_back(1.464293419849128, 0.5899627064354718, 0.9285702952416613);
		circles.emplace_back(-3.498630363028497, -4.354661873076111, 1.27887830378022);
		circles.emplace_back(3.809815009590238, 3.170462830457836, 1.103047764324583);
		circles.emplace_back(-0.5358083150349557, -4.843188778031617, 1.060490125860087);
		circles.emplace_back(-1.441831446718425, -1.008536333683878, 1.473510304815136);
		circles.emplace_back(1.178292946424335, -3.265320544596761, 0.4419144084909931);
		circles.emplace_back(0.4803751152940094, 4.432907940354198, 1.238280685781501);
		circles.emplace_back(-4.627549794968218, -4.296924613881856, 1.023628345201723);
		circles.emplace_back(3.428314763586968, -0.8501749741844833, 0.8158843870507553);
		circles.emplace_back(-3.740621402394027, 2.113880810793489, 1.239042136422358);
	}
	result_expected = 6.247860376178471;

	timer.reset();
	result_actual = algorithm(a115, b115, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #115: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a116(-3.950136329513043, 0.1226111073046923);
	Point b116(2.011521534528583, 1.230106526985765);
	{
		circles.emplace_back(-2.701282242778689, -1.978299932088703, 0.6943675369257107);
		circles.emplace_back(0.4096430796198547, -3.011457237880677, 1.083213631738909);
		circles.emplace_back(2.279847704339772, -4.733474070671946, 0.768895149952732);
		circles.emplace_back(-0.08912621298804879, 0.2144710370339453, 0.9945809504250064);
		circles.emplace_back(3.840613982174546, -2.010406304616481, 1.939168063062243);
		circles.emplace_back(3.268515698146075, -4.919264845084399, 0.8955376346828415);
		circles.emplace_back(-4.884654756169766, -4.987377582583576, 0.9072885682573542);
		circles.emplace_back(3.801096233073622, -2.455797039438039, 0.641561794350855);
		circles.emplace_back(4.8166902246885, -4.658674846868962, 1.425059398566373);
		circles.emplace_back(1.642463312018663, -4.246945979539305, 1.058933645836078);
		circles.emplace_back(-2.54450278589502, 0.8285949402488768, 1.055289629311301);
		circles.emplace_back(-3.353945629205555, 2.533547941129655, 0.9464793740538879);
		circles.emplace_back(-3.237101689446718, 2.584150761831552, 0.53527775418479);
		circles.emplace_back(-2.383569094818085, -4.507633096072823, 1.334353940351866);
		circles.emplace_back(-2.462699527386576, -0.468384416308254, 0.9749694459373131);
		circles.emplace_back(4.04819023096934, 3.599160581361502, 1.472621163423173);
		circles.emplace_back(-3.106629003304988, 0.477954160887748, 0.7838710672454908);
		circles.emplace_back(-0.8008668408729136, -0.2937611541710794, 1.163429049984552);
		circles.emplace_back(-1.672287636902183, 1.478626902680844, 0.4777126396773383);
		circles.emplace_back(-0.1334835519082844, 1.31078600184992, 0.7182416719617322);
		circles.emplace_back(-0.6419336306862533, -2.465671135578305, 1.297103027789853);
		circles.emplace_back(-0.7375487708486617, 1.207768491003662, 1.37162569204811);
		circles.emplace_back(3.710880952421576, -0.402860261965543, 0.6075156264705583);
		circles.emplace_back(-2.402558561880141, 1.359878454823047, 1.11852124214638);
		circles.emplace_back(0.1428908412344754, 1.085251790937036, 0.9007082756375894);
		circles.emplace_back(1.082142645027488, 1.82783335680142, 0.8571168119320646);
		circles.emplace_back(2.100271491799504, 4.998895216267556, 1.122769211861305);
		circles.emplace_back(-1.253719616215676, -4.896228334400803, 0.7137422362109646);
		circles.emplace_back(1.073626985307783, -2.950973974075168, 1.287709940993227);
		circles.emplace_back(3.212585325818509, -1.880798998754472, 0.6162394612329081);
		circles.emplace_back(3.817369632888585, -3.374879921320826, 1.695009564585052);
		circles.emplace_back(1.548548804130405, 0.2487602480687201, 0.6722610419848933);
		circles.emplace_back(2.59321021148935, 0.391220252495259, 0.8596241730032488);
		circles.emplace_back(2.679016671609133, 2.885222949553281, 0.4265896206023171);
		circles.emplace_back(-3.35318150697276, 3.341495783533901, 1.126782170473598);
	}
	result_expected = 11.76415493539563;

	timer.reset();
	result_actual = algorithm(a116, b116, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #116: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a117(-3.159312948118895, 0.4318776894360781);
	Point b117(3.106976216193289, -3.740796258673072);
	{
		circles.emplace_back(-1.530367380473763, 0.7299214624799788, 1.035058488906361);
		circles.emplace_back(2.362942902836949, 2.965601671021432, 0.885769065353088);
		circles.emplace_back(3.830545216333121, 0.267153934109956, 0.7823780411155894);
		circles.emplace_back(4.739750039298087, -3.649275621864945, 0.5453486332437023);
		circles.emplace_back(4.697913338895887, 2.061739398632199, 1.098129521333612);
		circles.emplace_back(-4.108523388858885, 4.308293655049056, 1.720118593121879);
		circles.emplace_back(-2.530034009832889, 3.533580538351089, 1.689955812622793);
		circles.emplace_back(2.299829118419439, 2.373944853898138, 0.9427965245908125);
		circles.emplace_back(3.461557195987552, 4.461927379015833, 0.8193508779862895);
		circles.emplace_back(3.721007278654724, 0.3935922193340957, 1.113490401464514);
		circles.emplace_back(0.8419688767753541, -4.652260148432106, 0.9482607420766725);
		circles.emplace_back(-2.287012038286775, 2.121970958542079, 1.082163281808607);
		circles.emplace_back(1.685710835736245, -4.612941842060536, 0.9563026647316292);
		circles.emplace_back(2.804817811120301, 1.295078543480486, 1.185627998760901);
		circles.emplace_back(-3.712977038230747, -1.53885104926303, 0.5653522743610665);
		circles.emplace_back(1.746345695573837, 3.591747784521431, 0.6698878289898857);
		circles.emplace_back(4.284497534390539, 3.59069979051128, 0.9793304331833496);
		circles.emplace_back(-3.500274752732366, -2.173294008243829, 0.3792980235768482);
		circles.emplace_back(-2.88627763511613, -1.657227713149041, 0.8178518078522756);
		circles.emplace_back(-3.418710313271731, 3.775595386978239, 0.3268081739312038);
		circles.emplace_back(2.295724542345852, 3.169059643987566, 1.318352728919126);
		circles.emplace_back(3.760292625520378, -1.572458420414478, 1.030535821127705);
		circles.emplace_back(3.357439048122615, 4.03224065201357, 1.340940659982152);
		circles.emplace_back(4.597318966407329, -0.1807233528234065, 0.6808820126345381);
		circles.emplace_back(1.370302664581686, 1.013677648734301, 0.9352193363709375);
		circles.emplace_back(-2.353673067409545, 2.089710657019168, 1.52961842447985);
		circles.emplace_back(-1.255131780635566, -0.312869178596884, 0.8322546373819932);
		circles.emplace_back(0.1732303737662733, 1.367986651603132, 0.9010576436528935);
		circles.emplace_back(-2.924773634877056, 2.463905054610223, 1.541374034318141);
		circles.emplace_back(1.119354485999793, -0.8737995172850788, 1.580724386242218);
		circles.emplace_back(1.952323180157691, 3.819311985280365, 0.6948950404068455);
		circles.emplace_back(-4.290525058750063, 4.509113116655499, 1.135644784593023);
		circles.emplace_back(-1.184839417692274, 3.650773807894439, 1.000955281103961);
		circles.emplace_back(2.658028628211468, 2.018765297252685, 0.6140371307032182);
		circles.emplace_back(-0.1408250699751079, -0.7629863568581641, 1.289259488112293);
	}
	result_expected = 7.631586474549986;

	timer.reset();
	result_actual = algorithm(a117, b117, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #117: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a118(-2.438917640130967, -2.413814691826701);
	Point b118(3.556570881512016, -1.328390872105956);
	{
		circles.emplace_back(1.606719640549272, -3.137720802333206, 0.8379887391114607);
		circles.emplace_back(0.3534623119048774, -3.345357056241482, 1.10290724367369);
		circles.emplace_back(4.897930503357202, 3.978407455142587, 0.4437128048157319);
		circles.emplace_back(1.687192821409553, 4.532503040973097, 1.244308845163323);
		circles.emplace_back(-0.6817784323357046, -0.3773032245226204, 1.215568116935901);
		circles.emplace_back(4.402466237079352, 3.709266886580735, 1.171383763221092);
		circles.emplace_back(-1.195404368918389, -0.5704464227892458, 0.3705966675421223);
		circles.emplace_back(-1.199800411704928, 4.658888562116772, 1.135427844547666);
		circles.emplace_back(2.066165695432574, 3.578840240370482, 1.020010728086345);
		circles.emplace_back(-1.281421456951648, -4.313032838981599, 1.215205950965173);
		circles.emplace_back(0.4608131875284016, -0.2718443819321692, 0.8165481723612174);
		circles.emplace_back(-1.584046168718487, 4.014235252980143, 1.352031534002162);
		circles.emplace_back(4.405214509461075, 0.4807534324936569, 1.202975207823329);
		circles.emplace_back(1.607973508071154, 3.825074203778058, 0.378873919439502);
		circles.emplace_back(-3.587019618134946, -4.782830832991749, 1.513711055158637);
		circles.emplace_back(4.707290900405496, 2.870411819312721, 1.824328262754716);
		circles.emplace_back(0.4362009488977492, -4.688448451925069, 1.34214781827759);
		circles.emplace_back(-2.845968168694526, 1.069826532620937, 1.532244073902257);
		circles.emplace_back(4.978658363688737, -4.750211539212614, 1.884480974427424);
		circles.emplace_back(2.408798465039581, 1.881901102606207, 1.258706647367217);
		circles.emplace_back(-1.789312676992267, 1.756360891740769, 0.8112956016091629);
		circles.emplace_back(-4.203867230098695, 2.470452242996544, 1.688270647986792);
		circles.emplace_back(0.2970411232672632, 3.481063751969486, 0.7796667240792885);
		circles.emplace_back(-4.90892726695165, -1.260815889108926, 1.054668235476129);
		circles.emplace_back(-2.409521390218288, -0.489968943875283, 1.284244314511306);
		circles.emplace_back(1.541943021584302, -2.533056626562029, 1.560267177200876);
		circles.emplace_back(2.229378761257976, -0.02737935399636626, 1.31139953865204);
		circles.emplace_back(-3.294708572793752, -3.911454386543483, 1.164151389640756);
		circles.emplace_back(-3.496119629126042, -0.268917812500149, 1.014056558697484);
		circles.emplace_back(-3.321121337357908, -4.485145935323089, 0.9333901737118139);
		circles.emplace_back(-2.521503192838281, -0.8781378646381199, 1.176043888251297);
		circles.emplace_back(3.729815545957536, 0.7991075259633362, 1.34111443341244);
		circles.emplace_back(1.69695469783619, -4.134486394468695, 0.9299903835868463);
		circles.emplace_back(0.7028213678859174, 4.175027611199766, 0.8944192135939374);
		circles.emplace_back(2.544546930585057, 1.528703558724374, 1.074341764184646);
		circles.emplace_back(1.092692285310477, -4.768627330195159, 0.6297034436138347);
		circles.emplace_back(1.209830057341605, 0.9740879922173917, 1.101169724180363);
	}
	result_expected = 16.27098289467292;

	timer.reset();
	result_actual = algorithm(a118, b118, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #118: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a119(-2.85646005673334, 0.9972199071198702);
	Point b119(3.132260066922754, -2.604603430256248);
	{
		circles.emplace_back(-3.557865379843861, 2.1992651023902, 1.33386569453869);
		circles.emplace_back(-3.05411642184481, 4.912367041688412, 1.511888011801056);
		circles.emplace_back(-4.076032780576497, -0.5307710240595043, 0.834819940966554);
		circles.emplace_back(0.2319252979941666, -4.029584957752377, 0.9590186876943334);
		circles.emplace_back(-0.9280571364797652, -2.89149803807959, 1.048040348687209);
		circles.emplace_back(4.500797467771918, -4.911357976961881, 1.080623417417519);
		circles.emplace_back(1.969368222635239, 4.109805498737842, 1.2335427331971);
		circles.emplace_back(1.535357863176614, -4.213441389147192, 1.184365802607499);
		circles.emplace_back(0.7524359761737287, 3.843183221761137, 0.8427748615154996);
		circles.emplace_back(0.1809518621303141, 3.734072733204812, 1.000501560303382);
		circles.emplace_back(-4.912945658434182, 4.136986986268312, 0.7607730531366541);
		circles.emplace_back(0.4199287411756814, -3.705701848957688, 1.183222440793179);
		circles.emplace_back(4.295517911668867, 2.133948339615017, 1.259997858130373);
		circles.emplace_back(3.876516858581454, -4.617291793692857, 0.9344336171401664);
		circles.emplace_back(-3.713171605486423, -1.929715338628739, 1.12305096082855);
		circles.emplace_back(-4.826555557083338, -2.199650371912867, 0.9990612260764464);
		circles.emplace_back(-4.246932400856167, 2.575007940176874, 1.118623895035125);
		circles.emplace_back(2.996568761300296, 1.754572906065732, 0.8906150941969826);
		circles.emplace_back(-4.056013252120465, -1.387853829655796, 0.9035095369210466);
		circles.emplace_back(1.998726052697748, 1.964719987008721, 0.7818752374732867);
		circles.emplace_back(-0.3412765241228044, 4.127104885410517, 0.8997624740703031);
		circles.emplace_back(-0.3188741323538125, 0.5268373084254563, 1.199001790140755);
		circles.emplace_back(1.34025450097397, -3.708499821368605, 1.155809955648146);
		circles.emplace_back(1.493277230765671, -1.529615295585245, 0.8705020742723718);
		circles.emplace_back(-0.6371517642401159, 2.909906420391053, 1.477009551110677);
		circles.emplace_back(-4.761437580455095, -4.574108540546149, 0.6949801431270316);
		circles.emplace_back(0.01237415941432118, 0.8418591856025159, 0.757397905155085);
		circles.emplace_back(-0.8288773545064032, 3.804758249316365, 1.25627617018763);
		circles.emplace_back(4.150845969561487, -4.071119904983789, 0.9371351194335147);
		circles.emplace_back(-4.388762612361461, -1.867437500040978, 0.8361980012850836);
		circles.emplace_back(1.38534972211346, 4.601785133127123, 0.6201329557457939);
		circles.emplace_back(-3.374481999780983, -4.211322639603168, 1.238200349616818);
		circles.emplace_back(-4.950766258407384, 4.327845417428762, 1.003913900000043);
		circles.emplace_back(-1.160042386036366, -2.063750608358532, 1.043428423791192);
		circles.emplace_back(1.848893908318132, 0.1790493936277926, 1.409337054588832);
		circles.emplace_back(-4.495298338588327, -1.407896645832807, 1.453548852424137);
		circles.emplace_back(4.463629934471101, 0.1565260929055512, 1.038189933006652);
		circles.emplace_back(-0.7933301921002567, 2.200966549571604, 1.152045397064648);
	}
	result_expected = 7.21547140846883;

	timer.reset();
	result_actual = algorithm(a119, b119, circles);
	std::cout << "time ================================================= " << timer.elapsed() << '\n';

	std::cout << "test #119: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a120(-3.901858906727284, -0.9004443865269423);
	Point b120(2.941859514918178, -3.970522647723556);
	{
		circles.emplace_back(2.797373568173498, 3.735283969435841, 1.739599002175964);
		circles.emplace_back(-2.229935263749212, 0.3071151371113956, 1.232863120432012);
		circles.emplace_back(0.3703079628758132, -3.703366953413934, 1.269858314772137);
		circles.emplace_back(4.73652831511572, 4.294544418808073, 1.113072665012441);
		circles.emplace_back(-0.8186348364688456, 0.8064340450800955, 1.143980413512327);
		circles.emplace_back(-3.390273952390999, 2.419448222499341, 1.226432995009236);
		circles.emplace_back(3.884189135860652, -4.879323698114604, 0.5506250080885365);
		circles.emplace_back(-0.5978528666310012, 1.667533235158771, 1.33569623210933);
		circles.emplace_back(-3.651222737971693, -3.550445714499801, 0.9953209240222349);
		circles.emplace_back(2.997926699463278, 4.275260500144213, 0.8841602572007105);
		circles.emplace_back(-1.222407903987914, -2.694236810784787, 1.922755760257132);
		circles.emplace_back(2.120062292087823, 1.926584613975137, 1.184250177047215);
		circles.emplace_back(0.6287409900687635, -2.087549713905901, 1.052551264525391);
		circles.emplace_back(0.8031845674850047, 4.071702200453728, 1.159832090768032);
		circles.emplace_back(1.726594686042517, -1.210916235577315, 1.542367199924774);
		circles.emplace_back(4.988581400830299, -4.81041299412027, 0.7401839608093723);
		circles.emplace_back(-2.942606618162245, 0.09343270910903811, 1.253353080595843);
		circles.emplace_back(0.7435632008127868, -0.007384929340332747, 0.8869527562754228);
		circles.emplace_back(4.535867415834218, -2.000781709793955, 1.421121818549);
		circles.emplace_back(1.593273899052292, -1.207545448560268, 1.504483005660586);
		circles.emplace_back(2.612455121707171, -1.834349564742297, 0.9110833426238968);
		circles.emplace_back(-4.941438313107938, 2.486764134373516, 0.6748935213079675);
		circles.emplace_back(1.546840739902109, -0.9704098640941083, 0.6097932677948847);
		circles.emplace_back(-3.836034398991615, -3.417202483396977, 0.9120689775096252);
		circles.emplace_back(4.753375754225999, 4.032030103262514, 1.221807325235568);
		circles.emplace_back(4.829979964997619, -4.920093638356775, 1.325773415178992);
		circles.emplace_back(3.876806481275707, 0.8500081929378211, 1.15206931817811);
		circles.emplace_back(4.828017696272582, 0.2849451010115445, 1.164956343290396);
		circles.emplace_back(-0.6708481046371162, 3.356847518589348, 1.617040108307265);
		circles.emplace_back(-4.55956649268046, -3.648665936198086, 1.123831623070873);
		circles.emplace_back(0.1951582380570471, 2.425579100381583, 0.8119769957615062);
		circles.emplace_back(-3.09890364529565, 3.050698649603873, 1.736237282236107);
		circles.emplace_back(2.786892422009259, 3.989673068281263, 1.055019694543444);
		circles.emplace_back(-1.913608668837696, 3.728916386608034, 1.106491456762887);
		circles.emplace_back(0.9185146749950945, 3.276093776803464, 1.320629587280564);
		circles.emplace_back(-3.034073852468282, -4.714215404819697, 1.435643230122514);
		circles.emplace_back(0.05525772692635655, 1.038782165851444, 0.5876743657281622);
	}
	result_expected = 13.53437018498092;

	timer.reset();
	result_actual = algorithm(a120, b120, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #120: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a121(-3.266006409656256, 0.2891313005238771);
	Point b121(3.264251252170652, 1.35238922573626);
	{
		circles.emplace_back(0.4331262200139463, 1.105655508581549, 0.8738889279076829);
		circles.emplace_back(-0.1208332343958318, -3.09900724561885, 1.331680843117647);
		circles.emplace_back(-4.143223122227937, 1.169033080805093, 0.8929553122492506);
		circles.emplace_back(0.5754024651832879, -0.6314712227322161, 0.9829843120416626);
		circles.emplace_back(-0.9468577452935278, 3.061988262925297, 1.032772817485966);
		circles.emplace_back(2.619041616562754, -0.08259180234745145, 1.114046930964105);
		circles.emplace_back(1.502886961679906, 1.678064179141074, 1.06348775990773);
		circles.emplace_back(-2.978294424246997, 4.186148752924055, 0.9253188997274264);
		circles.emplace_back(0.281096042599529, 1.934030691627413, 0.7730776382843032);
		circles.emplace_back(-1.117197626736015, -3.939380173105747, 1.141870426642708);
		circles.emplace_back(-3.337721668649465, -1.025838560890406, 0.6071761918487026);
		circles.emplace_back(-1.518134723883122, 4.014946685638279, 0.7723162127425893);
		circles.emplace_back(-0.700960757676512, -4.809388050343841, 1.226534566679038);
		circles.emplace_back(-4.62648413842544, 2.614463053178042, 0.6582398139638825);
		circles.emplace_back(-4.043643411714584, -0.7765269535593688, 1.096351988916285);
		circles.emplace_back(2.172063321340829, -0.9584481292404234, 1.429620810947381);
		circles.emplace_back(2.216986769344658, -1.821707484778017, 1.280107780755497);
		circles.emplace_back(4.224470464978367, -2.154942166525871, 0.7096974036423489);
		circles.emplace_back(3.600872426759452, 4.591826752293855, 0.3673624926479533);
		circles.emplace_back(2.600885641295463, 0.297549047973007, 0.6703142354032025);
		circles.emplace_back(2.912516405340284, 2.938502861652523, 1.157769362651743);
		circles.emplace_back(-0.4688414535485208, 1.522048905026168, 0.9136099387658759);
		circles.emplace_back(1.095130618195981, -4.549459579866379, 0.7897482513682916);
		circles.emplace_back(-3.666273362468928, 2.670953010674566, 0.6353910825913771);
		circles.emplace_back(1.178962157573551, 2.473900879267603, 0.8794226384023204);
		circles.emplace_back(4.813542745541781, -2.749798677396029, 0.2610062037827447);
		circles.emplace_back(2.362662230152637, -2.023723034653813, 0.9856022661319002);
		circles.emplace_back(3.119701368268579, -2.348551952745765, 0.5313489552820101);
		circles.emplace_back(-0.708849725779146, 3.880270428489894, 0.6552454248769208);
		circles.emplace_back(1.937023687642068, -3.250085811596364, 1.036313800071366);
		circles.emplace_back(-2.230708345305175, -0.979305359069258, 0.8265404660021886);
		circles.emplace_back(-0.2739644260145724, -1.070295644458383, 1.232552896649577);
		circles.emplace_back(3.073362840805203, 2.942388865631074, 0.7229250981239601);
		circles.emplace_back(-1.838268146384507, -2.710482000838965, 1.152589060482569);
		circles.emplace_back(3.368048008996993, 0.6037961482070386, 0.6788427652558311);
		circles.emplace_back(4.576165114995092, 0.09784197667613626, 0.4313809342915192);
		circles.emplace_back(1.927622819785029, 4.696566283237189, 0.6113471847726032);
		circles.emplace_back(-4.377346832770854, -2.207728463690728, 0.7562615714268759);
		circles.emplace_back(-0.9825224499218166, -1.611562410835177, 1.715385474241339);
	}
	result_expected = 15.28122775305492;

	timer.reset();
	result_actual = algorithm(a121, b121, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #121: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a122(-2.318551498930901, -3.028897849842906);
	Point b122(3.427557417657226, -1.184539532288909);
	{
		circles.emplace_back(4.582723302301019, 0.3378350497223437, 1.043713172920979);
		circles.emplace_back(-4.229857323225588, 4.469528801273555, 0.7341053114039823);
		circles.emplace_back(4.614423501770943, 3.286987741012126, 0.8430378685938194);
		circles.emplace_back(-2.786840244662017, -1.203390511218458, 0.9498114157235249);
		circles.emplace_back(-2.372958979103714, 2.125596629921347, 1.2325746136019);
		circles.emplace_back(-3.73155073961243, -3.467373338062316, 1.285581438126974);
		circles.emplace_back(3.370979621540755, -2.83343595219776, 1.544557832297869);
		circles.emplace_back(-4.412152532022446, -1.006096994969994, 0.936318722530268);
		circles.emplace_back(0.3188863745890558, 0.1267105923034251, 0.9393291630083694);
		circles.emplace_back(4.616131747607142, 4.515856623183936, 0.8722492885543033);
		circles.emplace_back(0.7654059934429824, -3.493044513743371, 1.389162760158069);
		circles.emplace_back(-3.927846930455416, 3.334554692264646, 0.8591073021059855);
		circles.emplace_back(-2.873418836388737, -4.933081676717848, 0.7487208454171195);
		circles.emplace_back(-1.39846166362986, -4.845270488876849, 1.023556752013974);
		circles.emplace_back(4.397394962143153, 2.877828918863088, 0.7705135313095525);
		circles.emplace_back(-3.766713242512196, -1.320840700063854, 1.16568038740661);
		circles.emplace_back(4.722045210655779, 0.8243507356382906, 1.522760378220118);
		circles.emplace_back(0.09680323535576463, -0.2233401616103947, 1.576421658019535);
		circles.emplace_back(-3.101119517814368, 4.712026787456125, 0.8286075871204956);
		circles.emplace_back(0.6718603358604014, 0.7011122885160148, 1.663110194238834);
		circles.emplace_back(-1.965326506178826, 1.737813183572143, 0.8743212723871693);
		circles.emplace_back(0.1015793881379068, 4.847099168691784, 0.8103165567154065);
		circles.emplace_back(1.407675633672625, -3.082908049691468, 0.798920011962764);
		circles.emplace_back(4.785378302913159, 3.128142741043121, 1.223649360169657);
		circles.emplace_back(-1.959833360742778, -4.900754804257303, 0.7164051510160788);
		circles.emplace_back(0.913250760640949, 2.1567476936616, 1.447505973861553);
		circles.emplace_back(4.096198400948197, -2.524521697778255, 0.9665430190740153);
		circles.emplace_back(-2.604758210945874, 2.887620099354535, 0.6204862167360261);
		circles.emplace_back(1.149745408911258, 2.153438569512218, 1.665250029205344);
		circles.emplace_back(-2.577125655952841, -1.395780497696251, 0.4041839014971629);
		circles.emplace_back(-3.985468891914934, -3.966297053266317, 0.4439828605158254);
		circles.emplace_back(0.7722727837972343, 3.227894355077296, 0.645979421888478);
		circles.emplace_back(2.626771733630449, 2.74431019788608, 0.8359517607605085);
		circles.emplace_back(-0.5739270360209048, -0.5734830326400697, 1.583247745246626);
		circles.emplace_back(-4.53918190440163, 4.990271094720811, 0.5729020862607285);
		circles.emplace_back(0.6132400478236377, 0.08462968515232205, 0.9325120837660505);
		circles.emplace_back(-3.56185546843335, -0.8914160192944109, 1.726326383813284);
	}
	result_expected = 6.034858288965026;

	timer.reset();
	result_actual = algorithm(a122, b122, circles);
	std::cout << "time ================================================= " << timer.elapsed() << '\n';

	std::cout << "test #122: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a123(-3.597401774954051, 0.9670662153512239);
	Point b123(2.542782840784639, 1.270348945632577);
	{
		circles.emplace_back(3.73167754849419, 0.2393529959954321, 1.142337127611972);
		circles.emplace_back(-2.03998921206221, 4.376005481462926, 1.466815421241336);
		circles.emplace_back(-4.988388784695417, -4.903170994948596, 0.2087910671951249);
		circles.emplace_back(-4.159589882474393, -2.897797881159931, 1.320447181700729);
		circles.emplace_back(1.12210996216163, -3.717595094349235, 1.22648044640664);
		circles.emplace_back(1.287201794330031, 3.011701859068125, 1.210813099215738);
		circles.emplace_back(-3.451992135960609, -3.640145312529057, 1.057072463189252);
		circles.emplace_back(3.722289309371263, -1.13955736393109, 1.312467110506259);
		circles.emplace_back(1.846617290284485, -1.403736693318933, 0.9280955882975831);
		circles.emplace_back(0.824216587934643, -2.713245686609298, 1.049999725702219);
		circles.emplace_back(-1.095656410325319, -3.530717759858817, 0.8512924553127958);
		circles.emplace_back(-4.806983682792634, 3.036296123173088, 1.75321495400276);
		circles.emplace_back(-1.117037285584956, 4.623638999182731, 0.659407729585655);
		circles.emplace_back(-2.982734672259539, -2.945296356920153, 0.7030365049606189);
		circles.emplace_back(-2.210140281822532, -2.541875068563968, 0.8337234164355323);
		circles.emplace_back(0.6661991844885051, -1.632676727604121, 1.266052065533586);
		circles.emplace_back(-3.893881391268224, -2.735825015697628, 1.284465513913892);
		circles.emplace_back(0.3546115732751787, -1.969053575303406, 0.8994524602079763);
		circles.emplace_back(-2.175472897943109, -1.130238987971097, 1.159140359680168);
		circles.emplace_back(4.325898054521531, 4.585477386135608, 0.4467917072819546);
		circles.emplace_back(1.195533305872232, -2.543924229685217, 1.11121538837906);
		circles.emplace_back(3.820316249039024, 3.989155592862517, 1.536315059126355);
		circles.emplace_back(-2.440095038618892, -3.275661778170615, 1.329958157869987);
		circles.emplace_back(-2.639719278085977, -4.208170517813414, 1.449216672149487);
		circles.emplace_back(0.7552769896574318, -4.432491681072861, 1.624788079573773);
		circles.emplace_back(-3.181559930089861, -1.208190785255283, 1.008826847397722);
		circles.emplace_back(4.984307924751192, -3.03540299879387, 0.9398741204990073);
		circles.emplace_back(-2.304346088785678, -3.602995935361832, 1.290242996742017);
		circles.emplace_back(-3.18416804773733, -0.4947137483395636, 0.9605751566356048);
		circles.emplace_back(-3.678727878723294, -2.462487553711981, 1.697254920587875);
		circles.emplace_back(0.8771120221354067, 2.167417805176228, 1.094999344903044);
		circles.emplace_back(1.590462408494204, -1.355198703240603, 0.629000920546241);
		circles.emplace_back(-0.5992317455820739, -1.971497146878392, 1.515326068340801);
		circles.emplace_back(1.8641746067442, -3.755251162219793, 1.51208869672846);
		circles.emplace_back(4.879185545723885, 2.903945047874004, 1.024684007023461);
		circles.emplace_back(1.252085522282869, -2.372806819621474, 1.437858592323027);
	}
	result_expected = 6.153461740270592;

	timer.reset();
	result_actual = algorithm(a123, b123, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #123: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a124(-3.622444208245724, -1.468334017321467);
	Point b124(2.905426369514316, -2.819043820723891);
	{
		circles.emplace_back(1.205818464513868, -3.265026973094791, 1.249472562992014);
		circles.emplace_back(1.701919178012758, 0.9935774351470172, 1.377045946265571);
		circles.emplace_back(0.02691763220354915, -2.463976505678147, 1.175008237292059);
		circles.emplace_back(1.904278986621648, -1.980843807104975, 0.7258746288483962);
		circles.emplace_back(-1.807804533746094, 4.19875095365569, 1.477327792602591);
		circles.emplace_back(-1.228158094454557, 0.2168413181789219, 1.174280944955535);
		circles.emplace_back(-3.881551350932568, -4.25002089003101, 0.6347966735949739);
		circles.emplace_back(-1.828265485819429, 1.481605477165431, 1.114692021976225);
		circles.emplace_back(-0.3922519204206765, 1.786065597552806, 1.641269067977555);
		circles.emplace_back(-4.601016065571457, 2.736893820110708, 1.71848407855723);
		circles.emplace_back(-0.1327304705046117, 1.529098364990205, 1.161385901155882);
		circles.emplace_back(-0.6070960615761578, -1.965292810928077, 1.078417970356531);
		circles.emplace_back(4.012491044122726, -2.915912962052971, 0.1953185142716393);
		circles.emplace_back(-3.047433460596949, 1.815912483725697, 0.8856558509403839);
		circles.emplace_back(-1.693395113106817, 4.233860194217414, 0.9076979261590167);
		circles.emplace_back(-4.981845219153911, 4.555946749169379, 1.596122082252987);
		circles.emplace_back(4.673936881590635, 1.599037011619657, 0.9675801411038264);
		circles.emplace_back(-2.716670243535191, -3.774480333086103, 1.071774113015272);
		circles.emplace_back(-4.340807700064033, -0.8353462559171021, 0.7314768652198835);
		circles.emplace_back(-3.762432138901204, -2.688502355013043, 0.9692233500769362);
		circles.emplace_back(4.871054736431688, -1.32192520191893, 1.806439914205112);
		circles.emplace_back(1.400925742927939, -3.560823269654065, 1.673705489258282);
		circles.emplace_back(-1.939379659015685, -2.570814068894833, 0.5221215251134709);
		circles.emplace_back(-0.3554586763493717, -3.27073477441445, 0.5293240975355729);
		circles.emplace_back(-4.675342238042504, 3.347653003875166, 1.099780274392105);
		circles.emplace_back(-0.5093448772095144, -1.563291710335761, 0.7170039898483083);
		circles.emplace_back(4.99248158885166, 3.479128286708146, 1.105343137052841);
		circles.emplace_back(4.915528160054237, 3.781263360287994, 0.766172664775513);
		circles.emplace_back(4.745918700937182, -4.211900786031038, 1.213938084687106);
		circles.emplace_back(4.144805099349469, 3.316206422168761, 0.9004910751478746);
		circles.emplace_back(-0.4911328922025859, 1.047767584677786, 0.6861872322624549);
		circles.emplace_back(-1.930469854269177, 3.25730841839686, 0.8765454551437869);
		circles.emplace_back(-4.394605734851211, -3.919394065160304, 1.562006810563616);
		circles.emplace_back(2.069614760112017, -2.223860553931445, 0.7854028542758896);
		circles.emplace_back(-0.215812202077359, 4.549223722424358, 1.109194641350769);
	}
	result_expected = 7.696555175326627;

	timer.reset();
	result_actual = algorithm(a124, b124, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #124: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a125(-3.345984592568129, -2.771435065194964);
	Point b125(2.877560948487371, -3.430283596739173);
	{
		circles.emplace_back(-2.869479155633599, -4.534430948551744, 0.7742097595939412);
		circles.emplace_back(4.400428889784962, 4.904734629672021, 1.477033338579349);
		circles.emplace_back(-2.813121259678155, -4.740997448097914, 0.9851519891293719);
		circles.emplace_back(1.196700294967741, -0.2208715840242803, 1.48450571896974);
		circles.emplace_back(4.972784409765154, 1.551279171835631, 0.5023493055952712);
		circles.emplace_back(-4.474668179173023, 0.345766928512603, 1.074232222069986);
		circles.emplace_back(2.790711664129049, -2.043701524380594, 0.6995431162184104);
		circles.emplace_back(-2.443570776376873, 1.102563256863505, 0.9746274939039722);
		circles.emplace_back(-0.3714152961038053, 4.565987240057439, 0.4281002881703898);
		circles.emplace_back(0.3736215154640377, 3.256909020710737, 0.6145623495103791);
		circles.emplace_back(3.621657316107303, 4.608842374291271, 1.053632058738731);
		circles.emplace_back(-3.82399998838082, -0.7195038138888776, 1.629397691437043);
		circles.emplace_back(-4.325770882423967, 2.20589981181547, 0.5146141499979421);
		circles.emplace_back(0.6392643903382123, -0.08535832399502397, 1.232818821421824);
		circles.emplace_back(-3.47123014042154, -1.045773548539728, 1.446147310943343);
		circles.emplace_back(-3.094091133680195, 0.06288147298619151, 0.9530651598004624);
		circles.emplace_back(-4.789804175961763, 0.5078584258444607, 0.7505681664915755);
		circles.emplace_back(1.355353679973632, 2.663154655601829, 1.096149911149405);
		circles.emplace_back(4.200385396834463, 1.58199360826984, 0.9578968964749947);
		circles.emplace_back(-0.4052855423651636, -4.274514347780496, 0.8961258467985317);
		circles.emplace_back(-3.228920151013881, -0.4807892325334251, 0.7305802322225645);
		circles.emplace_back(3.546562262345105, 4.157496204134077, 0.7850868433481082);
		circles.emplace_back(-4.947398959193379, 4.158459941390902, 1.096186126605607);
		circles.emplace_back(-1.391538137104362, 4.905663605313748, 1.072798543679528);
		circles.emplace_back(0.2990110288374126, -1.316129274200648, 1.552267874521203);
		circles.emplace_back(-0.5476584541611373, 2.300131188239902, 1.132380653708242);
		circles.emplace_back(-2.116808893624693, 1.820911637041718, 1.027926841774024);
		circles.emplace_back(-4.142262560781091, 2.467817149590701, 1.034301617066376);
		circles.emplace_back(-3.484075933229178, 2.924661559518427, 1.556688597402535);
		circles.emplace_back(1.519455665256828, -3.470321295317262, 1.150654509128071);
		circles.emplace_back(-1.746338398661464, -3.202304851729423, 1.027885385486297);
		circles.emplace_back(-0.6464395229704678, -3.102848574053496, 1.303405904141255);
		circles.emplace_back(-0.6442409637384117, 4.311207213904709, 0.7148080358048901);
		circles.emplace_back(-2.717179844621569, -0.989726351108402, 1.380553124868311);
		circles.emplace_back(-2.635128756519407, 0.9486337448470294, 1.345452724839561);
	}
	result_expected = 9.961129020223673;

	timer.reset();
	result_actual = algorithm(a125, b125, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #125: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a126(-3.55240574805066, -3.084200887009501);
	Point b126(3.062882447149605, 0.9482606295496225);
	{
		circles.emplace_back(2.323527035769075, -2.038779088761657, 0.5313480738783255);
		circles.emplace_back(2.038515883032233, -3.059390999842435, 1.291391217033379);
		circles.emplace_back(4.031076792161912, -0.3440389293245971, 0.5357511866139247);
		circles.emplace_back(-1.16566178156063, -2.167568581644446, 1.184582388005219);
		circles.emplace_back(-3.025186152663082, -0.06660730810835958, 0.7943726352183148);
		circles.emplace_back(1.067801683675498, -4.051207646261901, 0.9757734262617305);
		circles.emplace_back(-3.258330512326211, -1.141135117504746, 0.7505793193122372);
		circles.emplace_back(-4.636182675603777, 4.664085044059902, 0.6276113465661183);
		circles.emplace_back(-0.8765476546250284, -2.027619585860521, 1.078218575264327);
		circles.emplace_back(3.32971143303439, 3.2389568653889, 0.4776331096189096);
		circles.emplace_back(-0.386442847084254, 2.019627129193395, 1.353164415783249);
		circles.emplace_back(2.574354282114655, 3.390311996918172, 1.551676853257231);
		circles.emplace_back(-3.950139798689634, 2.783926643896848, 1.019112819922157);
		circles.emplace_back(1.330993149895221, 1.689045818056911, 1.028442594944499);
		circles.emplace_back(-2.96086378628388, -4.930630826856941, 1.499205866106786);
		circles.emplace_back(-4.767326114233583, 0.9487450192682445, 1.42632655359339);
		circles.emplace_back(2.631086695473641, 3.184847433585674, 1.026495964382775);
		circles.emplace_back(-4.787851020228118, 4.816140381153673, 0.4442746031796559);
		circles.emplace_back(-0.5818960280157626, 3.842499481979758, 1.03786751201842);
		circles.emplace_back(2.635935379657894, 2.128826293628663, 0.6552376969484612);
		circles.emplace_back(0.1672544027678668, 2.221255481708795, 0.9517518327804282);
		circles.emplace_back(1.218186256010085, -2.763122117612511, 0.5611046524485572);
		circles.emplace_back(0.217945312615484, -0.630704106297344, 1.008461878472008);
		circles.emplace_back(-2.779609595891088, 4.949407100211829, 1.583935595746152);
		circles.emplace_back(0.1793355750851333, -2.583736914675683, 0.3034315935568884);
		circles.emplace_back(-2.172963998746127, 2.857522626873106, 0.7097802445059642);
		circles.emplace_back(-2.516357807908207, 3.911144325975329, 0.8211480288067832);
		circles.emplace_back(0.2240941883064806, -2.249997828621417, 1.010544897126965);
		circles.emplace_back(-1.996161036659032, -4.980287111829966, 0.5906502274097875);
		circles.emplace_back(-0.05966291064396501, 3.702132722828537, 1.582492344477214);
		circles.emplace_back(-1.5857995278202, 0.3760924260132015, 1.20198831341695);
		circles.emplace_back(-0.7289186981506646, 2.096800927538425, 0.9895293983863666);
		circles.emplace_back(2.993088865187019, -4.089279023464769, 1.817282489896752);
		circles.emplace_back(-3.089197457302362, 1.409668431151658, 1.191476262477226);
		circles.emplace_back(-2.396198350470513, 1.026968786027282, 0.7589022004744037);
	}
	result_expected = 15.35409469145352;

	timer.reset();
	result_actual = algorithm(a126, b126, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #126: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a127(-3.519544474314898, 1.090503679588437);
	Point b127(2.587227237876505, -0.5175442900508642);
	{
		circles.emplace_back(0.6838629557751119, 1.701028833631426, 1.291749942139722);
		circles.emplace_back(-2.07120826235041, -2.877375159878284, 1.435540543007664);
		circles.emplace_back(-1.832928054500371, 2.477125071454793, 0.968258857470937);
		circles.emplace_back(-0.6214223313145339, 2.940271811094135, 0.7862079797079786);
		circles.emplace_back(4.514835921581835, 4.812267741654068, 0.9140832085395231);
		circles.emplace_back(-3.70362795656547, -2.251144715119153, 0.9427269764943048);
		circles.emplace_back(-0.1658765436150134, 1.363063903991133, 1.030387664795853);
		circles.emplace_back(1.896591840777546, -2.512867611367255, 1.158081675204448);
		circles.emplace_back(-2.641245007980615, 4.31022445904091, 0.8973692515166476);
		circles.emplace_back(-1.915389040950686, -1.351856307592243, 1.254399797343649);
		circles.emplace_back(4.22095998423174, 0.3678335598669946, 1.655024660355411);
		circles.emplace_back(-3.892638070974499, 3.663695270661265, 1.141392805264331);
		circles.emplace_back(4.522179982159287, -2.978177119512111, 0.5774764331756159);
		circles.emplace_back(-4.52903188066557, -2.947711281012744, 1.136784895253368);
		circles.emplace_back(3.254655075725168, 4.854194766376168, 1.038310877629556);
		circles.emplace_back(0.4725571000017226, -3.088198744226247, 1.512451303075068);
		circles.emplace_back(-4.548869591671973, -2.380667577963322, 1.104137584124692);
		circles.emplace_back(4.186615177895874, -3.816548807080835, 1.004801908344962);
		circles.emplace_back(4.940649850759655, -4.594844516832381, 1.394978707912378);
		circles.emplace_back(1.512614830862731, 1.194917887914926, 1.825352758285589);
		circles.emplace_back(2.285070803482085, 4.206135624554008, 0.6674532459815964);
		circles.emplace_back(-1.711062307003886, 0.7173701212741435, 1.239523648493923);
		circles.emplace_back(1.449746007565409, 3.685409694444388, 1.393905493314378);
		circles.emplace_back(-0.281980384606868, 0.8374357339926064, 1.264700580318458);
		circles.emplace_back(1.394752629566938, -3.235942313913256, 2.017758977389895);
		circles.emplace_back(1.649207116570324, -4.094063898082823, 0.7960982961812988);
		circles.emplace_back(1.280015057418495, -0.7959829014725983, 0.5944473708746955);
		circles.emplace_back(2.923995114397258, -4.041039950679988, 0.5566439313115552);
		circles.emplace_back(-0.1318096625618637, 0.7048465474508703, 1.402975694625638);
		circles.emplace_back(2.529309091623873, -2.248086163308471, 0.8230905238771811);
		circles.emplace_back(-1.522946876939386, -2.978087284136564, 1.184700148622505);
		circles.emplace_back(-0.08423471124842763, 1.445121441502124, 1.236343781952746);
		circles.emplace_back(1.043391854036599, 2.341840488370508, 0.9435795005178078);
	}
	result_expected = 20.33271652212578;

	timer.reset();
	result_actual = algorithm(a127, b127, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #127: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a128(-2.254287253599614, -3.156985519453883);
	Point b128(3.297058524098247, 1.641818398609757);
	{
		circles.emplace_back(1.639347856398672, -0.627853365149349, 1.497343321912922);
		circles.emplace_back(4.101443106774241, -2.431007057894021, 0.8033194836927577);
		circles.emplace_back(-4.022322345990688, -2.125011968892068, 1.273996040900238);
		circles.emplace_back(-3.662039099726826, -1.198245247360319, 0.8318998707691208);
		circles.emplace_back(-3.992238992359489, 4.476488705258816, 0.9631933982251212);
		circles.emplace_back(0.8822186361066997, 4.886136942077428, 1.3424728525104);
		circles.emplace_back(-4.139741908293217, -2.91673673549667, 0.6762482179095968);
		circles.emplace_back(1.100275514181703, 0.2137105376459658, 1.385927191772498);
		circles.emplace_back(-3.13567124074325, -0.522736229468137, 0.8975156091852113);
		circles.emplace_back(0.7510668667964637, 0.7258969289250672, 0.2923577445792034);
		circles.emplace_back(0.4248705809004605, 0.2132486528716981, 1.34290349741932);
		circles.emplace_back(-1.193673855159432, 1.847640874329954, 1.545144345820881);
		circles.emplace_back(-4.044686348643154, 3.525426376145333, 0.6217981538502499);
		circles.emplace_back(-2.752941239159554, -0.8270016522146761, 1.587138582183979);
		circles.emplace_back(4.674022605177015, -3.822894857730716, 0.9748564228648319);
		circles.emplace_back(0.1911494531668723, -1.663577959407121, 0.3383931268705055);
		circles.emplace_back(1.569257553201169, -3.800495627801865, 1.750188249279745);
		circles.emplace_back(-1.851435310672969, 4.097109173890203, 0.5952849827473983);
		circles.emplace_back(-2.467656566295773, 4.800952638033777, 0.9601278817513957);
		circles.emplace_back(0.1522375852800906, 0.2481175470165908, 1.131792973238043);
		circles.emplace_back(1.744855425786227, 4.003889777231961, 0.8758061145665124);
		circles.emplace_back(3.340623003896326, -4.028601252939552, 0.9574793275678529);
		circles.emplace_back(-2.79313295846805, 2.734228677581996, 1.082485468755476);
		circles.emplace_back(-4.889779400546104, 1.330989499110729, 1.305163870309479);
		circles.emplace_back(-0.344440087210387, -4.822981806937605, 0.8682079333579167);
		circles.emplace_back(-3.10856761643663, -3.053680134471506, 0.7424827264854684);
		circles.emplace_back(-1.109146939124912, -3.992408302146941, 0.9962383880047126);
		circles.emplace_back(-0.06768773542717099, -4.863634824287146, 1.174129732069559);
		circles.emplace_back(-2.072410646360368, 2.909306788351387, 1.064341199561022);
		circles.emplace_back(2.634553944226354, -1.646732927765697, 0.387630058103241);
		circles.emplace_back(4.736394549254328, -2.849221408832818, 0.6956888598157093);
		circles.emplace_back(-1.700270373839885, -2.939439255278558, 0.4737866065697744);
		circles.emplace_back(-2.183393321465701, -4.120457211975008, 0.4069966748123988);
		circles.emplace_back(0.559549720492214, 2.752698550466448, 1.154850405291654);
		circles.emplace_back(-0.2623497485183179, -0.788443956989795, 1.471112410235219);
		circles.emplace_back(-4.176360361743718, 1.474756740499288, 1.172539025289006);
		circles.emplace_back(-3.843820493202657, 0.7664361759088933, 0.9946419475367292);
	}
	result_expected = 16.71096454881414;

	timer.reset();
	result_actual = algorithm(a128, b128, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #128: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a129(-2.614884703885764, 3.670344607904553);
	Point b129(2.688421418424696, 0.5833044145256281);
	{
		circles.emplace_back(-0.7848021597601473, -2.359466326888651, 1.381397570879199);
		circles.emplace_back(0.6413899199105799, 3.428548488300294, 1.291897962871007);
		circles.emplace_back(-0.9569201921112835, -4.322984039317816, 1.177806572732516);
		circles.emplace_back(-0.732679630164057, 1.244226752314717, 0.6825427033239975);
		circles.emplace_back(-0.491814052220434, 4.670416831504554, 1.37780220627319);
		circles.emplace_back(-1.403556365985423, 3.072150212246925, 0.7127562157111242);
		circles.emplace_back(0.08078537182882428, 4.34265818214044, 0.844109921134077);
		circles.emplace_back(3.177266211714596, 1.901912281755358, 1.103459063009359);
		circles.emplace_back(-3.692219459917396, -2.980381224770099, 0.9759428034303709);
		circles.emplace_back(3.446970887016505, -4.51990321977064, 1.371617534500547);
		circles.emplace_back(1.179657478351146, -0.3924929932691157, 1.489536556391977);
		circles.emplace_back(-2.370837780181319, -4.591774919535965, 1.115459125139751);
		circles.emplace_back(-4.038375688251108, 0.5462446133606136, 1.366816685418598);
		circles.emplace_back(-3.831662323791534, 0.07347357692196965, 1.341352036898024);
		circles.emplace_back(0.4869996313937008, -1.784809755627066, 1.550522933504544);
		circles.emplace_back(-1.669198370072991, -3.539078084286302, 0.2940141478786245);
		circles.emplace_back(3.128030060324818, 2.445247310679406, 0.9360347664682194);
		circles.emplace_back(2.727393328677863, -3.559406294953078, 0.6476442226441577);
		circles.emplace_back(-3.064163762610406, -1.665866544935852, 1.726572712673806);
		circles.emplace_back(1.384493669029325, -1.115729825105518, 0.8333415746921673);
		circles.emplace_back(-4.045380626339465, -3.552473995368928, 0.9693913295166566);
		circles.emplace_back(2.619515799451619, -4.758854622486979, 1.385981515771709);
		circles.emplace_back(-1.533493085298687, 3.801655287388712, 0.9631408741930499);
		circles.emplace_back(1.332202872727066, -3.705706347245723, 0.7377954187570139);
		circles.emplace_back(-4.182166035752743, 1.422736288513988, 0.9817426880588754);
		circles.emplace_back(3.4360919916071, 4.492687440942973, 0.992801120947115);
		circles.emplace_back(-0.4728155047632754, -0.7121562189422548, 0.63081719300244);
		circles.emplace_back(-3.255154208745807, -1.510642406065017, 1.679841932537965);
		circles.emplace_back(-0.4501181398518384, 1.440616876352578, 0.7602165431948378);
		circles.emplace_back(-3.795176062267274, -1.377729719970375, 1.072789020999335);
		circles.emplace_back(-1.586514527443796, 2.191537527833134, 1.323703958862461);
		circles.emplace_back(1.721449310425669, 4.00029894663021, 0.4058140155626461);
		circles.emplace_back(-2.725436736363918, -1.949029851239175, 1.199464086373337);
		circles.emplace_back(0.3469926794059575, 1.143919338937849, 0.6973419695859775);
	}
	result_expected = 10.3963230054226;

	timer.reset();
	result_actual = algorithm(a129, b129, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #129: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a130(-3.632484782021493, -0.6009640377014875);
	Point b130(3.378866770770401, -2.480527495965362);
	{
		circles.emplace_back(-0.7137768738903105, 0.7459255517460406, 0.7846977632725611);
		circles.emplace_back(3.287162336055189, 0.90443269116804, 1.142121899197809);
		circles.emplace_back(2.340299624484032, 3.701321233529598, 0.6160478080855682);
		circles.emplace_back(0.7334507559426129, -0.06250322097912431, 0.9261781874811276);
		circles.emplace_back(0.3316634730435908, 2.487653556745499, 1.256934994342737);
		circles.emplace_back(-3.19890107261017, 2.688092917669564, 1.205353421089239);
		circles.emplace_back(-1.053945634048432, 4.033289307262748, 0.5810328768333419);
		circles.emplace_back(3.198295945767313, 4.994859367143363, 1.394366952474229);
		circles.emplace_back(2.931575428228825, 0.7856202241964638, 0.5364183909492567);
		circles.emplace_back(-2.698849074076861, -2.034925410989672, 1.51290713546332);
		circles.emplace_back(3.274532796349376, -3.576135297771543, 0.9058659954229369);
		circles.emplace_back(4.602776116225868, 1.25836270628497, 1.173520203935914);
		circles.emplace_back(-1.812011145520955, -0.4553508828394115, 1.368607942503877);
		circles.emplace_back(2.536482859868556, 0.867006944026798, 1.032249752967618);
		circles.emplace_back(0.588312444742769, -1.174012848641723, 1.30563311020378);
		circles.emplace_back(-2.005003017839044, 2.813707969617099, 1.008564775506966);
		circles.emplace_back(4.548922542016953, -4.791767920833081, 0.3104228901909664);
		circles.emplace_back(1.691229969728738, 0.1364090270362794, 1.459829800925218);
		circles.emplace_back(-0.06657118210569024, 4.765895309392363, 0.8397167975315823);
		circles.emplace_back(-1.822851330507547, 0.6245699082501233, 0.6318409466417506);
		circles.emplace_back(-4.36005501775071, 1.261652687098831, 0.8695955196162686);
		circles.emplace_back(-4.594034443143755, -4.409560428466648, 1.108590604388155);
		circles.emplace_back(-2.96608324861154, -3.676016435492784, 1.239796163584105);
		circles.emplace_back(0.5463372427038848, -2.859677735250443, 1.392868968774565);
		circles.emplace_back(-1.455542154144496, -3.228866423014551, 0.9610253922408446);
		circles.emplace_back(2.388856278266758, -3.130583500023931, 0.901432759151794);
		circles.emplace_back(-2.882748374249786, -3.177051146049052, 1.315527715045027);
		circles.emplace_back(4.470108828973025, -3.838113031815737, 0.4476811413886025);
		circles.emplace_back(-2.088751222472638, 0.240839512553066, 0.9328464066376909);
		circles.emplace_back(-0.6517797685228288, 1.701337702106684, 1.246645329962484);
		circles.emplace_back(3.470931041520089, -4.927851955872029, 0.9337180982576683);
		circles.emplace_back(4.941790059674531, -3.701987417880446, 0.4799945045029744);
		circles.emplace_back(0.02600041916593909, -1.447738779243082, 1.334087534458376);
		circles.emplace_back(-2.051571176853031, -4.158824172336608, 0.9634895368246361);
		circles.emplace_back(-2.073641226161271, -2.8098074789159, 1.405121980723925);
		circles.emplace_back(-0.1366434129886329, 2.558405005838722, 1.785692218109034);
	}
	result_expected = 19.7171391370662;

	timer.reset();
	result_actual = algorithm(a130, b130, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #130: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a131(-3.344384736847132, -0.5326141845434904);
	Point b131(3.934843746479601, -2.678976496681571);
	{
		circles.emplace_back(1.575119064655155, -0.7664764276705682, 0.7082424437860027);
		circles.emplace_back(4.603996446821839, -3.569881815928966, 1.022412131982855);
		circles.emplace_back(3.282500288914889, 1.927805163431913, 1.474542281520553);
		circles.emplace_back(3.805717502254993, 4.343083591666073, 0.6687797194113955);
		circles.emplace_back(2.714648547116667, -4.194465570617467, 1.50185638226103);
		circles.emplace_back(2.254821944516152, -1.234177451115102, 0.7192133764969184);
		circles.emplace_back(-3.087867840658873, 2.417845276650041, 0.6815636414801701);
		circles.emplace_back(-0.3347891778685153, 0.5838315957225859, 0.9692464279243722);
		circles.emplace_back(1.472113265190274, -1.791196849662811, 1.234662569942884);
		circles.emplace_back(2.844392552506179, 4.784142256248742, 0.4108106927247718);
		circles.emplace_back(0.4629015293903649, 1.256052756216377, 1.33165923373308);
		circles.emplace_back(1.350066696759313, 0.3118160949088633, 1.642307806783356);
		circles.emplace_back(2.625386381987482, -1.240394294727594, 0.8726670426083728);
		circles.emplace_back(-3.104329307097942, 3.29323009820655, 1.454381980677135);
		circles.emplace_back(3.74284140067175, -3.555121461395174, 0.6547601893311366);
		circles.emplace_back(4.640014560427517, -0.02252470469102263, 0.7229341445723548);
		circles.emplace_back(3.854173517320305, 2.136568154674023, 1.452532045054249);
		circles.emplace_back(0.8694326947443187, 2.052938484121114, 0.7057341155828908);
		circles.emplace_back(1.817941267509013, -2.846733017358929, 0.9824395654490217);
		circles.emplace_back(-2.597957404796034, -3.91532746842131, 1.693778248527087);
		circles.emplace_back(-0.4413149482570589, 1.575063995551318, 1.127569449762814);
		circles.emplace_back(-4.866455879528075, -3.076370533090085, 0.4410009685205296);
		circles.emplace_back(2.370081127155572, 4.182471407111734, 1.86020398249384);
		circles.emplace_back(1.07758661499247, -1.48695066338405, 0.7293470213422552);
		circles.emplace_back(-1.338850201573223, -1.295139354187995, 0.9024941748706623);
		circles.emplace_back(-1.218924999702722, 3.310266539920121, 1.558047215011902);
		circles.emplace_back(1.262217026669532, -1.299815049860626, 0.7981650108238681);
		circles.emplace_back(4.865879674907774, 2.303914113435894, 1.313713863515295);
		circles.emplace_back(1.606547425035387, -2.334890321362764, 0.3179822896374389);
		circles.emplace_back(-1.586741183418781, 0.08697518380358815, 0.9190830811159685);
		circles.emplace_back(-3.478464640211314, 2.595765178557485, 0.4762027449673041);
		circles.emplace_back(-1.284104569349438, 2.395349557045847, 1.510379513190128);
		circles.emplace_back(3.750059625599533, 1.934180806856602, 0.7819088074145838);
		circles.emplace_back(4.324795238208026, -4.310427836608142, 0.993865027022548);
		circles.emplace_back(-4.571924086194485, -3.605947552714497, 1.775496565341018);
		circles.emplace_back(-2.681259957607836, -2.68816038267687, 0.9941401661140844);
		circles.emplace_back(2.528996604960412, 1.063563574571162, 1.112857368146069);
		circles.emplace_back(4.396323666442186, -4.334717991296202, 1.558298087469302);
	}
	result_expected = 15.32841282183361;

	timer.reset();
	result_actual = algorithm(a131, b131, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #131: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a132(-3.451501812320203, 1.81704837270081);
	Point b132(2.867061154451221, 1.60371440090239);
	{
		circles.emplace_back(-2.040649096015841, -0.8650970621965826, 0.7930898189777508);
		circles.emplace_back(-0.9563512704335153, -3.93972183810547, 1.134343034471385);
		circles.emplace_back(-4.339362655300647, -3.662730667274445, 1.502115304698236);
		circles.emplace_back(-2.907038785051554, -0.4064400144852698, 0.8279695786302909);
		circles.emplace_back(3.890202955808491, -3.711269383784384, 1.251016788766719);
		circles.emplace_back(-1.762119808699936, 3.99149204371497, 1.095800441759638);
		circles.emplace_back(-2.556592293549329, -4.811561338137835, 0.9505040754796936);
		circles.emplace_back(1.704052512068301, 4.924282671418041, 1.101826377748512);
		circles.emplace_back(0.3995309001766145, -3.052400404121727, 0.9661413144553079);
		circles.emplace_back(-0.4332627332769334, 1.60360500914976, 0.6842942268354818);
		circles.emplace_back(-1.633699100930244, 2.299390484113246, 1.11649115041364);
		circles.emplace_back(-4.003169133793563, 0.7522854185663164, 0.8327405307209119);
		circles.emplace_back(-4.55053853103891, -1.510374469216913, 1.164236778230406);
		circles.emplace_back(1.321040077600628, 0.1452199253253639, 0.9959058849839493);
		circles.emplace_back(-3.703504160512239, 4.360183507669717, 0.9063121767016127);
		circles.emplace_back(4.106652226764709, -4.237953966949135, 0.7668923334917053);
		circles.emplace_back(-4.815276677254587, 0.1489268825389445, 0.8243442319566383);
		circles.emplace_back(-2.569429462309927, -0.3805589978583157, 1.079230796988122);
		circles.emplace_back(-3.161172915715724, -2.439688134472817, 0.7854213989572599);
		circles.emplace_back(-2.339748672675341, -4.277988562826067, 1.339517715550028);
		circles.emplace_back(1.221465410199016, 2.36010734224692, 1.322851987020113);
		circles.emplace_back(4.210898524615914, 3.035582776647061, 1.206459772097878);
		circles.emplace_back(0.6929625640623271, -2.334390587639064, 0.6146610928000882);
		circles.emplace_back(-4.401260267477483, 0.6952910288237035, 1.290032751648687);
		circles.emplace_back(-3.567830922547728, -0.0105429976247251, 1.251598641672172);
		circles.emplace_back(-0.5655731982551515, -4.436777152586728, 0.7755152784986421);
		circles.emplace_back(-4.39957493217662, 0.7006227714009583, 0.8838919359492138);
		circles.emplace_back(0.5435726349242032, -0.5035562091507018, 0.7629003610229119);
		circles.emplace_back(-4.835846072528511, 1.640372278634459, 1.294374545873143);
		circles.emplace_back(0.9131546900607646, -2.973901641089469, 0.8401173612801358);
		circles.emplace_back(-3.681042522657663, 3.923953131306916, 1.502459316817112);
		circles.emplace_back(-3.607015598099679, -2.668140849564224, 0.8661141941091045);
		circles.emplace_back(-1.170822570566088, 2.220494581852108, 0.8961967036360874);
		circles.emplace_back(1.061731751542538, 1.784066793043166, 1.055870580603369);
		circles.emplace_back(-3.163607127498835, -2.438768411520869, 1.109174706763588);
		circles.emplace_back(4.660802653525025, 0.1655871677212417, 0.7507326411781832);
		circles.emplace_back(-2.161098339129239, -3.456925533246249, 1.188058212888427);
		circles.emplace_back(-0.5257275956682861, 3.5176289989613, 1.392432421981357);
	}
	result_expected = 9.078745531024694;

	timer.reset();
	result_actual = algorithm(a132, b132, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #132: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a133(-2.11256270064041, 1.644011335447431);
	Point b133(2.606317525263876, -2.450352599844337);
	{
		circles.emplace_back(3.64913230529055, 1.91063970560208, 0.6679773861775175);
		circles.emplace_back(-2.796570749487728, -0.861000728327781, 0.8680258146254345);
		circles.emplace_back(-2.450047165621072, -4.769004329573363, 1.465343501535244);
		circles.emplace_back(2.814081620890647, -3.971160671208054, 0.9704477945109828);
		circles.emplace_back(-1.350170860532671, 4.125068916473538, 1.117621685587801);
		circles.emplace_back(-1.14505406236276, -1.612324819434434, 1.001736809755675);
		circles.emplace_back(-0.3411665628664196, -0.0004142173565924168, 0.5609022490447386);
		circles.emplace_back(-1.783089770469815, 4.090683723334223, 1.184929401264526);
		circles.emplace_back(2.531534901354462, -3.378717501182109, 0.7545904773054644);
		circles.emplace_back(-2.553647675085813, 2.445787705946714, 0.457629466545768);
		circles.emplace_back(-0.650469686370343, 1.666275055613369, 1.10110209339764);
		circles.emplace_back(3.935930652078241, -1.623650097753853, 1.023601314076222);
		circles.emplace_back(-0.968583223875612, 2.812804586719722, 1.142682503233664);
		circles.emplace_back(-3.365790855605155, -0.06076792953535914, 1.428999293898232);
		circles.emplace_back(-3.129786571953446, 3.74800049001351, 1.017522378475405);
		circles.emplace_back(4.324244691524655, -3.712373462039977, 1.208365134778433);
		circles.emplace_back(-0.2815560554154217, 3.498736203182489, 1.063366662082262);
		circles.emplace_back(-2.3761115106754, 3.764648044016212, 1.029627683921717);
		circles.emplace_back(-0.5575383058749139, 4.666650414001197, 1.027461535925977);
		circles.emplace_back(-2.451357741374522, -4.760302442591637, 0.8576860598521306);
		circles.emplace_back(-3.004724762868136, 2.673914690967649, 1.058903346932493);
		circles.emplace_back(2.904139251913875, -4.443375875707716, 0.9581829993287101);
		circles.emplace_back(3.009376919362694, -4.225745771545917, 1.4256598303793);
		circles.emplace_back(0.2977386186830699, 0.7308064331300557, 1.386428913217969);
		circles.emplace_back(-4.858914713840932, -0.3404170111753047, 0.8768310693791136);
		circles.emplace_back(-3.021991702262312, 0.5330163449980319, 0.2851733912015333);
		circles.emplace_back(-1.408539486583322, -3.05140531854704, 0.9509618320269509);
		circles.emplace_back(2.06528804032132, -3.292330976109952, 0.899276456539519);
		circles.emplace_back(3.919224024284631, -3.841107415501028, 1.101048819324933);
		circles.emplace_back(1.531509661581367, 0.2733524166978896, 0.6506440976867451);
		circles.emplace_back(4.062357305083424, 0.1917536440305412, 0.7990614629117772);
		circles.emplace_back(-3.991918743122369, 1.579399213660508, 1.100648541119881);
		circles.emplace_back(-1.689920860808343, -0.2236958057619631, 1.499151077284478);
		circles.emplace_back(-2.70169977331534, -4.276518241968006, 1.337899476313032);
		circles.emplace_back(-4.833880772348493, -3.40277160750702, 1.438527858699672);
		circles.emplace_back(-1.564396296162158, 3.415679123718292, 1.320443381299265);
		circles.emplace_back(-0.5378250847570598, -2.548775786999613, 1.259477410442196);
	}
	result_expected = -1;

	timer.reset();
	result_actual = algorithm(a133, b133, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #133: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a134(-2.18751174537465, -3.741052536293864);
	Point b134(3.272299939300865, 0.7129339817911386);
	{
		circles.emplace_back(-0.4030463821254671, -4.69216174678877, 0.9854215034050866);
		circles.emplace_back(2.300450981128961, -4.415477144066244, 1.507243467471562);
		circles.emplace_back(-0.9839926124550402, -0.1255924976430833, 1.182818181277253);
		circles.emplace_back(1.620065032038838, -0.4270883020944893, 1.334941489133052);
		circles.emplace_back(-2.718618393409997, 2.184575602877885, 0.8742066302569582);
		circles.emplace_back(1.986463528592139, -2.915379873011261, 1.021701001538895);
		circles.emplace_back(4.427187105175108, 3.92722754040733, 0.7841371566290035);
		circles.emplace_back(3.025049755815417, 2.782084986101836, 0.6706974719418213);
		circles.emplace_back(1.930922295432538, 0.9050632384605706, 1.331280933250673);
		circles.emplace_back(-1.855971373151988, 1.848692481871694, 1.100765270716511);
		circles.emplace_back(-1.02825520792976, -3.969503825064749, 0.8953562578419223);
		circles.emplace_back(-1.272363641764969, -0.5804127943702042, 1.065701183932833);
		circles.emplace_back(1.711744300555438, -4.29575317306444, 0.232270993781276);
		circles.emplace_back(0.9204161888919771, 4.826443439815193, 0.5992839318001643);
		circles.emplace_back(1.455519336741418, 2.010054339189082, 1.387230971013196);
		circles.emplace_back(-4.723141684662551, 0.6182062602601945, 1.345613146177493);
		circles.emplace_back(2.797095605637878, -1.109305245336145, 1.127760455221869);
		circles.emplace_back(2.115027888212353, 3.064245644491166, 0.6366155146388337);
		circles.emplace_back(-0.8912279759533703, 3.969819874037057, 0.4128579379292205);
		circles.emplace_back(3.448692348320037, -2.585262304637581, 1.134635792835615);
		circles.emplace_back(2.677173132542521, 4.431019097100943, 0.9776375797344371);
		circles.emplace_back(2.250213872175664, 2.671719205100089, 1.308700377424247);
		circles.emplace_back(-0.6226923386566341, -4.884470293764025, 1.526515716291033);
		circles.emplace_back(-4.489210008177906, 3.739388922695071, 0.9658656580606475);
		circles.emplace_back(4.773534482810646, 0.6089301663450897, 1.197363665211014);
		circles.emplace_back(-4.239578985143453, -4.715825922321528, 0.9714526158990338);
		circles.emplace_back(-3.605315040331334, -1.849853231105953, 0.4365112764528021);
		circles.emplace_back(-0.7236233376897871, 4.895526340696961, 0.4349565986776724);
		circles.emplace_back(0.1865244680084288, 1.339089653920382, 1.79934368066024);
		circles.emplace_back(-0.9186443057842553, -0.1992747443728149, 0.5567101943539455);
		circles.emplace_back(-0.1079451735131443, -4.812115805689245, 0.9296542402124032);
		circles.emplace_back(-4.544467276427895, 2.724978032056242, 0.6983754033455625);
		circles.emplace_back(-1.976691575255245, 4.786299157422036, 1.414214175078087);
		circles.emplace_back(-3.496768504846841, -4.922125681769103, 0.7475611769827082);
		circles.emplace_back(-1.02116673020646, 4.590648987796158, 1.394858668162487);
	}
	result_expected = 14.4175573860998;

	timer.reset();
	result_actual = algorithm(a134, b134, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #134: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a135(-3.242637894582003, 0.3069411385804415);
	Point b135(3.047851604875177, -1.940266033634543);
	{
		circles.emplace_back(-4.884532152209431, 1.560286919120699, 1.376351375714876);
		circles.emplace_back(-4.750886315014213, -1.083777670282871, 0.9597086305497213);
		circles.emplace_back(-3.722609125543386, 4.059526019264013, 0.445796246570535);
		circles.emplace_back(3.311587919015437, -4.647309316787869, 0.8382582260062917);
		circles.emplace_back(-0.3788226866163313, -1.025703081395477, 1.718204948701896);
		circles.emplace_back(-4.57240961259231, 0.4645151714794338, 0.8884973370237276);
		circles.emplace_back(4.743470016401261, -4.983898426871747, 1.549505468015559);
		circles.emplace_back(4.761357039678842, 0.2725797123275697, 0.7544497336959466);
		circles.emplace_back(-3.488464744295925, -1.459793460089713, 0.9613372585503384);
		circles.emplace_back(-2.340471732895821, -2.893019637558609, 1.160380775644444);
		circles.emplace_back(-0.643633792642504, -3.262820409145206, 0.9901215836638584);
		circles.emplace_back(-1.385875765699893, -2.695391539018601, 1.390031933714636);
		circles.emplace_back(-2.165808684658259, 4.98707148944959, 1.175219776458107);
		circles.emplace_back(-3.491289450321347, -2.313218747731298, 1.752048335061408);
		circles.emplace_back(-4.743639656808227, -4.075996179599315, 1.192926506954245);
		circles.emplace_back(2.097493789624423, -3.344289443921298, 0.9701561962487175);
		circles.emplace_back(4.243242416996509, 0.3611553623341024, 1.413672727881931);
		circles.emplace_back(-1.378946083132178, -2.615694010164589, 0.4914557691896334);
		circles.emplace_back(-2.511998710688204, -3.291268639732152, 0.934673632751219);
		circles.emplace_back(-4.335295867640525, 3.524064321536571, 0.8310543458210304);
		circles.emplace_back(-4.112773879896849, -2.689180227462202, 1.623568638018332);
		circles.emplace_back(-1.962763092014939, -1.363053394015878, 0.9779832350322976);
		circles.emplace_back(3.514190448913723, -4.659200098831207, 1.042107219877653);
		circles.emplace_back(3.903515234123915, -2.769045948516577, 1.045044793304987);
		circles.emplace_back(-1.297354164998978, 4.800693893339485, 1.168562168045901);
		circles.emplace_back(3.338318134192377, 2.879832207690924, 0.3369122487260028);
		circles.emplace_back(2.606139581184834, 0.8842088398523629, 1.18536376573611);
		circles.emplace_back(2.123243131209165, 1.79929788922891, 0.9778284564381464);
		circles.emplace_back(0.8016715361736715, 3.268265018705279, 0.8672134397784248);
		circles.emplace_back(1.21479699620977, -3.766541753429919, 1.205677721905522);
		circles.emplace_back(-3.404830091167241, -4.951143122743815, 1.279522239905782);
		circles.emplace_back(-0.003254215698689222, -3.791513724718243, 1.734625130682252);
		circles.emplace_back(4.501590577419847, -2.555337229277939, 1.175777365663089);
		circles.emplace_back(-0.4361430532298982, -2.219882078934461, 0.5129703947110101);
		circles.emplace_back(-0.3606493142433465, -0.4767515021376312, 1.435123813454993);
		circles.emplace_back(-4.455415427219123, -1.461014973465353, 1.125596506497823);
	}
	result_expected = 7.530251881611333;

	timer.reset();
	result_actual = algorithm(a135, b135, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #135: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a136(-2.62992040393874, -0.4034100752323866);
	Point b136(2.971208186354488, 1.492669576779008);
	{
		circles.emplace_back(-4.97668948257342, -0.1019411697052419, 0.7456140317255631);
		circles.emplace_back(-4.57223299657926, -0.1033066515810788, 1.248830587859265);
		circles.emplace_back(3.603689770679921, -4.94792117504403, 0.8171205452876165);
		circles.emplace_back(-0.793700001668185, 2.451286574359983, 0.8106768712168559);
		circles.emplace_back(-2.074844150338322, 2.948026845697314, 0.7379671780625358);
		circles.emplace_back(-4.924270713236183, -0.6775647145695984, 1.439849240588956);
		circles.emplace_back(0.4567777109332383, 4.213528053369373, 1.335923853307031);
		circles.emplace_back(-1.142492743674666, -4.82510028174147, 0.68143362889532);
		circles.emplace_back(0.9692066186107695, 0.4793425719253719, 1.026495770434849);
		circles.emplace_back(-2.422953632194549, 2.161148313898593, 0.6453495833324268);
		circles.emplace_back(2.54161047982052, 4.707550478633493, 0.4664049546932801);
		circles.emplace_back(3.735677504446357, 3.857000621501356, 1.509614525199868);
		circles.emplace_back(-0.3951092972420156, -0.812143546063453, 0.5352258181897923);
		circles.emplace_back(-1.103794754017144, 1.841037378180772, 0.715324802068062);
		circles.emplace_back(2.111107867676765, 3.715548941399902, 0.7621951246401295);
		circles.emplace_back(-1.560192147735506, -2.06177415093407, 0.7674353182548657);
		circles.emplace_back(-1.681369652505964, -3.546416417229921, 1.307557738269679);
		circles.emplace_back(-1.89133730949834, 3.130861904937774, 1.098052610387094);
		circles.emplace_back(3.702466033864766, 0.1984142116270959, 0.9338018990820273);
		circles.emplace_back(-2.880688591394573, -3.174347763415426, 1.909131609485484);
		circles.emplace_back(-2.264617362525314, -1.890370000619441, 1.1969353916822);
		circles.emplace_back(3.899010948371142, -3.320426575373858, 1.026387613010593);
		circles.emplace_back(-1.609109218697995, -4.477948902640492, 0.6643211623420938);
		circles.emplace_back(-4.756589757744223, 4.323863333556801, 0.7327584278071299);
		circles.emplace_back(-2.206617144402117, -4.388721131253988, 0.9091456264955923);
		circles.emplace_back(0.5337361874990165, 4.180969048757106, 1.109712582384236);
		circles.emplace_back(0.2336893533356488, 0.1797905541025102, 0.729835096350871);
		circles.emplace_back(4.530033154878765, -3.579488035757095, 0.8831654458073899);
		circles.emplace_back(-3.023791268933564, 4.427158266771585, 1.309561017272062);
		circles.emplace_back(-4.805169019382447, -0.05160445580258965, 1.589927317365073);
		circles.emplace_back(2.327205722685903, 4.421495704445988, 1.324840625398792);
		circles.emplace_back(-0.1829900196753442, -2.58212509797886, 1.159313863213174);
		circles.emplace_back(-1.283482958097011, -4.407501507084817, 1.04395063885022);
		circles.emplace_back(2.237476177979261, 2.415160646196455, 1.170190200186334);
		circles.emplace_back(-3.525462208781391, 2.690615693572909, 1.167914821044542);
		circles.emplace_back(1.232090240810066, -0.2208138746209443, 0.9315834457753226);
		circles.emplace_back(-4.246354543138295, 3.435499363113195, 1.179802824300714);
		circles.emplace_back(1.271974791307002, -0.1863945857621729, 0.6085993898799642);
	}
	result_expected = 6.181869232196096;

	timer.reset();
	result_actual = algorithm(a136, b136, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #136: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a137(-3.953093289863318, -0.2115188669413328);
	Point b137(2.958702882286161, 2.109614500775933);
	{
		circles.emplace_back(-0.04710691282525659, 4.255196230951697, 1.19612266740296);
		circles.emplace_back(-2.175354973878711, -4.832504328805953, 1.031347679975443);
		circles.emplace_back(-0.01558567630127072, -2.353167205583304, 0.5802731515141204);
		circles.emplace_back(-2.21820494858548, -3.235403543803841, 1.044370208843611);
		circles.emplace_back(-1.774852985981852, 3.976159302983433, 1.404504018300213);
		circles.emplace_back(1.070459138136357, -2.129852164071053, 0.6227155513362959);
		circles.emplace_back(3.834731348324567, 3.827532937284559, 1.087545222020708);
		circles.emplace_back(3.182258249726146, -1.49829771136865, 1.852794001833536);
		circles.emplace_back(-3.577288442756981, 4.910590227227658, 1.311165502178483);
		circles.emplace_back(-3.036864541936666, -3.750986463855952, 1.058721802872606);
		circles.emplace_back(-4.255196156445891, 1.249140670988709, 1.135480142035521);
		circles.emplace_back(4.378540592733771, -4.039769389200956, 0.4948513739509507);
		circles.emplace_back(-4.702235099393874, -2.86560746608302, 1.267227290873416);
		circles.emplace_back(-1.963769167196006, 4.907501561101526, 1.148114013276063);
		circles.emplace_back(-2.297269648406655, 4.314302506390959, 1.337634527147747);
		circles.emplace_back(-4.185317845549434, 3.100334096234292, 1.741494863363914);
		circles.emplace_back(4.651670425664634, 2.458958283532411, 1.478097423282452);
		circles.emplace_back(2.306534361559898, 0.4674547701142728, 1.674727056338452);
		circles.emplace_back(3.795885320287198, -0.7445943984203041, 1.131929877330549);
		circles.emplace_back(0.4094973136670887, -0.7960879453457892, 1.247922771400772);
		circles.emplace_back(3.032551275100559, 3.400722409132868, 0.5051070576766505);
		circles.emplace_back(-1.030120977666229, -3.610936601180583, 0.6352717834291979);
		circles.emplace_back(-4.150794066954404, -3.157270036172122, 0.6154427831294015);
		circles.emplace_back(-3.915489937644452, 3.259755761828274, 0.8559056853642687);
		circles.emplace_back(-0.06944842869415879, 1.106541252229363, 1.290208509215154);
		circles.emplace_back(-4.227911841589957, -1.632024447899312, 0.8818238447653129);
		circles.emplace_back(-2.257482453715056, -0.8505649887956679, 1.127229903987609);
		circles.emplace_back(-4.626687488052994, 1.754576193634421, 1.352386810095049);
		circles.emplace_back(-1.641643212642521, -1.955895510036498, 0.214990387740545);
		circles.emplace_back(4.63788767112419, -3.609047948848456, 1.415415398892947);
		circles.emplace_back(-0.5781701835803688, 2.821221554186195, 1.129126748605631);
		circles.emplace_back(4.263497327920049, 2.074673234019428, 0.8992291547590866);
		circles.emplace_back(2.691861952189356, -1.11256766365841, 1.145745743508451);
		circles.emplace_back(-0.8810560894198716, -2.800579804461449, 0.1501104108290747);
		circles.emplace_back(-3.588098667096347, -2.409440616611391, 1.082824580348097);
	}
	result_expected = 16.74955101277525;

	timer.reset();
	result_actual = algorithm(a137, b137, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #137: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a138(-2.232928532641381, 2.193043382838368);
	Point b138(2.870440253522247, 3.446857953444123);
	{
		circles.emplace_back(-0.6888697319664061, 0.9118399978615344, 1.125125980027951);
		circles.emplace_back(1.497980060521513, -0.3749921848066151, 1.882718862663023);
		circles.emplace_back(-3.341817569453269, 0.2325790119357407, 1.547948090289719);
		circles.emplace_back(-2.713154575321823, 3.979780601803213, 0.9893294560024514);
		circles.emplace_back(3.757804168853909, -4.468486693222076, 1.649244780722074);
		circles.emplace_back(2.871503725182265, 2.656319022644311, 0.6863278047414496);
		circles.emplace_back(0.003827151376754045, 4.388894939329475, 1.005472487374209);
		circles.emplace_back(4.612319732550532, 0.935192524921149, 0.9632678729249163);
		circles.emplace_back(4.777520101051778, 3.46087233396247, 0.6004440031247213);
		circles.emplace_back(-4.805746756028384, -0.9056300320662558, 1.739910818613134);
		circles.emplace_back(-2.352971045766026, -0.4188234708271921, 1.792145323590375);
		circles.emplace_back(-3.998513722326607, -0.6254651886411011, 0.9077638606308027);
		circles.emplace_back(3.048433668445796, 1.599939011503011, 1.455210005980916);
		circles.emplace_back(-4.755310814362019, 2.625834660138935, 0.7970931587507948);
		circles.emplace_back(-3.542616518680006, -3.435304441954941, 0.8051735896850004);
		circles.emplace_back(-4.000169408973306, 0.9525894443504512, 1.035873717884533);
		circles.emplace_back(-4.103651728946716, 4.479291264433414, 1.144069254701026);
		circles.emplace_back(3.327737629879266, -2.172000634018332, 1.226456792256795);
		circles.emplace_back(-4.286733067128807, -2.979574350174516, 0.9600703845033421);
		circles.emplace_back(-2.757039607968181, 0.2996121230535209, 0.861907089385204);
		circles.emplace_back(2.016384720336646, -4.974134757649153, 1.2216491201194);
		circles.emplace_back(-0.1013602199964225, -3.142673245165497, 0.5174345785519108);
		circles.emplace_back(3.766744395252317, 2.984304113779217, 0.4353671163553372);
		circles.emplace_back(4.553296754602343, -1.18694479810074, 1.102150395954959);
		circles.emplace_back(2.303429685998708, 4.662256424780935, 0.9108685262268409);
		circles.emplace_back(2.414934055414051, -0.446894948836416, 1.162850656197406);
		circles.emplace_back(-1.047474720980972, -0.3875983250327408, 0.6623546275077388);
		circles.emplace_back(0.118488899897784, -2.100425295066088, 1.111174245667644);
		circles.emplace_back(-2.507442708592862, 0.02202326199039817, 0.6367905547609553);
		circles.emplace_back(2.763044310268015, 0.3812655271030962, 0.6651976149762049);
		circles.emplace_back(0.2482660138048232, -1.353657089639455, 0.4187778235180303);
		circles.emplace_back(-0.4732672986574471, -4.840209137182683, 1.015381297026761);
		circles.emplace_back(-2.472519769798964, -4.918430449906737, 1.800445443741046);
		circles.emplace_back(-3.228995373938233, -4.498069507535547, 0.8645070584723725);
		circles.emplace_back(-4.617537872400135, 0.3898001345805824, 0.689657240989618);
		circles.emplace_back(-3.362912789452821, 3.6423549358733, 1.330991727230139);
		circles.emplace_back(2.567724373657256, -0.6799491704441607, 0.9884309695800766);
	}
	result_expected = 5.255133104408729;

	timer.reset();
	result_actual = algorithm(a138, b138, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #138: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a139(-2.084238029550761, -1.072226835414767);
	Point b139(3.431438801344484, 3.956643739715219);
	{
		circles.emplace_back(0.6985250278376043, 4.728987331036478, 1.601511918590404);
		circles.emplace_back(-2.110649028327316, 0.7885178434662521, 1.620138168591075);
		circles.emplace_back(-2.651417918968946, 1.025913127232343, 1.419511597347446);
		circles.emplace_back(4.56641596974805, -0.555259941611439, 1.03485651218798);
		circles.emplace_back(2.26997539633885, -1.9640828599222, 1.490250548790209);
		circles.emplace_back(1.587334114592522, 1.578265477437526, 0.7799174840794876);
		circles.emplace_back(-2.542392208706588, 3.543969688471407, 0.5858086023246869);
		circles.emplace_back(-2.547876706812531, 0.644348340574652, 0.8832875492284074);
		circles.emplace_back(4.112330956850201, -0.9653737512417138, 1.103880277159624);
		circles.emplace_back(0.2474809135310352, -3.281937211286277, 0.7774462015600875);
		circles.emplace_back(2.956278410274535, 0.04837637534365058, 1.827060415013693);
		circles.emplace_back(4.031304901000112, 1.838113574776798, 1.374321230524219);
		circles.emplace_back(3.75489097321406, -0.04769983934238553, 0.8930455860449);
		circles.emplace_back(-0.1750296843238175, 2.539584350306541, 0.9565803147153928);
		circles.emplace_back(-4.710739783477038, 2.941739072557539, 0.6751222938066348);
		circles.emplace_back(4.017221869435161, -0.2661871514283121, 1.411709619895555);
		circles.emplace_back(-2.28902077069506, 4.845616694074124, 1.460625761258416);
		circles.emplace_back(2.418396032880992, 4.440011673141271, 0.4841435444774106);
		circles.emplace_back(-1.150675069075078, -1.802188290748745, 0.8635753525188192);
		circles.emplace_back(-1.892937424127012, -2.323259839322418, 0.8497180734062567);
		circles.emplace_back(-1.635185105260462, 2.939329228829592, 1.438747372548096);
		circles.emplace_back(-4.198980864603072, 3.426801536697894, 0.9141811388777569);
		circles.emplace_back(0.1861504022963345, 1.36211029952392, 1.250188174447976);
		circles.emplace_back(-0.08183384547010064, -0.33664166694507, 1.095891823829152);
		circles.emplace_back(3.179276196751744, -0.7548368093557656, 0.6751001915661617);
		circles.emplace_back(1.520133286248893, 2.718027785886079, 0.9096761816414073);
		circles.emplace_back(1.227756154257804, -1.682706198189408, 0.5816506990930065);
		circles.emplace_back(4.702622105833143, 3.533437682781368, 0.8615808829898014);
		circles.emplace_back(-4.397117157932371, 1.958056285511702, 0.8940577973378822);
		circles.emplace_back(-0.5387262743897736, -0.6768081220798194, 0.5304768382804468);
		circles.emplace_back(3.419907682109624, 0.1696387282572687, 0.837800296372734);
		circles.emplace_back(-0.629536344204098, -0.3885865560732782, 0.789613381610252);
		circles.emplace_back(4.863497188780457, -4.932757515925914, 0.5294778692303225);
		circles.emplace_back(2.314770005177706, 0.2920021791942418, 1.54680953968782);
		circles.emplace_back(-2.529010500293225, -1.805892495904118, 0.4272150283446535);
		circles.emplace_back(4.758954865392298, 1.984461939428002, 1.493492346652783);
		circles.emplace_back(-3.163755831774324, -0.3803202440030873, 1.076057167421095);
	}
	result_expected = 17.90874953590826;

	timer.reset();
	result_actual = algorithm(a139, b139, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #139: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a140(-2.217094297986478, 3.683836402371526);
	Point b140(2.820742295589298, 2.96908431686461);
	{
		circles.emplace_back(4.934803356882185, 3.173149956855923, 0.9253413751954213);
		circles.emplace_back(-1.772752364631742, -3.840157494414598, 0.6940508206142112);
		circles.emplace_back(-2.325428251642734, 0.5040966835804284, 1.661727216769941);
		circles.emplace_back(-3.284476704429835, 2.52147558843717, 0.973837225860916);
		circles.emplace_back(3.734872804488987, 0.8819993981160223, 0.7727955943206325);
		circles.emplace_back(-0.02379668643698096, -0.8621635031886399, 0.325469799595885);
		circles.emplace_back(1.717295132111758, 2.146406092215329, 1.338977534067817);
		circles.emplace_back(3.905848239082843, 1.825083883013576, 1.198050532280467);
		circles.emplace_back(-1.529640632215887, -0.4580878256820142, 0.7003740813815966);
		circles.emplace_back(1.211202146951109, 4.250533587764949, 1.087892822991125);
		circles.emplace_back(-1.898493214976043, 0.9697298682294786, 0.4896273601567372);
		circles.emplace_back(2.130855598952621, -1.656862271483988, 0.5797791736433282);
		circles.emplace_back(-2.915973828639835, 2.417557153385133, 0.5004543646005913);
		circles.emplace_back(3.42338104499504, -4.335416376125067, 0.7126371310325339);
		circles.emplace_back(-1.864269140642136, -1.293580329511315, 1.189529499574564);
		circles.emplace_back(-4.609490896109492, 0.138568936381489, 0.9364691592985763);
		circles.emplace_back(-4.02669016038999, 4.611860036384314, 0.6567754399729893);
		circles.emplace_back(-0.2495925617404282, 0.509115916211158, 0.6067739001708105);
		circles.emplace_back(-4.188353202771395, 0.9970816574059427, 0.7224032804137095);
		circles.emplace_back(0.9280909015797079, 4.69447452807799, 0.4515503673115745);
		circles.emplace_back(2.637616193387657, 1.892683531623334, 0.8976076493738219);
		circles.emplace_back(-3.537817292381078, 2.867376052308828, 1.324062457424589);
		circles.emplace_back(-1.618476610165089, -4.743490202818066, 0.8757665840676053);
		circles.emplace_back(-1.256842466536909, -1.672049739863724, 1.66269269476179);
		circles.emplace_back(-3.807268214877695, 2.840860120486468, 1.039531908254139);
		circles.emplace_back(-0.1224998501129448, -2.104619618039578, 0.6252436074661091);
		circles.emplace_back(0.06898868130519986, 4.340400767978281, 1.089938042662106);
		circles.emplace_back(-1.594193077180535, 2.118588837329298, 1.348443571687676);
		circles.emplace_back(0.1006803498603404, -3.166040044743568, 0.6565868652192876);
		circles.emplace_back(-2.869798720348626, -1.600784554611892, 1.265249896910973);
		circles.emplace_back(-2.678284484427422, -3.783015182707459, 1.330583425774239);
		circles.emplace_back(-0.8224720158614218, -4.118131415452808, 1.230315363430418);
		circles.emplace_back(-3.642044772859663, -3.401218906510621, 1.261702007497661);
		circles.emplace_back(-1.610365186352283, -1.552901479881257, 1.09519536041189);
		circles.emplace_back(-2.517924166750163, 0.2597503713332117, 0.5657542146509513);
		circles.emplace_back(3.940643982496113, 0.0917608686722815, 0.7770212104776874);
		circles.emplace_back(1.070470532868057, -1.521316517610103, 1.784810453909449);
		circles.emplace_back(1.483459405135363, 4.149406917858869, 0.7149512042524293);
		circles.emplace_back(-4.436736281495541, -3.901237605605274, 1.019293363927863);
	}
	result_expected = 7.167463712625491;

	timer.reset();
	result_actual = algorithm(a140, b140, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #140: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a141(-2.574769928585738, 2.352045016363263);
	Point b141(3.740999852772802, -3.611550142988563);
	{
		circles.emplace_back(-3.544357216451317, 3.60273108119145, 1.28015531396959);
		circles.emplace_back(2.629854141268879, -2.639709871727973, 1.154474032553844);
		circles.emplace_back(1.02572452975437, -1.18161280406639, 0.4556918361457065);
		circles.emplace_back(-0.2206195774488151, -2.188657990191132, 0.8082191044231877);
		circles.emplace_back(-3.379711846355349, -3.511278943624347, 0.7444744915002957);
		circles.emplace_back(0.3724338510073721, -0.1703112875111401, 0.9581492696655913);
		circles.emplace_back(0.2908677118830383, 3.790028777439147, 1.250089614023454);
		circles.emplace_back(-2.288676656316966, 3.223045056220144, 0.7099061496322974);
		circles.emplace_back(4.263800994958729, -1.707988565322012, 1.811706795380451);
		circles.emplace_back(1.865893027279526, -1.983002473134547, 0.6832197579322382);
		circles.emplace_back(-4.133966334629804, -4.472225240897387, 1.030354138207622);
		circles.emplace_back(2.701895956415683, 4.753428043331951, 0.9860917737474665);
		circles.emplace_back(0.3253740794025362, -3.397413843777031, 1.33802493030671);
		circles.emplace_back(-0.55285140639171, 4.970517314504832, 0.613267755578272);
		circles.emplace_back(1.208382386248559, 3.661213268060237, 0.9191616381751373);
		circles.emplace_back(-1.361272230278701, 1.25641762977466, 0.5735637251054868);
		circles.emplace_back(-1.057328751776367, 3.357887046877295, 0.7649615558097138);
		circles.emplace_back(-1.943809406366199, 0.8585286769084632, 1.141042238357477);
		circles.emplace_back(-2.852260724175721, -4.984098940622061, 1.510284382221289);
		circles.emplace_back(1.726266529876739, 1.26390373101458, 1.345150248869322);
		circles.emplace_back(3.119552021380514, -0.3244225098751485, 1.208215438597835);
		circles.emplace_back(-0.9663103870116174, 4.193657308351249, 0.9522357550216838);
		circles.emplace_back(-3.471070874948055, -2.540200937073678, 0.6760491735534742);
		circles.emplace_back(-1.859192482661456, -0.174660871271044, 1.232852411246858);
		circles.emplace_back(2.952389956917614, 2.385524848941714, 1.036106042400934);
		circles.emplace_back(-0.9446770488284528, -0.4779170197434723, 0.8434409702895209);
		circles.emplace_back(0.006453848909586668, 4.667676680255681, 1.31288178388495);
		circles.emplace_back(-2.647515239659697, -0.5514983623288572, 0.7720515553141012);
		circles.emplace_back(-3.609680456575006, -4.984907724428922, 1.121161895315163);
		circles.emplace_back(1.429013970773667, -3.509015168529004, 1.134312324528582);
		circles.emplace_back(-4.797931856010109, -3.550894556101412, 0.9054453546414151);
		circles.emplace_back(1.671723632607609, -1.599524926859885, 0.4787548056570813);
		circles.emplace_back(-3.748626143205911, 4.620697752106935, 1.370816554990597);
		circles.emplace_back(3.895849895197898, -2.136471292469651, 1.199315766408108);
		circles.emplace_back(-3.118596563581377, 1.350397600326687, 0.9453059092396869);
		circles.emplace_back(-4.634122808929533, 4.671264782082289, 1.098173846746795);
		circles.emplace_back(1.411070700269192, -1.769376459997147, 0.8858681290643289);
		circles.emplace_back(-2.099421329330653, 0.403782760258764, 1.753641413873993);
	}
	result_expected = 13.52289866829791;

	timer.reset();
	result_actual = algorithm(a141, b141, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #141: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a142(-3.420895788352937, -0.2417915146797895);
	Point b142(2.781014764215797, -3.626167690381408);
	{
		circles.emplace_back(0.642994639929384, -0.8713789074681699, 1.468680337467231);
		circles.emplace_back(1.21955074602738, 0.1074672560207546, 0.9702474974794313);
		circles.emplace_back(4.964816037099808, -3.999663020949811, 0.525607659225352);
		circles.emplace_back(1.587772697675973, -4.999204950872809, 0.9658220197772607);
		circles.emplace_back(-3.12455320963636, 3.235715033952147, 0.9392341995844616);
		circles.emplace_back(-1.450614721979946, -0.07935167523100972, 1.192377217742614);
		circles.emplace_back(3.836663037072867, -3.010629459749907, 0.8712976330192759);
		circles.emplace_back(2.744544160086662, 2.380745091941208, 1.216603315784596);
		circles.emplace_back(-2.259202788118273, -2.725023792590946, 0.7988773450488225);
		circles.emplace_back(-4.957069416996092, -2.292339012492448, 1.146690582181327);
		circles.emplace_back(4.260980661492795, -2.327897313516587, 1.317091804672964);
		circles.emplace_back(-3.2031434844248, -3.877910042647272, 1.226757963723503);
		circles.emplace_back(1.38931350549683, -3.712363278027624, 1.275496498332359);
		circles.emplace_back(0.4027078370563686, -3.388086340855807, 1.27686894882936);
		circles.emplace_back(0.8105161529965699, -4.384973554406315, 1.169219494401477);
		circles.emplace_back(4.742244107183069, -0.4535802244208753, 0.4785907801473513);
		circles.emplace_back(0.2908030175603926, 0.3350284765474498, 1.250872416864149);
		circles.emplace_back(0.6317242863588035, -2.764611344318837, 0.8717977266060188);
		circles.emplace_back(2.870540276635438, 1.203349379356951, 1.594185079983435);
		circles.emplace_back(1.444699147250503, 4.157834576908499, 1.009366922290064);
		circles.emplace_back(-0.4003749950788915, -2.026736524421722, 1.02459409374278);
		circles.emplace_back(-0.3934092377312481, -0.02046537352725863, 1.148146744188852);
		circles.emplace_back(4.599467453081161, 4.559207463171333, 1.418068170710467);
		circles.emplace_back(-1.060374940279871, 0.6761900172568858, 1.101107919984497);
		circles.emplace_back(2.889643574599177, 1.414977132808417, 0.9240798515034839);
		circles.emplace_back(0.5731330323033035, -1.830534178297967, 0.998805548925884);
		circles.emplace_back(0.600372941698879, 2.916827092412859, 0.6741901217261329);
		circles.emplace_back(1.315369613002986, -2.685941911768168, 0.347891562920995);
		circles.emplace_back(-1.285063426475972, 1.187584714498371, 1.433858191757463);
		circles.emplace_back(3.859360662754625, -0.843929925467819, 0.5401237566256896);
		circles.emplace_back(-1.948183549102396, -2.742564149666578, 1.413446904043667);
		circles.emplace_back(2.196283254306763, 2.507071916479617, 0.6078179541276767);
		circles.emplace_back(3.175519884098321, -1.360714065376669, 1.209387768409215);
		circles.emplace_back(0.2703287242911756, -3.0946035659872, 1.338991899252869);
		circles.emplace_back(-1.25554317375645, -2.283318799454719, 0.710866708192043);
		circles.emplace_back(-0.2740638260729611, 3.621244237292558, 0.7681974449427798);
		circles.emplace_back(1.352991324383765, -3.498445621225983, 1.094805728807114);
	}
	result_expected = 15.56190057754999;

	timer.reset();
	result_actual = algorithm(a142, b142, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #142: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a143(-2.688337973784655, -1.242139590904117);
	Point b143(2.883762074168772, 1.254184463992715);
	{
		circles.emplace_back(4.651500077452511, 3.361512015108019, 1.17255769057665);
		circles.emplace_back(2.56163457641378, 4.094429041724652, 1.529338563489728);
		circles.emplace_back(-2.029102544765919, -4.221527560148388, 1.481404778151773);
		circles.emplace_back(4.188330320175737, -2.219375350978225, 0.8659963894868269);
		circles.emplace_back(-4.724199844058603, 4.10720371408388, 0.1945214130682871);
		circles.emplace_back(-0.5310369725339115, -0.02964250976219773, 0.9778161506867036);
		circles.emplace_back(-3.148570156190544, 0.6106843077577651, 1.133402768732048);
		circles.emplace_back(2.758692263159901, -2.039810281712562, 1.324745849403553);
		circles.emplace_back(1.464858471881598, 0.7665665005333722, 0.732184458640404);
		circles.emplace_back(2.466738384682685, -3.836690357420594, 1.207751008286141);
		circles.emplace_back(2.048771937843412, 4.665216191206127, 0.9079102874035015);
		circles.emplace_back(3.598601112607867, 3.292294486891478, 1.355890578473918);
		circles.emplace_back(0.1529142423532903, -3.615011458750814, 0.9057906797388567);
		circles.emplace_back(0.9619876951910555, 4.95273734210059, 1.458025437849574);
		circles.emplace_back(-0.6272721965797246, 0.52821732359007, 0.5211245049955323);
		circles.emplace_back(2.775165860075504, -2.267367003951222, 0.7895479520549997);
		circles.emplace_back(-1.323464142624289, 0.397338813636452, 1.04221323246602);
		circles.emplace_back(-0.7573462999425828, 3.920727230142802, 0.5320788771612569);
		circles.emplace_back(4.285713837016374, -1.452658476773649, 1.529933807603084);
		circles.emplace_back(-0.8684317977167666, 1.399718599859625, 1.16790249964688);
		circles.emplace_back(1.472630186472088, -4.185015794355422, 1.146935126069002);
		circles.emplace_back(2.42347066057846, -4.549496143590659, 0.8633580059977248);
		circles.emplace_back(-4.490580374840647, 0.5549572990275919, 0.8610694550210609);
		circles.emplace_back(-0.3177149943076074, 2.43060466600582, 0.9638360497308894);
		circles.emplace_back(0.7331168162636459, 2.103448223788291, 1.51881744035054);
		circles.emplace_back(0.3197937621735036, -1.414255460258573, 0.6589910818496718);
		circles.emplace_back(-4.602851027157158, 4.740770335774869, 1.344962691771798);
		circles.emplace_back(2.090590156149119, -2.032835192512721, 0.8857568335952236);
		circles.emplace_back(2.978065360803157, 3.580469356384128, 1.157737083523534);
		circles.emplace_back(-0.8743983530439436, 2.755831351969391, 0.4636134002590552);
		circles.emplace_back(2.357530656736344, 3.924598668236285, 0.8215661603258922);
		circles.emplace_back(-2.248248129617423, 2.30851344531402, 0.6397223915671929);
	}
	result_expected = 7.413239089702344;

	timer.reset();
	result_actual = algorithm(a143, b143, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #143: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a144(-2.902293513994664, -0.05963992886245251);
	Point b144(2.732374907936901, -2.072265988215804);
	{
		circles.emplace_back(3.293499832507223, -0.641569287981838, 0.5267207019263878);
		circles.emplace_back(-0.2602409175597131, 1.833673387300223, 0.2983270969940349);
		circles.emplace_back(-4.669136155862361, 4.78347183438018, 1.126111710746772);
		circles.emplace_back(-1.975743405055255, -4.57667131209746, 1.078513264632784);
		circles.emplace_back(-3.954999207053334, 3.267222980502993, 1.343945030705072);
		circles.emplace_back(0.9059160412289202, 0.446057494264096, 1.060721811163239);
		circles.emplace_back(1.522888995241374, -0.1133334706537426, 1.069206146639772);
		circles.emplace_back(0.06914739729836583, 2.816628383006901, 0.8153334898641332);
		circles.emplace_back(1.6053357697092, 2.956656983587891, 1.0343060557032);
		circles.emplace_back(-2.868592066224664, 2.84057893557474, 1.357062655012123);
		circles.emplace_back(3.603675130289048, 4.270208750385791, 1.075017409329303);
		circles.emplace_back(-3.363214104901999, -2.449396627489477, 0.7776305254315957);
		circles.emplace_back(-4.590529149863869, 2.790627183858305, 1.40038074797485);
		circles.emplace_back(3.92232587793842, 1.81338696507737, 1.573967622849159);
		circles.emplace_back(-3.684904009569436, -2.298755391966552, 1.570798602071591);
		circles.emplace_back(-0.3387048724107444, 1.466164567973465, 0.9667451897403224);
		circles.emplace_back(4.234153737779707, 4.980241789016873, 1.525308670126833);
		circles.emplace_back(-0.4131912789307535, 3.519624366890639, 0.8288400788558646);
		circles.emplace_back(-0.5244518560357392, 1.648504075128585, 0.715238222409971);
		circles.emplace_back(3.817200355697423, -2.415128315333277, 0.6728297941153869);
		circles.emplace_back(1.53360711177811, 2.287680173758417, 1.328590316162445);
		circles.emplace_back(4.091244211886078, 2.897011439781636, 1.668294050055556);
		circles.emplace_back(0.2590037207119167, 2.093580283690244, 1.165098345768638);
		circles.emplace_back(0.02131573623046279, -1.633230948355049, 0.9834088888252154);
		circles.emplace_back(3.990688922349364, 2.741773731540889, 1.435134206782095);
		circles.emplace_back(-1.186093103606254, -3.302322428207844, 0.7268137465463951);
		circles.emplace_back(-3.939482017885894, 1.96271046763286, 1.181127290776931);
		circles.emplace_back(-2.564592680428177, -2.072222603019327, 1.37985051444266);
		circles.emplace_back(0.6210069195367396, 4.874413523357362, 0.6007655306486412);
		circles.emplace_back(0.6594141270034015, -3.988671719562262, 1.652426956710406);
		circles.emplace_back(-4.882306817453355, 0.4042895673774183, 1.071752563281916);
		circles.emplace_back(-3.574872876051813, 3.91393011668697, 1.368397895270027);
		circles.emplace_back(3.74022718751803, -3.167174935806543, 1.309907670016401);
		circles.emplace_back(4.296478133182973, 3.414578300435096, 0.8892342618899419);
		circles.emplace_back(-4.924620173405856, 0.6595149240456522, 0.7823199972277507);
		circles.emplace_back(4.495906324591488, 3.877140472177416, 1.168072399334051);
		circles.emplace_back(-2.193380200769752, 2.530253555160016, 1.234488982963376);
		circles.emplace_back(-2.528724365402013, 3.475141369272023, 0.942517634970136);
		circles.emplace_back(0.09258498670533299, 4.501090662088245, 0.5832820443203672);
	}
	result_expected = 6.0636386170723;

	timer.reset();
	result_actual = algorithm(a144, b144, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #144: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a145(-3.990104823838919, 2.192369000986218);
	Point b145(3.866599550005049, 2.995772609487176);
	{
		circles.emplace_back(-0.619407759513706, 0.5284788343124092, 1.169195033493452);
		circles.emplace_back(-0.9945125435478985, -1.94251251174137, 0.8877818064065649);
		circles.emplace_back(1.541517910081893, 4.763863587286323, 1.043320775195025);
		circles.emplace_back(-1.541639531496912, -1.259303928818554, 1.287841332727112);
		circles.emplace_back(-0.5763450614176691, 0.2918706531636417, 0.4685629171086475);
		circles.emplace_back(0.6949530052952468, 3.965123456437141, 1.342120649595745);
		circles.emplace_back(0.4344224114902318, 0.3287612996064126, 0.9745945289498195);
		circles.emplace_back(-0.4143770621158183, 0.1928733685053885, 0.8997201500693336);
		circles.emplace_back(-0.2426194190047681, 2.909803714137524, 1.011234811949544);
		circles.emplace_back(3.551104075741023, -3.286959386896342, 0.8598220047773792);
		circles.emplace_back(0.424061615485698, -2.989549322519451, 1.189746629982255);
		circles.emplace_back(-2.181672605220228, -2.225606122519821, 1.185938437678851);
		circles.emplace_back(0.880612360779196, -0.8969969232566655, 0.3376807936234399);
		circles.emplace_back(-2.619717207271606, 4.002421323675662, 0.3891388836549595);
		circles.emplace_back(-1.07623916817829, 3.447099102195352, 0.629645026824437);
		circles.emplace_back(-2.487051284406334, -0.9739680564962327, 0.8622628638753667);
		circles.emplace_back(-2.10766309639439, 0.252212721388787, 0.7593052333919331);
		circles.emplace_back(4.229660748969764, -4.967825605999678, 1.178961352375336);
		circles.emplace_back(-0.2689535799436271, -3.466061225626618, 1.050543867959641);
		circles.emplace_back(-0.07561598205938935, 1.72835378209129, 0.9391828447813168);
		circles.emplace_back(-1.257583310361952, -1.236814216244966, 0.7555049036396667);
		circles.emplace_back(3.42019798932597, -4.326504382770509, 1.683931277622469);
		circles.emplace_back(-1.73919991357252, -1.971508676651865, 0.8417470760410651);
		circles.emplace_back(2.44789602002129, -0.1131750992499292, 0.6542713841656222);
		circles.emplace_back(-1.130958774592727, 1.146518539171666, 1.017406770843081);
		circles.emplace_back(3.981945745181292, -4.187602929305285, 1.170143010211177);
		circles.emplace_back(-0.1161180692724884, -1.285613833460957, 1.26963910961058);
		circles.emplace_back(-2.392849850002676, -0.1463637291453779, 0.9910693507874384);
		circles.emplace_back(4.410396965686232, -2.750171863008291, 0.4851604760391637);
		circles.emplace_back(2.929192918818444, 3.547705162782222, 1.03080500618089);
		circles.emplace_back(1.058722243178636, 1.061272618826479, 0.6699579123174771);
		circles.emplace_back(-2.274154594633728, -1.226250750478357, 1.368868193239905);
		circles.emplace_back(1.178055985365063, 4.07977408496663, 1.475660502794199);
		circles.emplace_back(2.812956317793578, -4.067972570192069, 1.471237385389395);
		circles.emplace_back(-2.056617948692292, -3.68167424807325, 0.7601850496372208);
		circles.emplace_back(1.57958340132609, -2.348576516378671, 1.347573032672517);
		circles.emplace_back(-3.011685360688716, 0.9431880828924477, 1.37258042760659);
		circles.emplace_back(2.175582416821271, -3.021153996232897, 0.5939280330901965);
	}
	result_expected = 10.68640434446772;

	timer.reset();
	result_actual = algorithm(a145, b145, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #145: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a146(-3.290292907040566, -3.629297463223338);
	Point b146(3.342219272162765, 0.8808199409395456);
	{
		circles.emplace_back(0.2360580093227327, -3.322136455681175, 0.81590114349965);
		circles.emplace_back(3.940193506423384, -3.965913795400411, 1.171545615862124);
		circles.emplace_back(-0.7400335487909615, -1.491797517519444, 0.8679623480187728);
		circles.emplace_back(1.427845165599138, 4.070944485720247, 1.093585536233149);
		circles.emplace_back(0.8180053322575986, -4.425355119165033, 1.073612123937346);
		circles.emplace_back(-2.063968495931476, 3.762350443284959, 1.441050836327486);
		circles.emplace_back(-3.405598953831941, 3.98774626897648, 0.7467827410669997);
		circles.emplace_back(-3.189517769496888, 3.803395682480186, 1.203216655715369);
		circles.emplace_back(1.521380131598562, -0.6941963150165975, 0.8031403921777382);
		circles.emplace_back(3.723925764206797, -3.744686872232705, 1.026632713968866);
		circles.emplace_back(-2.239240456838161, 3.363278221804649, 0.7518694794969633);
		circles.emplace_back(-2.160161070059985, -3.402070889715105, 1.143463078117929);
		circles.emplace_back(-3.278879581484944, 1.435826460365206, 1.483071525231935);
		circles.emplace_back(-3.235046023037285, 2.367015357594937, 0.9493590111611411);
		circles.emplace_back(0.006561435293406248, 0.4133275081403553, 1.19352772955317);
		circles.emplace_back(3.110347141046077, -1.911056770477444, 0.6295709563186391);
		circles.emplace_back(-1.310878398362547, 2.539011111948639, 0.4675976369762793);
		circles.emplace_back(2.805151718202978, -0.8726137061603367, 0.5630603992147371);
		circles.emplace_back(4.886806074064225, -0.1217389362864196, 0.9274873095797375);
		circles.emplace_back(1.849907368887216, 4.302911085542291, 0.8201145376777276);
		circles.emplace_back(-2.291723878588527, 0.486139643471688, 0.6968963763443753);
		circles.emplace_back(4.488337903749198, -0.3143746103160083, 0.6078689986141398);
		circles.emplace_back(2.766324293334037, -4.451238831970841, 0.987980050756596);
		circles.emplace_back(-1.012211700435728, 2.834013893734664, 0.7727258731378241);
		circles.emplace_back(4.119055445771664, -1.844042900484055, 0.8063617824809626);
		circles.emplace_back(3.811711065936834, 4.429352020379156, 0.7708417795365676);
		circles.emplace_back(-4.250215126667172, -2.738963996525854, 0.7775848603108897);
		circles.emplace_back(4.899464033078402, -4.123437784146518, 0.3569860373856499);
		circles.emplace_back(-2.447637643199414, 3.911540599074215, 1.373005325137638);
		circles.emplace_back(1.202105504926294, -1.555633747484535, 0.9884612199151888);
		circles.emplace_back(4.694072294514626, -3.069235782604665, 0.6358176510082557);
		circles.emplace_back(1.831596151459962, -3.607655616942793, 1.540493055037223);
		circles.emplace_back(-2.68998863408342, 1.156872438732535, 1.842987762601115);
		circles.emplace_back(0.8201323891989887, -0.8298791642300785, 0.835048081097193);
		circles.emplace_back(0.4130642977543175, -0.301302766893059, 1.281246739788912);
	}
	result_expected = 15.21031756719893;

	timer.reset();
	result_actual = algorithm(a146, b146, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #146: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a147(-3.073309309314936, -3.665443612262607);
	Point b147(2.745946911629289, 1.179162779822946);
	{
		circles.emplace_back(-3.514803780708462, 1.903966928366572, 1.624220747337676);
		circles.emplace_back(2.564609518740326, 2.971223990898579, 1.478377320128493);
		circles.emplace_back(3.393938622903079, 3.292031802702695, 0.8959695224883034);
		circles.emplace_back(-1.093803073745221, -4.553277699742466, 1.395850411592983);
		circles.emplace_back(1.92827999824658, -0.2068179775960743, 0.9010200128657743);
		circles.emplace_back(-4.075061094481498, 1.362124879378825, 1.290283418749459);
		circles.emplace_back(-0.06852988852187991, 0.1611791527830064, 1.049640469602309);
		circles.emplace_back(3.481280484702438, -2.215838802512735, 1.594950397522189);
		circles.emplace_back(3.571529819164425, -2.450131860096008, 1.495567886414938);
		circles.emplace_back(0.8133157039992511, -4.874952256213874, 1.682375739631243);
		circles.emplace_back(1.078750228043646, 0.6558043346740305, 1.002915731840767);
		circles.emplace_back(1.969184840563685, 4.316285967361182, 1.160939807887189);
		circles.emplace_back(-1.184118886012584, 2.130768161732703, 1.158507614512928);
		circles.emplace_back(-4.317599318455905, -1.391726473812014, 1.351842544949613);
		circles.emplace_back(4.83674714108929, -3.519054462667555, 0.8215626327553763);
		circles.emplace_back(-3.234937989618629, -1.863459919113666, 1.340450854110531);
		circles.emplace_back(1.028421230148524, 2.83567174570635, 0.4363633600296453);
		circles.emplace_back(-3.109788994770497, 1.718609945382923, 1.031608226685785);
		circles.emplace_back(1.017034796532243, 4.743184468243271, 1.460362755157985);
		circles.emplace_back(1.374264287296683, 2.584138743113726, 1.106761042098515);
		circles.emplace_back(-0.26103236945346, -0.4338149982504547, 1.425243351166136);
		circles.emplace_back(0.6227450375445187, -2.30139427119866, 1.657168940803967);
		circles.emplace_back(1.897230648901314, 1.602680238429457, 0.8809934118995443);
		circles.emplace_back(3.597194312606007, -1.837859612423927, 1.299753747018985);
		circles.emplace_back(-0.1915873889811337, -1.724632873665541, 0.6680928298505022);
		circles.emplace_back(3.544960778672248, -1.369739344809204, 1.379761745943688);
		circles.emplace_back(-0.9833443560637534, 4.49454007903114, 0.8806749761337413);
		circles.emplace_back(0.4327868320979178, 2.980643853079528, 1.064218807662837);
		circles.emplace_back(-0.9840318304486573, -2.220029446762055, 1.274741651047952);
		circles.emplace_back(-2.056922174524516, 0.07114518200978637, 1.134650037414394);
		circles.emplace_back(0.2307775779627264, 4.676426763180643, 1.777656721160747);
		circles.emplace_back(4.278459867928177, 1.149122368078679, 0.9842153194127604);
		circles.emplace_back(0.8069687406532466, -3.834529749583453, 0.4057299663545564);
		circles.emplace_back(4.125700418371707, 3.030718804802746, 0.8007793089142069);
		circles.emplace_back(1.511748207267374, 4.91288477787748, 1.533226097770966);
		circles.emplace_back(2.704284640494734, 2.321101285051554, 0.7609891147119924);
		circles.emplace_back(-2.119482320267707, -0.9534382331185043, 0.7160948450909927);
		circles.emplace_back(0.6179092382080853, -0.5572578334249556, 0.4586751017486676);
	}
	result_expected = 16.85503826382715;

	timer.reset();
	result_actual = algorithm(a147, b147, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #147: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a148(-2.88650682149455, 3.587108196690679);
	Point b148(3.378286199178547, 1.497769052162766);
	{
		circles.emplace_back(-4.554835895542055, -1.011125759687275, 0.7307243019575252);
		circles.emplace_back(0.8371885516680777, 0.05447749746963382, 0.683537468756549);
		circles.emplace_back(-0.1300096255727112, -3.164178046863526, 1.010411356319673);
		circles.emplace_back(4.329094134736806, -4.727858717087656, 0.7340097971027717);
		circles.emplace_back(-4.735219462309033, -4.395508950110525, 1.210756917879917);
		circles.emplace_back(1.593199989292771, 4.845303844194859, 1.344094655173831);
		circles.emplace_back(2.465086213778704, -2.070877484511584, 1.463846828532405);
		circles.emplace_back(4.445027236361057, -3.320566473994404, 1.235016988753341);
		circles.emplace_back(-2.749221252743155, -2.161127084400505, 0.3998463731491938);
		circles.emplace_back(3.517726811114699, 4.200223244260997, 1.459887224505655);
		circles.emplace_back(1.74096955684945, -3.520940791349858, 1.657742085610516);
		circles.emplace_back(-0.7243173266761005, -2.166955473367125, 0.747629416338168);
		circles.emplace_back(0.904592105653137, -0.2587219304405153, 1.086717710108496);
		circles.emplace_back(-4.579612032976002, -4.180745419580489, 0.9723213790683075);
		circles.emplace_back(-4.839233413804322, 0.7394114439375699, 1.300444591161795);
		circles.emplace_back(-3.97595665184781, 4.03488373151049, 1.025559114082716);
		circles.emplace_back(-3.335837835911661, -0.4197511984966695, 0.951840203278698);
		circles.emplace_back(-4.324454551097006, 2.504574328195304, 0.606762519176118);
		circles.emplace_back(4.585415374021977, 4.107925307471305, 0.9745594687061384);
		circles.emplace_back(-0.9084978024475276, 1.674735953565687, 0.6883315622573718);
		circles.emplace_back(-2.744742988143116, -2.999406119342893, 1.127131949202157);
		circles.emplace_back(1.781630462501198, -2.025274459738284, 0.7467417861102148);
		circles.emplace_back(0.1933436165563762, -4.484282142948359, 0.9137439352693035);
		circles.emplace_back(-4.786639760714024, -0.4965452686883509, 1.164535198896192);
		circles.emplace_back(2.538883385714144, -0.9329102723859251, 1.079687893786468);
		circles.emplace_back(-2.755311650689691, 2.581170580815524, 0.8892172925872728);
		circles.emplace_back(3.989990118425339, -4.577849830966443, 1.426962672476657);
		circles.emplace_back(0.1372933690436184, 2.152249438222498, 0.6708131190156563);
		circles.emplace_back(3.792292529251426, -2.617599663790315, 1.103906297148205);
		circles.emplace_back(2.973642258439213, -2.635312390048057, 1.277765040728263);
		circles.emplace_back(-3.655329972971231, -2.897330864798278, 0.5295791351469233);
		circles.emplace_back(1.532287907321006, 1.835566142108291, 1.098471961333416);
		circles.emplace_back(-1.638920197729021, 3.466715945396572, 1.156388635956682);
		circles.emplace_back(-4.625224431511015, -0.1108891819603741, 0.9605745275272056);
		circles.emplace_back(3.992283816915005, -2.082881990354508, 1.490657797385938);
		circles.emplace_back(-2.184455103706568, -0.8249377855099738, 1.929582982487045);
		circles.emplace_back(0.6198780401609838, 4.586610461119562, 1.217987943277694);
		circles.emplace_back(-1.667066940572113, 0.2899144100956619, 1.570124037819914);
		circles.emplace_back(2.937370024155825, 0.2460157056339085, 0.6558523361803963);
		circles.emplace_back(-2.415146853309125, -0.9178253100253642, 1.154450318752788);
	}
	result_expected = 7.798509042585216;

	timer.reset();
	result_actual = algorithm(a148, b148, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #148: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a149(-3.035828932654113, -2.223505897447467);
	Point b149(2.41686183726415, -1.974423101171851);
	{
		circles.emplace_back(4.9177280603908, 1.266940834466368, 1.008912488282658);
		circles.emplace_back(4.725113718304783, 4.698001730721444, 0.7789805314270779);
		circles.emplace_back(2.157650857698172, -0.6560689653269947, 1.198311250773259);
		circles.emplace_back(1.408356439787894, 3.275542536284775, 0.7823687026044354);
		circles.emplace_back(0.6085656187497079, 0.4467449919320643, 0.6964362070197239);
		circles.emplace_back(-0.4527791938744485, -0.6729732011444867, 1.108329849387519);
		circles.emplace_back(0.5410768347792327, -3.791762951295823, 1.03918036215473);
		circles.emplace_back(-3.55718970997259, -1.716585422400385, 0.3014620445435867);
		circles.emplace_back(-4.544597698841244, -4.2402309528552, 1.050784871564247);
		circles.emplace_back(-0.744805762078613, 3.648151855450124, 1.451121919113211);
		circles.emplace_back(1.191747568082064, -4.721250913571566, 1.12875687230844);
		circles.emplace_back(-3.662554349284619, 1.284852118697017, 0.9545239513507112);
		circles.emplace_back(-2.514556425157934, 0.1139901042915881, 0.8641968604410066);
		circles.emplace_back(-4.228477773722261, -1.855629973579198, 0.970144321094267);
		circles.emplace_back(-2.957468938548118, -3.628787498455495, 1.285206512664445);
		circles.emplace_back(-2.988247617613524, 2.635857013519853, 1.381619759253226);
		circles.emplace_back(-4.604930898640305, 3.665233778301626, 1.306946288258769);
		circles.emplace_back(-0.1965932711027563, 0.9362324210815132, 1.107761509600095);
		circles.emplace_back(-3.427211150992662, -0.2116430993191898, 1.166248084721155);
		circles.emplace_back(4.52430420788005, 0.4660974978469312, 1.53942170755472);
		circles.emplace_back(-1.251192654017359, 0.05618786672130227, 1.048961658054031);
		circles.emplace_back(-1.453379129525274, 2.28746336651966, 1.746254168148152);
		circles.emplace_back(4.231959979515523, -2.177418309729546, 1.521924456139095);
		circles.emplace_back(2.884038009215146, 2.049757798667997, 1.063403762853704);
		circles.emplace_back(3.236903937067837, -3.14536522841081, 1.396092951134778);
		circles.emplace_back(1.026085114572197, -1.924580608028919, 0.7273382524726912);
		circles.emplace_back(4.515488750766963, -0.3233896265737712, 1.210459494334645);
		circles.emplace_back(-3.782998125534505, -1.015018506441265, 0.868903630762361);
		circles.emplace_back(3.260662185493857, -4.336108036804944, 0.7777387209935114);
		circles.emplace_back(-1.869403806049377, 4.489613596815616, 0.586575937573798);
		circles.emplace_back(4.976071894634515, -2.880591379944235, 1.012926955125295);
		circles.emplace_back(-1.538693106267601, -3.905464557465166, 1.253852225304581);
		circles.emplace_back(0.4396707401610911, 0.6157539668492973, 1.637692952784709);
		circles.emplace_back(3.689395308028907, 2.156300947535783, 1.221649203565903);
		circles.emplace_back(0.8811377105303109, -2.840693464968354, 0.7885687047382817);
		circles.emplace_back(3.09511806583032, 4.780181332025677, 0.4247694939607754);
		circles.emplace_back(-1.701382210012525, -2.317050055135041, 0.3392588530434295);
		circles.emplace_back(3.366850044112653, -3.373518500011414, 0.6650721355574205);
		circles.emplace_back(0.2772568096406758, -3.100205475930125, 1.07392674756702);
	}
	result_expected = -1;

	timer.reset();
	result_actual = algorithm(a149, b149, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #149: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a150(-2.51671803323552, 1.306160302832723);
	Point b150(3.872718328144401, -1.910841261968017);
	{
		circles.emplace_back(-0.59711858863011, 0.8816498727537692, 0.9144599069142714);
		circles.emplace_back(-0.9623450762592256, -4.038921960163862, 1.309956113318913);
		circles.emplace_back(-4.395270135719329, 0.5982775730080903, 1.141067454521544);
		circles.emplace_back(-4.040691351983696, -3.121777025517076, 1.035691378475167);
		circles.emplace_back(-4.754315258469433, -4.206502896267921, 0.6686573601095005);
		circles.emplace_back(-0.03539699362590909, -0.3765689278952777, 1.081035692361183);
		circles.emplace_back(-3.091022211592644, 3.958665558602661, 1.38980286361184);
		circles.emplace_back(2.992635925766081, 1.721491201315075, 0.8500789821380749);
		circles.emplace_back(3.636567483190447, 0.8863154496066272, 1.252316070045344);
		circles.emplace_back(3.496156062465161, 2.214391615707427, 1.235383106698282);
		circles.emplace_back(1.00416972534731, -2.315942163113505, 0.4704247213667258);
		circles.emplace_back(0.8485654159449041, -2.364085798617452, 0.8734305849531665);
		circles.emplace_back(-1.331731954123825, -1.145134319085628, 1.335128057259135);
		circles.emplace_back(2.369332842063159, 4.220306046772748, 1.220802192878909);
		circles.emplace_back(2.876909200567752, 1.335731984581798, 0.7339855571975931);
		circles.emplace_back(2.833233249839395, -1.178416663315147, 0.6755297314608469);
		circles.emplace_back(-2.059845475014299, 3.952282525133342, 0.900663372944109);
		circles.emplace_back(0.6015960755757987, -1.761708210688084, 0.9969198639737441);
		circles.emplace_back(0.378448769915849, 1.056433019693941, 0.6675538811599835);
		circles.emplace_back(-4.802659621927887, 3.96276660496369, 0.7980433585355058);
		circles.emplace_back(0.2288868860341609, 3.70402431814, 1.235213473322801);
		circles.emplace_back(-4.577082351315767, 0.9169036452658474, 1.204420009371824);
		circles.emplace_back(-3.530172023456544, 1.162962967064232, 0.8424808876356109);
		circles.emplace_back(-1.258622820023447, 3.248172311577946, 0.9277029477292671);
		circles.emplace_back(-3.526475613471121, -1.43026176141575, 0.5084430751157925);
		circles.emplace_back(-4.644387413281947, -3.509930658619851, 1.431876990874298);
		circles.emplace_back(1.564402647782117, -3.076719532255083, 0.9094077795511111);
		circles.emplace_back(-2.020558177027851, 2.090431491378695, 0.9091341151157394);
		circles.emplace_back(0.8973517478443682, 3.069969292264432, 0.9382216985104604);
		circles.emplace_back(4.446516789030284, -3.771006173919886, 1.070675076288171);
		circles.emplace_back(2.725842942018062, 3.64219413837418, 1.057140280096792);
		circles.emplace_back(-1.200847628060728, -1.267700919415802, 0.3317096386337652);
		circles.emplace_back(4.453924077097327, 1.815213046502322, 0.7865098976297303);
		circles.emplace_back(1.089008513372391, -1.500467683654279, 0.7673888105200604);
		circles.emplace_back(-0.5908998544327915, 2.993149680551142, 0.957265331945382);
		circles.emplace_back(0.5551526485942304, -2.072926161345094, 1.174800922931172);
		circles.emplace_back(-2.215169460978359, -1.125187885481864, 0.7831751785008236);
		circles.emplace_back(0.4318422195501626, 2.533610740210861, 0.7663849839707836);
	}
	result_expected = 8.26473724385745;

	timer.reset();
	result_actual = algorithm(a150, b150, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #150: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a151(-3.706742368172854, -1.695410383865237);
	Point b151(3.152087552007288, 0.9427603278309107);
	{
		circles.emplace_back(-4.855989573989064, -4.123323222156614, 0.8996315820375457);
		circles.emplace_back(-4.291360431816429, -0.103985492605716, 0.936251630890183);
		circles.emplace_back(-3.601500533986837, 1.863858096767217, 1.432873473805375);
		circles.emplace_back(-1.016052316408604, -2.274082137737423, 1.003757987706922);
		circles.emplace_back(3.95115822320804, 1.604786089155823, 0.9474233512068166);
		circles.emplace_back(-3.50209676893428, 0.5219307285733521, 0.9916057455586269);
		circles.emplace_back(3.899145156610757, 3.846964461263269, 0.949941837391816);
		circles.emplace_back(1.334900313522667, 0.3511193417944014, 1.49826796001289);
		circles.emplace_back(1.558473019395024, 0.251476455014199, 0.9096599868265911);
		circles.emplace_back(-3.389522719662637, 2.539032080676407, 0.5722124198218808);
		circles.emplace_back(-3.962683568242937, 2.883913649711758, 1.032887978875078);
		circles.emplace_back(0.4025918641127646, 0.4183786059729755, 0.7960869510425255);
		circles.emplace_back(-0.3834242862649262, 3.225867685396224, 1.050606504012831);
		circles.emplace_back(0.1738169719465077, 2.695262467022985, 0.8873089603846892);
		circles.emplace_back(1.173273788299412, -1.313460206147283, 1.392195034609176);
		circles.emplace_back(0.1375971944071352, -1.621957023162395, 0.7286570149241015);
		circles.emplace_back(2.230752191971987, 3.32068792777136, 1.429460329306312);
		circles.emplace_back(-2.95562508283183, 4.842327029909939, 1.824891064106487);
		circles.emplace_back(-0.06278582150116563, -3.076921605970711, 0.6758615877712145);
		circles.emplace_back(1.461611988488585, -2.611879103351384, 1.167191450367682);
		circles.emplace_back(-0.3723627445288002, 3.967504103202373, 1.726500303600915);
		circles.emplace_back(-3.697958632837981, 0.5190889514051378, 1.24324916487094);
		circles.emplace_back(4.49353484204039, -2.771885169204324, 1.186791147501208);
		circles.emplace_back(-2.60737078031525, 3.363352927844971, 1.584877465548925);
		circles.emplace_back(-4.477811858523637, 2.457571208942682, 1.098969154176302);
		circles.emplace_back(-4.14280331460759, 3.588859045412391, 1.340132162137888);
		circles.emplace_back(-1.011936927679926, -2.491747082676739, 0.8558619238669052);
		circles.emplace_back(-2.465130721684545, -0.306315899360925, 1.069232560391538);
		circles.emplace_back(3.993970851879567, -1.986779707949609, 0.8450664869742468);
		circles.emplace_back(-0.6755093554966152, 4.422745367046446, 0.7805672451620921);
		circles.emplace_back(4.981856143567711, -3.972777102608234, 1.232248569536023);
		circles.emplace_back(3.875587887596339, -4.228987253736705, 0.6979307201923802);
		circles.emplace_back(2.252090473193675, 2.891596572007984, 0.9135469047119841);
		circles.emplace_back(3.6987055814825, -0.6285452633164823, 1.16718944797758);
		circles.emplace_back(-1.956287694629282, 4.455543986987323, 0.7765903928084299);
		circles.emplace_back(0.230949732940644, 3.870363358873874, 1.142081955377944);
		circles.emplace_back(-2.606102346908301, 1.104039025958627, 1.599458132288419);
	}
	result_expected = 8.537759298484255;

	timer.reset();
	result_actual = algorithm(a151, b151, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #151: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a152(-3.132441740017384, -3.795596955344081);
	Point b152(3.036125095095485, -2.957285171374679);
	{
		circles.emplace_back(2.7316540828906, 3.986172436270863, 1.467347902827896);
		circles.emplace_back(-3.320780594367534, 3.712233465630561, 1.087224420090206);
		circles.emplace_back(0.8695989032275975, 0.9293025336228311, 0.7103738203411921);
		circles.emplace_back(2.77810642728582, 4.7736248630099, 0.877007399010472);
		circles.emplace_back(-3.09130608337, -1.201506711076945, 1.75238261197228);
		circles.emplace_back(1.262308557052165, 3.588365034665912, 0.8369624791434034);
		circles.emplace_back(-2.733875664416701, -2.629982510115951, 0.6813852925086393);
		circles.emplace_back(4.357280361000448, 0.5575548927299678, 0.7720531769795342);
		circles.emplace_back(-3.383402314502746, -0.6007303553633392, 0.8340223553823307);
		circles.emplace_back(-4.435599267017096, -3.178979384247214, 0.6713311861967668);
		circles.emplace_back(4.757881963159889, 4.686118217650801, 1.606236959458329);
		circles.emplace_back(3.265529333148152, -4.406087559182197, 1.45875110689085);
		circles.emplace_back(4.952153086196631, -0.2645560051314533, 1.112796411779709);
		circles.emplace_back(-0.3343130531720817, -3.988728991243988, 1.424055379047058);
		circles.emplace_back(4.120048542972654, 1.192313118372113, 1.020473548793234);
		circles.emplace_back(-0.669842769857496, -2.953248575795442, 0.6671083126915618);
		circles.emplace_back(-1.778816555161029, 2.301747289020568, 1.445812468160875);
		circles.emplace_back(-4.200103438924998, 3.475719874259084, 1.220400894409977);
		circles.emplace_back(2.096031324472278, -1.447240894194692, 0.8049541970947757);
		circles.emplace_back(1.155857464764267, -1.432218600530177, 0.961127737420611);
		circles.emplace_back(0.4464157740585506, 0.834289260674268, 0.503583820653148);
		circles.emplace_back(-3.622047232929617, 4.567401057574898, 0.9415840309346094);
		circles.emplace_back(-0.03861710196360946, -2.346454702783376, 0.8323506236774847);
		circles.emplace_back(-0.2323727426119149, 0.1335564744658768, 1.016940995608456);
		circles.emplace_back(1.396299705374986, -0.6143587850965559, 1.568397993198596);
		circles.emplace_back(3.403281399514526, 2.243016737047583, 0.8843468817183747);
		circles.emplace_back(-0.8220654889009893, -2.407559093553573, 1.183828681590967);
		circles.emplace_back(4.119135483633727, 2.430379122961313, 0.9932793081970884);
		circles.emplace_back(1.37049236567691, 1.144664639141411, 0.9096460388740524);
		circles.emplace_back(2.772556429263204, -1.624019534792751, 1.035611438029446);
		circles.emplace_back(4.622132431250066, 4.982366573531181, 1.411517358501442);
		circles.emplace_back(0.0436965306289494, 3.613093902822584, 0.5529807924991473);
		circles.emplace_back(4.225706101860851, 3.83424554252997, 0.4120858354726806);
		circles.emplace_back(4.053524082992226, -1.546472136396915, 1.659150310861878);
		circles.emplace_back(0.1293622027151287, -1.411688334774226, 0.755141465109773);
		circles.emplace_back(-3.004548500757664, 2.087192700710148, 1.394300262420438);
	}
	result_expected = 7.559277616919725;

	timer.reset();
	result_actual = algorithm(a152, b152, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #152: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a153(-2.622891962062567, 2.180836336687207);
	Point b153(3.891115327831358, 0.05623186565935612);
	{
		circles.emplace_back(3.828357586171478, 3.436765151564032, 0.8055230023572221);
		circles.emplace_back(-4.551608280744404, 1.359642508905381, 0.7714800624875351);
		circles.emplace_back(4.868506237398833, 2.575483948457986, 1.897134295222349);
		circles.emplace_back(4.575513687450439, -4.691646045539528, 1.421923555596732);
		circles.emplace_back(-1.563800985459238, -4.791752786841244, 0.8061142169171944);
		circles.emplace_back(2.493924910668284, -1.940270096529275, 1.469054680760018);
		circles.emplace_back(2.677444766741246, -1.062356519978493, 1.079101393301971);
		circles.emplace_back(-3.281762532424182, -2.528168449643999, 1.596102568483911);
		circles.emplace_back(2.614411057438701, 2.622398177627474, 0.9572502030292526);
		circles.emplace_back(-0.9709272324107587, -2.3689712327905, 0.8867220218060538);
		circles.emplace_back(-2.011291228700429, -3.00819308264181, 0.6756261480273679);
		circles.emplace_back(2.288056362885982, 3.649935589637607, 1.364582063048147);
		circles.emplace_back(3.959596154745668, 2.232519856188446, 0.7505498323822394);
		circles.emplace_back(2.911687272135168, -1.341355957556516, 1.287516858498566);
		circles.emplace_back(-0.1109641161747277, 3.961251352448016, 0.7816229480551555);
		circles.emplace_back(1.941093534696847, 4.100096148904413, 0.7742419507121667);
		circles.emplace_back(-4.120867496822029, -4.928792116697878, 0.8535681033739819);
		circles.emplace_back(-2.843595535960048, -2.219722282607108, 1.069568415614776);
		circles.emplace_back(4.754821329843253, 1.232995942700654, 0.9798502677353098);
		circles.emplace_back(-0.08506118087098002, -2.692488750908524, 1.111664749099873);
		circles.emplace_back(2.555773665662855, 1.092490388546139, 1.222821043455042);
		circles.emplace_back(2.091626862529665, 3.332469060551375, 0.9397209753049537);
		circles.emplace_back(-2.933673087973148, -2.811387542169541, 1.391337913204916);
		circles.emplace_back(-0.5819469760172069, 1.121621464844793, 1.159861656255089);
		circles.emplace_back(-4.779158069286495, -0.9368145815096796, 1.093959048972465);
		circles.emplace_back(-3.596775361802429, 4.211678605061024, 1.458834170061164);
		circles.emplace_back(0.1242337445728481, 4.703004576731473, 1.151400205981918);
		circles.emplace_back(3.624640975613147, 3.951178283896297, 0.806365812360309);
		circles.emplace_back(0.6735154218040407, -0.9090228914283216, 0.7834636625135317);
		circles.emplace_back(-0.7475444651208818, -2.612284116912633, 0.9056379631860181);
		circles.emplace_back(-4.893961262423545, -2.001344065647572, 0.7206101040588692);
		circles.emplace_back(1.96249331580475, -3.04459378356114, 1.524567748955451);
		circles.emplace_back(-2.016291043255478, -0.02328939503058791, 0.6862427877495065);
		circles.emplace_back(0.6556035415269434, 2.507010910194367, 0.6560173167614266);
		circles.emplace_back(1.899794831406325, -1.45715308142826, 0.7901092604966834);
		circles.emplace_back(-3.618702951353043, 3.168758654501289, 0.6001680256566032);
		circles.emplace_back(4.316048657055944, -1.421594263520092, 0.9034993417793884);
		circles.emplace_back(2.312836314085871, -2.976770580280572, 0.424601547117345);
		circles.emplace_back(0.1526949810795486, 4.675340217072517, 0.6906290195183828);
		circles.emplace_back(-2.711085162591189, 4.496767481323332, 0.8246220543747768);
	}
	result_expected = 16.85711546641779;

	timer.reset();
	result_actual = algorithm(a153, b153, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #153: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a154(-2.162488061469048, 2.699591549113393);
	Point b154(3.921645232941955, 1.854561591520905);
	{
		circles.emplace_back(3.577119631227106, -3.926218652632087, 0.9923015740001574);
		circles.emplace_back(1.338900330010802, 3.971999890636653, 1.621126572857611);
		circles.emplace_back(-4.724953782279044, 3.843133051414043, 1.164689214085229);
		circles.emplace_back(0.5599563871510327, 4.470731464680284, 1.136628066352569);
		circles.emplace_back(-0.797261914703995, 2.227320896927267, 1.033348550111987);
		circles.emplace_back(-3.556994365062565, -1.284190502483398, 0.8577682002214715);
		circles.emplace_back(1.419497921597213, -1.71362143708393, 1.555394987878389);
		circles.emplace_back(-2.897163990419358, -3.043032682035118, 0.8897194834193214);
		circles.emplace_back(-3.456702495459467, 4.803105650935322, 0.831407592468895);
		circles.emplace_back(2.586336696986109, 3.3111782069318, 1.829017139668576);
		circles.emplace_back(-3.22368671419099, -0.9890957060270011, 0.6206997028784826);
		circles.emplace_back(-1.986213109921664, -3.71125970268622, 1.098783640540205);
		circles.emplace_back(-2.088642029557377, -3.927712847944349, 0.7885322956601157);
		circles.emplace_back(3.047964370343834, -3.462926123756915, 1.168251944589429);
		circles.emplace_back(-1.472295813728124, 2.041943513322622, 0.8561441210331395);
		circles.emplace_back(-0.4191099130548537, -2.565031030680984, 1.023496072390117);
		circles.emplace_back(4.29230801993981, 0.7096805493347347, 0.7917117335600778);
		circles.emplace_back(-1.319059517700225, -4.373667116742581, 1.757088187639601);
		circles.emplace_back(1.986743093002588, 2.014757466968149, 0.6043040137505158);
		circles.emplace_back(0.2870308398269117, -1.118123380001634, 1.11860611832235);
		circles.emplace_back(-2.791850806679577, 1.207544940989465, 1.492624608310871);
		circles.emplace_back(3.573965250980109, -2.385895743500441, 1.091989839938469);
		circles.emplace_back(-4.113935071509331, -4.7026182920672, 0.6732485377928241);
		circles.emplace_back(-2.403066793922335, 4.217746241483837, 0.5842908144230022);
		circles.emplace_back(2.546864042524248, -4.725933328736573, 1.535140759195201);
		circles.emplace_back(2.345853771548718, 0.3205452230758965, 0.6668947532074525);
		circles.emplace_back(2.251430891919881, -2.333341354969889, 0.4177273787325248);
		circles.emplace_back(-1.91079048672691, 4.233932013157755, 1.025835566804744);
		circles.emplace_back(-2.252625504042953, -1.465167750138789, 1.144945258158259);
		circles.emplace_back(-4.563144620042294, -4.738557694945484, 0.9592885693302378);
		circles.emplace_back(2.279468548949808, -4.982267671730369, 0.8466420840704814);
		circles.emplace_back(-1.835155647713691, 3.512509514112025, 0.699250793014653);
		circles.emplace_back(3.98939172970131, 3.465200362261385, 1.015200814954005);
		circles.emplace_back(0.229446419980377, 3.585934715811163, 0.972386092157103);
		circles.emplace_back(2.987701341044158, -1.810005872976035, 0.8515928001375869);
		circles.emplace_back(-1.051307234447449, 4.937019997742027, 1.132718630298041);
	}
	result_expected = 12.37296295946367;

	timer.reset();
	result_actual = algorithm(a154, b154, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #154: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a155(-2.755446232389659, -1.575936390087008);
	Point b155(2.279246983584017, 0.7405337486416101);
	{
		circles.emplace_back(-4.744066579733044, 3.124185020569712, 1.31281912534032);
		circles.emplace_back(-4.434192755725235, 1.935756157618016, 1.462388375657611);
		circles.emplace_back(-3.959848054219037, 4.314540096092969, 0.865561564755626);
		circles.emplace_back(-2.70374822197482, -3.673918901477009, 0.7508092691889032);
		circles.emplace_back(-2.522119807545096, -3.808446282055229, 1.230060760327615);
		circles.emplace_back(0.8521600090898573, -0.3948388923890889, 1.056064188550226);
		circles.emplace_back(0.08453084854409099, 4.369842160958797, 1.360784813319333);
		circles.emplace_back(3.59397302614525, -3.870663049165159, 1.069372719875537);
		circles.emplace_back(-3.136129991617054, 4.977673355024308, 0.9945154367713257);
		circles.emplace_back(2.679103955160826, -2.453398972284049, 0.8661510647507384);
		circles.emplace_back(-4.751727196853608, 4.008927696850151, 1.302424888475798);
		circles.emplace_back(-4.663359040860087, 3.310298530850559, 1.395400881045498);
		circles.emplace_back(-1.549077380914241, 1.522347938735038, 1.01204376288224);
		circles.emplace_back(3.635641701985151, 1.444970180746168, 0.8445156693225726);
		circles.emplace_back(1.700641156639904, 2.74084601784125, 1.359255878464319);
		circles.emplace_back(0.6087070167995989, -2.001892153639346, 1.421328612673096);
		circles.emplace_back(0.8523403177969158, -0.7654523919336498, 1.206851570052095);
		circles.emplace_back(-4.681959103327245, -0.02603752771392465, 0.9121485395124181);
		circles.emplace_back(0.6168225384317338, 1.407540610525757, 0.6031781140947714);
		circles.emplace_back(2.905880885664374, -1.43142543034628, 1.44257237247657);
		circles.emplace_back(3.795534137170762, 0.5004712683148682, 0.5924737381981685);
		circles.emplace_back(4.346368939150125, -2.166929023806006, 0.9290222581243142);
		circles.emplace_back(-0.4925441206432879, -4.318887291010469, 1.064070730865933);
		circles.emplace_back(4.585314302239567, -1.289813232142478, 1.175307380291633);
		circles.emplace_back(-3.685629994142801, -1.06996153248474, 0.7066614174516871);
		circles.emplace_back(0.794397306162864, 4.788011291529983, 1.518889752938412);
		circles.emplace_back(-3.256767948623747, 2.307579412590712, 0.8214584846748039);
		circles.emplace_back(-1.308888320345432, -1.180872383993119, 1.261569902230985);
		circles.emplace_back(-4.789325303863734, -3.917977178934962, 0.8279091946547851);
		circles.emplace_back(4.180137978401035, 0.2686121710576117, 1.051584727154113);
		circles.emplace_back(4.243482819292694, 3.199839990120381, 0.5395049470243976);
		circles.emplace_back(3.485473475884646, 1.710855283308774, 1.397896814835258);
		circles.emplace_back(3.675900076050311, 1.443437130656093, 0.6483622586121782);
		circles.emplace_back(1.588878554757684, 4.059092497918755, 1.010635897167958);
		circles.emplace_back(4.397959115449339, 3.006436235737056, 0.6489604220492765);
		circles.emplace_back(-0.0964832422323525, -2.68767575500533, 1.623981226538308);
	}
	result_expected = 6.074430850599517;

	timer.reset();
	result_actual = algorithm(a155, b155, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #155: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a156(-2.614524539094418, -1.268058119341731);
	Point b156(2.839009271468967, 1.160471731796861);
	{
		circles.emplace_back(-1.259078572038561, -1.091264055576175, 0.9781106695765629);
		circles.emplace_back(-4.354555865284055, 4.943890168797225, 1.227046142960899);
		circles.emplace_back(-0.5143372458405793, 1.819261547643691, 1.464110106159933);
		circles.emplace_back(-1.821697361301631, 2.252295350190252, 1.450894518918358);
		circles.emplace_back(1.988226936664432, 1.259428227785975, 0.498225954757072);
		circles.emplace_back(3.462405374739319, -0.2410863828845322, 1.276308797555975);
		circles.emplace_back(-1.00413701729849, 4.062466837931424, 0.5586324666859581);
		circles.emplace_back(4.730280910152942, 0.6518823816441, 1.546148598729633);
		circles.emplace_back(2.631902319844812, -3.256733024027199, 1.593586510070599);
		circles.emplace_back(4.086408915463835, 4.668006009887904, 1.831551845441572);
		circles.emplace_back(1.928374457638711, 4.837785859126598, 1.229093203996308);
		circles.emplace_back(4.717112437356263, -2.610407324973494, 0.8874351758277043);
		circles.emplace_back(-1.830403229687363, -2.684605789836496, 0.9410338329384103);
		circles.emplace_back(-3.218214379157871, 1.260956737678498, 1.455671967449598);
		circles.emplace_back(4.333359494339675, 3.063670874107629, 0.7821613149018958);
		circles.emplace_back(-2.616593900602311, 0.8026139973662794, 1.259185278578661);
		circles.emplace_back(4.037420784588903, -1.543123365845531, 0.8846419342095032);
		circles.emplace_back(-4.534499978180975, -4.971459091175348, 1.392497698660009);
		circles.emplace_back(-4.386129577178508, -1.250193554442376, 0.8625329873757437);
		circles.emplace_back(2.150696434546262, -2.057037393096834, 1.081272287643515);
		circles.emplace_back(1.992514522280544, 0.2379380562342703, 1.053234428004362);
		circles.emplace_back(4.672726488206536, -3.042021666187793, 0.8425584713695571);
		circles.emplace_back(0.7267773221246898, 3.542763732839376, 1.100038534146734);
		circles.emplace_back(-3.590808312874287, 2.881926612462848, 0.8163239476969465);
		circles.emplace_back(4.491709915455431, -0.2320894389413297, 0.6269250590587034);
		circles.emplace_back(-4.653355849441141, -2.469263740349561, 1.044908345560543);
		circles.emplace_back(4.473539504688233, -0.6228764611296356, 0.5292102637933567);
		circles.emplace_back(-2.647509395610541, -0.239396917168051, 0.4377765666460618);
		circles.emplace_back(1.003786528017372, -2.780595568474382, 1.037056667567231);
		circles.emplace_back(-2.360049427952617, 1.560175854247063, 0.8618794268695638);
		circles.emplace_back(1.318320750724524, 4.919568106997758, 0.9406862893374636);
		circles.emplace_back(2.542767983395606, -3.475971093866974, 0.5305464023491367);
		circles.emplace_back(-2.807178834918886, 2.61419682065025, 0.63391359152738);
		circles.emplace_back(2.91559417033568, -2.693457559216768, 1.213639972056262);
		circles.emplace_back(-0.829051707405597, 4.493441667873412, 1.073825274338014);
		circles.emplace_back(-1.106071032118052, 0.2764053991995752, 1.44619323683437);
		circles.emplace_back(2.910131232347339, -4.44166082656011, 1.206582506583072);
		circles.emplace_back(2.134225389454514, -1.693200517911464, 1.759432181972079);
		circles.emplace_back(0.5722155491821468, -0.8287202636711299, 1.009907116484828);
		circles.emplace_back(4.760232095140964, 0.1949166669510305, 1.58445113801863);
	}
	result_expected = 20.34563058187442;

	timer.reset();
	result_actual = algorithm(a156, b156, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #156: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a157(-2.986462369095534, -3.908813280984759);
	Point b157(3.456657384987921, -0.8495183493942022);
	{
		circles.emplace_back(-0.6594360829330981, 2.815866621676832, 0.9867928544292226);
		circles.emplace_back(-0.2778818621300161, -0.2809713897295296, 1.531022850307636);
		circles.emplace_back(3.926688849460334, 4.817881092894822, 0.7446910032304004);
		circles.emplace_back(4.344076078850776, -4.617133310530335, 1.034913190617226);
		circles.emplace_back(2.052649816032499, 1.763300879392773, 0.8892539024585857);
		circles.emplace_back(3.588779459241778, -1.233103529084474, 0.2858967129839584);
		circles.emplace_back(0.7921061175875366, 2.427085426170379, 0.9596773221390321);
		circles.emplace_back(0.03542318241670728, 1.77493262803182, 0.9623521603411063);
		circles.emplace_back(2.487514929380268, -4.265320783015341, 1.232363825128414);
		circles.emplace_back(-1.489526310469955, 1.847265015821904, 1.342305749910883);
		circles.emplace_back(-2.579923935700208, -0.8379104058258235, 1.058233176660724);
		circles.emplace_back(3.494752419646829, -2.747153097297996, 0.9780204247916117);
		circles.emplace_back(4.042135330382735, 0.2371947537176311, 0.9539616138441488);
		circles.emplace_back(4.918144152034074, 3.488315043505281, 0.8442578170215711);
		circles.emplace_back(-0.1861672312952578, -2.261111659463495, 0.3963330211350694);
		circles.emplace_back(3.455053253564984, -2.881117698270828, 1.312062987568788);
		circles.emplace_back(-4.494200304616243, -2.767392366658896, 0.6155595273943617);
		circles.emplace_back(-3.432682070415467, -2.386094874236733, 1.131021161540411);
		circles.emplace_back(2.804328387137502, -4.84260925790295, 1.120053603523411);
		circles.emplace_back(-4.653021877165884, -4.63347438024357, 1.182197439367883);
		circles.emplace_back(4.615254353266209, -2.341388154309243, 0.9909417904214933);
		circles.emplace_back(1.81334561901167, 1.722658982034773, 1.378902128315531);
		circles.emplace_back(2.734731973614544, -1.639073451515287, 0.6386564208427443);
		circles.emplace_back(-4.611051434185356, -3.201967005152255, 0.9254229659913107);
		circles.emplace_back(-2.647324644494802, -0.3727635811083019, 1.067370052379556);
		circles.emplace_back(4.421557534951717, 3.280029760207981, 1.083371479599736);
		circles.emplace_back(-0.432631375733763, -4.678745397832245, 1.466441008844413);
		circles.emplace_back(0.3963360958732665, -3.670924224425107, 1.450404223124496);
		circles.emplace_back(-1.606820758897811, -2.262753273826092, 0.718103428487666);
		circles.emplace_back(-0.9748723800294101, -3.059579806867987, 1.341821822128259);
		circles.emplace_back(-1.823098307941109, -2.565259931143373, 0.9690336549887433);
		circles.emplace_back(1.91160878399387, -0.5330151435919106, 1.493478443357162);
		circles.emplace_back(0.3656026418320835, -4.991037293802947, 1.270260744658299);
		circles.emplace_back(3.721508991438895, -2.812436542008072, 1.262051493837498);
		circles.emplace_back(-1.060067603830248, -2.910506890621036, 1.682662300788797);
		circles.emplace_back(1.486313680652529, -3.418009087909013, 0.7735260416520759);
		circles.emplace_back(-4.708288733381778, 3.840069409925491, 0.9114977835910394);
		circles.emplace_back(3.586838238406926, -4.904002214316279, 1.350240638083778);
	}
	result_expected = 15.24742126572924;

	timer.reset();
	result_actual = algorithm(a157, b157, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #157: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a158(-2.926638636272401, 0.5453810412436724);
	Point b158(2.518602037336677, 3.767116392031312);
	{
		circles.emplace_back(-1.43647879594937, 4.849777987692505, 1.52014452854637);
		circles.emplace_back(2.370113807264715, -4.072247364092618, 0.8655092649860308);
		circles.emplace_back(1.011699202936143, -0.2041915315203369, 0.1748047995613888);
		circles.emplace_back(-3.770441382657737, -0.4221651726402342, 0.8666104491567239);
		circles.emplace_back(3.760268741752952, -2.847971019800752, 1.401608663261868);
		circles.emplace_back(1.379373578820378, -4.554147433955222, 0.6126344552962109);
		circles.emplace_back(2.060330819804221, 1.967307308223099, 1.617691246583126);
		circles.emplace_back(3.808191528078169, -3.531567321624607, 0.7003641382092609);
		circles.emplace_back(4.452933112625033, -1.107244596350938, 0.6305670995963737);
		circles.emplace_back(-3.749781970400363, 2.893746432382613, 1.645847222139127);
		circles.emplace_back(0.8855971624143422, -4.683665598277003, 0.7429227702086791);
		circles.emplace_back(-4.767198695335537, -2.246448730584234, 0.8162337130168452);
		circles.emplace_back(4.765187969896942, 4.863408009987324, 1.130423178034834);
		circles.emplace_back(-3.704298653174192, 1.930302896071225, 0.7413412337424233);
		circles.emplace_back(-4.540503101889044, 4.431719279382378, 1.012879106053151);
		circles.emplace_back(-4.092672464903444, 0.8268874953500926, 0.8765405640704557);
		circles.emplace_back(-4.755470764357597, 4.08370514633134, 0.9386960159288719);
		circles.emplace_back(4.873337701428682, 0.5998204625211656, 1.215158026269637);
		circles.emplace_back(4.828945079352707, -0.188161504920572, 1.243521209270693);
		circles.emplace_back(1.32947368780151, 0.5421727034263313, 1.231388692441396);
		circles.emplace_back(-1.242540285456926, 2.135930836666375, 0.8378544912906363);
		circles.emplace_back(0.5465903249569237, 0.6561799882911146, 0.9608280451735481);
		circles.emplace_back(2.733555173035711, -4.486108364071697, 1.056933740549721);
		circles.emplace_back(-0.767961775418371, -2.998740554321557, 1.112782914633863);
		circles.emplace_back(0.2426720666699111, -0.09840382961556315, 1.625419586081989);
		circles.emplace_back(0.5654837866313756, -0.3384992876090109, 1.329128824151121);
		circles.emplace_back(3.812547416891903, -0.9053252241574228, 1.168085333541967);
		circles.emplace_back(0.09379903087392449, -0.6628805142827332, 1.260278541850857);
		circles.emplace_back(3.369194574188441, 1.836110197473317, 0.699886163813062);
		circles.emplace_back(0.6173454714007676, -0.6652241782285273, 1.335092893033288);
		circles.emplace_back(-4.856884928885847, -1.939751484896988, 1.3278050650144);
		circles.emplace_back(-0.9758049971424043, -2.865996726322919, 1.55761957548093);
		circles.emplace_back(1.670176002662629, -4.250702138524503, 1.119333896343596);
		circles.emplace_back(-2.928200482856482, -0.5469112866558135, 0.9742879073834046);
		circles.emplace_back(0.3651802777312696, 2.452607902232558, 1.075846419692971);
		circles.emplace_back(0.1273397193290293, 0.5775864305905998, 0.7081171250669285);
		circles.emplace_back(-1.326499164570123, -1.688008203636855, 1.630956072476692);
		circles.emplace_back(1.608452361542732, -0.6017561466433108, 1.339113035215996);
	}
	result_expected = 6.97242173188933;

	timer.reset();
	result_actual = algorithm(a158, b158, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #158: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a159(-3.3354487339966, 2.55845688469708);
	Point b159(3.597456944640726, -3.247585317119956);
	{
		circles.emplace_back(3.382549674715847, -4.9347461364232, 1.411210745410062);
		circles.emplace_back(-2.347546808887273, -0.7374529610387981, 0.6657043275656178);
		circles.emplace_back(1.665680010337383, -4.359172268304974, 1.215303206234239);
		circles.emplace_back(0.5820243037305772, 3.007816395256668, 1.336826654174365);
		circles.emplace_back(-3.413915408309549, -0.1525051076896489, 0.5780533679528161);
		circles.emplace_back(0.636542949359864, 4.576086227316409, 0.9365321698831394);
		circles.emplace_back(-0.3440926666371524, 3.73101390665397, 1.953077770373784);
		circles.emplace_back(-4.270683324430138, 4.156934472266585, 1.562305171252228);
		circles.emplace_back(-3.981212319340557, 3.355961281340569, 1.024307209881954);
		circles.emplace_back(3.715111732017249, -4.458075955044478, 0.7059667983325197);
		circles.emplace_back(-1.391188639681786, 3.570573457982391, 0.6645316118141635);
		circles.emplace_back(-2.865012029651552, 4.032432122621685, 0.9745517283910885);
		circles.emplace_back(1.47276837611571, 3.195002123247832, 0.8260231231106445);
		circles.emplace_back(3.928846146445721, 0.02832659753039479, 1.771081720222719);
		circles.emplace_back(4.640589968767017, 0.7071576663292944, 0.3352115949848666);
		circles.emplace_back(3.469223997090012, 3.907440255861729, 1.007580027240328);
		circles.emplace_back(4.043148986529559, 4.371501274872571, 1.244309176993556);
		circles.emplace_back(1.272060994524509, 4.417288245167583, 1.156249915598892);
		circles.emplace_back(4.856702161487192, 2.178809887263924, 1.162054155417718);
		circles.emplace_back(-2.942526189144701, 4.388744391035289, 1.099410766432993);
		circles.emplace_back(-2.926714282948524, -1.176405202131718, 0.8316017653094604);
		circles.emplace_back(4.946462616790086, -4.164074661675841, 0.8973281863844021);
		circles.emplace_back(2.084562608506531, -3.934017044957727, 1.281255623907782);
		circles.emplace_back(2.038347704801708, -2.040949400980026, 1.378224277379922);
		circles.emplace_back(0.08687470806762576, -0.4563399846665561, 0.9799299956532195);
		circles.emplace_back(1.755305316764861, 2.080317491199821, 1.163376437290571);
		circles.emplace_back(-4.141207451466471, -1.184069903101772, 0.984955196850933);
		circles.emplace_back(1.136793608311564, 0.4625275428406894, 1.444532444770448);
		circles.emplace_back(-4.278778780717403, 1.819091450888664, 1.003490788419731);
		circles.emplace_back(-3.963494531344622, -0.4255707957781851, 1.245551007962786);
		circles.emplace_back(1.048714758362621, -3.388453980442137, 1.178459642664529);
		circles.emplace_back(3.311203664634377, 4.831585462670773, 1.634356644260697);
		circles.emplace_back(4.852995134424418, 4.205029599834234, 0.7480019075097516);
		circles.emplace_back(0.9462625277228653, -4.849831296596676, 1.565164945810102);
		circles.emplace_back(1.455765662249178, -4.834931918885559, 1.151471329131164);
		circles.emplace_back(4.386959152761847, -4.446571089792997, 0.8119889729423448);
		circles.emplace_back(-1.142247554380447, -1.730766023974866, 1.102457331423648);
		circles.emplace_back(-1.112474172841758, -1.683324950281531, 0.8901797052239998);
	}
	result_expected = 21.59278383485694;

	timer.reset();
	result_actual = algorithm(a159, b159, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #159: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a160(-3.568900238256902, 0.4687969703227282);
	Point b160(2.025525154080242, 0.6833151523023844);
	{
		circles.emplace_back(-4.442988450173289, 2.20169415930286, 0.9785552047425881);
		circles.emplace_back(-4.778861587401479, 4.896800487767905, 0.8093739864183589);
		circles.emplace_back(-3.393724013585597, -1.831069875042886, 1.446088556130417);
		circles.emplace_back(3.330705829430372, -3.655303607229143, 0.884603264904581);
		circles.emplace_back(4.978343786206096, -1.550221999641508, 1.354558153287508);
		circles.emplace_back(2.159585601184517, 2.668906922917813, 1.086777293193154);
		circles.emplace_back(0.8960880408994853, -4.418300099205226, 1.063251299900003);
		circles.emplace_back(0.2887025964446366, -1.837961210403591, 1.045171172707342);
		circles.emplace_back(-0.3002637648023665, 4.413516393397003, 0.9438871596241369);
		circles.emplace_back(-1.159328443463892, -3.935647525358945, 1.151179250399582);
		circles.emplace_back(-2.16104143531993, -0.4179775970987976, 0.3344005543040112);
		circles.emplace_back(-3.134041100274771, -3.465084510389715, 0.3141329135512933);
		circles.emplace_back(3.648586624767631, 2.768571379128844, 1.050352104962803);
		circles.emplace_back(4.179911224637181, -1.841172587592155, 1.257178809377365);
		circles.emplace_back(1.850833564531058, 3.766389444936067, 1.008432489004917);
		circles.emplace_back(-3.902019450906664, 2.651099993381649, 1.509302024566568);
		circles.emplace_back(0.0706485309638083, 2.984671785961837, 0.6841056038392708);
		circles.emplace_back(0.3343381243757904, -4.672592047136277, 1.093217730452307);
		circles.emplace_back(3.052757552359253, 2.516959409695119, 0.8375702428398654);
		circles.emplace_back(2.520329139661044, -1.822420738171786, 1.862864545476623);
		circles.emplace_back(-0.4059246438555419, 1.59427055856213, 0.903858990012668);
		circles.emplace_back(-1.045565383974463, 1.580544507596642, 0.8238121744478121);
		circles.emplace_back(-2.944437561091036, 2.311925597023219, 0.9695692912442609);
		circles.emplace_back(-3.350708198267967, -4.57145283697173, 1.19994296238292);
		circles.emplace_back(-4.811211570631713, -2.754053922835737, 0.9098356801783666);
		circles.emplace_back(4.402476085815579, 4.235238644760102, 0.7140199376968667);
		circles.emplace_back(-1.069920167792588, 0.9133147005923092, 1.032044829544611);
		circles.emplace_back(-4.848768080119044, 1.540556906256825, 1.128165823989548);
		circles.emplace_back(2.713499467354268, 4.438929718453437, 0.9720548114972188);
		circles.emplace_back(-4.456694803666323, 0.2138858637772501, 0.7636423125630244);
		circles.emplace_back(-3.796512095723301, -2.728596439119428, 0.8910928247729316);
		circles.emplace_back(-3.247411751653999, 1.975278581958264, 1.33176371853333);
	}
	result_expected = 5.770034399977337;

	timer.reset();
	result_actual = algorithm(a160, b160, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #160: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a161(-2.935927360784262, 0.8027112651616335);
	Point b161(2.198754122015089, -2.144554605707526);
	{
		circles.emplace_back(-1.645296381320804, 2.946631226222962, 1.551117806020193);
		circles.emplace_back(4.773177697788924, 1.554826081264764, 0.7145073757739737);
		circles.emplace_back(3.370598789770156, -3.171756661031395, 1.283132651611231);
		circles.emplace_back(2.56540093338117, -4.763277114834636, 1.41725724118296);
		circles.emplace_back(2.981015408877283, 1.127786755096167, 1.250069935317151);
		circles.emplace_back(-4.337046046275645, 0.05577431293204427, 0.6011626652674749);
		circles.emplace_back(4.212055422831327, 4.819731970783323, 0.9147890671854838);
		circles.emplace_back(3.433173389639705, -1.375250627752393, 1.172771856025792);
		circles.emplace_back(-0.8574267267249525, -0.8744650823064148, 0.8950734208105131);
		circles.emplace_back(3.491281575988978, 1.892441355157644, 0.5162172404350712);
		circles.emplace_back(-4.662665228825063, 0.3633302613161504, 1.420259895711206);
		circles.emplace_back(0.2159734047017992, 4.05955376336351, 0.9974051464581861);
		circles.emplace_back(-4.896887016948313, 1.748735539149493, 1.133446482638828);
		circles.emplace_back(3.73466870514676, -0.01792597351595759, 1.478590616886504);
		circles.emplace_back(0.5672328476794064, 3.070105982478708, 1.332905761501752);
		circles.emplace_back(1.85645749559626, 4.112427982036024, 1.131594190956093);
		circles.emplace_back(3.58979499200359, 3.001423615496606, 1.399261949094944);
		circles.emplace_back(-2.041890800464898, 2.821676835883409, 0.8197534271748737);
		circles.emplace_back(3.251277965027839, 4.499597975518554, 1.737606301321648);
		circles.emplace_back(-4.300389329437166, -2.292262928094715, 1.336475378298201);
		circles.emplace_back(-2.143563141580671, 3.010299548041075, 0.5635303620947525);
		circles.emplace_back(0.4105416196398437, 4.975072529632598, 1.57946716689039);
		circles.emplace_back(1.813385032583028, 3.827540760394186, 0.7665487386053428);
		circles.emplace_back(0.7971897884272039, 3.920526618603617, 0.741870247409679);
		circles.emplace_back(-0.8665355830453336, 2.667063127737492, 1.381062770145945);
		circles.emplace_back(-2.977348037529737, 4.727931388188154, 0.252109878254123);
		circles.emplace_back(3.402978603262454, -3.927817104849964, 0.8713836451759561);
		circles.emplace_back(-2.347918299492449, -0.5769087304361165, 1.080888208816759);
		circles.emplace_back(-4.755479854065925, 3.598269273061305, 0.5929627712117508);
		circles.emplace_back(-4.660915329586715, 3.816699085291475, 0.8936228904640301);
		circles.emplace_back(-1.516671052668244, 2.182307916227728, 0.6448670389363542);
		circles.emplace_back(4.430159612093121, 2.673959496896714, 1.197100868704729);
		circles.emplace_back(-1.839389756787568, -2.610085576307029, 0.7438327820273116);
		circles.emplace_back(-0.9651087853126228, -1.634803956840187, 1.305154778226279);
		circles.emplace_back(4.519564693327993, -2.647677154745907, 0.9449884735280647);
		circles.emplace_back(-3.992656653281301, 2.171307175885886, 0.7870119509054347);
		circles.emplace_back(1.319604467134923, 3.476443004328758, 1.387386069376953);
		circles.emplace_back(-3.909722499083728, 1.269812097307295, 0.9407513707643375);
	}
	result_expected = 5.998433770103167;

	timer.reset();
	result_actual = algorithm(a161, b161, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #161: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a162(-2.394924152176827, -0.3027114551514387);
	Point b162(3.423659542109817, -1.848713969811797);
	{
		circles.emplace_back(-3.212071585003287, -0.6831214367412031, 0.2739805918419733);
		circles.emplace_back(1.606698187533766, -4.283419095445424, 1.840861147711985);
		circles.emplace_back(3.270316261332482, 1.239812124986202, 1.286102321301587);
		circles.emplace_back(-2.00015117181465, 1.926544902380556, 0.7403561357175931);
		circles.emplace_back(-4.597530534956604, -1.118343693669885, 1.465145179838873);
		circles.emplace_back(-4.957113282289356, -4.634964999277145, 1.371686911466531);
		circles.emplace_back(-0.7659986172802746, 1.843719810713083, 1.290216302988119);
		circles.emplace_back(-0.08176159346476197, 3.521976678166538, 1.434209971898235);
		circles.emplace_back(0.440275187138468, 2.896244793664664, 1.711851814086549);
		circles.emplace_back(0.1567008602432907, -1.390683043282479, 1.696314556081779);
		circles.emplace_back(3.179476030636579, -0.08270818972960114, 1.252967232442461);
		circles.emplace_back(-0.4302076087333262, 4.762531260494143, 1.152790330187417);
		circles.emplace_back(3.19280261406675, 1.623479898553342, 1.281263949978165);
		circles.emplace_back(-3.485306047368795, -2.76958406670019, 1.525017188233323);
		circles.emplace_back(-2.238716434221715, 1.348706053104252, 0.5842461330583318);
		circles.emplace_back(-2.632447781506926, 4.126104286406189, 0.6878347162390127);
		circles.emplace_back(-2.123103972990066, -4.367801870685071, 0.5886580216931179);
		circles.emplace_back(0.6288081943057477, 1.501492562238127, 0.5562511557945982);
		circles.emplace_back(-0.837010235991329, -0.5317774531431496, 1.03544432434719);
		circles.emplace_back(-4.30827620672062, -3.490944250952452, 0.8848759019048884);
		circles.emplace_back(0.5884280917234719, -4.997885844204575, 0.7871316412230953);
		circles.emplace_back(1.879819741006941, 1.773144139442593, 1.522307141148485);
		circles.emplace_back(4.627496639732271, 1.457920565735549, 0.6698882181895897);
		circles.emplace_back(1.49221807019785, 1.905914579983801, 0.8001825503772124);
		circles.emplace_back(-3.933491243515164, 1.900015736464411, 1.02217797099147);
		circles.emplace_back(4.516520372126251, 4.77034906623885, 1.495601554471068);
		circles.emplace_back(-3.716972388792783, -4.91054781479761, 1.526522714388557);
		circles.emplace_back(-1.820272232871503, -1.638720838818699, 1.435313138901256);
		circles.emplace_back(-4.988753276411444, -4.368851089384407, 0.8500185277545824);
		circles.emplace_back(2.78501987690106, 3.986401564907283, 1.174114589462988);
		circles.emplace_back(4.823620871175081, -4.527499231044203, 0.5115072000538931);
		circles.emplace_back(-4.946764430496842, -1.954535020049661, 1.189933492452838);
		circles.emplace_back(-4.682800935115665, -4.98406418832019, 0.7826672657160088);
		circles.emplace_back(4.089501097332686, -0.1940212841145694, 1.024302642163821);
	}
	result_expected = 6.773247701824389;

	timer.reset();
	result_actual = algorithm(a162, b162, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #162: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a163(-2.761996455024928, -2.317377043887973);
	Point b163(3.119717923458666, -1.857290228828788);
	{
		circles.emplace_back(4.269037412013859, -2.057135736104101, 1.138132247910835);
		circles.emplace_back(-3.983520695473999, 0.07713387487456203, 0.8843051242409273);
		circles.emplace_back(-1.653695919085294, 4.369316913653165, 0.9993082319619133);
		circles.emplace_back(-0.104728068690747, -3.002632765565068, 1.620655936538242);
		circles.emplace_back(-4.037129657808691, -2.909499609377235, 1.21207222903613);
		circles.emplace_back(-4.608286914881319, 4.437186426948756, 0.6741574899060652);
		circles.emplace_back(2.320504474919289, -3.45864127157256, 1.261270300601609);
		circles.emplace_back(2.392870441544801, 1.245806363876909, 1.41319382970687);
		circles.emplace_back(-1.950467845890671, -4.735434127505869, 1.781942056328989);
		circles.emplace_back(3.191011680755764, -4.021313574630767, 1.532387967291288);
		circles.emplace_back(2.419552698265761, -3.788273453246802, 1.078698934731074);
		circles.emplace_back(2.083023127634078, 3.850006961729378, 1.00392138378229);
		circles.emplace_back(-4.413284624461085, -1.465493680443615, 0.9034612484509125);
		circles.emplace_back(-1.197468971367925, -0.8305402402766049, 1.251872943039052);
		circles.emplace_back(-3.249885637778789, -0.1426099124364555, 1.32844364263583);
		circles.emplace_back(2.549862184096128, -4.610182682517916, 1.184611393488012);
		circles.emplace_back(0.1484546973370016, -1.777013053651899, 1.165927052334882);
		circles.emplace_back(1.021699404809624, 3.856589521747082, 0.4794553260086104);
		circles.emplace_back(4.480485327076167, 0.3187681664712727, 0.7494411823572591);
		circles.emplace_back(3.19775601150468, -3.840329928789288, 0.6526816425612196);
		circles.emplace_back(-2.671210917178541, 3.98084374377504, 0.5400049705291167);
		circles.emplace_back(4.466012346092612, -2.610781260300428, 1.154018277744763);
		circles.emplace_back(-1.743636813480407, 1.075851742643863, 0.9935334327863529);
		circles.emplace_back(-3.288973986636847, 2.344119322951883, 0.7854991029715165);
		circles.emplace_back(-3.820982372853905, 0.4362534009851515, 1.158917726040818);
		circles.emplace_back(2.143962502013892, -1.682704284321517, 0.3081212022574618);
		circles.emplace_back(-4.755867857020348, 2.876971492078155, 0.7473013216396793);
		circles.emplace_back(1.516049166675657, 4.605621977243572, 0.9674076646799221);
		circles.emplace_back(2.368691156152636, -0.04893000470474362, 1.055644992436282);
		circles.emplace_back(3.537973787169904, -4.510020527523011, 1.160028974642046);
		circles.emplace_back(-4.97017279965803, -2.078490073326975, 1.150609994656406);
		circles.emplace_back(-4.960654361639172, -3.746307676192373, 1.422847594902851);
		circles.emplace_back(-0.8053988008759916, -2.323085118550807, 0.2356055411277339);
		circles.emplace_back(2.471866242121905, 0.01653618412092328, 0.7599555929424241);
		circles.emplace_back(4.092779878992587, 4.909313262905926, 1.244011729001067);
		circles.emplace_back(-3.80604081088677, -1.609629744198173, 0.3828750651562586);
		circles.emplace_back(-1.420134750660509, -2.296483360696584, 0.8368705034954473);
		circles.emplace_back(2.756166562903672, 3.075167534407228, 1.548180991760455);
	}
	result_expected = -1;

	timer.reset();
	result_actual = algorithm(a163, b163, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #163: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();



	Point a164(-2.743432607036084, 0.07341557927429676);
	Point b164(3.18972791871056, 1.677895480766892);
	{
		circles.emplace_back(0.01006360864266753, -2.553104774560779, 1.320747548365034);
		circles.emplace_back(-1.388512959238142, -3.534712449181825, 0.5456950072897597);
		circles.emplace_back(-2.802141581196338, 1.628731873352081, 1.19814084910322);
		circles.emplace_back(1.195277713704854, 3.806176071520895, 0.6387736178701743);
		circles.emplace_back(-1.648987217340618, -4.162466411944479, 1.402902900264598);
		circles.emplace_back(-1.855145373847336, -4.038814653176814, 1.29362101580482);
		circles.emplace_back(-0.9437925298698246, -3.240182034205645, 1.466229956340976);
		circles.emplace_back(-4.142199333291501, -4.155518768820912, 1.786743213771842);
		circles.emplace_back(-3.557656633201987, 3.347379511687905, 0.494997812458314);
		circles.emplace_back(-2.295153883751482, -2.693286084104329, 0.3310360998613759);
		circles.emplace_back(-2.774147551972419, -3.350137423258275, 0.5701012666570022);
		circles.emplace_back(1.262295374181122, 2.88433380657807, 1.13308398744557);
		circles.emplace_back(3.807379289064556, 3.090808156412095, 1.541546168806962);
		circles.emplace_back(2.203366800677031, 0.8038658206351101, 0.8795890600653364);
		circles.emplace_back(1.51313551934436, -0.9977137506939471, 0.7964870946248993);
		circles.emplace_back(-1.520476753357798, -1.061137409415096, 1.033433922403492);
		circles.emplace_back(1.458896214608103, 2.352216809522361, 0.8741616424871608);
		circles.emplace_back(0.5432921159081161, 4.515325736720115, 1.103824338992126);
		circles.emplace_back(4.327608414459974, -4.072750101331621, 1.417070183134638);
		circles.emplace_back(-2.133085785899311, 2.553479711059481, 0.6678704990306868);
		circles.emplace_back(-3.47181057324633, -2.043788556475192, 1.120628994214348);
		circles.emplace_back(-4.659684144426137, -0.4318574140779674, 0.9086542618693784);
		circles.emplace_back(1.971459139604121, -4.224773778114468, 1.312993182032369);
		circles.emplace_back(0.4424468451179564, -1.126360811758786, 1.02381698123645);
		circles.emplace_back(1.301292839925736, -4.456008102279156, 0.531522514228709);
		circles.emplace_back(3.006084293592721, -0.06842501694336534, 0.9949543621158227);
		circles.emplace_back(0.6579647003673017, -1.395301220472902, 1.558563628257252);
		circles.emplace_back(4.395015446934849, -4.200180780608207, 0.9140325627056881);
		circles.emplace_back(-2.155389518011361, 1.422666267026216, 0.7531856172950938);
		circles.emplace_back(3.558722150046378, 3.556298890616745, 1.4094483503839);
		circles.emplace_back(2.423240353818983, 3.150971366558224, 0.6067623004550113);
		circles.emplace_back(-4.747616311069578, 3.550782992970198, 0.9201415051473304);
		circles.emplace_back(-1.33560222806409, 2.162885901052505, 0.5356401740806177);
		circles.emplace_back(-3.538143045734614, -4.529481793288141, 1.332992204255424);
		circles.emplace_back(1.819704340305179, 1.310169661883265, 0.9511300957063212);
		circles.emplace_back(0.3478826791979373, -1.32564177038148, 1.052368675428442);
		circles.emplace_back(1.197078011464328, -0.04892208380624652, 1.185636052978225);
		circles.emplace_back(-4.001908029895276, -1.89846089342609, 1.417718673287891);
	}
	result_expected = 15.98577528553132;

	timer.reset();
	result_actual = algorithm(a164, b164, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #164: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';
	circles.clear();


	}

	if (big_tests) {

	


	Point a7(1, 1);
	Point b7(9, 9);
	{
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
	}
	result_expected = 13.51711753058981;

	timer.reset();
	result_actual = algorithm(a7, b7, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test  #7: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a8(1, 1);
	Point b8(9, 9);
	{
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
	}
	result_expected = 16.07123503713144;

	timer.reset();
	result_actual = algorithm(a8, b8, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test  #8: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a9(1, 1);
	Point b9(9, 9);
	{
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
	}
	result_expected = 13.7274470620482;

	timer.reset();
	result_actual = algorithm(a9, b9, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test  #9: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a10(1, 1);
	Point b10(9, 9);
	{
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
	}
	result_expected = 14.69287157740538;

	timer.reset();
	result_actual = algorithm(a10, b10, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #10: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a11(1, 1);
	Point b11(9, 9); 
	{
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
	}
	result_expected = 14.98672182510387;

	timer.reset();
	result_actual = algorithm(a11, b11, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #11: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a12(1, 1);
	Point b12(9, 9);
	{
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
	}
	result_expected = 12.49336694213408;

	timer.reset();
	result_actual = algorithm(a12, b12, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #12: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a13(1, 1);
	Point b13(9, 9);
	{
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
	}
	result_expected = 12.54895262026183;

	timer.reset();
	result_actual = algorithm(a13, b13, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #13: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a14(1, 1);
	Point b14(9, 9);
	{
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
	}
	result_expected = 14.74674113879269;

	timer.reset();
	result_actual = algorithm(a14, b14, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #14: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a15(1, 1);
	Point b15(9, 9);
	{
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
	}
	result_expected = 16.79656548837717;

	timer.reset();
	result_actual = algorithm(a15, b15, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #15: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a16(1, 1);
	Point b16(9, 9);
	{
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
	}
	result_expected = 17.31021875860946;

	timer.reset();
	result_actual = algorithm(a16, b16, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #16: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a17(1, 1);
	Point b17(9, 9);
	{
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
	}
	result_expected = 15.90732348954008;

	timer.reset();
	result_actual = algorithm(a17, b17, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #17: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a18(1, 1);
	Point b18(9, 9);
	{
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
	}
	result_expected = 17.61768871639577;

	timer.reset();
	result_actual = algorithm(a18, b18, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #18: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a19(1, 1);
	Point b19(9, 9);
	{
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
	}
	result_expected = 17.21433284181037;

	timer.reset();
	result_actual = algorithm(a19, b19, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #19: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a20(1, 1);
	Point b20(9, 9);
	{
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
	}
	result_expected = 15.11552899882889;

	timer.reset();
	result_actual = algorithm(a20, b20, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #20: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();






	Point a21(1, 1);
	Point b21(9, 9);
	{
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
	}
	result_expected = 11.91428396991884;

	timer.reset();
	result_actual = algorithm(a21, b21, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #21: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();



	Point a22(1, 1);
	Point b22(9, 9);
	{
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
	}
	result_expected = 18.11294822544123;

	timer.reset();
	result_actual = algorithm(a22, b22, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #22: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	Point a23(1, 1);
	Point b23(9, 9);
	{
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
	}
	result_expected = 15.70633562298226;

	timer.reset();
	result_actual = algorithm(a23, b23, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #23: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a24(1, 1);
	Point b24(9, 9);
	{
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
	}
	result_expected = 15.16885571581733;

	timer.reset();
	result_actual = algorithm(a24, b24, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #24: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




	Point a25(1, 1);
	Point b25(9, 9);
	{
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
	}
	result_expected = 15.00554047147732;

	timer.reset();
	result_actual = algorithm(a25, b25, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #25: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	result_expected = 13.4876530125745;
	timer.reset();
	result_actual = algorithm(a36, b36, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #36: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





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
	result_expected = 11.57936863004565;
	timer.reset();
	result_actual = algorithm(a37, b37, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	result_expected = 11.66006079253472;
	timer.reset();
	result_actual = algorithm(a39, b39, circles);
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #47: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();





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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #63: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();




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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
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
	//std::cout << "time ================================================= " << timer.elapsed() << '\n';
	std::cout << "time = " << timer.elapsed() << '\n';

	std::cout << "test #71: " <<
		(are_equal(result_actual, result_expected) ? "ok" : "FAILED") << '\n';
	if (verbose)
		std::cout << "expected = " << result_expected << "\nactual = " << result_actual << '\n';

	circles.clear();


	}




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




int main()
{

	Timer timer;
	const std::size_t number_of_tests = 1u;
	for (std::size_t i = 0u; i < number_of_tests; ++i) {
		//test_tiptoe_through_the_circles(tiptoe_through_the_circles, false, true);
		test_tiptoe_through_the_circles(tiptoe_through_the_circles, true, true);
	}
	const double all_tests_time = timer.elapsed();
	std::cout << "all tests = \t" << all_tests_time << '\n';
	std::cout << "one full test = \t" << all_tests_time / number_of_tests << '\n';
	std::cout << "copy = \t\t\t\t\t" << g_copy / number_of_tests << '\n';
	std::cout << "tangents.reserve = \t\t\t" << g_tangents_reserve / number_of_tests << '\n';
	std::cout << "add_tangents = \t\t\t\t" << g_add_tangents / number_of_tests << '\n';
	std::cout << "filter_tangents = \t\t\t" << g_filter_tangents / number_of_tests << '\n';
	std::cout << "filter_tangents_preparation = \t\t" << g_filter_tangents_preparation / number_of_tests << '\n';
	std::cout << "filter_tangents_filtering = \t\t" << g_filter_tangents_filtering / number_of_tests << '\n';
	std::cout << "add_and_filter_tangents = \t\t" << g_add_and_filter_tangents / number_of_tests << '\n';
	std::cout << "get_points_on_circles = \t\t" << g_get_points_on_circles / number_of_tests << '\n';
	std::cout << "arcs_size = \t\t\t\t" << g_arcs_size / number_of_tests << '\n';
	std::cout << "arcs.reserve = \t\t\t\t" << g_arc_reserve / number_of_tests << '\n';
	std::cout << "add_arcs = \t\t\t\t" << g_add_arcs / number_of_tests << '\n';
	std::cout << "filter_arcs = \t\t\t\t" << g_filter_arcs / number_of_tests << '\n';
	std::cout << "graph.reserve = \t\t\t" << g_graph_reserve / number_of_tests << '\n';
	std::cout << "add_nodes_to_graph = \t\t\t" << g_add_nodes_to_graph / number_of_tests << '\n';
	std::cout << "connect_nodes_of_graph = \t\t" << g_connect_nodes_of_graph / number_of_tests << '\n';
	std::cout << "merge_neighbors_for_similar_nodes = \t" << g_merge_neighbors_for_similar_nodes / number_of_tests << '\n';
	std::cout << "graph = \t\t\t\t" << g_graph / number_of_tests << '\n';
	std::cout << "dijkstra = \t\t\t\t" << g_dijkstra / number_of_tests << '\n';
	
	return 0;
}

