#include "tarjan.h"





bool depth_first_search(const Lists_t& adjcency_lists, Vertex_t start, Vertexes_t& gray_and_black, Vertexes_t& gray, Stack_t& stack)
{
	gray_and_black.insert(start);
	gray.insert(start);

	for (const auto neighbor : adjcency_lists.at(start))
	{
		if (gray.find(neighbor) == gray.cend())
		{
			if (gray_and_black.find(neighbor) == gray_and_black.cend())
			{
				bool no_cycles = depth_first_search(adjcency_lists, neighbor, gray_and_black, gray, stack);
				if (!no_cycles)
					return false;

				stack.push(neighbor);
			}

			gray.erase(neighbor);
		}
		else
			return false;
	}
	return true;
}

bool tarjan(const Lists_t& adjacency_lists,
	Numbers_t& numbersOut)
{
	Vertexes_t gray_and_black;
	Vertexes_t gray;
	Stack_t stack;

	for (const auto& vertex_and_neighbours : adjacency_lists)
	{
		if (gray.find(vertex_and_neighbours.first) == gray.cend())
		{
			if (gray_and_black.find(vertex_and_neighbours.first) == gray_and_black.cend())
			{
				bool no_cycles = depth_first_search(adjacency_lists, vertex_and_neighbours.first, gray_and_black, gray, stack);
				if (!no_cycles)
					return false;

				stack.push(vertex_and_neighbours.first);
			}
			gray.erase(vertex_and_neighbours.first);
		}
		else
			return false;
	}

	int number = 0;
	while (!stack.empty())
	{
		numbersOut.insert(std::make_pair(stack.top(), number));
		stack.pop();
		++number;
	}

	return true;
}
