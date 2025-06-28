// ---------------------------- lazy propogation ---------------------------------------
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

// —— GENERIC TEMPLATE —— (fully generic, no edits below)
template< typename _Node, typename _Tag, class MergeFn, class ApplyFn >
class LazySegmentTree {
    int n, size, height;
    vector<_Node> tree;
    vector<_Tag>  lazy;
    MergeFn  merge;
    ApplyFn  apply;
  public:
    LazySegmentTree(const vector<_Node>& data)
      : merge(MergeFn()), apply(ApplyFn()) {
        n = data.size();
        size = 1; while (size < n) size <<= 1;
        height = __lg(size);
        tree.assign(2*size, _Node());
        lazy.assign(2*size, _Tag());
        for (int i = 0; i < n; ++i)
            tree[size + i] = data[i];
        for (int i = size - 1; i > 0; --i)
            tree[i] = merge(tree[i<<1], tree[i<<1|1]);
    }
    static _Tag combine_tags(const _Tag& a, const _Tag& b) {
        return (a + b) % MOD;
    }
    void push(int i) {
        if (lazy[i] == _Tag()) return;
        for (int c : {i<<1, i<<1|1}) {
            apply(tree[c], lazy[i]);
            lazy[c] = combine_tags(lazy[c], lazy[i]);
        }
        lazy[i] = _Tag();
    }
    void push_path(int i) {
        for (int h = height; h > 0; --h)
            push(i >> h);
    }
    void pull_path(int i) {
        while (i > 1) {
            i >>= 1;
            tree[i] = merge(tree[i<<1], tree[i<<1|1]);
            apply(tree[i], lazy[i]);
        }
    }
    void range_apply(int l, int r, const _Tag& tag) {
        l += size; r += size;
        int l0 = l, r0 = r;
        push_path(l0);
        push_path(r0-1);
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                apply(tree[l], tag);
                lazy[l] = combine_tags(lazy[l], tag);
                ++l;
            }
            if (r & 1) {
                --r;
                apply(tree[r], tag);
                lazy[r] = combine_tags(lazy[r], tag);
            }
        }
        pull_path(l0);
        pull_path(r0-1);
    }
    _Node range_query(int l, int r) {
        l += size; r += size;
        push_path(l);
        push_path(r-1);
        _Node resL = _Node(), resR = _Node();
        bool usedL = false, usedR = false;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                resL = usedL ? merge(resL, tree[l]) : tree[l];
                usedL = true; ++l;
            }
            if (r & 1) {
                --r;
                resR = usedR ? merge(tree[r], resR) : tree[r];
                usedR = true;
            }
        }
        if (!usedL) return usedR ? resR : _Node();
        if (!usedR) return resL;
        return merge(resL, resR);
    }
};

// —— PROBLEM SPECIALIZATION ——
// Node: {sum(a), sum(a^2), sum(a^3), count}
using Node =     //array<ll,4>;
// Tag: add x to each element
using Tag  = ll;
// Merge: coefficient-wise addition
struct MergeFn {
    Node operator()(const Node& A, const Node& B) const {
        return {
            // (A[0] + B[0]) % MOD,
            // (A[1] + B[1]) % MOD,
            // (A[2] + B[2]) % MOD,
            // (A[3] + B[3]) % MOD
        };
    }
};
// Apply: polynomial shift by x
struct ApplyFn {
    void operator()(Node& A, const Tag& x) const {
        // ll a0 = (A[0] + A[3] * x) % MOD;
        // ll a1 = (A[1] + 2 * x % MOD * A[0] + A[3] * (x*x % MOD)) % MOD;
        // ll a2 = (A[2]
        //          + 3 * x % MOD * A[1]
        //          + 3 * (x*x % MOD) * A[0]
        //          + A[3] * ((x*x % MOD) * x % MOD)
        //         ) % MOD;
        // A = { a0, a1, a2, A[3] };
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;
    vector<ll> a(N);
    for (int i = 0; i < N; ++i) cin >> a[i];

    vector<Node> init(N);
    for (int i = 0; i < N; ++i) {
        ll v = a[i] % MOD;
        init[i] = { v, v*v % MOD, v*v%MOD*v % MOD, 1 };
    }
    LazySegmentTree<Node,Tag,MergeFn,ApplyFn> seg(init);

    int Q; cin >> Q;
    while (Q--) {
        int type, L, R;
        cin >> type >> L >> R;
        if (type == 1) {
            ll X; cin >> X;
            seg.range_apply(L-1, R, X % MOD);
        } else {
            auto ans = seg.range_query(L-1, R);
            // we need sum of a^3
            cout << ans[2] << '\n';
        }
    }
    return 0;
}
