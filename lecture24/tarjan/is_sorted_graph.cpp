#include "is_sorted_graph.h"

bool is_sorted_graph()
{
	return false;
}

bool is_ascending(const Lists_t& adjacency_lists,
	const Numbers_t& numbers)
{
	for (const auto& vertex_and_neighbours : adjacency_lists)
		for (const auto neighbor : vertex_and_neighbours.second)
			if (numbers.at(neighbor) <= numbers.at(vertex_and_neighbours.first))
				return false;

	return true;
}

std::size_t calculate_range(const Numbers_t& numbers)
{
	int minimum = numbers.cbegin()->second;
	int maximum = numbers.cbegin()->second;

	for (const auto& vertex_and_number : numbers)
	{
		if (vertex_and_number.second < minimum)
			minimum = vertex_and_number.second;
		if (vertex_and_number.second > maximum)
			maximum = vertex_and_number.second;
	}

	return static_cast <std::size_t> (maximum - minimum + 1);
}

bool is_continuous(const Numbers_t& numbers, std::size_t length)
{
	std::vector < bool > vector;
	vector.resize(length + 1);

	for (auto element : vector)
		element = false;

	for (const auto& vertex_and_number : numbers)
	{
		if (static_cast <std::size_t> (vertex_and_number.second) < vector.size())
			vector.at(static_cast <std::size_t> (vertex_and_number.second)) = true;
		else
			return false;
	}

	bool numbers_are_continuos = true;
	bool one_false_allowed = true;
	for (auto element : vector)
	{
		if (one_false_allowed && !element)
		{
			one_false_allowed = false;
			continue;
		}
		numbers_are_continuos = numbers_are_continuos && element;
	}

	return numbers_are_continuos;
}
bool is_sorted_graph(const Lists_t& adjacency_lists,
	const Numbers_t& numbers)
{
	if (adjacency_lists.empty() || numbers.empty())
		return false;

	std::size_t range = calculate_range(numbers);
	if (range != numbers.size())
		return false;

	if (!is_continuous(numbers, range))
		return false;

	return is_ascending(adjacency_lists, numbers);
}