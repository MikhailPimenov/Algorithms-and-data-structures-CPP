#pragma once

#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

template <typename T>
struct hash_on_sum : private std::hash<typename T::value_type> {
	using count_type = typename T::value_type;
	using base = std::hash<count_type>;

	std::size_t operator()(const T& obj) const{
		return base::operator()(
			std::accumulate(
				obj.cbegin(),
				obj.cend(),
				0,
				[](std::size_t sum, const count_type& next) {
					return sum + std::hash<count_type>{}(next);
				}
			)
			);
	}
};



using Vertex_t = char;
using Vertexes_t = std::unordered_set < Vertex_t >;
using Lists_t = std::unordered_map < Vertex_t, Vertexes_t >;
using Stack_t = std::stack < Vertex_t >;
using Numbers_t = std::unordered_map<Vertex_t, int>;
using Component_t = Vertexes_t;
using Components_t = std::unordered_set<Component_t, hash_on_sum<Component_t>>;



