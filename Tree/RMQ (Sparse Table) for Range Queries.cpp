//═══════════════════════════════════════════════════════════════════════════════
// RMQ (Sparse Table) for Range Queries
//═══════════════════════════════════════════════════════════════════════════════

template<typename T, class F = function<T(const T&,const T&)>>
struct RMQ {
    int n, LOG;
    vector<vector<T>> st;
    F func;
    RMQ() {}
    RMQ(const vector<T>& arr, F f = F()) : func(f) {
        n = arr.size();
        LOG = 32 - __builtin_clz(n);
        st.assign(LOG, vector<T>(n));
        st[0] = arr;
        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i + (1<<k) <= n; ++i) {
                st[k][i] = func(st[k-1][i], st[k-1][i + (1<<(k-1))]);
            }
        }
    }
    // query in [l, r]
    T query(int l, int r) {
        int k = 31 - __builtin_clz(r - l + 1);
        return func(st[k][l], st[k][r - (1<<k) + 1]);
    }
};



int main() {
    vector<int> a = {5, 2, 4, 7, 1, 3, 6};
    
    // Build RMQ with min
    RMQ<int> rmq(a, [](int x, int y) { return min(x, y); });

    cout << rmq.query(1, 4) << "\n"; // min in [1..4] = min(2, 4, 7, 1) = 1
    cout << rmq.query(3, 5) << "\n"; // min in [3..5] = min(7, 1, 3) = 1
}
