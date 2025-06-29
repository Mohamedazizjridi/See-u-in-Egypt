//═══════════════════════════════════════════════════════════════════════════════
// HOPCROFT–KARP BIPARTITE MATCHING
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Hopcroft–Karp algorithm for max matching in bipartite graph.
 * Time: O(E sqrt(V)), Space: O(V + E)
 */
pair<vector<int>, vector<int>> hopcroftKarp(const vector<vector<int>>& graph, int n, int m) {
    vector<int> dist(n), ptr(n), matchU(n, -1), matchV(m, -1);
    auto bfs = [&]() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);
        for (int u = 0; u < n; ++u) if (matchU[u] < 0) { dist[u] = 0; q.push(u); }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                int u2 = matchV[v];
                if (u2 >= 0 && dist[u2] < 0) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                } else if (u2 < 0) {
                    found = true;
                }
            }
        }
        return found;
    };
    function<bool(int)> dfs = [&](int u) {
        for (int &cid = ptr[u]; cid < (int)graph[u].size(); ++cid) {
            int v = graph[u][cid];
            int u2 = matchV[v];
            if (u2 < 0 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                matchU[u] = v;
                matchV[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    };
    while (bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        for (int u = 0; u < n; ++u) if (matchU[u] < 0) dfs(u);
    }
    return {matchU, matchV};
}
