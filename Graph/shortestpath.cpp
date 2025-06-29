//═══════════════════════════════════════════════════════════════════════════════
// SHORTEST PATHS
//═══════════════════════════════════════════════════════════════════════════════

/**
 * Dijkstra's algorithm for non-negative weighted graph.
 * Time: O((V + E) log V), Space: O(V)
 */
vector<ll> dijkstra(const vector<vector<pair<int,ll>>>& graph, int start) {
    int n = graph.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, start);
    dist[start] = 0;
    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto& [v,w] : graph[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

/**
 * Bellman–Ford algorithm supporting negative weights.
 * Time: O(V * E), Space: O(V)
 */
vector<ll> bellmanFord(const vector<tuple<int,int,ll>>& edges, int n, int start) {
    const ll INF = LLONG_MAX/4;
    vector<ll> dist(n, INF);
    dist[start] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (auto& [u,v,w] : edges) {
            dist[v] = min(dist[v], dist[u] + w);
        }
    }
    return dist;
}

/**
 * Floyd–Warshall algorithm for all-pairs shortest paths.
 * Time: O(V^3), Space: O(V^2)
 */
vector<vector<ll>> floydWarshall(vector<vector<ll>> dp) {
    int n = dp.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
    return dp;
}
