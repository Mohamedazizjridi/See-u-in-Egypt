// Fenweek tree
// We'll build a Fenwick Tree where:

// add(l, x) and add(r+1, -x) lets us apply +x to range [l, r].

// query(k) gives value at position k after all updates.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, q;
vector<ll> bit, a;

void add(int i, ll x) {
    for (; i <= n; i += i & -i) bit[i] += x;
}

ll query(int i) {
    ll res = 0;
    for (; i > 0; i -= i & -i) res += bit[i];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.resize(n + 1);
    bit.assign(n + 2, 0); // 1-based

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        // Set initial value in BIT
        add(i, a[i]);
        add(i + 1, -a[i]); // neutralize effect past i
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            add(l, u);
            add(r + 1, -u);
        } else {
            int k;
            cin >> k;
            cout << query(k) << '\n';
        }
    }
    return 0;
}
