#include "filter_arcs.h"

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