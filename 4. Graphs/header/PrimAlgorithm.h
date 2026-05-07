#ifndef PRIM_ALGORITHM_H
#define PRIM_ALGORITHM_H

#include "Graph.h"
#include <vector>

struct mst_edge {
    int u;
    int v;
    int weight;
};

struct mst_result {
    std::vector<mst_edge> edges;
    int total_weight;
};

class PrimAlgorithm {
public:
    static mst_result execute(const Graph& graph, int start_node);
};

#endif // PRIM_ALGORITHM_H