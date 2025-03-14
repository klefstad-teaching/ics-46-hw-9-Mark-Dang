#include "dijkstras.h"


struct Node{ 
    int vertex;
    int weight;
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    //adjacency list: vector containing vector of edges

    //the return is the distance to each node from the given:
    //NOTE: WE CAN EDIT THE PARENT VECTOR
    vector<int> result;
    vector<bool> visited(G.numVertices-1, false);
    vector<int> distances(G.numVertices-1, INF);

    auto compare = [](const Node& a, const Node& b) {return a.weight > b.weight;};
    priority_queue<Node, std::vector<Node>, decltype(compare)> pq(compare);

    pq.push(Node(source, 0));
    distances[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        
        int vertex = current.vertex;
        result.push_back(vertex);

        if (visited[vertex] == true) continue;

        visited[vertex] = true;
        for (auto n: G[vertex]) {
            int nvertex = n.dst;
            int nweight = n.weight;

            if (!visited[nvertex] && distances[vertex] + nweight < distances[nvertex]){
                distances[nvertex] = distances[vertex] + nweight;
                pq.push(Node(nvertex, distances[nvertex]));
            }
        }
    }

    return result;
}



//vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination);

//void print_path(const vector<int>& v, int total);