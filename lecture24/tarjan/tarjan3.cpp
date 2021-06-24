#include "tarjan3.h"

namespace Tarjan3 {
	void depth_first_search(const Lists_t& g, Vertex_t start, Vertexes_t& used, Vertexes_t& loop_detector, Stack_t& stack) {
		used.insert(start);
		loop_detector.insert(start);

		for (Vertex_t neighbor : g.at(start)) {
			if (loop_detector.find(neighbor) != loop_detector.cend())
				throw - 1;
			if (used.find(neighbor) == used.cend())
				depth_first_search(g, neighbor, used, loop_detector, stack);
		}
		stack.push(start);
		loop_detector.erase(start);
	}
}

bool tarjan3(const Lists_t& g, Numbers_t& n)
{
	Vertexes_t used;
	Vertexes_t loop_detector;
	Stack_t stack;

	try {
		for (const auto& vn : g)
			if (used.find(vn.first) == used.cend())
				Tarjan3::depth_first_search(g, vn.first, used, loop_detector, stack);
	}
	catch (int) {
		return false;
	}

	int number = 0;
	while (!stack.empty()) {
		n.insert(std::pair<Vertex_t, int>(stack.top(), number));
		stack.pop();
		++number;
	}

	return true;
}
