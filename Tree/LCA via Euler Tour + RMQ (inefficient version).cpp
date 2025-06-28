//═══════════════════════════════════════════════════════════════════════════════
// LCA via Euler Tour + RMQ (inefficient version)
//═══════════════════════════════════════════════════════════════════════════════

struct LCA_RMQ {
    vector<int> euler, height, first;
    RMQ<pair<int,int>> rmq; // stores {height, node}
    void dfs(int u, int p, const vector<vector<int>>& tree, int h) {
        first[u] = euler.size();
        euler.emplace_back(h, u);
        for (int v : tree[u]) {
            if (v == p) continue;
            dfs(v, u, tree, h+1);
            euler.emplace_back(h, u);
        }
    }
    LCA_RMQ(const vector<vector<int>>& tree, int root=0) {
        int n = tree.size();
        first.assign(n, -1);
        dfs(root, -1, tree, 0);
        rmq = RMQ<pair<int,int>>(euler, [](auto &a, auto &b){ return a.first < b.first ? a : b; });
    }
    int query(int u, int v) {
        int l = first[u], r = first[v];
        if (l > r) swap(l,r);
        return rmq.query(l, r).second;
    }
};
