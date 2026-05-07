#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>

// graph structure
class Graph {

private:
    int V; // number of vertices

    // adjacency list: each index is a vertex, holding a list of its neighbours
    // we use a pair to store (neighbour, weight)
    // Note: Modified from list to vector to unify with Prim's algorithm requirements
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    // constructor, initializes the number of vertices and resizes the list
    Graph(int numVertices);

    // adding an edge
    // isDirected = true for topological sort (DAG)
    // isDirected = false for prim's (undirected)
    void addEdge(int u, int v, int weight = 0, bool isDirected = true);

    // Getters allowing external algorithms to access the graph's data securely
    int getV() const;
    const std::vector<std::vector<std::pair<int, int>>>& getAdj() const;
};

#endif // GRAPH_H