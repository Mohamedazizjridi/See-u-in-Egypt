//═══════════════════════════════════════════════════════════════════════════════
// MAX FLOW (Dinic)
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Dinic's algorithm for maximum flow.
 * Time: O(E sqrt(V)) for unit networks, O(V^2 E) general, Space: O(V + E)
 */
struct Edge { int v, rev; ll cap; };
ll dinicMaxFlow(int s, int t, vector<vector<Edge>>& g) {
    int n = g.size();
    vector<int> level(n), ptr(n);
    auto bfs = [&]() {
        fill(level.begin(), level.end(), -1);
        queue<int> q; q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) if (level[e.v] < 0 && e.cap > 0) {
                level[e.v] = level[u] + 1;
                q.push(e.v);
            }
        }
        return level[t] >= 0;
    };
    function<ll(int,ll)> dfs = [&](int u, ll pushed) {
        if (!pushed || u == t) return pushed;
        for (int& cid = ptr[u]; cid < (int)g[u].size(); ++cid) {
            auto &e = g[u][cid];
            if (level[e.v] != level[u] + 1 || e.cap == 0) continue;
            if (ll tr = dfs(e.v, min(pushed, e.cap))) {
                e.cap -= tr;
                g[e.v][e.rev].cap += tr;
                return tr;
            }
        }
        return 0LL;
    };
    ll flow = 0;
    while (bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        while (ll pushed = dfs(s, LLONG_MAX)) flow += pushed;
    }
    return flow;
}
