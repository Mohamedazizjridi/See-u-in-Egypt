/═══════════════════════════════════════════════════════════════════════════════
// STRONGLY CONNECTED COMPONENTS (Kosaraju)
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Kosaraju's algorithm to find SCCs in a directed graph.
 * Time: O(V + E), Space: O(V + E)
 */
vector<vector<int>> sccKosaraju(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> vis(n);
    vector<int> order;
    function<void(int)> dfs1 = [&](int u) {
        vis[u] = true;
        for (int v : graph[u]) if (!vis[v]) dfs1(v);
        order.push_back(u);
    };
    for (int i = 0; i < n; ++i) if (!vis[i]) dfs1(i);
    vector<vector<int>> rev(n);
    for (int u = 0; u < n; ++u)
        for (int v : graph[u]) rev[v].push_back(u);
    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> comps;
    function<void(int, vector<int>&)> dfs2 = [&](int u, vector<int>& comp) {
        vis[u] = true;
        comp.push_back(u);
        for (int v : rev[u]) if (!vis[v]) dfs2(v, comp);
    };
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        if (!vis[u]) {
            comps.emplace_back();
            dfs2(u, comps.back());
        }
    }
    return comps;
}
