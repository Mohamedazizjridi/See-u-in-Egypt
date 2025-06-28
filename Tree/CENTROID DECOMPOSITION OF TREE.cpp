//═══════════════════════════════════════════════════════════════════════════════
// CENTROID DECOMPOSITION OF TREE
//═══════════════════════════════════════════════════════════════════════════════

vector<int> subtreeSize;
vector<bool> centroidMarked;

int dfsSize(int u, int p, const vector<vector<int>>& tree) {
    subtreeSize[u] = 1;
    for (int v : tree[u]) if (v != p && !centroidMarked[v])
        subtreeSize[u] += dfsSize(v, u, tree);
    return subtreeSize[u];
}

int getCentroid(int u, int p, int n, const vector<vector<int>>& tree) {
    for (int v : tree[u]) if (v != p && !centroidMarked[v]) {
        if (subtreeSize[v] > n/2)
            return getCentroid(v, u, n, tree);
    }
    return u;
}

void decompose(int u, int p, const vector<vector<int>>& tree, vector<int>& centParent) {
    int n = dfsSize(u, -1, tree);
    int centroid = getCentroid(u, -1, n, tree);
    centroidMarked[centroid] = true;
    centParent[centroid] = p;
    for (int v : tree[centroid]) if (!centroidMarked[v])
        decompose(v, centroid, tree, centParent);
}

vector<int> centroidDecomposition(const vector<vector<int>>& tree) {
    int n = tree.size();
    subtreeSize.assign(n, 0);
    centroidMarked.assign(n, false);
    vector<int> centParent(n, -1);
    decompose(0, -1, tree, centParent);
    return centParent;
}