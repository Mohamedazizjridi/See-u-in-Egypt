//═══════════════════════════════════════════════════════════════════════════════
// HUNGARIAN ALGORITHM (Kuhn–Munkres)
//═══════════════════════════════════════════════════════════════════════════════
/**
 * Hungarian algorithm for min-cost perfect matching in a dense bipartite graph.
 * Time: O(n^3), Space: O(n^2)
 */
ll hungarian(const vector<vector<ll>>& cost) {
    int n = cost.size();
    vector<ll> u(n+1), v(n+1);
    vector<int> p(n+1), way(n+1);
    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        ll j0 = 0;
        vector<ll> minv(n+1, LLONG_MAX);
        vector<char> used(n+1);
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            ll delta = LLONG_MAX;
            for (int j = 1; j <= n; ++j) if (!used[j]) {
                ll cur = cost[i0-1][j-1] - u[i0] - v[j];
                if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                if (minv[j] < delta) { delta = minv[j]; j1 = j; }
            }
            for (int j = 0; j <= n; ++j) {
                if (used[j]) { u[p[j]] += delta; v[j] -= delta; }
                else minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return -v[0];
}
