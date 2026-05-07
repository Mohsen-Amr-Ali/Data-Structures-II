#include "PrimAlgorithm.h"
#include <queue>
#include <functional> // Fixed: Required for std::greater to work with the priority queue
#include <iostream>

mst_result PrimAlgorithm::execute(const Graph& graph, int start_node) {
    int v_count = graph.getV();
    const auto& adj = graph.getAdj();

    mst_result result;
    result.total_weight = 0;

    using pq_element = std::pair<int, std::pair<int, int>>;
    std::priority_queue<pq_element, std::vector<pq_element>, std::greater<pq_element>> pq;

    std::vector<bool> in_mst(v_count, false);
    in_mst[start_node] = true;

    for (const auto& neighbor : adj[start_node]) {
        pq.push({neighbor.second, {start_node, neighbor.first}});
    }

    while (!pq.empty() && result.edges.size() < v_count - 1) {
        auto top_element = pq.top();
        pq.pop();

        int weight = top_element.first;
        int u = top_element.second.first;
        int v = top_element.second.second;

        if (in_mst[v]) {
            continue;
        }

        in_mst[v] = true;
        result.total_weight += weight;
        result.edges.push_back({u, v, weight});

        for (const auto& neighbor : adj[v]) {
            int next_node = neighbor.first;
            int next_weight = neighbor.second;

            if (!in_mst[next_node]) {
                pq.push({next_weight, {v, next_node}});
            }
        }
    }

    return result;
}