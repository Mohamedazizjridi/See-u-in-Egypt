//═══════════════════════════════════════════════════════════════════════════════
// BASIC DP ON TREES
//═══════════════════════════════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

// Computes DFS order, parent array, and depth array for a tree
// Time: O(V+E)
void getOrder(const vector<vector<int>>& tree, int root,
              vector<int>& order, vector<int>& parent, vector<int>& depth) {
    int n = tree.size();
    vector<bool> vis(n, false);
    stack<int> st;
    st.push(root);
    vis[root] = true;
    parent.assign(n, -1);
    depth.assign(n, 0);
    order.clear();
    order.push_back(root);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v : tree[u]) {
            if (!vis[v]) {
                vis[v] = true;
                st.push(v);
                order.push_back(v);
                parent[v] = u;
                depth[v] = depth[u] + 1;
            }
        }
    }
}

// Computes subtree sizes
// Time: O(V+E)
vector<int> getSize(const vector<vector<int>>& tree, int root = 0) {
    int n = tree.size();
    vector<int> order, parent, depth;
    getOrder(tree, root, order, parent, depth);
    vector<int> sz(n, 1);
    for (int i = n - 1; i > 0; --i) {
        int u = order[i];
        if (parent[u] != -1)
            sz[parent[u]] += sz[u];
    }
    return sz;
}
