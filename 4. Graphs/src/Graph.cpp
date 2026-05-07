#include "Graph.h"

// constructor, initializes the number of vertices and resizes the list
Graph::Graph(int numVertices) : V(numVertices) {
    adj.resize(V);
}

// adding an edge
// isDirected = true for topological sort (DAG)
// isDirected = false for prim's (undirected)
void Graph::addEdge(int u, int v, int weight, bool isDirected) {
    adj[u].push_back({v, weight});
    if (!isDirected) {
        adj[v].push_back({u, weight});
    }
}

// Getters allowing external algorithms to access the graph's data securely
int Graph::getV() const {
    return V;
}

const std::vector<std::vector<std::pair<int, int>>>& Graph::getAdj() const {
    return adj;
}//
// Created by mohse on 08/05/2026.
//