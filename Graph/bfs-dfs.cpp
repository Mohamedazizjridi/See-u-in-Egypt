//═══════════════════════════════════════════════════════════════════════════════
// BASIC GRAPH TRAVERSAL
//═══════════════════════════════════════════════════════════════════════════════

/**
 * Depth-first search traversal.
 * Time: O(V + E)  - visits each vertex and edge once
 * Space: O(V)    - recursion/stack and visited array
 */
void dfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n);
    stack<int> st;
    visited[start] = true;
    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

/**
 * Breadth-first search traversal.
 * Time: O(V + E)  - enqueues each neighbor once
 * Space: O(V)    - queue and visited array
 */
void bfs(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<bool> visited(n);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}