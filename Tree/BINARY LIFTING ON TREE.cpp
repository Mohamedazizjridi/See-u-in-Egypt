//═══════════════════════════════════════════════════════════════════════════════
// BINARY LIFTING ON TREE
//═══════════════════════════════════════════════════════════════════════════════

struct BinaryLifting {
    int N, LOG;
    vector<int> depth;
    vector<vector<int>> up;
    BinaryLifting(const vector<vector<int>>& tree, int root=0) {
        N = tree.size();
        LOG = 32 - __builtin_clz(N);
        depth.assign(N, -1);
        up.assign(LOG, vector<int>(N, -1));
        // BFS to set parent[0] and depth
        queue<int> q;
        q.push(root);
        depth[root] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : tree[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    up[0][v] = u;
                    q.push(v);
                }
            }
        }
        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i < N; ++i) {
                int p = up[k-1][i];
                up[k][i] = (p < 0 ? -1 : up[k-1][p]);
            }
        }
    }
    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u,v);
        int diff = depth[u] - depth[v];
        for (int k = 0; k < LOG; ++k)
            if (diff & (1<<k)) u = up[k][u];
        if (u == v) return u;
        for (int k = LOG-1; k >= 0; --k)
            if (up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        return up[0][u];
    }
    int distance(int u, int v) {
        int w = lca(u,v);
        return depth[u] + depth[v] - 2*depth[w];
    }
    int kthAncestor(int u, int k) {
        for (int i = 0; i < LOG; ++i)
            if (k & (1<<i)) {
                u = up[i][u];
                if (u < 0) return -1;
            }
        return u;
    }
};