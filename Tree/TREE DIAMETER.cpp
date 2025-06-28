//═══════════════════════════════════════════════════════════════════════════════
// TREE DIAMETER
//═══════════════════════════════════════════════════════════════════════════════

// Helper BFS/DFS to find farthest node
int farthest(const vector<vector<int>>& tree, int src) {
    int n = tree.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    int far = src;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : tree[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[far]) far = v;
            }
        }
    }
    return far;
}

// Returns pair of endpoints (u,v)
pair<int,int> diameter(const vector<vector<int>>& tree) {
    int u = farthest(tree, 0);
    int v = farthest(tree, u);
    return {u, v};
}