#include "tarjan4.h"

namespace Tarjan4 {
    void depth_first_search(Vertex_t start, const Lists_t& G, Vertexes_t& used, Stack_t& stack, Vertexes_t& loop_detector) {
        used.insert(start);
        loop_detector.insert(start);

        for (Vertex_t neighbor : G.at(start)) {
            if (loop_detector.find(neighbor) != loop_detector.cend()) {
                throw - 1;
            }
            if (used.find(neighbor) == used.cend()) {
                depth_first_search(neighbor, G, used, stack, loop_detector);
            }

        }

        stack.push(start);
        loop_detector.erase(start);
    }
}

bool tarjan4(const Lists_t& G, Numbers_t& numbers_out) {
    Vertexes_t used;
    Vertexes_t loop_detector;
    Stack_t stack;

    try {
        for (const auto& vn : G) {
            if (used.find(vn.first) == used.cend()) {
                Tarjan4::depth_first_search(vn.first, G, used, stack, loop_detector);
            }
        }
    }
    catch (int) {
        numbers_out.clear();
        return false;
    }

    int number = 0;

    while (!stack.empty()) {
        Vertex_t vertex = stack.top();
        stack.pop();
        numbers_out.insert(std::pair<Vertex_t, int>(vertex, number));
        ++number;
    }

    return true;
}
