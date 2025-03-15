#include "dijkstras.h"


struct Node{ 
    int vertex;
    int weight;
};

//return longest distance to a vertex starting from G
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    //adjacency list: vector containing vector of edges

    vector<bool> visited(G.numVertices, false);
    vector<int> distances(G.numVertices, INF);
    for (size_t i = 0; i < previous.size(); ++i) previous[i] = -1;

    auto compare = [](const Node& a, const Node& b) {return a.weight > b.weight;};
    priority_queue<Node, std::vector<Node>, decltype(compare)> pq(compare);

    pq.push(Node(source, 0));
    distances[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int curvertex = current.vertex;

        if (visited[curvertex] == true) continue;

        visited[curvertex] = true;
        for (auto n: G[curvertex]) {
            int nvertex = n.dst;
            int nweight = n.weight;

            if (!visited[nvertex] && distances[curvertex] + nweight < distances[nvertex]){
                previous[nvertex] = curvertex;
                distances[nvertex] = distances[curvertex] + nweight;
                pq.push(Node(nvertex, distances[nvertex]));
            }
        }
    }

    return distances;
}



vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    stack<int> vertices;
    vertices.push(destination);
    vector<int> path;

    int curvertex = destination;
    while (previous[curvertex] != -1) {
        vertices.push(previous[curvertex]);
        curvertex = previous[curvertex];
    }

    while (!vertices.empty()) {
        path.push_back(vertices.top());
        vertices.pop();
    }

    return path;
}

void print_path(const vector<int>& v, int total) {
    for (auto vertex: v) std::cout << vertex << ' ';
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}