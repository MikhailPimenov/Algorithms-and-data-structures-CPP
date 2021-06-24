#include "kosaraju3.h"

void reverse_graph3(const Lists_t& g, Lists_t& rg) {
    for (const auto& vn : g)
        rg.insert(std::pair<Vertex_t, Vertexes_t>(vn.first, Vertexes_t()));

    for (const auto& vn : g)
        for (Vertex_t neighbor : vn.second)
            rg.at(neighbor).insert(vn.first);
}

void depth_first_search_forward3(const Lists_t& g, Vertex_t start, Vertexes_t& used, Stack_t& stack) {
    used.insert(start);

    for (Vertex_t neighbor : g.at(start))
        if (used.find(neighbor) == used.cend())
            depth_first_search_forward3(g, neighbor, used, stack);

    stack.push(start);
}

void depth_first_search_backward3(const Lists_t& g, Vertex_t start, Vertexes_t& used, Vertexes_t& component) {
    used.insert(start);
    component.insert(start);

    for (Vertex_t neighbor : g.at(start))
        if (used.find(neighbor) == used.cend())
            depth_first_search_backward3(g, neighbor, used, component);
}

int kosaraju3(const Lists_t& g, Components_t& c) {
    Vertexes_t used;
    Stack_t stack;

    for (const auto& vn : g)
        if (used.find(vn.first) == used.cend())
            depth_first_search_forward3(g, vn.first, used, stack);

    used.clear();
    Lists_t rg;
    reverse_graph3(g, rg);
    
    while (!stack.empty()) {
        Vertex_t vertex = stack.top();
        stack.pop();

        if (used.find(vertex) == used.cend()) {
            Vertexes_t component;
            depth_first_search_backward3(rg, vertex, used, component);
            c.push_back(component);
        }
    }

    return c.size();
}

int kosaraju_adapted3(const Lists_t& g) {
    Components_t c;

    int result = kosaraju3(g, c);

    return result;
}
