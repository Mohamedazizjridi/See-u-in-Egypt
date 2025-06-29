//═══════════════════════════════════════════════════════════════════════════════
// MINIMUM SPANNING TREE
//═══════════════════════════════════════════════════════════════════════════════

/**
 * Disjoint Set Union (Union-Find) with path compression and union by size.
 * Operations: find/union in nearly-O(1) amortized.
 */
struct DSU {
    vector<int> parent, sz;
    DSU(int n): parent(n), sz(n,1) { iota(parent.begin(), parent.end(), 0); }
    int find(int x){ return parent[x]==x ? x : parent[x]=find(parent[x]); }
    bool join(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a; sz[a]+=sz[b]; return true;
    }
};

/**
 * Kruskal's algorithm for MST using sorted edge list.
 * Time: O(E log E), Space: O(V)
 */
ll kruskal(vector<tuple<int,int,ll>>& edges, int n) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){ return get<2>(a) < get<2>(b); });
    DSU dsu(n);
    ll total = 0; int cnt = 0;
    for (auto &e: edges) {
        int u,v; ll w; tie(u,v,w)= e;
        if (dsu.join(u,v)) { total += w; cnt++; }
    }
    return cnt == n-1 ? total : -1;
}

/**
 * Prim's algorithm for MST using a priority queue.
 * Time: O(E log V), Space: O(V)
 */
ll prim(const vector<vector<pair<int,ll>>>& graph) {
    int n = graph.size();
    vector<bool> vis(n);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.emplace(0, 0);
    ll ans = 0;
    while (!pq.empty()) {
        auto [w,u] = pq.top(); pq.pop();
        if (vis[u]) continue;
        vis[u] = true;
        ans += w;
        for (auto& [v, wt] : graph[u]) {
            if (!vis[v]) pq.emplace(wt, v);
        }
    }
    return ans;
}