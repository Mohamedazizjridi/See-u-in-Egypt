//═══════════════════════════════════════════════════════════════════════════════
// BRIDGES AND ARTICULATION POINTS
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Finds all bridges in an undirected graph.
 * Time: O(V + E), Space: O(V)
 */
vector<pair<int,int>> findBridges(const vector<vector<int>>& graph) {
    int n = graph.size(), timer = 0;
    vector<int> disc(n, -1), low(n), parent(n, -1);
    vector<pair<int,int>> bridges;
    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        for (int v : graph[u]) {
            if (disc[v] == -1) {
                parent[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u])
                    bridges.emplace_back(min(u,v), max(u,v));
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    for (int i = 0; i < n; ++i) if (disc[i] == -1) dfs(i);
    return bridges;
}

/**
 * Finds all articulation points in an undirected graph.
 * Time: O(V + E), Space: O(V)
 */
vector<int> findArticulation(const vector<vector<int>>& graph) {
    int n = graph.size(), timer = 0;
    vector<int> disc(n, -1), low(n), parent(n, -1);
    vector<bool> art(n);
    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        int children = 0;
        for (int v : graph[u]) {
            if (disc[v] == -1) {
                parent[v] = u;
                ++children;
                dfs(v);
                low[u] = min(low[u], low[v]);
                if ((parent[u] == -1 && children > 1) ||
                    (parent[u] != -1 && low[v] >= disc[u]))
                    art[u] = true;
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    for (int i = 0; i < n; ++i) if (disc[i] == -1) dfs(i);
    vector<int> res;
    for (int i = 0; i < n; ++i) if (art[i]) res.push_back(i);
    return res;
}