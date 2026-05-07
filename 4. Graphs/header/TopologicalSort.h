#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "Graph.h"

class TopologicalSort {
public:
    // topological sort using kahn's algorithm
    static void execute(const Graph& graph);
};

#endif // TOPOLOGICAL_SORT_H