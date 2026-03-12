//--------------- Corrdinate Compression -------------------------------------
//--------------- Coordinate Compression -------------------------------------
struct CoordinateCompression {
    vector<long long> vals;                 // sorted unique original values
    unordered_map<long long,int> comp;      // original -> compressed

    void build(const vector<long long>& a, int start = 0) {
        vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        for (int i = 0; i < (int)vals.size(); i++) {
            comp[vals[i]] = i + start;
        }
    }

    int getCompressed(long long x) {
        return comp[x];
    }

    long long getOriginal(int c, int start = 0) {
        return vals[c - start];
    }
};
