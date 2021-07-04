#include "path4.h"

void path4(const Lists_t& G, Path_t& path_out, Vertex_t start, Vertex_t finish)
{
    Queue_t queue;
    queue.push(start);
    Distances_t distances;
    distances.insert(std::pair<Vertex_t, int>(start, 0));

    bool found = false;
    while (!queue.empty() && !found) {
        Vertex_t vertex = queue.front();
        queue.pop();

        for (Vertex_t neighbor : G.at(vertex)) {
            if (distances.find(neighbor) == distances.cend()) {
                distances.insert(std::pair<Vertex_t, int>(neighbor, distances.at(vertex) + 1));
                if (neighbor == finish) {
                    found = true;
                    break;
                }
                queue.push(neighbor);
            }
        }
    }
    if (!found) {
       path_out.clear();
       return;
    }
    
    Vertex_t vertex = finish;

    path_out.resize(distances.at(finish) + 1);
    std::size_t k = distances.at(finish);
    path_out[k] = finish;
    --k;

    while (vertex != start) {
        for (Vertex_t neighbor : G.at(vertex)) {
            if (distances.find(neighbor) != distances.cend() &&
                distances.at(neighbor) == distances.at(vertex) - 1) {
                path_out[k] = neighbor;
                --k;
                vertex = neighbor;
                break;
            }
        }
    }
}

