#include "floyd_uolsher3.h"

namespace Floyd_uolsher3 {
	int get_unreachable_maximum(const Lists3_t& g) 
	{
		int maximum = 0;
		for (const auto& vn : g)
			for (const auto& vd : vn.second)
				maximum += vd.second;
		return maximum * 100;
	}
	int mimimum(int a, int b) {
		return a <= b ? a : b;
	}
}

void floyd_uolsher3(const Lists3_t& g, All_distances3_t& d)
{
	std::vector<Vertex3_t> v;
	v.reserve(g.size() + 1);
	v.push_back(Vertex3_t());
	for (const auto& vn : g)
		v.push_back(vn.first);


	std::array<All_distances3_t, 2> f;
	Distances3_t d_empty;
	int maximum = Floyd_uolsher3::get_unreachable_maximum(g);


	for (const auto& vn : g)
		d_empty.insert(std::pair<Vertex3_t, int>(vn.first, 0));

	for (auto& element : f)
		for (const auto& vn : g)
			element.insert(std::pair<Vertex3_t, Distances3_t>(vn.first, d_empty));

	for (const auto& vn1 : g)
		for (const auto& vn2 : g)
			if (vn1.second.find(vn2.first) != vn1.second.cend())
				f[0].at(vn1.first).at(vn2.first) = vn1.second.at(vn2.first);
			else f[0].at(vn1.first).at(vn2.first) = maximum;

	for (const auto& vn : g)
		f[0].at(vn.first).at(vn.first) = 0;


	for (int k = 1; k < g.size() + 1; ++k)
		for (int i = 1; i < g.size() + 1; ++i)
			for (int j = 1; j < g.size() + 1; ++j)
				f[k % 2][v[i]][v[j]] = Floyd_uolsher3::mimimum(f[(k - 1) % 2][v[i]][v[j]],
					f[(k - 1) % 2][v[i]][v[k]] + f[(k - 1) % 2][v[k]][v[j]]);

	d = f[(g.size()) % 2];
}
