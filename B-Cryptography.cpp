#include<bits/stdc++.h>
using namespace std;
#define int long long 

const int MAXV = 40;

struct item {
    long long inv;
    array<int, MAXV + 1> cnt;
};

struct segtree {
    int size;
    vector<item> values;
    item NEUTRAL_ELEMENT = {1, 0, 0, 1};  
    segtree() {
        NEUTRAL_ELEMENT.inv = 0;
        NEUTRAL_ELEMENT.cnt.fill(0);
    }
    item merge(item    &l, item &r) {
       item res;
       res.iv=(l.inv+r.inv);
       int cross=0;
       int  prefr=0;
       for(int v=1;v<=40;v++)
       {
        cross+=l.cnt[v]*prefr;
        prefr+=r.cnt[v];
       }
       res.inv+=cross;
       for(int v=1;v<=40;v++)
       {
        res.cnt[v]=l.cnt[v]+r.cnt[v];
       }
       return res;
    }

    item single(int val) {
        item res;
        res.inv = 0;
        res.cnt.fill(0);
        if (1 <= val && val <= MAXV) res.cnt[val] = 1;
        return res;
    }

    void init(int n) {
        size = 1;
        while (size < n) size *= 2;
        values.assign(2 * size, NEUTRAL_ELEMENT);
    }

    void build(vector<item>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size()) {
                values[x] = single(a[lx]);
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int i, item v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            values[x] = single(v);
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m) set(i, v, 2 * x + 1, lx, m);
        else set(i, v, 2 * x + 2, m, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }

    void set(int i, item v) {
        set(i, v, 0, 0, size);
    }

    item calc(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) return NEUTRAL_ELEMENT;
        if (lx >= l && rx <= r) return values[x];
        int m = (lx + rx) / 2;
        item s1 = calc(l, r, 2 * x + 1, lx, m);
        item s2 = calc(l, r, 2 * x + 2, m, rx);
        return merge(s1, s2);
    }

    item calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
    int n; cin >> n;
    int q; cin >> q;

    segtree st;
    st.init(n);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    st.build(a);

     while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            int l = x - 1, r = y; 
            auto ans = st.calc(l, r);
            cout << ans.inv << '\n';
        } else {
            int idx = x - 1;
            int val = y; 
            st.set(idx, val);
        }
    }

    return 0;
}
