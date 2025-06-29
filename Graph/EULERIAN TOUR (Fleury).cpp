//═══════════════════════════════════════════════════════════════════════════════
// EULERIAN TOUR (Fleury)
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Finds an Eulerian path/circuit in an undirected graph using Fleury's algorithm.
 * Time: O(E^2) naive, Space: O(E)
 */
vector<int> fleury(vector<vector<int>> graph, int root = 0) {
    int n = graph.size();
    vector<int> ptr(n), st, path;
    st.push_back(root);
    while (!st.empty()) {
        int u = st.back();
        if (ptr[u] < graph[u].size()) {
            int v = graph[u][ptr[u]++];
            // remove edge u-v
            auto& adj = graph[v];
            adj.erase(find(adj.begin(), adj.end(), u));
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
    return path;
}
