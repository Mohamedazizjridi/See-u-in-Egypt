//═══════════════════════════════════════════════════════════════════════════════
// CYCLE DETECTION
//═══════════════════════════════════════════════════════════════════════════════

/**
 * Detects a cycle in an undirected graph using iterative DFS.
 * Time: O(V + E)  - explores all vertices and edges
 * Space: O(V)    - visited, parent arrays, and stack
 */
bool undCycle(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> vis(n);
    vector<int> parent(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            stack<int> st;
            vis[i] = true;
            st.push(i);
            while (!st.empty()) {
                int u = st.top(); st.pop();
                for (int v : graph[u]) {
                    if (!vis[v]) {
                        vis[v] = true;
                        parent[v] = u;
                        st.push(v);
                    } else if (parent[u] != v) {
                        return true;  // found cross-edge
                    }
                }
            }
        }
    }
    return false;
}

/**
 * Detects a cycle in a directed graph using recursion stack tracking.
 * Time: O(V + E)  - visits each node/edge once
 * Space: O(V)    - recursion stack and visit arrays
 */
bool dirCycleUtil(int u, const vector<vector<int>>& graph, vector<int>& vis) {
    vis[u] = 1; // 1 = visiting
    for (int v : graph[u]) {
        if (vis[v] == 0) {
            if (dirCycleUtil(v, graph, vis)) return true;
        } else if (vis[v] == 1) {
            return true; // back-edge
        }
    }
    vis[u] = 2; // finished
    return false;
}

bool dirCycle(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> vis(n, 0);
    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0 && dirCycleUtil(i, graph, vis))
            return true;
    }
    return false;
}