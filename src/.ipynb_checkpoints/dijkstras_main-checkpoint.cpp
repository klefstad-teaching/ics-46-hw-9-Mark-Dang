#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("src/small.txt", G);
    vector<int> parent(G.numVertices, -1);
    std::cout << "dijkstra starting" << std::endl;
    vector<int> v = dijkstra_shortest_path(G, 0, parent);
    for (auto e: v) std::cout << e << ' ';
    std::cout << std::endl;

    for (int i = 0; i < G.numVertices; ++i) {
        vector<int> path = extract_shortest_path(v, parent, i);
        print_path(path, v[i]);
    }
    return 0;
}