//═══════════════════════════════════════════════════════════════════════════════
// EULER TOUR FOR SUBTREE QUERIES
//═══════════════════════════════════════════════════════════════════════════════

// Returns vector of pairs {tin, tout} for each node
vector<pair<int,int>> eulerTour(const vector<vector<int>>& tree, int root = 0) {
    int n = tree.size();
    vector<int> ptr(n, 0);
    vector<int> st;
    vector<int> path;
    st.push_back(root);
    while (!st.empty()) {
        int u = st.back();
        if (ptr[u] < (int)tree[u].size()) {
            int v = tree[u][ptr[u]++];
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
    vector<pair<int,int>> times(n, {-1,-1});
    for (int i = 0; i < (int)path.size(); ++i) {
        int u = path[i];
        if (times[u].first == -1) times[u].first = i;
        times[u].second = i;
    }
    return times;
}