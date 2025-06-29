//═══════════════════════════════════════════════════════════════════════════════
// TOPOLOGICAL SORT
//═══════════════════════════════════════════════════════════════════════════════

/**
 * Topological sort of a DAG using Kahn's algorithm.
 * Time: O(V + E)  - processes each edge/vertex
 * Space: O(V)    - indegree array and stack
 */
vector<int> topologicalOrder(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : graph[u])
            indeg[v]++;
    stack<int> st;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) st.push(i);
    vector<int> order;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        order.push_back(u);
        for (int v : graph[u]) {
            if (--indeg[v] == 0)
                st.push(v);
        }
    }
    return order;
}
