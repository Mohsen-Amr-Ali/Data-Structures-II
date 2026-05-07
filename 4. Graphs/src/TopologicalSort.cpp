#include "TopologicalSort.h"
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void TopologicalSort::execute(const Graph& graph) {
    int V = graph.getV();
    const auto& adj = graph.getAdj();
    
    vector<int> in_degree(V, 0);

    // calculating in-degree of all vertices
    for (int u = 0; u < V; u++) {
        for (auto const& [v, weight] : adj[u]) {
            in_degree[v]++;
        }
    }
    // counter for each node, loop through every edge in the graph
    // if there's an edge pointing to v, increment the node's counter

    // creating a queue and enqueue all vertices with in-degree 0, our "starting tasks"
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0)
            q.push(i);
    }

    vector<int> top_order;

    while (!q.empty()) {
        int u = q.front();
        q.pop(); // take node u out of queue...
        top_order.push_back(u); // ...and add it to final top_order list

        // for every neighbour v that u pointed to, decrement its in-degree
        for (auto const& [v, weight] : adj[u]) {
            if (--in_degree[v] == 0)
                q.push(v);
        }
        // once a neighbour's in-degree reaches 0, it's ready to be added to the queue
    }

    // cycle check
    // if we finish our loop but top_order list doesn't have all the vertices...
    // ...due to a cycle. the nodes keep waiting on each other
    // and their in-degrees never reach zero
    if (top_order.size() != V) {
        cout << "Cycle detected in the graph! Topological Sort not possible." << endl;
        return;
    }

    cout << "Topological Order: ";
    for (int node : top_order) cout << node << " ";
    cout << endl;
}

// notes: "auto const&" used for efficiency and safety, 'const' to tell compiler you don't intend to change data (just reading it)...
// ...prevents accidentally altering it, '&' used so instead of making a copy of the data, you're looking directly at the original data in memory...
// ...just pointing to existing edge, 'auto' tells c++ to figure out the data type